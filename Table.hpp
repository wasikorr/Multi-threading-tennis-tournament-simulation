//
// Created by jakub on 22.09.2019.
//

#ifndef TABLE_TANNIS_CHAMP_SIMULATION_TABLE_HPP
#define TABLE_TANNIS_CHAMP_SIMULATION_TABLE_HPP

class Table
{
public:
    int id;
    bool status;
    int playerOneX;
    int playerOneY;
    int playerTwoX;
    int playerTwoY;

    Table();
    Table(int id);
};

#endif //TABLE_TANNIS_CHAMP_SIMULATION_TABLE_HPP
