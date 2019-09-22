//
// Created by jakub on 22.09.2019.
//

#include <curses.h>
#include <string>

#include "DrawManager.hpp"
#include "App.hpp"

DrawManager::DrawManager() {}

void DrawManager::initVisualisation()
{
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
void DrawManager::drawView()
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
void DrawManager::drawTables()
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
void DrawManager::drawBallCenter()
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
void DrawManager::drawJudgeCenter()
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
void DrawManager::drawDeliverCenter()
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
void DrawManager::drawBallAmount(App *app)
{
    std::string str = to_string(app->getAmountOfFreeBalls());
    const char *temp = str.c_str();
    mvprintw(4, 117, temp);
}
void DrawManager::drawSecondsToDeliver(App *app)
{
    string str = to_string(app->secondsToDeliver);
    const char *temp = str.c_str();
    if (app->secondsToDeliver == 0)
    {
        attron(COLOR_PAIR(3));
        mvprintw(4, 126, "++++");
        attroff(COLOR_PAIR(4));
    }
    else
        mvprintw(4, 126, temp);
}
void DrawManager::drawPlayers(App *app)
{
    for (auto &player : app->players)
    {
        string str = to_string(player->id);
        const char *temp = str.c_str();
        mvprintw(player->actualX, player->actualY, temp);
    }
}
void DrawManager::drawJudgeStatus(App *app)
{
    if (app->judge->isOnBrake == true)
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

