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
void CheckX(const GameState &pState, int value[]){
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
                //if (value[i] == 2){value[i] = 10;}
                //if (value[i] == 3){value[i] = 100;}
                if (value[i] == 4){value[i] = 1000;}
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
                //if (value[i] == 2){value[i] = 10;}
                //if (value[i] == 3){value[i] = 100;}
                if (value[i] == 4){value[i] = 1000;}
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
            //if(value[0] == 2){value[0] = 10;}
            //if(value[0] == 11){value[0] = 100;}
            if(value[0] == 4){value[0] = 1000;}
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
            //if(value[0] == 2){value[0] = 10;}
            //if(value[0] == 3){value[0] = 100;}
            if(value[0] == 4){value[0] = 1000;}
        }
    }
}

//occupying 3 corners give bonus
void CheckSC(const GameState &pState, int value[0]){
    //int corners[4] = {0,3,12,15};
    value[0] = 0;
    if (pState.at(0) == 1 && pState.at(3) == 1 && pState.at(15) == 1){
        value[0] = 100;
    }
    if (pState.at(3) == 1 && pState.at(15) == 1 && pState.at(12) == 1){
        value[0] = 100;
    }
    if (pState.at(15) == 1 && pState.at(12) == 1 && pState.at(0) == 1){
        value[0] = 100;
    }
    if (pState.at(12) == 1 && pState.at(0) == 1 && pState.at(3) == 1){
        value[0] = 100;
    }
}

int evaluationFunc(const GameState &pState, uint8_t Player){
    int sum = 0;
    //ROWS
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(pState.at(i,j) == Player){
                sum++;
            }
        }
    }

    //COLS
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(pState.at(j,i) == Player){
                sum++;
            }
        }
    }
    
    //diag1
    int temp = 0;
    for(int i = 0; i < 4; i++){
        if(pState.at(i, temp) == Player){
            sum++;
        }
        temp++;
    }

    //diag2
    temp = 3;
    for(int i = 0; i < 4; i++){
        if(pState.at(i, temp) == Player){
            sum++;
        }
        temp--;
    }
    return sum;
}

///////////////////////////////////////////////////////////////////////
int minimax_val(const GameState &pState, uint8_t Player, int depth, int maxDepth){
    depth++; 
    std::vector<GameState> lNextStates;
    pState.findPossibleMoves(lNextStates); //THIS IS MU 
        
    // HEURESTICS FUNCTION
    /*
    int value_r[4];
    int value_c[4];
    int value_d1[1];
    int value_d2[1];
    int value_spec[1];
    CheckX(pState, value_r);
    CheckY(pState, value_c);
    CheckD1(pState, value_d1);
    CheckD2(pState, value_d2);
    CheckSC(pState, value_spec);

    int totalValue = 0;
    for(int i = 0; i < 4; i++){
        totalValue = totalValue + value_r[i] + value_c[i];
    }
    totalValue = totalValue + value_d1[0] + value_d2[0] + value_spec[0]; 
    */
    if (depth > maxDepth || pState.isEOG() ){ //4 is possible
        //std::cerr << "Total is " << totalValue << std::endl;
        if (pState.isXWin() == true){return 1000;}
        else if (pState.isOWin() == true){return -1000;}
        else if (pState.isDraw() == true){return 0;}
        else{return  evaluationFunc(pState, Player);}
    }


    //if(count == 2){
    //    return 0;
    //}    
    //Here we want to return +-1 or 0
    else{

        //std::cerr << "WE ARE HERE" << std::endl;
        if (Player == 1){ // CELL_X){ //mNextPlayer is private
            int size = lNextStates.size();
            //std::cerr << size << std::endl;
            int bestPossible = -std::numeric_limits<int>::max();//-INFINITY;
            for(int i = 0; i < size; ++i){ //20 instead of size
                int v = minimax_val(lNextStates[i], pState.getNextPlayer(), depth, maxDepth);
                bestPossible = std::max(v, bestPossible);
            }
            //std::cerr << "I AM HERE" << std::endl;
            return bestPossible;
        }
        else{
            int size = lNextStates.size();
            int bestPossible = std::numeric_limits<int>::max();//INFINITY;
            for(int i = 0; i < size; ++i){ //20 instead of size
                int v = minimax_val(lNextStates[i], pState.getNextPlayer(), depth, maxDepth);
                bestPossible = std::min(v, bestPossible);
            }
            //std::cerr << "NOW I AM B" << std::endl;
            return  bestPossible;
        }   
    }
}

GameState Player::play(const GameState &pState,const Deadline &pDue)
{
    std::vector<GameState> lNextStates;
    pState.findPossibleMoves(lNextStates); //THIS IS MU

    
    if (lNextStates.size() == 0) return GameState(pState, Move());
    
    //Initializer
    int choice = 0;
    int maxVal = 0;
    int temp = 0;
    if (pState.getNextPlayer() == 1){
        maxVal = 100000;
        temp = 100000;
    }
    int maxDepth = 0;
    if (lNextStates.size() > 10){maxDepth = 2;}
    else if (lNextStates.size() > 8){maxDepth = 3;}
    else {maxDepth = 18-lNextStates.size() ;}
    //std::cerr << maxDepth << std::endl; 
    for (unsigned i = 0; i < lNextStates.size(); ++i){
        temp = minimax_val(lNextStates[i], pState.getNextPlayer(), 0, maxDepth);
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
    
 }

/*namespace TICTACTOE*/ }
