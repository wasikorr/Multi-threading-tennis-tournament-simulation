//
// Created by jakub on 22.09.2019.
//

#ifndef TABLE_TANNIS_CHAMP_SIMULATION_PLAYER_HPP
#define TABLE_TANNIS_CHAMP_SIMULATION_PLAYER_HPP

#include <mutex>
#include <condition_variable>
#include "Ball.hpp"

class Player
{

public:
    int id;
    bool hasBreak;
    int defaultX;
    int defaultY;
    int actualX;
    int actualY;
    bool isPlaying;

    Player *opponent;
    int playOnTableID;

    Ball *ball;

    std::mutex mutexPlayer;
    std::condition_variable ifVarPlayer;

    std::mutex mutexOpponent;
    std::condition_variable ifVarOpponent;

    Player();
    Player(int id);
    ~Player();

    void setDefaultXY(int defaultX, int defaultY);
    void setActualXY(int actualX, int actualY);
};

#endif //TABLE_TANNIS_CHAMP_SIMULATION_PLAYER_HPP
