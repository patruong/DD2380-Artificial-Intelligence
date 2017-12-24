import java.util.*;
/*The states are selected in or near the end game and the states represents situations where the answer makes a big difference for the outcome of the game. 
Note that you are not playing a full game as you would when you play against a friend or yourself.*/
public class Player {
    /**
     * Performs a move
     *
     * @param gameState
     *            the current state of the board
     * @param deadline
     *            time before which we must have returned
     * @return the next state the board is in after our move
     */

    private int MAXDEPTH = 2; // indicates how far we will go in search depth
    private int PLAYER1X = 1; 
    private int PLAYER2O = 2; 
    private static final int SIZE_BOARD = 4;
    private static final int CHECK_WIN_MARK = 58; //when to start looking for a potential winning mark before using minimax
    private Map<String, Integer> boardToValueMap = new HashMap<String, Integer>();// ex : x0...x.xx.0.0 = 27
    private boolean notInitialized = true;
    private int[] cellValues = new int[32];
    //DONE

    public GameState play(final GameState gameState, final Deadline deadline) {

        int depth = 2;
        int alpha = Integer.MIN_VALUE;
        int beta = Integer.MAX_VALUE;
        int bestNext = Integer.MIN_VALUE;
        GameState bestMove = null;
        int v = 0;

        Vector<GameState> nextStates = new Vector<GameState>();
        
        gameState.findPossibleMoves(nextStates);
        if(nextStates.size()<35){
            Collections.sort(nextStates, (a,b) -> getEvalValueState(a) - getEvalValueState(b));
        }

        if(notInitialized){
            initializeHashMap();
            notInitialized = false;
        }

    int childSize = nextStates.size();

    if (childSize  == 0) {
            // Must play "pass" move if there are no other moves possible.
            return new GameState(gameState, new Move());
        }
    /*
    if(childSize < 50){
        depth = 3;
    }*/
    if(childSize < 35){
        depth = 3;
    }
    if(childSize < 20){
        depth = 4;
    }
    if(childSize < 10){
        depth = 9;
    }

        //Collections.sort(nextStates, (a,b) -> getEvalValueState(a) - getEvalValueState(b)); //TODO:
       
        
                for(GameState child : nextStates){
                    v = alphaBetaSearch(child, depth, alpha, beta); //TODO: This is wrong?><><><
                    if(v > bestNext){
                        bestNext = v;
                        bestMove = child;//TODO: Need the corresponding move/gamestate
                    }
                    
                }
        

        /**
         * Here you should write your algorithms to get the best next move, i.e.
         * the best next state. This skeleton returns a random move instead.
         */
        //Random random = new Random();
        //return nextStates.elementAt(random.nextInt(nextStates.size()));
        return bestMove;
    }    

    //Add depth
    public int alphaBetaSearch(GameState gameState, int depth, int alpha, int beta){
        return minValue(gameState, depth, alpha, beta);
    }

    public int maxValue(GameState gameState,int depth, int alpha, int beta){
        if(gameState.isEOG() || depth == 0){
            return getEvalValueState(gameState);
        }

        Vector<GameState> nextStates = new Vector<GameState>();
        gameState.findPossibleMoves(nextStates);
        int v = Integer.MIN_VALUE;
        depth -= 1;
        for(GameState children : nextStates){
            v = Math.max(v, minValue(children, depth, alpha, beta));//TODO: wrong pseudocode?
            if(v >= beta){
                return v;
            }
            alpha = Math.max(alpha,v);
        }
        return v;
    }

    public int minValue(GameState gameState,int depth, int alpha, int beta){
        if(gameState.isEOG() || depth == 0){
            return getEvalValueState(gameState);
        }

        Vector<GameState> nextStates = new Vector<GameState>();
        gameState.findPossibleMoves(nextStates);
        int v = Integer.MAX_VALUE;
        depth -= 1;
        for(GameState children : nextStates){
            v = Math.min(v,maxValue(children, depth, alpha, beta));//TODO: wrong pseudocode?
            if(v <= alpha){
                return v;
            }
            beta = Math.min(beta,v);
        }
        return v;
    }


    public int getEvalValueState(GameState gameState){
        String boardString = gameState.toMessage().substring(0,64);

        if(boardToValueMap.containsKey(boardString)){
            return boardToValueMap.get(boardString);
        }

        int gameStateEval = 0;
    
        if(gameState.isEOG()){
            if(gameState.isXWin()){
                gameStateEval +=  1000;
            }else if(gameState.isOWin()){
                gameStateEval -=  1000;
            }else{
                gameStateEval = 0;
            }
            boardToValueMap.put(boardString, gameStateEval);

            return gameStateEval;
        }
    
    
        int cell = 0;
        int layer = 0;
        for(int i = 0; i < 64; i++){
            cell = i;
            if(gameState.at(i) == 1){
                layer = gameState.cellToLay(cell);

                if(layer == 2){
                    cell -= 16;
                }
                if(layer == 3){
                    cell -= 48;
                }

                if(cellValues[cell] == 0){
                    gameStateEval += 5;
                }else{
                    gameStateEval += cellValues[cell];
                }
            }
        }

        //insert into hashmap so we dont have to calculate for this gameBoard/state again
        boardToValueMap.put(boardString, gameStateEval);
        return gameStateEval;
    }

    
    public void initializeHashMap(){
        cellValues[0] = 7;
        cellValues[3] = 7;
        cellValues[12] = 7;
        cellValues[15] = 7;

        cellValues[21] = 6;
        cellValues[22] = 6;
        cellValues[25] = 6;
        cellValues[26] = 6;
    }    

}