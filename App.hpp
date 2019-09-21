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

using namespace std;

class App
{
public:
    bool ready;
    //TEST
    mutex mutexPlayers[30];
    condition_variable ifVarPlayers[30];

    //obiekty dla watkow
    // Deliverer *deliverer;
    vector<Player *> players;
    Judge *judge;

    //obiekty dla zasobow
    vector<Ball *> balls;
    vector<Table *> tables;

    //mutex dla stolow
    mutex mutexTables;
    condition_variable ifVarTables;

    //mutex dla pilek
    mutex mutexBalls;
    condition_variable ifVarBalls;

    //kolejka
    mutex mutexForQueue;
    vector<Player *> queue;

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
    bool isPlayerInQueue(Player *player);

    int secondsToDeliver;

    //wizualizacja
    void basicVisualisation();
    void drawPlayers();
    void drawJudgeStatus();
    void drawBallAmount();
    void drawSecondsToDeliver();

    //helpers dla wizualizacji
    void initVisualisation();
    void drawTables();
    void drawView();
    void drawJudgeCenter();
    void drawBallCenter();
    void drawDeliverCenter();

    void drawTableSeats();
    void drawTableSeats2();
};

#endif //TABLE_TANNIS_CHAMP_SIMULATION_APP_HPP
