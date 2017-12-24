#include "player.hpp"
#include <cstdlib>
#include <algorithm> //std::max()
namespace TICTACTOE
{
int eval(const GameState &pState){
    int value_row[4] = {0,0,0,0};
    int value_col[4] = {0,0,0,0};
    int value_diag1[1] = {0};
    int value_diag2[1] = {0};
    int diag1[4] = {0,5,10,15};
    int diag2[4] = {3,6,9,12};
    for (int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if (unsigned(pState.at(i,j)) == 2){
                value_row[i] = 0;
                break;
            }
            if (unsigned(pState.at(i,j)) == 1){
                value_row[i]++;
                if (value_row[i] == 4){value_row[i] = 100;}
            }
        }    
    }
    
    for (int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if (unsigned(pState.at(j,i)) == 2){
                value_col[i] = 0;
                break;
            }
            if (unsigned(pState.at(j,i)) == 1){
                value_col[i]++;
                if(value_col[i] == 4){value_row[i] = 100;}
            }
        }
    }

    for (int i = 0; i < 4; i++){
        if (unsigned(pState.at(diag1[i])) == 2){
            value_diag1[0] = 0;
            break;
        }
        if (unsigned(pState.at(diag1[i])) == 1){
            value_diag1[0]++;
            if(value_diag1[0] == 4){value_diag1[0] = 100;}
        }
    }

    for (int i = 0; i < 4; i++){
        if (unsigned(pState.at(diag2[i])) == 2){
            value_diag2[0] = 0;
            break;
        }
        if (unsigned(pState.at(diag2[i])) == 1){
            value_diag2[0]++;
            if(value_diag2[0] == 4){value_diag2[0] = 100;}
        }
    }

    int evaluation_value = 0;
    for (int i = 0; i < 4; i++){
        evaluation_value = evaluation_value + value_row[i] + value_col[i];
    }
    evaluation_value = evaluation_value + value_diag1[0] + value_diag2[0];
    return evaluation_value;

}
int minimax(const GameState &pState,int depth){
    std::vector<GameState> lNextStates;
    pState.findPossibleMoves(lNextStates);
     
    if(lNextStates.size() == 0){
        int util = eval(pState);
        return util;
    }
    
    if(depth == 0){
        int util = eval(pState);
        return util;
    }
    else{
        if(pState.getNextPlayer() == 2){
            int bestPossible = -1000000;
            for (unsigned i = 0; i < lNextStates.size(); i++){
                int v = minimax(lNextStates[i], depth-1);
                bestPossible = std::max(bestPossible, v);
            }
            return bestPossible;
        }
        else{
            int bestPossible = 1000000;
            for (unsigned i = 0; i < lNextStates.size(); i++){
                int v = minimax(lNextStates[i], depth-1);
                bestPossible = std::min(bestPossible, v);
            }
            return bestPossible;
        }
    }
}

GameState Player::play(const GameState &pState,const Deadline &pDue)
{
    std::vector<GameState> lNextStates;
    pState.findPossibleMoves(lNextStates);

    if (lNextStates.size() == 0) return GameState(pState, Move());
    
    int choice = 0;
    int temp = 0;
    int val = 0;
    if (pState.getNextPlayer() == 1){
        val = 1000;
        temp = 1000;
    }
    for (unsigned i = 0; i < lNextStates.size(); ++i){
        if (lNextStates.size() > 13){temp = minimax(lNextStates[i],2);}
        else if(lNextStates.size() > 10){temp = minimax(lNextStates[i],3);}
        else if(lNextStates.size() > 8){temp = minimax(lNextStates[i],4);}
        else{temp = minimax(lNextStates[i],5);}
        if(pState.getNextPlayer() == 2){
            if(temp > val){
                val = temp;
                choice = i;
            }
        }
        else{
            if(temp < val){
                val = temp;
                choice = i;
            }
        }
    }
    
    return lNextStates[choice];
    /*
     * Here you should write your clever algorithms to get the best next move, ie the best
     * next state. This skeleton returns a random move instead.
     */
    //return lNextStates[rand() % lNextStates.size()];
}

/*namespace TICTACTOE*/ }
