#include "cube.hpp"
#include <iostream>

using namespace std;

void SimulateRubiksCube();

int main() {
    SimulateRubiksCube();
    return 0;
}

void SimulateRubiksCube() {
    Cube rubiks_cube;
    string move;

    while (true) {
        cout << endl;
        rubiks_cube.PrintCube();
        cout << endl;

        cout << "Enter a move to make (Q to quit): ";
        cin >> move;

        if (move[0] == 'U') {
            if (move.length() == 1) {
                rubiks_cube.UMove();
            }
            else if (move[1] == '\'') {
                rubiks_cube.UPrimeMove();
            }
        }

        else if (move[0] == 'D') {
            if (move.length() == 1) {
                rubiks_cube.DMove();
            }
            else if (move[1] == '\'') {
                rubiks_cube.DPrimeMove();
            }
        }

        else if (move[0] == 'F') {
            if (move.length() == 1) {
                rubiks_cube.FMove();
            }
            else if (move[1] == '\'') {
                rubiks_cube.FPrimeMove();
            }
        }

        else if (move[0] == 'B') {
            if (move.length() == 1) {
                rubiks_cube.BMove();
            }
            else if (move[1] == '\'') {
                rubiks_cube.BPrimeMove();
            }
        }

        else if (move[0] == 'L') {
            if (move.length() == 1) {
                rubiks_cube.LMove();
            }
            else if (move[1] == '\'') {
                rubiks_cube.LPrimeMove();
            }
        }

        else if (move[0] == 'R') {
            if (move.length() == 1) {
                rubiks_cube.RMove();
            }
            else if (move[1] == '\'') {
                rubiks_cube.RPrimeMove();
            }
        }

        else if (move == "Q") {
            break;
        }

        else {
            cout << "Invalid move." << endl;
        }
    }
}
