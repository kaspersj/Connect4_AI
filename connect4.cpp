#include "connect4.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

int main(int argc, char *argv[]) {
    cout << "Press 1 for terminal and 2 for graphics: ";
    int choice;
    while (!(cin >> choice)) {
        cin.clear();
        string garbage;
        getline(cin, garbage);
        cout << "Press 1 for terminal and 2 for graphics: ";
    }
    if (choice == 1) {
        terminalPlay();
    } else {
        cout << "Under construction..." << endl;
        //graphicsPlay(argc, argv);
    }
    return 0;
}

void terminalPlay(){
    
    string player1, player2;
    int i;
    char j;
    Board board = getBoard(player1, player2);
    
    bool gameOver = false;
    
    while (! gameOver){
        board.prettyPrintBoard(cout);
        cout << "\nEnter: the column to move, q to quit, s to save" << endl;
        
        if (board.toMove() == 1){
            cout << player1 << " enter your move: ";
        }
        
        else{
            cout << player2 << " enter your move: ";
        }
        
        cin >> i;
        if (cin.good()){
            if (i < 1 || i > NUM_COLS){
                cout << "ILLEGAL MOVE: Try again" << endl;
            }
            
            else if (i >= 1 && i <= NUM_COLS){
                int move = i - 1;
                Result result = board.makeMove(move);
                if (result == IllegalMove){
                    cout << "ILLEGAL MOVE: Try again" << endl;
                }
                
                else if (result == Win){
                    if (board.toMove() == 1){
                        cout << "Congratulations " << player2 << "! You won!" <<
                        endl;
                    }
                    
                    else{
                        cout << "Congratulations " << player1 << "! You won!" <<
                        endl;
                    }
                    gameOver = true;
                }
                else if (result == Draw){
                    cout << "Draw!" << endl;
                    gameOver = true;
                }
                else if (result == NoResult){
                }
            }
        }
        
        else{
            cin.clear();
            cin >> j;
            if (j == 'q'){
                cout << "Thanks for playing!"<< endl;
            }
            else if (j == 's'){
                saveBoard(player1, player2, board);
            }
        }
    }
    board.prettyPrintBoard(cout);
}



Board getBoard(string &p1, string &p2) {
    cout << "Enter L to load a game, or P to play: " << flush;
    string fen, i;
    Board board;
    cin >> i;
    
    if (i == "P" || i == "p"){
        cout << "Player 1, enter your name: " << endl;
        cin >> p1;
        
        
        cout << "Player 2, enter your name: " << endl;
        cin >> p2;
        
        
        board = Board();
    }
    
    else{
        string fileBoard;
        cout << "Enter the filename: " << flush;
        cin >> fileBoard;
        ifstream input_file;
        
        
        input_file.open(fileBoard.c_str());
        getline(input_file, p1);
        getline(input_file, p2);
        getline(input_file, fen);
        
        
        board = Board(fen);
    }
    
    
    return board;
    
}


void saveBoard(string p1, string p2, const Board &board) {
    
    string fileName;
    cout << "Enter the filename: " << flush;
    cin >> fileName;
    
    ofstream input_file;
    input_file.open(fileName);
    input_file << p1 << endl;
    input_file << p2 << endl;
    board.printBoard_as_FENstring(input_file);
    
    input_file.close();
}
