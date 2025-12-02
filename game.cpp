#include <iostream> 
#include <ctime> // random numbers
#include <cstdlib>
#include <iomanip> //format output width 

using namespace std;

int board [4] [4]; // 4x4 board
int ldirection[] = {-1, 1, 0, 0}; // row change, up, down, left, right
int cdirection[] = {0, 0, -1, 1}; // colum change, up, down, left, right
pair<int, int> genemtyposition() {                                                        //pairs two values, struct could have been used but experimentation
	int taken = 1, line, colum;
	while (taken) {                         // loop to find empty spot
		line = rand() % 4;                  // random rows
		colum = rand() % 4;
		if (board [line][colum] == 0) {           //if spot is empty
			taken = 0;                        //if empty loop is done
			return make_pair (line, colum);             //return the row, colum
		}

	}

}    
void addpiece(){
	pair<int, int> pos = genemtyposition(); //gets emtpy cell
	board[pos.first][pos.second] = 2;      // then puts a 2
}
void newgame () {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			board [i][j] = 0;                    // emptys board

		}

	}
	addpiece();                        //place 2 start tiles
	addpiece();
}
void printmenu() {
	system("clear");                         //clear screen everytime for a cleaner look
	for (int i = 0; i < 4; ++i) {                    
		for (int j = 0; j < 4; ++j) {
			if (board [i][j] == 0)                      
				cout << setw(4) << ".";
			else
				cout << setw(4) << board [i][j];   //print number with the width 4
		}
		cout << "\n";
	}
	cout << "n: new game, w,s,a,d coresponds with the arrow keys, q: quit" << endl; //display moves
}
bool canmove(int line, int colum, int nextline, int nextcolumn) {
	if (nextline < 0 || nextcolumn <0 || nextline >= 4 || nextcolumn >= 4 || board[line][colum] != board[nextline][nextcolumn] && board[nextline][nextcolumn] != 0) {
		return false;                          //checking to see if moving/merging is valid, next cell not equal and not zero no move can be made.

	}
	return true;             //all else move is valid
}
void moveinput(int direction) {
    int startline = 0, startcolumn = 0, linestep = 1, columnstep = 1;

    if (direction == 0) {          // up start bottom up
        startline = 3;
        linestep = -1;
    }
    if (direction == 1) {          // down start top down
        startcolumn = 3;
        columnstep = -1;
    }

    int acceptiablemove = 0;    //checks is a move even happend
    int movedAtAll = 0;   // checks tile movement

    do {
        acceptiablemove = 0;                                      

        for (int i = startline; i >= 0 && i < 4; i += linestep) {                        //scan grid in order
            for (int j = startcolumn; j >= 0 && j < 4; j += columnstep) {
                int nextI = i + ldirection[direction];                               //targets the row
                int nextj = j + cdirection[direction];                               //targets the column

                if (board[i][j] && canmove(i, j, nextI, nextj)) {                    //current cell has tile and can move or merge
                    board[nextI][nextj] += board[i][j];                              // merge shift
                    board[i][j] = 0;                                                 // clears tile that moved
                    acceptiablemove = 1;                                               // confirms one move
                    movedAtAll = 1;                                                // something actually moved
                }
            }
        }

        printmenu();                                                                    //to show board after each sweep
    } while (acceptiablemove);                                                                // keep it going until no moves are possible 

    // add peice if moved and only if moved
    if (movedAtAll) {
        addpiece();
    }
}
int main () {
	srand(time(0));                                                                        //seed rng
	char commandtodir [128];                                           // a lookup table a character index array converting keyboard key into a direction
                                                                           // 128 covers the ASCII table so any keys can be used ex w in this table is ASCII 119
	commandtodir ['w'] = 0;                                             // up, S down, etc.
	commandtodir ['s'] = 1;
	commandtodir ['a'] = 2;
	commandtodir ['d'] = 3;
	newgame();

	while (true) {
		printmenu();                                                //signaling new and quit game
		char command;
		cin >> command;
		if (command == 'n') {
			newgame ();
		}
		else if (command == 'q') {
			break;
		}
		else {
			int currentdirection = commandtodir[command];                              //else continue 
			moveinput (currentdirection);
		}

	}
	return 0;

}