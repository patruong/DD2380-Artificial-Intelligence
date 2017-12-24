#include "player.hpp"
#include <cstdlib>
#include <math.h>
#include <algorithm> // std::max
#include <limits> // std::numeric_limits<int>::max()

namespace TICTACTOE3D
{


int evalFunc(const GameState &pState){
    //int sum = 0;
    
    /*
    int X[76];
    int O[76];

    for(int i = 0; i < 76; i++){
        X[i] = 0;
        O[i] = 0;
    }*/

    int WinRows[76][4] = {
        //Rows
        {0,1,2,3},
        {4,5,6,7},
        {8,9,10,11},
        {12,13,14,15},

        {16,17,18,19},
        {20,21,22,23},
        {24,25,26,27},
        {28,29,30,31},

        {32,33,34,35},
        {36,37,38,39},
        {40,41,42,43},
        {44,45,46,47},

        {48,49,50,51},
        {52,53,54,55},
        {56,57,58,59},
        {60,61,62,63},
        //Cols
        {0,4,8,12},
        {1,5,9,13},
        {2,6,10,14},
        {3,7,11,15},

        {16,20,24,28},
        {17,21,25,29},
        {18,22,26,30},
        {19,23,27,31},

        {32,36,40,44},
        {33,37,41,45},
        {34,38,42,46},
        {35,39,43,47},

        {48,52,56,60},
        {49,53,57,61},
        {50,54,58,62},
        {51,55,59,63},
        //Depth
        {0,16,32,48},
        {1,17,33,49},
        {2,18,34,50},
        {3,19,35,51},

        {4,20,36,52},
        {5,21,37,53},
        {6,22,38,54},
        {7,23,39,55},

        {8,24,40,56},
        {9,25,41,57},
        {10,26,42,58},
        {11,27,43,59},

        {12,28,44,60},
        {13,29,45,61},
        {14,30,46,62},
        {15,31,47,63},
        //Diagonals
        {0,5,10,15},//1 (1)
        {3,6,9,12},//2
        {16,21,26,31},
        {28,25,22,19},
        {44,41,38,35},
        {32,37,42,47},
        {48,53,58,63},//5 (3)
        {60,57,54,51},//6
          
        {0,20,40,60},//7 (4)
        {12,24,36,48},//8
        {1,21,41,61},
        {13,25,37,49},
        {2,22,42,62},
        {14,26,38,50},
        {3,23,43,63},//3 (2)
        {15,27,39,51},//4
        

        {0,17,34,51},//9 (5)
        {3,18,33,48},//10
        {4,21,38,55},
        {7,22,37,52},
        {8,25,42,59},
        {11,26,41,56},
        {12,29,46,63},//11 (6)
        {15,30,45,60},//12
        
        
        //Main diagonals
        {0,21,42,63},
        {3,22,41,60},
        {12,25,38,51},
        {15,26,37,48}
    };

    /*
    for(int i = 0; i < 76; i++){
        for(int j = 0; j < 4; j++){
            if(pState.at(WinRows[i][j]) == 2){
                O[i]++;
            }
            if(pState.at(WinRows[i][j]) == 1){
                X[i]++;
            }
        }
    } */
    /*IMPLEMENT HEURESTICS ARRAY FOR SPECIAL CASES ALSO TO TEST*/ 
    
    //CORNER VALUES
    /*
    int cornerVals[8] = {0,3,12,15,48,51,60,63};
    int corn = 0;
    for(int i = 0; i < 8; i++){
        if(pState.at(cornerVals[i]) == 1){
            corn += 50;
        }
        if(pState.at(cornerVals[i]) == 2){
            corn -= 50;
        }
    }
    //MIDDLE VALUES
    int midVals[8] = {21,22,25,26,37,38,41,42};
    int mid = 0;
    for(int i = 0; i < 8; i++){
        if(pState.at(midVals[i]) == 1){
            mid += 50;
        }
        if(pState.at(midVals[i]) == 2){
            mid -= 50;
        }
    }*/
    /*
    int util = 0;

    util += corn;
    for(int i = 0; i < 76; i++){
        if(O[i] == 1){util -= 1;}
        else if(O[i] == 2){util -= 10;}
        else if(O[i] == 3){util -= 100;}
        else if(O[i] == 4){util -= 1000;}

        if(X[i] == 1){util += 1;}
        else if(X[i] == 2){util += 10;}
        else if(X[i] == 3){util += 100;}
        else if(X[i] == 4){util += 1000;}
    }*/
    int heur_Array[5][5] = {
        {0, -1, -10, -100, -1000},
        {1, 0, 0, 0, 0},
        {10, 0, 0, 0, 0},
        {100, 0, 0, 0, 0},
        {1000, 0, 0, 0, 0}
    };

    int util = 0;
    int players;
    int others;
    for(int i = 0; i < 76; i++){
        players = others = 0;
        for(int j = 0; j < 4; j++){
            if(pState.at(WinRows[i][j]) == 1){
                players++;
            }
            else if(pState.at(WinRows[i][j]) == 2){
                others++;
            }
        }
        util += heur_Array[players][others];
    }
    //util += corn+mid;
    //int specials[8] = {
    //    {0,3,12,15,48,51,60,63}
    //};
    /*
    int sixPos = 6;
    if (pState.at(0) == 1){util+=sixPos;}
    if (pState.at(3) == 1){util+=sixPos;}
    if (pState.at(12) == 1){util+=sixPos;}
    if (pState.at(15) == 1){util+=sixPos;}
    if (pState.at(48) == 1){util+=sixPos;}
    if (pState.at(51) == 1){util+=sixPos;}
    if (pState.at(60) == 1){util+=sixPos;}
    if (pState.at(63) == 1){util+=sixPos;}

    if (pState.at(0) == 2){util-=sixPos;}
    if (pState.at(3) == 2){util-=sixPos;}
    if (pState.at(12) == 2){util-=sixPos;}
    if (pState.at(15) == 2){util-=sixPos;}
    if (pState.at(48) == 2){util-=sixPos;}
    if (pState.at(51) == 2){util-=sixPos;}
    if (pState.at(60) == 2){util-=sixPos;}
    if (pState.at(63) == 2){util-=sixPos;}
    
    int fourPos = 4;
    if (pState.at(16) == 1){util += fourPos;}
    if (pState.at(19) == 1){util += fourPos;}
    if (pState.at(28) == 1){util += fourPos;}
    if (pState.at(31) == 1){util += fourPos;}
    if (pState.at(32) == 1){util += fourPos;}
    if (pState.at(35) == 1){util += fourPos;}
    if (pState.at(44) == 1){util += fourPos;}
    if (pState.at(47) == 1){util += fourPos;}

    if (pState.at(16) == 2){util -= fourPos;}
    if (pState.at(19) == 2){util -= fourPos;}
    if (pState.at(28) == 2){util -= fourPos;}
    if (pState.at(31) == 2){util -= fourPos;}
    if (pState.at(32) == 2){util -= fourPos;}
    if (pState.at(35) == 2){util -= fourPos;}
    if (pState.at(44) == 2){util -= fourPos;}
    if (pState.at(47) == 2){util -= fourPos;}
    */
    return util;

}
int minimax_val(const GameState &pState, uint8_t Player, int depth, int maxDepth, int alpha, int beta){
    depth++;
    std::vector<GameState> lNextStates;
    pState.findPossibleMoves(lNextStates);
    int v;

    if (depth > maxDepth || pState.isEOG() ) {
        //if(pState.isXWin() == true){return 10000;}
        //else if (pState.isOWin() == true){return - 10000;}
        //else if (pState.isDraw() == true){return 0;}
        //else{return evalFunc(pState,Player);} //{return 0;}
        return evalFunc(pState);
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
    //if next player is 2 --> we are player 1
    /* 
    int heurestics[2][lNextStates.size()];
    int highest_lowest[lNextStates.size()];
    for(int i = 0; i < lNextStates.size(); ++i){
        heurestics[0] = evalFunc(lNextStates[i],1);
        heurestics[1] = i;
    }
    if
    */
    int choice = 0;
    int maxVal = 0;
    //int temp = 0;
    /*if (pState.getNextPlayer() == 1){
        maxVal = 10000000;
        temp = 10000000;
    }*/

    // ITERATIVE DEEPENING
    int maxDepth = 2;
    /*
    if (lNextStates.size() < 10){maxDepth = 10;}
    else if (lNextStates.size() < 15){maxDepth = 5;}
    else if (lNextStates.size() < 20){maxDepth = 4;}
    else if(lNextStates.size() < 35){maxDepth = 3;}
    */
    //else {maxDepth = 78-lNextStates.size();}
    /*
    if(lNextStates.size() == 76){
        alpha = std::numeric_limits<int>::min()
        beta = std::numeric_limits<int>::max()
    }else{
        
    }*/

    int alpha = -1000000000;
    int temp = -1000000000;
    int temp_index = 0;
    std::cerr << lNextStates.size() << std::endl;
    for (unsigned i = 0; i < lNextStates.size(); ++i){
        alpha = minimax_val(lNextStates[i], pState.getNextPlayer(), 0, maxDepth,  alpha, 10000000);
        /*
        if(pState.getNextPlayer() == 2){
            if(temp > maxVal || temp == maxVal){
                maxVal = temp;
                choice = i;
            }
        }
        if(pState.getNextPlayer() == 1){
            if(temp > maxVal || temp == maxVal){
                maxVal = temp;
                choice = i;
            }
        }*/
        if(alpha > temp){
            temp = alpha;
            temp_index = i;
        }

    }
    return lNextStates[temp_index];
    //return lNextStates[rand() % lNextStates.size()];
}

/*namespace TICTACTOE3D*/ }
