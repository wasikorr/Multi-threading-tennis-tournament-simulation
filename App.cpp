//
// Created by jakub on 22.09.2019.
//

#include <ncurses.h>
#include <string>
#include <pthread.h>
#include <iostream>

#include "App.hpp"

using namespace std;

App::App()
{
    judge = new Judge();
    //deliverer = new Deliverer();

    //tworzenie stolow
    for (int i = 0; i < 10; i++)
    {
        tables.push_back(new Table(i));
    }

    //tworzenie zawodnikow
    for (int i = 0; i < 30; i++)
    {
        players.push_back(new Player(i));
    }

    for (int i = 0; i < 15; i++)
    {
        balls.push_back(new Ball());
    }

    queue.reserve(30);
}

//skladowe wizualizacji
void App::drawTables()
{
    for (int i = 0; i < 5; i++)
    {
        attron(COLOR_PAIR(5));
        mvprintw(4, i * 20 + 5, "-----------");
        mvprintw(11, i * 20 + 5, "-----------");
        for (int j = 5; j < 11; j++)
        {
            mvprintw(j, i * 20 + 5, "|");
            mvprintw(j, i * 20 + 15, "|");
        }
        attroff(COLOR_PAIR(5));

        mvprintw(7, i * 20 + 6, "_________");
    }

    //drugi rząd
    for (int i = 0; i < 5; i++)
    {
        attron(COLOR_PAIR(5));
        mvprintw(19, i * 20 + 5, "-----------");
        mvprintw(26, i * 20 + 5, "-----------");
        for (int j = 20; j < 26; j++)
        {
            mvprintw(j, i * 20 + 5, "|");
            mvprintw(j, i * 20 + 15, "|");
        }
        attroff(COLOR_PAIR(5));

        mvprintw(22, i * 20 + 6, "_________");
    }
}

void App::drawView()
{

    attron(COLOR_PAIR(1));
    mvprintw(0, 0, "-----------------------------------------------------------------------------------------------------");
    mvprintw(15, 0, "-----------------------------------------------------------------------------------------------------");
    mvprintw(30, 0, "-----------------------------------------------------------------------------------------------------");
    for (int i = 1; i < 30; i++)
    {
        mvprintw(i, 0, "|");
        mvprintw(i, 20, "|");
        mvprintw(i, 40, "|");
        mvprintw(i, 60, "|");
        mvprintw(i, 80, "|");
        mvprintw(i, 100, "|");
    }

    attroff(COLOR_PAIR(1));
}

void App::drawBallCenter()
{
    attron(COLOR_PAIR(5));
    mvprintw(1, 114, "--------");
    mvprintw(3, 114, "--------");
    mvprintw(5, 114, "--------");

    mvprintw(2, 114, "|");
    mvprintw(2, 121, "|");
    mvprintw(4, 114, "|");
    mvprintw(4, 121, "|");

    mvprintw(2, 115, "PILKI");

    attroff(COLOR_PAIR(5));
}

void App::drawBallAmount()
{
    string str = to_string(getAmountOfFreeBalls());
    const char *temp = str.c_str();
    mvprintw(4, 117, temp);
}

void App::initVisualisation()
{
    //inicjalizacja
    initscr();
    noecho(); //pressed characters do not print on the screen
    cbreak(); //pressed keys are immediately returned by getch() instead of waiting until new line is read
    keypad(stdscr, TRUE);
    curs_set(0);
    start_color();
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);
    init_pair(5, COLOR_WHITE, COLOR_BLACK);
}

void App::drawTableSeats()
{

    attron(COLOR_PAIR(4));
    //pierwszy rząd
    for (int i = 0; i < 5; i++)
    {
        int row = 3;
        int column = i * 20 + 10;
        mvprintw(row, column, "*");
        mvprintw(row + 9, column, "*");
    }

    //drugi rzad
    for (int i = 0; i < 5; i++)
    {
        int row = 18;
        int column = i * 20 + 10;
        mvprintw(row, column, "*");
        mvprintw(row + 9, column, "*");
    }

    attroff(COLOR_PAIR(4));
}

void App::drawJudgeCenter()
{

    attron(COLOR_PAIR(5));
    mvprintw(1, 105, "--------");
    mvprintw(3, 105, "--------");
    mvprintw(5, 105, "--------");

    mvprintw(2, 105, "|");
    mvprintw(2, 112, "|");
    mvprintw(4, 105, "|");
    mvprintw(4, 112, "|");

    mvprintw(4, 106, "SEDZIA");
    attroff(COLOR_PAIR(5));
}

void App::drawDeliverCenter()
{
    attron(COLOR_PAIR(5));
    mvprintw(1, 124, "--------");
    mvprintw(3, 124, "--------");
    mvprintw(5, 124, "--------");

    mvprintw(2, 124, "|");
    mvprintw(2, 131, "|");
    mvprintw(4, 124, "|");
    mvprintw(4, 131, "|");

    mvprintw(2, 125, "DOSTAW");

    attroff(COLOR_PAIR(5));
}

void App::drawSecondsToDeliver()
{
    string str = to_string(secondsToDeliver);
    const char *temp = str.c_str();
    if (secondsToDeliver == 0)
    {
        attron(COLOR_PAIR(3));
        mvprintw(4, 126, "++++");
        attroff(COLOR_PAIR(4));
    }
    else
        mvprintw(4, 126, temp);
}

int App::getEndOfQueueX()
{
    return queue.size() + 5;
}

int App::getQueueY()
{
    return 108;
}

int App::getAmountOfFreeTables()
{
    int result = 0;
    for (auto &table : tables)
    {
        if (table->status == true)
            result++;
    }

    return result;
}

int App::getAmountOfFreeBalls()
{
    int result = 0;
    for (auto &ball : balls)
    {
        if (ball->inUse == false)
            result++;
    }

    return result;
}

Table *App::findFreeTable()
{
    for (auto &table : tables)
    {
        if (table->status == true)
            return table;
    }
}

Ball *App::findFreeBall()
{
    for (auto &ball : balls)
    {
        if (ball->inUse == false)
            return ball;
    }
}

void App::drawPlayers()
{
    for (auto &player : players)
    {
        string str = to_string(player->id);
        const char *temp = str.c_str();
        mvprintw(player->actualX, player->actualY, temp);
    }
}

void App::drawJudgeStatus()
{
    if (judge->isOnBrake == true)
    {
        attron(COLOR_PAIR(4));
        mvprintw(2, 108, "--");
        attroff(COLOR_PAIR(4));
    }

    else
    {
        attron(COLOR_PAIR(3));
        mvprintw(2, 108, "++");
        attroff(COLOR_PAIR(3));
    }
}

void App::drawTableSeats2()
{
    for (auto &table : tables)
    {
        mvprintw(table->playerOneX, table->playerOneY, "#");
        mvprintw(table->playerTwoX, table->playerTwoY, "#");
    }
}

void App::correctQueuePositions()
{
    for (auto &player : queue)
    {
        player->actualX = player->actualX - 2;
    }
}

bool App::isPlayerInQueue(Player *player)
{
    for (auto &pl : players)
    {
        if (player == pl)
            return true;
    }
    return false;
}