//
// Created by jakub on 22.09.2019.
//

#include "Player.hpp"
#include <ncurses.h>

Player::Player()
{
    this->actualX = defaultX;
    this->actualY = defaultY;
}

Player::Player(int id)
{
    this->id = id;
    this->defaultX = 33;
    this->defaultY = id * 3 + 5;
    this->actualX = this->defaultX;
    this->actualY = this->defaultY;
    this->hasBreak = true;
    this->opponent = nullptr;
    this->playOnTableID = -1;
    this->isPlaying = false;
    this->ball = nullptr;
}

Player::~Player()
{
    delete this;
}

void Player::setDefaultXY(int defaultX, int defaultY)
{
    this->defaultX = defaultX;
    this->defaultY = defaultY;
}

void Player::setActualXY(int actualX, int actualY)
{
    this->actualX = actualX;
    this->actualY = actualY;
}
