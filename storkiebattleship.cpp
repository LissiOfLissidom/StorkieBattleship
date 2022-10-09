/*
Battleship

for game booth here: 
https://www.chickensmoothie.com/Forum/viewtopic.php?t=4788768

coded by LiLi041 on ChickenSmoothie, (c) 2022
*/

#include <iostream>
#include <stdlib.h>   
#include <time.h>
using namespace std;

const int height = 3;
const int width = 3;
const int ships = 5;
const int guesses = 5;

//board size 3x3
/*
(1,1) (1,2) (1,3)
(2,1) (2,2) (2,3)
(3,1) (3,2) (3,3)
*/
/*
board look
+---+---+---+
|   |   |   |
+---+---+---+
|   |   |   |
+---+---+---+
|   |   |   |
+---+---+---+
*/
/*
X = hit (ship, guessed)
- = miss (not ship, guessed)
O = surviving ship (ship, not guessed)
*/
//5x length-1 ships

bool board[height][width]; 
int hitmiss[height][width];
//0 = nothing, 1 = hit, 2 = surviving ship, 3 = miss

void print() {
    //board
    for (int i = 0; i < height; i++) {
        //horizontal dividers
        for (int j = 0; j < width; j++) {
            cout << "+---";
        }
        cout << "+" << endl;
        //vertical dividers + hit/miss
        for (int j = 0; j < width; j++) {
            cout << "| ";
            if (hitmiss[i][j] == 1) 
                cout << "X ";
            else if (hitmiss[i][j] == 2) 
                cout << "O ";
            else if (hitmiss[i][j] == 3) 
                cout << "- ";
            else
                cout << "  ";
        }
        cout << "|" << endl;
    }

    //last horizontal divider
    for (int j = 0; j < width; j++) {
        cout << "+---";
    }
    cout << "+" << endl;
    cout << endl;
}

int main() {
    string name;
    cout << "Initializing game..." << endl;
    cout << "Welcome to Battleship!" << endl;

    string input;
    do {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                board[i][j] = false;
                hitmiss[i][j] = 0;
            }
        }

        cout << "Enter name: ";
        cin >> name;
        
        cout << "Enter " << guesses << " coordinates:" << endl;
        cout << "(Please format like [1 1], without the brackets)" << endl;

        int x[guesses], y[guesses];
        for (int i = 0; i < guesses; i++) {
            cout << "Guess " << i + 1 << ": ";
            cin >> x[i] >> y[i];
            x[i]--;
            y[i]--;
        }

        srand (time(NULL));
        int count = 0;
        while (count < guesses) {
            int rng = rand() % (height * width);
            int xcoor = (rng / 3), ycoor = (rng % 3);
            if (board[xcoor][ycoor] == false) {
                board[xcoor][ycoor] = true;
                count++;
            }
        }

        for (int i = 0; i < guesses; i++) {
            //guessed and ship exists; hit
            if (board[x[i]][y[i]] == true) {
                hitmiss[x[i]][y[i]] = 1;
            }
            //guessed and ship doesn't exist; miss
            else {
                hitmiss[x[i]][y[i]] = 3;
            }
        }

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (hitmiss[i][j] == 0 && board[i][j] == true)
                    hitmiss[i][j] = 2;
            }
        }

        cout << "The sound of splashes repeats 5 times. You peer over the edge, and see the result." << endl;
        print();

        cout << "Play again? (Y/n)" << endl;
        cin >> input;
    } while (input != "n" && input != "N");

    return 0;
}
