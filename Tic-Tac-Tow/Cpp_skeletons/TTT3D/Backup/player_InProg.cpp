#include "player.hpp"
#include <cstdlib>
#include <math.h>
#include <algorithm> // std::max
#include <limits> // std::numeric_limits<int>::max()

namespace TICTACTOE3D
{


int evalFunc(const GameState &pState, uint8_t Player){
    int sum = 0;
    
    
    int X[76];
    int O[76];

    for(i = 0; i < 76; i++){
        X[i] = 0;
        O[i] = 0;
    }

    int WinRows[76][4] = {
        {0,5,10,15},//1 (1)
        {3,6,9,12},//2

        {3,23,43,63},//3 (2)
        {15,27,39,51},//4

        {48,53,58,63},//5 (3)
        {60,57,54,51},//6
        
        {0,20,40,60},//7 (4)
        {12,24,36,48},//8

        {10,17,34,51},//9 (5)
        {3,18,33,48},//10

        {12,29,46,63},//11 (6)
        {15,30,45,60}//12
    };
    
    for(int i = 0; i < 12; i++){
        for(int j = 0; j < 4; j++){
            if(pState.at(diag[i][j]) == 2){
                D[i] = 0;
                break;
            }
            if(pState.at(diag[i][j]) == 1){
                D[i]++;
                
                if(D[i] == 2){D[i] = 10;}
                else if(D[i] == 11){D[i] = 100;}
                else if(D[i] == 101){D[i] = 1000;}
            }

        }
    } 
    
   
    //CORNER VALUES
    int cornerVals[8] = {0,3,12,15,48,51,60,63};
    int corn = 0;
    for(int i = 0; i < 8; i++){
        if(pState.at(cornerVals[i]) == 1){
            corn += 2;
        }
    }
    
    // SUMMATION
    sum = LR + COLS + ROWS + corn;
    for(int i = 0; i < 12; i++){
        sum += D[i];
    }
    for(int i = 0; i < 4; i++){
        sum += MD[i];
    }
    return sumi;

}
int minimax_val(const GameState &pState, uint8_t Player, int depth, int maxDepth, int alpha, int beta){
    depth++;
    std::vector<GameState> lNextStates;
    pState.findPossibleMoves(lNextStates);
    int v;

    if (depth > maxDepth || pState.isEOG() ) {
        if(pState.isXWin() == true){return 10000;}
        else if (pState.isOWin() == true){return - 10000;}
        else if (pState.isDraw() == true){return 0;}
        else{return evalFunc(pState,Player);} //{return 0;}
    }
    else{
        if(Player == 1){
            int size = lNextStates.size();
            /*IMPLEMENT SORTING*/
            

            v = std::numeric_limits<int>::min();
            for(int i = 0; i < size; ++i){
                v = std::max(v, minimax_val(lNextStates[i], pState.getNextPlayer(), depth, maxDepth, alpha, beta));
                alpha = std::max(v, alpha);
                if (beta < alpha || beta == alpha){
                    break;
                }
            }
            //return bestPossible;
        }
        else{
            int size = lNextStates.size();
            /*IMPLEMENT SORTING*/

            v = std::numeric_limits<int>::max();
            for(int i = 0; i < size; ++i){
                v = std::min(v, minimax_val(lNextStates[i], pState.getNextPlayer(), depth, maxDepth, alpha, beta));
                beta = std::min(v, beta);
                if (beta < alpha || beta == alpha){
                    break;
                }
            }
            
            //return bestPossible;
        }
        return v;
    }
}


GameState Player::play(const GameState &pState,const Deadline &pDue)
{
    std::vector<GameState> lNextStates;
    pState.findPossibleMoves(lNextStates);

    if (lNextStates.size() == 0) return GameState(pState, Move());

    /*
     * Here you should write your clever algorithms to get the best next move, ie the best
     * next state. This skeleton returns a random move instead.
     */
    
    /*IMPLEMENT SORTING*/
    //If next player is 2 --> we are player 1
    /*
    int heurestics = 0;
    int highest_lowest = 0;
    if(pState.getNextPlayer() == 2){
        for(int i = 0; i < lNextStates.size(); ++i){
             if(evalFunc(lNextStates[i],1) > heurestics){
                heurestics = evalFunc(lNextStates[i],1);
                highest_lowest = i;
             }
        }
    }
    else{
        for(int i = 0; i < lNextStates.size(); ++i){
            if(evalFunc(lNextStates[i],2) < heurestics){
                heurestics = evalFunc(lNextStates[i],2);
                highest_lowest = i;
            }
        }
    }
    */
    int choice = 0;
    int maxVal = 0;
    int temp = 0;
    if (pState.getNextPlayer() == 1){
        maxVal = 100000;
        temp = 100000;
    }
    int maxDepth = 2;
    if (lNextStates.size() < 15){maxDepth = 5;}
    else if (lNextStates.size() < 20){maxDepth = 4;}
    else if(lNextStates.size() < 30){maxDepth = 3;}
    //else {maxDepth = 66-lNextStates.size();}
    std::cerr << lNextStates.size() << std::endl;
    for (unsigned i = 0; i < lNextStates.size(); ++i){
        temp = minimax_val(lNextStates[i], pState.getNextPlayer(), 0, maxDepth,  std::numeric_limits<int>::min(),  std::numeric_limits<int>::max());
        if(pState.getNextPlayer() == 2){
            if(temp > maxVal){
                maxVal = temp;
                choice = i;
            }
        }
        if(pState.getNextPlayer() == 1){
            if(temp > maxVal){
                maxVal = temp;
                choice = i;
            }
        }
    }
    return lNextStates[choice];
    //return lNextStates[rand() % lNextStates.size()];
}

/*namespace TICTACTOE3D*/ }
