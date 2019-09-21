//
// Created by jakub on 22.09.2019.
//

#include "Table.hpp"
#include <ncurses.h>

Table::Table()
{
}

Table::Table(int id)
{
    int row = 0, column = 0;

    this->id = id;
    if (id < 5)
    {
        row = 3;
        column = id * 20 + 10;
    }
    else
    {
        row = 18;
        column = (id - 5) * 20 + 10;
    }

    this->playerOneX = row;
    this->playerOneY = column;
    this->playerTwoX = row + 9;
    this->playerTwoY = column;
    this->status = true;
}

