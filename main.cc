#include <iostream>
#include <string>
#include <memory>
#include "board.h"
#include "human.h"
#include "player.h"
#include "computerone.h"
#include "controller.h"
#include "window.h"

using namespace std;

int main() {

    // create instance of controller function
    Controller control {}; 
    bool state;
    string enhance;

    cout << "Welcome to Chess! Would you like to run with enhancements? (y/n)" << endl; 
    cin >> enhance;
    while (enhance != "y" && enhance != "Y" && enhance != "n" && enhance != "N" && !cin.eof()) {
            cout << "Invalid response, enter y or n" << endl;
            cin >> enhance;
    }
    if(enhance == "y" || enhance == "Y") {
        state = true;
    } else {

        if (cin.eof()) { exit(0); }

        state = false;
    }
    control.setEnhancements(state); // Turns enhancements on or off
    while (1) {
        control.gameFlow(); // call controller 
        cout << "Play again? (y/n)" << endl; // prompt to play again
        string again; 
        cin >> again; 
        // get valid input
        while (again != "y" && again != "Y" && again != "n" && again != "N" && !cin.eof()) {
            cout << "Invalid response, enter y or n" << endl;
            cin >> again;
        }
        // end game if user does not play again
        if(again == "n" || again == "N" || cin.eof()) {
            cout << "Final Score:" << endl;
            cout << "White Wins: " << control.getWhiteWins() << endl;
            cout << "Black Wins: " << control.getBlackWins() << endl;
            exit(0);
        } 
    }

}
