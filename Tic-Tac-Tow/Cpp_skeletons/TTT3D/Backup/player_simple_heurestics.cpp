#include "player.hpp"
#include <cstdlib>
#include <math.h>
#include <algorithm> // std::max
#include <limits> // std::numeric_limits<int>::max()

namespace TICTACTOE3D
{


int evalFunc(const GameState &pState, uint8_t Player){
    int sum = 0;
    
    // Layer Row(1st) - 16 winning rows
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            for(int k = 0; k < 4; k++){
               if(pState.at(i,j,k) == Player){
                   sum++;
               } 
            }
        }
    }

    // COLS (2nd) - 16 winning rows
    for(int i = 0; i < 4; i++){
        for(int k = 0; k < 4; k++){
            for(int j = 0; j < 4; j++){
                if(pState.at(i,j,k) == Player){
                    sum++;
                }
            }
        }
    }
    
    // ROWS (3rd) - 16 winning rows
    for(int j = 0; j < 4; j++){
        for(int k = 0; k < 4; k++){
            for(int i = 0; i < 4; i++){
                if(pState.at(i,j,k) == Player){
                    sum++;
                }
            }
        }
    }
     
    // DIAGONALS
    int diag[12][4] = {
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
            if(pState.at(diag[i][j]) == Player){
                sum++;
            }
        }
    } 
    
    // MAIN DIAGONALS
    int mdiag[4][4] = {
        {0,21,42,63},
        {3,22,41,60},
        {12,25,38,51},
        {15,26,37,48}
    };

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(pState.at(mdiag[i][j]) == Player){
                sum++;
            }
        }
    }
    
    return sum;

}
int minimax_val(const GameState &pState, uint8_t Player, int depth, int maxDepth, int alpha, int beta){
    depth++;
    std::vector<GameState> lNextStates;
    pState.findPossibleMoves(lNextStates);
    int v;

    if (depth > maxDepth || pState.isEOG() ) {
        if(pState.isXWin() == true){return 1000;}
        else if (pState.isOWin() == true){return 1000;}
        else if (pState.isDraw() == true){return 0;}
        else{return evalFunc(pState,Player);} //{return 0;}
    }
    else{
        if(Player == 1){
            int size = lNextStates.size();
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
