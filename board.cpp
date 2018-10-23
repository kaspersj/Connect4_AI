#include "board.h"


Board::Board() {
    nextPlayer_to_move = Player1;
	
	for(int k = 0; k < NUM_ROWS; k++) {
		for(int j = 0; j < NUM_COLS; j++) {
			data[k][j] = Empty;
		}
	}
}

Board::Board(const string &fen) {
    
    int k = 0;
    int currentRow = 0;
    int position = 0;
    
    while (k < (fen.length() - 1)) {
        if (fen[k] == '7') {
            for (int j = 0; j < NUM_COLS; j++) {
                data[currentRow][j] = Empty;
            }
            k++;
        }
        
        else if (fen[k] == '/') {
            k++;
            currentRow++;
        }
        
        else if (fen[k] == ' ') {
            if (fen[k+1] == 'x') {
                nextPlayer_to_move = Player1;
            }
            else {
                nextPlayer_to_move = Player2;
            }
            
            k++;
        }
        
        else {
            switch(fen[k]) {
                case 'x':
                    data[currentRow][position] = Player1;
                    position++;
                    k++;
                    break;
                case 'o':
                    data[currentRow][position] = Player2;
                    position++;
                    k++;
                    break;
                case '/':
                    break;
                case ' ':
                    break;
                default:
                    int end = (fen[k] - '0');
                    for (int j = position; j < (position + end); j++) {
                        data[currentRow][j] = Empty;
                    }
                    position += end;
                    k++;
                    break;
            }
        }
    }
    
    
}

void Board::printBoard_as_FENstring(ostream &os) const {
    
    for (int k = 0; k < NUM_ROWS; k++) {
        
        int countEmpty = 0;
        
        for (int j = 0; j < NUM_COLS; j++) {
            if (data[k][j] == Empty) {
                countEmpty++;
            }
            else {
                os << countEmpty;
                
                if (data[k][j] == Player1) {
                    os << PLAYER1_TOKEN;
                }
                else {
                    os << PLAYER2_TOKEN;
                }
            }
            
            if (j == (NUM_COLS - 1)) {
                os << countEmpty << '/';
            }
        }
        
    }
    
    if (nextPlayer_to_move == Player1) {
        os << " " << PLAYER1_TOKEN << endl;
    }
    else {
        os << " " << PLAYER2_TOKEN << endl;
    }
    
    return;
}


PieceType Board::atLocation(int row, int col) {
    return data[row][col];
}

void Board::prettyPrintBoard(ostream &os) const {
	os << endl;
    for (int row = NUM_ROWS - 1; row >= 0; row--)  {
        os << "     +---+---+---+---+---+---+---+"
           << endl
           << "    ";
        
        for (int col = 0; col < NUM_COLS; col++)   {
            os << " | " ;
            if ( data[row][col] == Player1)
                os <<  PLAYER1_TOKEN;
            else if (data[row][col] == Player2)
                os << PLAYER2_TOKEN;
            else
                os << EMPTY_TOKEN;
        }
        os << " |" << endl;
    }
    os << "     +---+---+---+---+---+---+---+" << endl
       <<"  col  1   2   3   4   5   6   7" << endl;
    return;
}

int Board::toMove() const {
    if (nextPlayer_to_move == Player1) {
        return 1;
    }
    else {
        return 2;
    }
}

Result Board::makeMove(int col) {
    int row;
    
    row = getFirstFreeRow(col);
    
    if (row == NUM_ROWS) {
        return IllegalMove;
    }
    
    data[row][col] = nextPlayer_to_move;
    
    updateToMove();
    
    if (isBoardFull() && !isWin(row, col)) {
        return Draw;
    }
    if (isWin(row, col)) {
        return Win;
    }
    return NoResult;
}
/*
bool Board::getWin(int row, int col) {
    
    if (isWin(row, col) == true) {
        return true;
    }
    
    return false;
}
*/
int Board::getFirstFreeRow(int col) const {
    
    if (col >= NUM_COLS || col < 0) {
        return -1;
    }
    
    for (int k = 0; k < NUM_ROWS; k++){
        
        
        if (data[k][col] == Empty){
            
            return k;
        }
    }
    return NUM_ROWS;
    
    
}

PieceType Board::updateToMove() {
    if (nextPlayer_to_move == Player1) {
		nextPlayer_to_move = Player2;
		return Player1;
	}
	else {
		nextPlayer_to_move = Player1;
		return Player2;
	}
}

bool Board::isBoardFull() const {
    int totalSum = 0;
    int fullBoard = 42;
    for(int r = 0; r < NUM_ROWS; r++) {
        for(int c = 0; c < NUM_COLS; c++) {
            if (data[r][c] == Player2  || data[r][c] == Player1) {
                totalSum++;
            }
        }

        if (totalSum == fullBoard) {
            return true;
        }
    }
    return false;
}


bool Board::inBounds(int row, int col) const {
    
    if(row < NUM_ROWS && col < NUM_COLS && row >= 0 && col >= 0){
        return true;
    }
    else {
        return false;
    }
}

int Board::piecesInDirection(int row, int col, int dRow, int dCol) const {
    
        int PieceTypeCount = 0;
        int currentRow = row + dRow;
        int currentCol = col + dCol;
        
        
        while (inBounds(currentRow, currentCol)) {
            if (data[row][col] == data[currentRow][currentCol]) {
                ++PieceTypeCount;
                currentRow = currentRow + dRow;
                currentCol = currentCol + dCol;
            }
            else {
                return PieceTypeCount;
            }
        }
        return PieceTypeCount;
    }


bool Board::isWin(int row, int col) const {
    if (piecesInDirection(row, col, -1, 0) + piecesInDirection(row, col, 1, 0) >= 3) {
        
        
        return true;
    }
        
        
        if (piecesInDirection(row, col, 0, -1) +
            piecesInDirection(row, col, 0, 1) >= 3) {
            
            
            return true;
        }
        
        
        if (piecesInDirection(row, col, 1, 1) +
            piecesInDirection(row, col, -1, -1) >= 3) {
            
            
            return true;
        }
        
        
        if (piecesInDirection(row, col, -1, 1) +
            piecesInDirection(row, col, 1, -1) >= 3) {
            
            
            return true;
        }
        
        
    return false;
}

int Board::getMaxPiecesInDirection(int row, int col, PieceType p) {
    int a;
    int b;
    int c;
    
    data[row][col] = p;
    a = piecesInDirection(row, col, -1, 0);
    b = piecesInDirection(row, col, 1, 1) + piecesInDirection(row, col, -1, -1);
    c = piecesInDirection(row, col, -1, 1) + piecesInDirection(row, col, 1, -1);
    
    if ((a > b) && (a > c)) {
        data[row][col] = Empty;
        return a;
    }
    else if ((b > a) && (b > c)) {
        data[row][col] = Empty;
        return b;
    }
    
    data[row][col] = Empty;
    return c;
}


int Board::getPiecesInDirection(int row, int col, int drow, int dcol, PieceType p) {
    int num = 0;
    
    data[row][col] = p;
    
    num = piecesInDirection(row, col, drow, dcol);
    
    data[row][col] = Empty;
    
    return num;
}

int Board::getFreeRow(int col) {
    return getFirstFreeRow(col);
}

int Board::getPieces(int row, int col, int drow, int dcol) {
    return piecesInDirection(row, col, drow, dcol);
}



