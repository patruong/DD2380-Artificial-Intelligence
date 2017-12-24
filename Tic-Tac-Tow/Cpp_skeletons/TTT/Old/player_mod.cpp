#include "player.hpp"
#include <cstdlib>
#include <math.h>
#include <algorithm> // std::max
#include <limits> // std::numeric_limits<int>::max();
namespace TICTACTOE
{

// CHECK row-heurestics
int value_row[4];
int CheckX(const GameState &pState, int value[]){
    int k = 0;
    //int value[4] = {0,0,0,0};
    for(int i = 0; i < 4; i++){
        value[i] = 0;
        for(int j = 0; j < 4; j++){
            if (unsigned(pState.at(i,j)) == 2){
                k = k + 4 - j;
                value[i] = 0;
                break;
            }
            if (unsigned(pState.at(i,j)) == 1){
                value[i]++;
                k++; //HERE WE CHOOSE WHICH X AND O TO SKIP AND RUN MINIMAX ON ONLY THESE.
                if (value[i] == 2){value[i] = 10;}
                if (value[i] == 11){value[i] = 100;}
                if (value[i] == 101){value[i] = 1000;}
            }
        }
    }
    
}

// CHECK col-heurestics
int value_col[4];
void CheckY(const GameState &pState, int value[]){
    int k = 0;
    //int value[4] = {0,0,0,0};
    for(int i = 0; i < 4; i++){
        value[i] = 0;
        for(int j = 0; j < 4; j++){
            if (unsigned(pState.at(j,i)) == 2){
                k = k + 4 - j;
                value[i] = 0;
                break;
            }
            if (unsigned(pState.at(j,i)) == 1){
                value[i]++;
                k++; //HERE WE CHOOSE WHICH X AND O TO SKIP AND RUN MINIMAX ON ONLY THESE.
                if (value[i] == 2){value[i] = 10;}
                if (value[i] == 11){value[i] = 100;}
                if (value[i] == 101){value[i] = 1000;}
            }
        }
    }
}

// CHECK special case diagonal 1
int diag1;
void CheckD1(const GameState &pState, int value[]){
    int diag[4] = {0,5,10,15};
    value[0] = 0;
    for (int i = 0; i < 4; ++i){
        if (unsigned(pState.at(diag[i])) == 2){
            value[0] = 0;
            break;
        }
        if (unsigned(pState.at(diag[i])) == 1){
            value[0]++;
            if(value[0] == 2){value[0] = 10;}
            if(value[0] == 11){value[0] = 100;}
            if(value[0] == 101){value[0] = 1000;}
        }
    }
}

// CHECK special case diagonal 2
int diag2;
void CheckD2(const GameState &pState, int value[0]){
    int diag[4] = {3,6,9,12};
    value[0] = 0;
    for (int i = 0; i < 4; ++i){
        if (unsigned(pState.at(diag[i])) == 2){
            value[0] = 0;
            break;
        }
        if (unsigned(pState.at(diag[i])) == 1){
            value[0]++;
            if(value[0] == 2){value[0] = 10;}
            if(value[0] == 11){value[0] = 100;}
            if(value[0] == 101){value[0] = 1000;}
        }
    }
}
/*
int minimax(const GameState &pState, uint8_t Player, int count){
    count++;
    std::vector<GameState> lNextStates;
    pState.findPossibleMoves(lNextStates);

     //UTILITY FUNCTION
    if(lNextStates.size() == 0){
        //std::cerr << "I've returned a State" << std::endl;
        if (pState.isXWin() == true){
            //std::cerr << "X win return" << std::endl;
            return 10000;}
        if (pState.isOWin() == true){
            //std::cerr << "Y win return" << std::endl;
            return -10000;} // Find how to do this?  
        if (pState.isDraw() == true){
            //std::cerr << "DRAW return" << std::endl;
            return 0;}//GameState(pState, Move()); 
    }
    
    // HEURESTICS FUNCTION
    int value_r[4];
    int value_c[4];
    int value_d1[1];
    int value_d2[1];
    CheckX(pState, value_r);
    CheckY(pState, value_c);
    CheckD1(pState, value_d1);
    CheckD2(pState, value_d2);

    int totalValue = 0;
    for(int i = 0; i < 4; i++){
        totalValue = totalValue + value_r[i] + value_c[i];
    }
    totalValue = totalValue + value_d1[0] + value_d2[0]; 
    
    if (count == 3){ //4 is possible
        //std::cerr << "Total is " << totalValue << std::endl;
        return totalValue;
    }
    else{
        if (Player == 1){
            int bestPossible = -100000;
            for (int i = 0; i < lNextStates.size(); ++i){
                int v = minimax(lNextStates[i], getNextPlayer(), count);

            }
        }
    }

}*/

GameState Player::play(const GameState &pState,const Deadline &pDue)
{
    std::vector<GameState> lNextStates;
    pState.findPossibleMoves(lNextStates);

    if (lNextStates.size() == 0) return GameState(pState, Move());

    /*
     * Here you should write your clever algorithms to get the best next move, ie the best
     * next state. This skeleton returns a random move instead.
     */
    
    std::cerr << unsigned(pState.getNextPlayer()) << std::endl;
    return lNextStates[rand() % lNextStates.size()];
}

/*namespace TICTACTOE*/ }
