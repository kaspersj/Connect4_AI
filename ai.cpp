#include "ai.h"
#include "board.h"
#include <cstdlib>
#include <ctime>
#include <iostream>


int connect4AI(const Board& board){
    Board board2 = board;
    
    int countEmpty = 0;
    
    for (int k = 0; k < NUM_ROWS; k++) {
        for (int j = 0; j < NUM_COLS; j++) {
            if (board2.atLocation(k, j) == Empty) {
                countEmpty++;
            }
        }
    }
    
    if (countEmpty == 41) {
        for (int k = 0; k < NUM_ROWS; k++) {
            for (int j = 0; j < NUM_COLS; j++) {
                if (board2.atLocation(k, j) == Player1) {
                    if (j != 3) {
                        return 3;
                    }
                    else {
                        return 4;
                    }
                }
            }
        }
    }
    
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 6; j++) {
            Board board3 = board;
            Result resultW = Win;
            
            if(board3.makeMove(i) == resultW) {
                
                return i;
            }
        }
    }
    
    for (int k = 0; k < NUM_COLS; k++) {
        for (int j = 0; j < NUM_ROWS; j++) {
            if (board2.atLocation(j, k) == Player1) {
                // This outputs how many Player1 pieces the computer sees on all sides of Player1 pieces
                //std::cout << j << " " << k << " " << board2.getPieces(j, k, 1, 0) << " " << board2.getPieces(j, k, 1, 1) << " " << board2.getPieces(j, k, 0, 1) << " " << board2.getPieces(j, k, -1, 1) << " " << board2.getPieces(j, k, -1, 0) << " " << board2.getPieces(j, k, -1, -1) << " " << board2.getPieces(j, k, 0, -1) << " " << board2.getPieces(j, k, 1, -1) << std::endl;
                if (board2.getPieces(j, k, -1, 0) == 2) {
                    if (board2.getFreeRow(k) == j+1) {
                         return k;
                    }
                }
                else if (board2.getPieces(j, k, 0, 1) == 2) {
                    if (board2.getFreeRow(k+3) == j) {
                        return k+3;
                    }
                    else if (board2.getFreeRow(k-1) == j) {
                        return k-1;
                    }
                }
                else if (board2.getPieces(j, k, 0, -1) == 2) {
                    if (board2.getFreeRow(k-3) == j) {
                        return k-3;
                    }
                    else if (board2.getFreeRow(k+1) == j) {
                        return k+1;
                    }
                }
                else if (board2.getPieces(j, k, 1, 1) == 2) {
                    if (board2.getFreeRow(k-1) == j-1) {
                        return k-1;
                    }
                    else if (board2.getFreeRow(k+3) == j+3) {
                        return k+3;
                    }
                }
                else if (board2.getPieces(j, k, -1, 1) == 2) {
                    if (board2.getFreeRow(k+1) == j-1) {
                        return k+1;
                    }
                    else if (board2.getFreeRow(k-3) == j+3) {
                        return k-3;
                    }
                }
            }
            else if (board2.atLocation(j, k) == Empty) {
                if (board2.getPiecesInDirection(j, k, 0, 1, Player1) + board2.getPiecesInDirection(j, k, 0, -1, Player1) >= 3) {
                    if (board2.getFreeRow(k) == j) {
                        return k;
                    }
                }
                else if (board2.getPiecesInDirection(j, k, 1, 1, Player1) + board2.getPiecesInDirection(j, k, -1, -1, Player1) >= 3) {
                    if (board2.getFreeRow(k) == j) {
                        return k;
                    }
                }
                else if (board2.getPiecesInDirection(j, k, 1, -1, Player1) + board2.getPiecesInDirection(j, k, -1, 1, Player1) >= 3) {
                    if (board2.getFreeRow(k) == j) {
                        return k;
                    }
                }
            }
        }
    }
    
    int maxSum = 0;
    int maxColumn = 0;
    
    
    for (int c = 0; c < NUM_COLS; c++) {
        int currentSum = 0;
        
        for (int r = 6; r > 0; r--) {
 
            if (board2.atLocation(r, c) == Empty) {
                
                if (board2.atLocation(r, c) == Empty && board2.makeMove(c) && board2.makeMove(c) == Win) {
                    break;
                }
                
                if (board2.getPiecesInDirection(r, c, -1, 0, Player2) == 2) {
                    if (board2.atLocation(r+1, c) == Empty) {
                        if (board2.getFreeRow(c) == r) {
                            currentSum += 70;
                        }
                        else {
                            currentSum += 5;
                        }
                    }
                }
                
                if (board2.getPiecesInDirection(r, c, 0, 1, Player2) == 2) {
                    if (board2.atLocation(r, c+3) == Empty || board2.atLocation(r, c-1) == Empty) {
                        if (board2.getFreeRow(c) == r) {
                            currentSum += 70;
                        }
                        else {
                            currentSum += 5;
                        }
                    }
                    else {
                        currentSum += 1;
                    }
                }
                
                
                if (board2.getPiecesInDirection(r, c, 0, 1, Player2) == 1 && board2.getPiecesInDirection(r, c, 0, -1, Player2) == 1) {
                    if (board2.atLocation(r, c+2) == Empty || board2.atLocation(r, c-2) == Empty) {
                        if (board2.getFreeRow(c) == r) {
                            currentSum += 70;
                        }
                        else {
                            currentSum += 5;
                        }
                    }
                    else {
                        currentSum += 1;
                    }
                }
                
                if (board2.getPiecesInDirection(r, c, 1, 1, Player2) == 2) {
                    if (board2.atLocation(r+3, c+3) == Empty || board2.atLocation(r-1, c-1) == Empty) {
                        if (board2.getFreeRow(c) == r) {
                            currentSum += 70;
                        }
                        else {
                            currentSum += 5;
                        }
                    }
                    else {
                        currentSum += 1;
                    }
                }
                
                if (board2.getPiecesInDirection(r, c, 1, 1, Player2) == 1 && board2.getPiecesInDirection(r, c, -1, -1, Player2) == 1) {
                    if (board2.atLocation(r+2, c+2) == Empty || board2.atLocation(r-2, c-2) == Empty) {
                        if (board2.getFreeRow(c) == r) {
                            currentSum += 70;
                        }
                        else {
                            currentSum += 5;
                        }
                    }
                    else {
                        currentSum += 1;
                    }
                }
                
                if (board2.getPiecesInDirection(r, c, 1, -1, Player2) == 2) {
                    if (board2.atLocation(r-3, c-3) == Empty || board2.atLocation(r+1, c+1) == Empty) {
                        if (board2.getFreeRow(c) == r) {
                            currentSum += 70;
                        }
                        else {
                            currentSum += 5;
                        }
                    }
                    else {
                        currentSum += 1;
                    }
                }
                
                if (board2.getPiecesInDirection(r, c, 1, -1, Player2) == 1 && board2.getPiecesInDirection(r, c, -1, 1, Player2) == 1) {
                    if (board2.atLocation(r+2, c-2) == Empty || board2.atLocation(r-2, c+2) == Empty) {
                        if (board2.getFreeRow(c) == r) {
                            currentSum += 70;
                        }
                        else {
                            currentSum += 5;
                        }
                    }
                    else {
                        currentSum += 1;
                    }
                }
                
                if (board2.getPiecesInDirection(r, c, 0, 1, Player2) + board2.getPiecesInDirection(r, c, 0, -1, Player2) == 1){
                    
                    if (board2.getFreeRow(c) == r) {
                        currentSum += 10;
                    }
                    else {
                        currentSum += 5;
                    }
                    
                }
                if (board2.getPiecesInDirection(r, c, -1, 0, Player2) == 1 ) {
                    if (board2.getFreeRow(c) == r) {
                        currentSum += 10;
                    }
                    else {
                        currentSum += 5;
                 }
                }
                    
                if (board2.getPiecesInDirection(r, c, 1, 1, Player2) +
                        board2.getPiecesInDirection(r, c, -1, -1, Player2) == 1) {
                    if (board2.getFreeRow(c) == r) {
                        currentSum += 10;
                    }
                    else {
                        currentSum += 5;
                    }
                }
                    
                if(board2.getPiecesInDirection(r, c, -1, 1, Player2) +
                   board2.getPiecesInDirection(r, c, 1, -1, Player2) == 1) {
                    if (board2.getFreeRow(c) == r) {
                        currentSum += 10;
                    }
                    else {
                        currentSum += 5;
                    }
                }
                    
                if (board2.getPiecesInDirection(r, c, 0, 1, Player2) + board2.getPiecesInDirection(r, c, 0, -1, Player2) == 0 ||
                    board2.getPiecesInDirection(r, c, -1, 0, Player2) == 0 || board2.getPiecesInDirection(r, c, 1, 1, Player2) +
                    board2.getPiecesInDirection(r, c, -1, -1, Player2) == 0 || board2.getPiecesInDirection(r, c, -1, 1, Player2) +
                    board2.getPiecesInDirection(r, c, 1, -1, Player2) == 0) {
                    
                    if (board2.getFreeRow(c) == r) {
                        currentSum += 1;
                    }
                
                }
                if (board2.getMaxPiecesInDirection(r, c, Player1) == 2) {
                    if (board2.getFreeRow(c) == r) {
                        currentSum+= 10;
                    }
                    else {
                        currentSum += 5;
                    }
                    
                }
                
                if (board2.atLocation(r, c-1) == Player2 && board2.atLocation(r, c+1) == Empty && board2.atLocation(r, c+2) == Player2) {
                    if (board2.getFreeRow(c) == r) {
                        currentSum += 50;
                    }
                    else {
                        currentSum += 5;
                    }
                }
                
                if (board2.atLocation(r, c-1) == Player1 && board2.atLocation(r, c+1) == Empty && board2.atLocation(r, c+2) == Player1) {
                    if (board2.getFreeRow(c) == r) {
                        currentSum += 15;
                    }
                    else {
                        currentSum += 5;
                    }
                }
                
                
            }
        }

        if (currentSum > maxSum) {
            maxColumn = c;
            maxSum = currentSum;
        }
        if (currentSum == maxSum) {
            if (abs(3 - maxColumn) < abs(3 - c)) {
                maxColumn = c;
            }
        }

    }
    
    return maxColumn;
    
}


