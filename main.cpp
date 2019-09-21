//
// Created by jakub on 22.09.2019.
//

#include <iostream>
#include <ncurses.h>
#include <random>
#include <unistd.h>
#include <algorithm>
#include <thread>
#include <chrono>

#include "App.hpp"

using namespace std;

bool ready;
char quit;

void runThreads(App *app);
void player_func(App *app, Player *player);
void judge_func(App *app);
void draw_func(App *app);
void deliver_func(App *app);

int main()
{
    srand(time(NULL));
    ready = true;
    App *app = new App();
    app->initVisualisation();
    runThreads(app);
    getchar();
    ready = false;
    endwin();
    return 0;
}

void runThreads(App *app)
{
    app->ready == true;
    vector<thread> vecOfPlayersThreads;

    //watki zawodnikow
    for (int i = 0; i < 30; i++)
    {
        thread t1(player_func, app, app->players.at(i));
        vecOfPlayersThreads.push_back(move(t1));
    }

    thread judgeT(judge_func, app);
    thread drawT(draw_func, app);
    thread deliverT(deliver_func, app);

    do
    {
        quit = wgetch(stdscr);
    } while (quit != 'q');
    ready = false;
    deliverT.join();
    drawT.join();
    judgeT.join();
    for (int i = 0; i < 30; i++)
    {
        vecOfPlayersThreads.at(i).join();
    }
}

void draw_func(App *app)
{
    clear();
    int counter = 0;
    while (ready == true)
    {
        erase();
        string str = to_string(counter);
        const char *temp = str.c_str();
        mvprintw(1, 1, temp);
        counter++;

        //rysowanie statyczne - bez zmian
        app->drawView();
        app->drawTables();
        app->drawJudgeCenter();
        app->drawBallCenter();
        app->drawDeliverCenter();

        //rysowanie dynamiczne
        app->drawPlayers();
        app->drawJudgeStatus();
        app->drawBallAmount();
        app->drawSecondsToDeliver();

        refresh();
        // usleep(300);
        this_thread::sleep_for(chrono::milliseconds(200));
    }
}

void player_func(App *app, Player *player)
{
    while (ready == true)
    {
        player->hasBreak = false;

        //ustaw sie do kolejki
        {
            string str = to_string(player->id);
            const char *temp = str.c_str();
            unique_lock<mutex> Mqueue(app->judge->mutexForQueue);
            app->queue.push_back(player);
            player->setActualXY(app->getEndOfQueueX(), app->getQueueY());
            app->judge->ifVarForQueue.notify_one();
        }

        //CZEKAJ - dopoki jestes w kolejnce
        {
            unique_lock<mutex> Mplayer(player->mutexPlayer);
            // while (app->isPlayerInQueue(player))
            while (player->playOnTableID == -1)
                player->ifVarPlayer.wait(Mplayer);
        }

        player->isPlaying = true;
        int matchTime = rand() % 10000 + 1;
        this_thread::sleep_for(chrono::milliseconds(matchTime));
        player->isPlaying = false;
        player->opponent->ifVarOpponent.notify_one();
        {
            unique_lock<mutex> Mopponent(player->mutexOpponent);
            while (player->opponent->isPlaying == true)
                player->ifVarOpponent.wait(Mopponent);
        }

        if (player->id >= player->opponent->id)
        {
            app->tables.at(player->playOnTableID)->status = true;
            app->ifVarTables.notify_one();

            player->ball->durability--;
            if (player->ball->durability == 0)
                app->balls.erase(std::remove(app->balls.begin(), app->balls.end(), player->ball), app->balls.end());
            else
            {
                player->ball->inUse = false;
                app->ifVarBalls.notify_one();
            }
        }

        player->playOnTableID = -1;

        // //po meczu

        player->actualX = player->defaultX;
        player->actualY = player->defaultY;
        player->hasBreak = true;
        int breakTime = rand() % 5 + 1;
        this_thread::sleep_for(chrono::seconds(breakTime));
    }
}

void judge_func(App *app)
{
    while (ready == true)
    {
        app->judge->isOnBrake = false;
        Player *playerOne = nullptr;
        Player *playerTwo = nullptr;

        //po 20 zawodnikach przerwa
        for (int i = 0; i < 20; i++)
        {

            unique_lock<mutex> Mqueue(app->judge->mutexForQueue);
            while (app->queue.size() < 2)
                app->judge->ifVarForQueue.wait(Mqueue);

            //wczytanie pierwszych 2 zawodnikow z kolejki do wskaznikow i usuniecie ich z listy
            playerOne = app->queue.front();
            app->queue.erase(app->queue.begin());
            playerTwo = app->queue.front();
            app->queue.erase(app->queue.begin());

            {
                unique_lock<mutex> Mtables(app->mutexTables);
                while (app->getAmountOfFreeTables() == 0)
                    app->ifVarTables.wait(Mtables);
            }

            {
                unique_lock<mutex> Mballs(app->mutexBalls);
                while (app->getAmountOfFreeBalls() == 0)
                    app->ifVarBalls.wait(Mballs);
            }

            Table *table;
            Ball *ball;
            table = app->findFreeTable();
            ball = app->findFreeBall();
            ball->inUse = true;
            table->status = false;
            playerOne->actualX = table->playerOneX;
            playerOne->actualY = table->playerOneY;
            playerTwo->actualX = table->playerTwoX;
            playerTwo->actualY = table->playerTwoY;

            //ustawienie wartosci zawodnikow, tak aby mogli symulowac mecz i zwolnic stol
            playerOne->opponent = playerTwo;
            playerTwo->opponent = playerOne;
            playerOne->playOnTableID = playerTwo->playOnTableID = table->id;
            playerOne->ball = playerTwo->ball = ball;

            //poprawienie aktualnej pozycji zawodnikow
            app->correctQueuePositions();

            //sygnal
            playerOne->ifVarPlayer.notify_one();
            playerTwo->ifVarPlayer.notify_one();

            this_thread::sleep_for(chrono::seconds(1));
        }
        app->judge->isOnBrake = true;
        this_thread::sleep_for(chrono::seconds(5));
    }
}

void deliver_func(App *app)
{
    while (ready == true)
    {
        app->secondsToDeliver = 120;
        while (app->secondsToDeliver > 0)
        {
            this_thread::sleep_for(chrono::seconds(1));
            app->secondsToDeliver--;
        }

        vector<Ball *> tempBalls;
        for (int i = 0; i < 15; i++)
        {
            tempBalls.push_back(new Ball());
        }
        this_thread::sleep_for(chrono::seconds(2));
        app->balls = tempBalls;
        app->ifVarBalls.notify_one();
    }
}