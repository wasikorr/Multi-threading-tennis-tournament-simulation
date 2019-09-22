//
// Created by jakub on 22.09.2019.
//

#ifndef TABLE_TANNIS_CHAMP_SIMULATION_DRAWMANAGER_HPP
#define TABLE_TANNIS_CHAMP_SIMULATION_DRAWMANAGER_HPP

//#include "App.hpp"

class App;

class DrawManager
{
public:

    DrawManager();

    void initVisualisation();
    void drawPlayers(App *app);
    void drawJudgeStatus(App *app);
    void drawBallAmount(App *app);
    void drawSecondsToDeliver(App *app);
    void drawTables();
    void drawView();
    void drawJudgeCenter();
    void drawBallCenter();
    void drawDeliverCenter();
};

#endif //TABLE_TANNIS_CHAMP_SIMULATION_DRAWMANAGER_HPP
