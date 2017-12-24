#include "player.hpp"
#include <cstdlib>
#include <math.h>
#include <algorithm> // std::max
#include <limits> // std::numeric_limits<int>::max();
namespace TICTACTOE
{

const int Possible_wins[10][4] = {
    {0,1,2,3},
    {4,5,6,7},
    {8,9,10,11},
    {12,13,14,15},
    {0,4,8,11},
    {1,5,9,13},
    {2,6,10,14},
    {3,7,11,15},
    {0,5,10,15},
    {3,6,9,11}
};

/////////////HEURESTICS FOR X/////////////////////////////////////
// CHECK row-heurestics
int value_row[4];
int CheckX(const GameState &pState, int value[]){
    int k = 0;
    //int value[4] = {0,0,0,0};
    for(int i = 0; i < 4; i++){
        value[i] = 0;
        for(int j = 0; j < 4; j++){
            /*
            if (unsigned(pState.at(i,j)) == 2){
                k = k + 4 - j;
                value[i] = 0;
                break;
            }*/
            if (unsigned(pState.at(i,j)) == 1){
                value[i]++;
                k++; //HERE WE CHOOSE WHICH X AND O TO SKIP AND RUN MINIMAX ON ONLY THESE.
                if (value[i] == 2){value[i] = 10;}
                if (value[i] == 11){value[i] = 50;}
                if (value[i] == 51){value[i] = 1000;}
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
            /*if (unsigned(pState.at(j,i)) == 2){
                k = k + 4 - j;
                value[i] = 0;
                break;
            }*/
            if (unsigned(pState.at(j,i)) == 1){
                value[i]++;
                k++; //HERE WE CHOOSE WHICH X AND O TO SKIP AND RUN MINIMAX ON ONLY THESE.
                if (value[i] == 2){value[i] = 10;}
                if (value[i] == 11){value[i] = 50;}
                if (value[i] == 51){value[i] = 1000;}
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
        /*if (unsigned(pState.at(diag[i])) == 2){
            value[0] = 0;
            break;
        }*/
        if (unsigned(pState.at(diag[i])) == 1){
            value[0]++;
            if(value[0] == 2){value[0] = 10;}
            if(value[0] == 11){value[0] = 50;}
            if(value[0] == 51){value[0] = 1000;}
        }
    }
}

// CHECK special case diagonal 2
int diag2;
void CheckD2(const GameState &pState, int value[0]){
    int diag[4] = {3,6,9,12};
    value[0] = 0;
    for (int i = 0; i < 4; ++i){
        /*if (unsigned(pState.at(diag[i])) == 2){
            value[0] = 0;
            break;
        }*/
        if (unsigned(pState.at(diag[i])) == 1){
            value[0]++;
            if(value[0] == 2){value[0] = 10;}
            if(value[0] == 11){value[0] = 50;}
            if(value[0] == 51){value[0] = 1000;}
        }
    }
}

//occupying 3 corners give bonus
void CheckSC(const GameState &pState, int value[0]){
    int corners[4] = {0,3,12,15};
    value[0] = 0;
    
    if (pState.at(0) == 1 && pState.at(3) == 1 && pState.at(15) == 1){
        value[0] = 50;
    }
    if (pState.at(3) == 1 && pState.at(15) == 1 && pState.at(12) == 1){
        value[0] = 50;
    }
    if (pState.at(15) == 1 && pState.at(12) == 1 && pState.at(0) == 1){
        value[0] = 50;
    }
    if (pState.at(12) == 1 && pState.at(0) == 1 && pState.at(3) == 1){
        value[0] = 50;
    }
    //if (pState.at(0) == 1 && pState.at(3) == 1 && pState.at(12) == 1 && pState.at(15) == 1){
    //    value[0] = 500;
    //}
    /*
    for (int i = 0; i < 4; ++i){
        if (unsigned(pState.at(corners[i]) == 1)){
            value[0]++;
        }
    }
    */
}

void CheckSC_mid(const GameState &pState, int value[0]){
    int corners[4] = {5,6,9,10};
    value[0] = 0;
    
    if (pState.at(5) == 1 && pState.at(6) == 1 && pState.at(10) == 1){
        value[0] = 50;
    }
    if (pState.at(6) == 1 && pState.at(10) == 1 && pState.at(9) == 1){
        value[0] = 50;
    }
    if (pState.at(10) == 1 && pState.at(9) == 1 && pState.at(5) == 1){
        value[0] = 50;
    }
    if (pState.at(9) == 1 && pState.at(5) == 1 && pState.at(6) == 1){
        value[0] = 50;
    }
    //if (pState.at(5) == 1 && pState.at(6) == 1 && pState.at(10) == 1 && pState.at(9)){
    //    value[0] = 500;
    //}
    /*
    for (int i = 0; i < 4; ++i){
        if (unsigned(pState.at(corners[i]) == 1)){
            value[0]++;
        }
    }
    */

}
/*RE-write the end heurestics*/


///////////////////////////////////////////////////////////////////////
int minimax_val(const GameState &pState, uint8_t Player, int count){
    //count++; 
    std::vector<GameState> lNextStates;
    pState.findPossibleMoves(lNextStates); //THIS IS MU
    
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
    int value_spec[1];
    int value_spec2[1];
    CheckX(pState, value_r);
    CheckY(pState, value_c);
    CheckD1(pState, value_d1);
    CheckD2(pState, value_d2);
    CheckSC(pState, value_spec);
    CheckSC_mid(pState, value_spec2);

    int totalValue = 0;
    for(int i = 0; i < 4; i++){
        totalValue = totalValue + value_r[i] + value_c[i];
    }
    totalValue = totalValue + value_d1[0] + value_d2[0] + value_spec[0] + value_spec2[0]; 
     
    if (count ==  0){// && lNextStates.size() > 4){ //4 is possible
           return totalValue;
    }
    else{
        if (Player == 1){ // CELL_X){ //mNextPlayer is private
            int size = lNextStates.size();

            int bestPossible = -std::numeric_limits<int>::max();//-INFINITY;
            for(int i = 0; i < size; ++i){ //20 instead of size
                int v = minimax_val(lNextStates[i], pState.getNextPlayer(), count-1);
                bestPossible = std::max(v, bestPossible);
            }
            return bestPossible;
        }
        else{
            int size = lNextStates.size();
            int bestPossible = std::numeric_limits<int>::max();//INFINITY;
            for(int i = 0; i < size; ++i){ 
                int v = minimax_val(lNextStates[i], pState.getNextPlayer(), count-1);
                bestPossible = std::min(v, bestPossible);
            }

            return  bestPossible;
        }   
    }
}

GameState Player::play(const GameState &pState,const Deadline &pDue)
{
    std::vector<GameState> lNextStates;
    pState.findPossibleMoves(lNextStates); //THIS IS MU

    
    if (lNextStates.size() == 0) return GameState(pState, Move());
    /*
     * Here you should write your clever algorithms to get the best next move, ie the best
     * next state. This skeleton returns a random move instead.
     */
    int choice = 0;
    int maxVal = 0;
    int temp = 0;
    if (pState.getNextPlayer() == 1){
        maxVal = 100000;
        temp = 100000;
    } 
    
    for (int i = 0; i < lNextStates.size(); ++i){
        temp = minimax_val(lNextStates[i], pState.getNextPlayer(), 2);
        //std::cerr << "AT THE END NOW" << temp << std::endl;
        if (pState.getNextPlayer() == 2){
            if (temp > maxVal){
                maxVal = temp;
                choice = i;
            }
        }
        if (pState.getNextPlayer() == 1){
            if (temp < maxVal){
                maxVal = temp;
                choice = i;
            }
        }
    }
    return lNextStates[choice];
    
    //return lNextStates[rand() % lNextStates.size()];
}

/*namespace TICTACTOE*/ }
