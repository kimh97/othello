#include "player.hpp"

int heuristic[8][8] = {{100, -50, 50, 50, 50, 50, -50, 100},
                         {-50, -100, 0, 0, 0, 0, -100, -50},
                         {50, 0, 0, 0, 0, 0, 0, 50},
                         {50, 0, 0, 0, 0, 0, 0, 50},
                         {50, 0, 0, 0, 0, 0, 0, 50},
                         {50, 0, 0, 0, 0, 0, 0, 50},
                         {-50, -100, 0, 0, 0, 0, -100, -50},
                         {100, -50, 50, 50, 50, 50, -50, 100}};

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
    p_side = side;

    if (p_side == WHITE)
    {
        std::cerr << "AI is WHITE" << std::endl;
        o_side = BLACK;
    }
    else
    {
        std::cerr << "AI is BLACK" << std::endl;
        o_side = WHITE;
    }
    
    copy_board = new Board();

    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */
    
    vector<Move> myMoves;
    int heuristic1;
    int heuristic2;
    int heuristic;
    int prev_heuristic;

    if (opponentsMove != nullptr)
    {
        copy_board->doMove(opponentsMove, o_side);
    }

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Move testMove(i, j);

            if (copy_board->checkMove(&testMove, p_side))
            {
                myMoves.push_back(testMove);
            }
        }
    }

    if (myMoves.size() != 0)
    { 
        int save_x;
        int save_y;

        for (int i = 0 ; i < (int) myMoves.size(); i++)
            {
                prev_heuristic = heuristic;

                int x = myMoves[i].getX();
                int y = myMoves[i].getY();
                heuristic1 = comp_heuristic(copy_board, x, y, p_side);
                heuristic2 = abs_heuristic(x, y); 
            

                if (p_side == BLACK)
                {
                    heuristic = heuristic1 + heuristic2;
                    if (heuristic > prev_heuristic)
                    {
                        save_x = x;
                        save_y = y;
                    }
                } 
                else
                {
                    heuristic = heuristic1 - heuristic2;
                    if (heuristic < prev_heuristic)
                    {
                        save_x = x;
                        save_y = y;
                    }
                }

            }
        
        Move *makeMove = new Move(save_x, save_y);
        copy_board->doMove(makeMove, p_side);

        return makeMove;
    }
    else
        return nullptr;
   
}


int Player::comp_heuristic(Board *copy_board, int x, int y, Side p_side) {

    int heuristic;
       
    Board *testBoard = copy_board->copy();
       
    Move *t_move = new Move(x, y);
    testBoard->doMove(t_move, p_side);
    heuristic = testBoard->countBlack() - testBoard->countWhite();

    return heuristic;
}

int Player::abs_heuristic(int x, int y) {
    
    return heuristic[x][y];

}

        