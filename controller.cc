#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>
#include <sstream>
#include "board.h"
#include "human.h"
#include "player.h"
#include "computerone.h"
#include "computertwo.h"
#include "computerthree.h"
#include "computerfour.h"
#include "computerfive.h"
#include "controller.h"
#include "convertor.h"
#include "window.h"
#include "displayMoves.h"

using namespace std;

// anything to do with piece location needs to be try and catch'd 

float Controller::getBlackWins() const {
    return blackWins;
}

float Controller::getWhiteWins() const {
    return whiteWins;
}

void Controller::setEnhancements(bool state) {
    enhanceOn = state;
}

void Controller::gameFlow() {

    Xwindow xw;
    string cmd;
    auto board = make_unique<Board>(); // create new board
    string player1string;
    string player2string; 
    bool currGame = false; 
    bool gameWon = false; 
    bool setUpCalled = false;
    unique_ptr<Player> player1;
    unique_ptr<Player> player2;

    while (1) {

        if (cin.eof()) {
            cout << "Final Score:" << endl;
            cout << "White Wins: " << getWhiteWins() << endl;
            cout << "Black Wins: " << getBlackWins() << endl;
            exit(0);

        }

        cin >> cmd;

        try {

        if (cmd == "game" && !currGame) {
                
                string curr = ""; 
                string player = ""; 
                getline(cin,curr); 
                istringstream iss {curr}; 
                int counter = 0; 

                while (iss >> player) {

                    if (counter == 0) {

                        player1string = player; 

                    } else if (counter == 1) {

                        player2string = player; 

                    }

                    counter++; 

                } 

                if (counter != 2) {

                    throw logic_error{"Please enter 2 players!"}; 

                }

                if (!((player1string == "human" || player1string == "computer1" || player1string == "computer2" ||
                player1string == "computer3" || player1string == "computer4" || player1string == "computer5") && (player2string == "human" || player2string == "computer1" 
                || player2string == "computer2" || player2string == "computer3" || player2string == "computer4" || player2string == "computer5"))) {
 
                    throw logic_error{"Please enter valid players!"};

                }

            if (!board->getSetup()) { // Checks if set up has been called
                board->init(xw, true);
            board->allNextMoves(true); // should these be in if statement???
            board->allNextMoves(false);
            }

            cout << *board << endl;

            // put this in a try catch ??

                if (player1string == "human") {

                    player1 = make_unique<Human>();

                } else if (player1string == "computer1") {

                    player1 = make_unique<ComputerOne>();

                } else if (player1string == "computer2") {

                    player1 = make_unique<ComputerTwo>();

                } else if (player1string == "computer3") {

                    player1 = make_unique<ComputerThree>();

                } else if (player1string == "computer4") {

                    player1 = make_unique<ComputerFour>();

                } else if (player1string == "computer5") {

                    player1 = make_unique<ComputerFive>();

                } else {

                    player1 = make_unique<Human>();

                }

                // put this in a try catch ??
                if (player2string == "human") {

                    player2 = make_unique<Human>();

                } else if (player2string == "computer1") {

                    player2 = make_unique<ComputerOne>();

                } else if (player2string == "computer2") {

                    player2 = make_unique<ComputerTwo>();

                } else if (player2string == "computer3") {

                    player2 = make_unique<ComputerThree>();

                } else if (player2string == "computer4") {

                    player2 = make_unique<ComputerFour>();

                } else if (player2string == "computer5") {

                    player2 = make_unique<ComputerFive>();

                } else {

                    player2 = make_unique<Human>();

                } 
            currGame = true; 

        } else if (cmd == "move" && currGame) {
                bool validMove = false;
                    std::vector<Pos> moves; 
                    bool turn = board->getTurn(); 
                    if(turn) {
                        if (board->isStalemate(turn)) {
                            cout << "Stalemate!" << endl;
                            blackWins+=0.5;
                            whiteWins+=0.5;
                            return;
                        }
                        moves  = player1->getMove(board->getNextMoves(turn), board->getNextMoves(!turn), turn, board->getNextAttacks(turn), board->getNextAttacks(!turn), board->getPieces(true), board->getPieces(false), board->getNextChecks(true), board->getNextChecks(false));
                    } else {
                        if (board->isStalemate(turn)) {
                            cout << "Stalemate!" << endl;
                            blackWins+=0.5;
                            whiteWins+=0.5;
                            return;
                        }
                        moves  = player2->getMove(board->getNextMoves(!turn), board->getNextMoves(turn),turn,  board->getNextAttacks(!turn), board->getNextAttacks(turn), board->getPieces(true), board->getPieces(false), board->getNextChecks(true), board->getNextChecks(false));
                    }

                    if (board->tryMove(moves.at(0), moves.at(1))) {
                        validMove = true;
                        char newPiece; // Is pawn promotion mandatory???
                        if(board->pieceAtLocation(moves.at(1), turn) == 'P' && turn && ((moves.at(1)).r == 0)) { // White pawn promotion
                            newPiece = player1->getPromotion(turn);
                            board->removePiece(moves.at(1));
                            board->addPiece(moves.at(1), newPiece);
                        } else if (board->pieceAtLocation(moves.at(1), turn) == 'p' && !turn && ((moves.at(1)).r == 7)){ // Black pawn promotion
                            newPiece = player2->getPromotion(turn);
                            board->removePiece(moves.at(1));
                            board->addPiece(moves.at(1), newPiece);
                        }
                        cout << *board << endl;
                        if (board->isCheck((board->getKing(!(board->getTurn()))))) {
                             if (board->isCheckmate((board->getKing(!turn)))) {
                                 if(board->getTurn()) {
                                     cout << "Checkmate! White wins!" << endl; 
                                     whiteWins++;
                                     return;
                                 } else {
                                     cout << "Checkmate! Black wins!" << endl; 
                                     blackWins++;
                                     return;
                                }
                                gameWon = true; 
                             }
                                    if (board->getTurn()) {
                                        cout << "Black is in check." << endl;
                                    } else {
                                        cout << "White is in check." << endl;
                                    }
                        }                       
                    } else {
                        validMove = false;
                        cout << "Not a valid move, please try again" << endl;
                    }
                

            if (gameWon) {
                break;
            }
            
            if(validMove) {
                board->setTurn(!board->getTurn());
            }
            
            
        } else if (cmd == "resign" && currGame) {

            if (board->getTurn()) {
                // cout black wins
                blackWins++;
                cout << "Black wins!" << endl;
                return;
                // prompt to play again 
                
            } else {

                // cout white wins
                whiteWins++; 
                cout << "White wins!" << endl;
                return;
                // prompt to play again

            }

        } else if (cmd == "setup" && !currGame) {
            
            board->setSetup(); // Indicates to board that set up has been called 
            if(!setUpCalled) {
                board->init(xw, false);
            }
            setUpCalled = true;
            
            string func; 
            
            while (cin >> func) { 

                try {

                if (func != "+" && func != "-" && func != "=" && func != "done") {

                    cin.clear(); 
                    while (cin.get() != '\n') {
                        continue;
                    }
                    throw logic_error{"Please enter a valid setup function"}; 

                }

                string loco;
                Convertor convert; 

                if (func == "+") {

                    char piece;
                    cin >> piece >> loco;
                    Pos location = convert.stringToPos(loco);
                    board->addPiece(location, piece);  

                    cout << *board << endl; 

                } else if (func == "-") {

                    cin >> loco;
                    Pos location = convert.stringToPos(loco);
                    board->removePiece(location); 

                     cout << *board << endl;

                } else if (func == "=") {

                    string color;
                    cin >> color;

                    if (color == "white") {
                        board->setTurn(true);
                    } else if (color == "black") {
                        board->setTurn(false);
                    } else {
                        // reprompt
                    }

                } else if (func == "done") {
                    // Check if setup conditions of satisfied
                    if(!board->setUpConditions()) {
                         cout << *board << endl;
                        cout << "Set Up Conditions not satisfied, please correct this and try again" << endl;
                    } else {
                        cout << "Exiting Setup Mode" << endl;
                        break;
                    }
                } 

                } catch (logic_error& r) {

                    cout << r.what() << endl;
                    cin.clear();  

                }

            }

            // commands of setup to modify it 

        } else if (cmd == "help" && currGame && enhanceOn) {
            string func;
            DisplayMoves d;
            while(1) {
                cin >> func;
                if(func == "all") {
                    if(board->getTurn()) {
                        d.print(board->getNextMoves(true));
                    } else {
                        d.print(board->getNextMoves(false));
                    }
                    break;
                } else if (func == "attacks") {
                    if(board->getTurn()) {
                        d.print(board->getNextAttacks(true));
                    } else {
                        d.print(board->getNextAttacks(false));
                    }
                    break;
                } else if (func == "checks") {
                    if(board->getTurn()) {
                        d.print(board->getNextChecks(true));
                    } else {
                        d.print(board->getNextChecks(false));
                    }
                    break;
                } else {
                    while (cin.get() != '\n') {
                        continue;
                    }
                    throw logic_error{"Not a valid help command. Please enter help all, help attacks, or help checks."}; 
                    break;
                }
            }
        } else {

            while (cin.get() != '\n') {
                continue;
            }
            throw logic_error{"Please enter a valid command!"}; 
            
        }

        if (currGame && board->isStalemate(board->getTurn())) {
            cout << "Stalemate!" << endl;
            blackWins += 0.5;
            whiteWins += 0.5;
            return; 
        } 

        cin.clear();

    } catch (logic_error& r) {

        cout << r.what() << endl; 

    }

    }

}
