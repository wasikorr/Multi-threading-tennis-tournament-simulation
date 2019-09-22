//
// Created by jakub on 22.09.2019.
//

#ifndef TABLE_TANNIS_CHAMP_SIMULATION_APP_HPP
#define TABLE_TANNIS_CHAMP_SIMULATION_APP_HPP

#include <vector>

#include "Player.hpp"
#include "Judge.hpp"
#include "Table.hpp"
#include "Ball.hpp"
#include "DrawManager.hpp"

using namespace std;

class App
{
public:
    bool ready;
    int secondsToDeliver;

    DrawManager* drawManager;

    vector<Player *> players;
    vector<Ball *> balls;
    vector<Table *> tables;
    Judge *judge;
    vector<Player *> queue;

    mutex mutexTables;
    mutex mutexPlayers[30];
    mutex mutexBalls;
    mutex mutexForQueue;

    condition_variable ifVarTables;
    condition_variable ifVarPlayers[30];
    condition_variable ifVarBalls;

    App();

    //dla stolow
    int getAmountOfFreeTables();
    Table *findFreeTable();
    //dla pilek
    int getAmountOfFreeBalls();
    Ball *findFreeBall();
    //dla kolejki
    int getEndOfQueueX();
    int getQueueY();
    void correctQueuePositions();
};

#endif //TABLE_TANNIS_CHAMP_SIMULATION_APP_HPP
