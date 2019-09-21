//
// Created by jakub on 22.09.2019.
//

#ifndef TABLE_TANNIS_CHAMP_SIMULATION_JUDGE_HPP
#define TABLE_TANNIS_CHAMP_SIMULATION_JUDGE_HPP

#include "Player.hpp"
#include <vector>

class Judge
{
public:
    bool isOnBrake;


    std::mutex mutexForQueue;
    std::condition_variable ifVarForQueue;

    Judge();
};

#endif //TABLE_TANNIS_CHAMP_SIMULATION_JUDGE_HPP
