#!/usr/bin/env python3

import sys
import random


# This is the TicTacToe starter bot in Python for the AILeague.
#
# It should be enhanced by reimplementing the genMove() function to create
# more intelligent moves than pure random.
#


# IMPROVE THIS FUNCTION TO MAKE A BETTER BOT.
#
def genMove():
    return "random"


# ----------------------------------------------------------------
# Global variables


# Change these to fit your own code.

# Settings
time_per_move = 1.0

# Updates
board_string = ""  # A string representing the board when it's updated
to_move      = ""  # The side to move.


# ----------------------------------------------------------------


def main():

    # Main loop for the Ai League TicTacToe protocol.
    for line in sys.stdin:
        tokens = line.split()
        if tokens == []:
            continue

        if tokens[0] == "setting":
            # Settings are sent at the beginning of a game and stay constant over the game.
            if len(tokens) < 3:
                print("Too short setting command: " + repr(tokens), file=sys.stderr)
                sys.stderr.flush()
                continue

            if tokens[1] == "time_per_move":
                time_per_move = float(tokens[2])
            else:
                print("Unknown setting command: " + tokens[1], file=sys.stderr)

        elif tokens[0] == "update":
            # Updates are sent every move.
            if len(tokens) < 3:
                print("Too short update command: " + repr(tokens), file=sys.stderr)
                sys.stderr.flush()
                continue

            if tokens[1] == "board":
                board_string = tokens[2:]
            elif tokens[1] == "tomove":
                to_move = tokens[2]
            else:
                print("Unknown update command: " + tokens[1], file=sys.stderr)

        elif tokens[0] == "action":
            # Actions are commands that demand a reply from the bot.

            if len(tokens) < 2:
                print("Too short action command: " + repr(tokens), file=sys.stderr)
                sys.stderr.flush()

                print("") # Just to give a reply
                sys.stdout.flush()
                continue

            if tokens[1] == "move":
                moveStr = genMove()
                print(moveStr)
            else:
                print("Unknown action command: " + tokens[1], file=sys.stderr)
                print("")

        else:
            print("Unsupported command:", tokens[0], file=sys.stderr)

        sys.stdout.flush()
        sys.stderr.flush()
            

if __name__ == "__main__":
    main()
