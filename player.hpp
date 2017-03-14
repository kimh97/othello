#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();

    Board *copy_board;
    Side p_side;
    Side o_side;

    Move *doMove(Move *opponentsMove, int msLeft);
    int comp_heuristic(Board *copy_board, int x, int y, Side p_side);
    int abs_heuristic(int x, int y);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
