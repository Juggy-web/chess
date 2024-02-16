#include <iostream>
#include <map>
#include "pawn.h"

using namespace std;

    Pawn::Pawn(int value, char type, Pos location): Piece{value, type, location} {}

    unique_ptr<Piece> Pawn::clone() const {
        return make_unique<Pawn>(*this);
    }

    bool Pawn::setEnPassant(bool val) {
        enPassant = val;
    }

    vector<Pos> Pawn::canMoveTo(const vector<unique_ptr<Piece>> &  whitePieces, const vector<unique_ptr<Piece>> &  blackPieces, bool attack) {
        // Pawn Movement
        // Two squares forwrad (if it's firstMove)
        // One squre forward (always)
        // Diagonal left or right by 1 (if there is an enemy on that square)
        // Diagonal left or right by 1 (if there is a pawn to the left or right of it that has enpassant true)
        
        vector<Pos> results;
        Pos tempPos = location;
        if(isWhite()) {
            tempPos.r--; // One forward
            results.emplace_back(tempPos);
            if(firstMove) {
                tempPos = location;
                tempPos.r-=2; // Two forward
                results.emplace_back(tempPos);
            }
            tempPos = location;
            tempPos.r--; // Left Diagonal
            tempPos.c--;
            results.emplace_back(tempPos);
            tempPos = location;
            tempPos.r--; // Right Diagonal
            tempPos.c++;
            results.emplace_back(tempPos);

            for(int i = 0; i < whitePieces.size(); i++) { // This checks if another white piece is blocking it's move
                for(int x = 0; x < results.size(); x++) {
                    if(whitePieces[i]->getLocation() == results[x]) {
                        results[x].r = -1;
                        results[x].c = -1;
                        if(x == 0) {
                            if(firstMove) {
                                results[1].r = -1;
                                results[1].c = -1;
                            }
                        }
                    }
                }
            }

            for(int i = 0; i < blackPieces.size(); i++) { // This checks if a black piece is blocking it's move
                    if(blackPieces[i]->getLocation() == results[0]) {
                        results[0].r = -1;
                        results[0].c = -1; 
                        if(firstMove) {
                            results[1].r = -1;
                            results[1].c = -1;
                        }
                    }
                    if(firstMove) {
                        if(blackPieces[i]->getLocation() == results[1]) {
                            results[1].r = -1;
                            results[1].c = -1;
                        }
                    }
            }

            bool leftDiagonal = false;
            bool rightDiagonal = false;
            Pos tempLeft = location;
            tempLeft.c--;
            Pos tempRight = location;
            tempRight.c++;
            for(int i = 0; i < blackPieces.size(); i++) { // This it's able to capture or enPassant
                if(blackPieces[i]->getLocation() == results[(results.size()-1)]) { // Checks if there is a peice on the right diagonal to capture
                    rightDiagonal = true;
                }
                if(blackPieces[i]->getLocation() == results[(results.size()-2)]) { // Checks if there is a peice on the left diagonal capture
                    leftDiagonal = true;
                }
                if(blackPieces[i]->getLocation() == tempLeft && blackPieces[i]->getEnPassant()) { // Checks if there a peice to the left which can be captured with enPassant
                    leftDiagonal = true;
                }
                if(blackPieces[i]->getLocation() == tempRight && blackPieces[i]->getEnPassant()) {  // Checks if there a peice to the right which can be captured with enPassant
                    rightDiagonal = true;
                }
            }

            if(!leftDiagonal) {
                results[(results.size()-2)].r = -1;
                results[(results.size()-2)].c = -1;
            }
            if(!rightDiagonal) {
                results[(results.size()-1)].r = -1;
                results[(results.size()-1)].c = -1;
            }

        } else {
            tempPos.r++; // One forward
            results.emplace_back(tempPos);
            if(firstMove) {
                tempPos = location;
                tempPos.r+=2; // Two forward
                results.emplace_back(tempPos);
            }
            tempPos = location;
            tempPos.r++; // Left Diagonal
            tempPos.c--;
            results.emplace_back(tempPos);
            tempPos = location;
            tempPos.r++; // Right Diagonal
            tempPos.c++;
            results.emplace_back(tempPos);

            for(int i = 0; i < blackPieces.size(); i++) { // This checks if another black piece is blocking it's move
                for(int x = 0; x < results.size(); x++) {
                    if(blackPieces[i]->getLocation() == results[x]) {
                        results[x].r = -1;
                        results[x].c = -1;
                        if(x == 0) {
                            if(firstMove) {
                                results[1].r = -1;
                                results[1].c = -1;
                            }
                        }
                    }
                }
            }

            for(int i = 0; i < whitePieces.size(); i++) { // This checks if a black piece is blocking it's move
                    if(whitePieces[i]->getLocation() == results[0]) {
                        results[0].r = -1;
                        results[0].c = -1; 
                        if(firstMove) {
                            results[1].r = -1;
                            results[1].c = -1;
                        }
                    }
                    if(firstMove) {
                        if(whitePieces[i]->getLocation() == results[1]) {
                            results[1].r = -1;
                            results[1].c = -1;
                        }
                    }
            }

            bool leftDiagonal = false;
            bool rightDiagonal = false;
            Pos tempLeft = location;
            tempLeft.c--;
            Pos tempRight = location;
            tempRight.c++;
            for(int i = 0; i < whitePieces.size(); i++) { // This it's able to capture or enPassant
                if(whitePieces[i]->getLocation() == results[(results.size()-1)]) { // Checks if there is a peice on the right diagonal to capture
                    rightDiagonal = true;
                }
                if(whitePieces[i]->getLocation() == results[(results.size()-2)]) { // Checks if there is a peice on the left diagonal capture
                    leftDiagonal = true;
                }
                if(whitePieces[i]->getLocation() == tempLeft && whitePieces[i]->getEnPassant()) { // Checks if there a peice to the left which can be captured with enPassant
                    leftDiagonal = true;
                }
                if(whitePieces[i]->getLocation() == tempRight && whitePieces[i]->getEnPassant()) {  // Checks if there a peice to the right which can be captured with enPassant
                    rightDiagonal = true;
                }
            }

            if(!leftDiagonal) {
                results[(results.size()-2)].r = -1;
                results[(results.size()-2)].c = -1;
            }
            if(!rightDiagonal) {
                results[(results.size()-1)].r = -1;
                results[(results.size()-1)].c = -1;
            }
        }

        if(attack) {
            results[0].r = -1;
            results[0].c = -1;
            if(firstMove) {
                results[1].r = -1;
                results[1].c = -1;
            }
        }

        vector<Pos> validMoves;
        for(int i = 0; i < results.size(); i++) {
            if(results[i].r >= 0 && results[i].c >= 0 && results[i].r <= 7 && results[i].c <= 7) {
                validMoves.emplace_back(results[i]);
            }
        }
        
        return validMoves; 
    }
