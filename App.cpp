//
// Created by jakub on 22.09.2019.
//

#include <ncurses.h>
#include <string>
#include <pthread.h>
#include <iostream>

#include "App.hpp"

App::App()
{
    judge = new Judge();

    for (int i = 0; i < 10; i++)
    {
        tables.push_back(new Table(i));
    }

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
void App::correctQueuePositions()
{
    for (auto &player : queue)
    {
        player->actualX = player->actualX - 2;
    }
}
