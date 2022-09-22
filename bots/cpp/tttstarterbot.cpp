#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;


// ----------------------------------------------------------------
// This is the TicTacToe starter bot in C++ for the AI League.
//
// It should be enhanced by reimplementing the genMove() function
// to create more intelligent moves than pure random.
// ----------------------------------------------------------------


// ----------------------------------------------------------------
// Global variables


// Change these to fit your own code.

// Settings
double time_per_move = 1.0;

// Updates
vector<int> board;    // The board, written when it's updated.
int         to_move;  // The side to move. Possible values: 1 or 2


// ----------------------------------------------------------------
//                         Settings functions


// Set the time per move, in seconds, from the AI League protocol.
//
void setTimePerMove(stringstream &ss)
{
    double val;
    ss >> val;

    time_per_move = val;
}


// ----------------------------------------------------------------
//                         Update functions


// Update the board from the Ai League protocol.
//
// Return True/False if it went well/bad.
//
bool updateBoard(stringstream &ss)
{
    vector<int> brd;
    brd.resize(9, 0);
    for (int i = 0; i < 9; i++) {
	if (!ss) {
	    cerr << "UpdateBoard: Too few parameters" << endl << flush;
	    return false;
	}

	int val;
	ss >> val;
	brd[i] = val;
    }

    board = brd;
    return true;
}

// Set the side to move from the AI League protocol.
//
// Return true/false if it went well/bad.
//
bool setToMove(stringstream &ss)
{
    if (!ss) {
	cerr << "SetToMove: Too few parameters" << endl << flush;
	return false;
    }

    int val;
    ss >> val;

    to_move = val;
    return true;
}


// ----------------------------------------------------------------
//                         Action functions


// IMPROVE THIS FUNCTION TO MAKE A BETTER BOT.
//
string genMove()
{
    return "random";
}


// ================================================================
//                     The Ai League bot


int main()
{
    srand(time(NULL));

    // Main loop for the Ai League TicTacToe protocol.
    string line;
    while (getline(cin, line)) {
	stringstream ss(line);

	// Get one token, separated by a space.
	string command;
	if (!getline(ss, command, ' ')) {
            continue;
	}

	string subCommand;
        if (command == "settings") {
	    // Settings are sent at the beginning of a game and stay constant over the game.
	    // Possible settings are "time_per_move"
	    if (!getline(ss, subCommand, ' ')) {
                cerr << "Too few parameters to update" << endl << flush;
		continue;
	    }

            if (subCommand == "time_per_move") {
                setTimePerMove(ss); 
	    } else {
                cerr << "Unknown setting command: " << subCommand << endl;
	    } 

	} else if (command == "update") {
	    // Updates are sent before every move.
	    // Possible updates are "board" and "tomove"
	    if (!getline(ss, subCommand, ' ')) {
                cerr << "Too few parameters to update" << endl << flush;
		cerr << flush;
		continue;
	    }

            if (subCommand == "board") {
                updateBoard(ss); 
	    } else if (subCommand == "tomove") {
                setToMove(ss); 
            } else {
                cerr << "Unknown update command: " << subCommand << endl;
	    }

	} else if (command == "action") {
	    // Only action is "move".

	    if (!getline(ss, subCommand, ' ')) {
		cout << "" << endl << flush; // Just to give a reply
		cout << flush;
                cerr << "Too few action tokens" << endl << flush;
		cerr << flush;
		continue;
	    }

            if (subCommand == "move") {
		cout << genMove().c_str() << endl;
	    } else {
                cerr << "Unknown action command: " << subCommand << endl;
		cout << endl;
	    }
	}

	cout << flush;
	cerr << flush;
    }

    return 0;
}
