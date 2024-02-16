#include <iostream>
#include <map>
#include "king.h"

// forward declaration 
bool checkEmpty(const vector<unique_ptr<Piece>>& whitePieces, const vector<unique_ptr<Piece>>& blackPieces, const Pos& currPos, const bool color); 
// ctor
King::King(int value, char type, Pos location): Piece{value, type, location}, castling{false}, isCheck{false} {}
// returns clone of piece
unique_ptr<Piece> King::clone() const {
    return make_unique<King>(*this);
}
// returns a vector of possible ending positions of the board
vector<Pos> King::canMoveTo(const vector<unique_ptr<Piece>> &  whitePieces, const vector<unique_ptr<Piece>> &  blackPieces, bool attack) {

    int rpos = getLocation().r;
    int cpos = getLocation().c;
    bool color = isWhite();
    vector<Pos> possibleMoves;
    // right
    if (rpos + 1 <= 7) {
        Pos newPos = {rpos+1, cpos};
        if (checkPossible(whitePieces, blackPieces, newPos, color, attack)[0]) {
            possibleMoves.emplace_back(newPos); 
        }
    } if (rpos - 1 >= 0) { // left
        Pos newPos = {rpos-1, cpos};
        if (checkPossible(whitePieces, blackPieces, newPos, color, attack)[0]) {
            possibleMoves.emplace_back(newPos); 
        }
    } if (cpos + 1 <= 7) { // down
        Pos newPos = {rpos, cpos + 1};
        if (checkPossible(whitePieces, blackPieces, newPos, color, attack)[0]) {
            possibleMoves.emplace_back(newPos); 
        }
    } if (cpos - 1 >= 0) { // up
        Pos newPos = {rpos, cpos - 1};
        if (checkPossible(whitePieces, blackPieces, newPos, color, attack)[0]) {
            possibleMoves.emplace_back(newPos); 
        }
    } if (rpos + 1 <= 7 && cpos + 1 <= 7) { // down and right
        Pos newPos = {rpos + 1, cpos + 1};
        if (checkPossible(whitePieces, blackPieces, newPos, color, attack)[0]) {
            possibleMoves.emplace_back(newPos); 
        }
    } if (rpos + 1 <= 7 && cpos - 1 >= 0) { // down and left
        Pos newPos = {rpos + 1, cpos - 1};
        if (checkPossible(whitePieces, blackPieces, newPos, color, attack)[0]) {
            possibleMoves.emplace_back(newPos); 
        }
    } if (rpos - 1 >= 0 && cpos - 1 >= 0) { // up and left
        Pos newPos = {rpos - 1, cpos - 1};
        if (checkPossible(whitePieces, blackPieces, newPos, color, attack)[0]) {
            possibleMoves.emplace_back(newPos); 
        }
    } if (rpos - 1 >= 0 && cpos + 1 <= 7) { // up and right
        Pos newPos = {rpos - 1, cpos + 1};
        if (checkPossible(whitePieces, blackPieces, newPos, color, attack)[0]) {
            possibleMoves.emplace_back(newPos); 
        }
    } if (firstMove && !isCheck && !attack) { // check king side castling
        Pos newPos1 = {rpos, cpos + 2};
        Pos newPos2 = {rpos, cpos + 1};
        Pos checker = {rpos, cpos + 3};
        // if squares in between are empty
        if (checkEmpty(whitePieces, blackPieces, newPos1, color) && checkEmpty(whitePieces, blackPieces, newPos2, color)) {
            if (color) { // white
                for (int i = 0; i < whitePieces.size(); i++) {
                    if (whitePieces.at(i)->getType() == 'R' && whitePieces.at(i)->getFirstMove() && whitePieces.at(i)->getLocation() == checker) {
                        castling = true;
                        possibleMoves.emplace_back(newPos1); 
                    }
                }
            } else { // black
                for (int i = 0; i < blackPieces.size(); i++) {
                    if (blackPieces.at(i)->getType() == 'r' && blackPieces.at(i)->getFirstMove() && blackPieces.at(i)->getLocation() == checker) {
                        castling = true; 
                        possibleMoves.emplace_back(newPos1); 
                    }
                }
            }
        }

        Pos newPos3 = {rpos, cpos - 1};
        Pos newPos4 = {rpos, cpos - 2};
        Pos newPos5 = {rpos, cpos - 3};
        Pos checker2 = {rpos, cpos - 4};
        // queen side castling
        if (checkEmpty(whitePieces, blackPieces, newPos3, color) && checkEmpty(whitePieces, blackPieces, newPos4, color) && checkEmpty(whitePieces, blackPieces, newPos5, color)) {
            if (color) { // white
                for (int i = 0; i < whitePieces.size(); i++) {
                    if (whitePieces.at(i)->getType() == 'R' && whitePieces.at(i)->getFirstMove() && whitePieces.at(i)->getLocation() == checker) {
                        castling = true;
                        possibleMoves.emplace_back(newPos4); 
                    }
                }
            } else { // black
                for (int i = 0; i < blackPieces.size(); i++) {
                    if (blackPieces.at(i)->getType() == 'r' && blackPieces.at(i)->getFirstMove() && blackPieces.at(i)->getLocation() == checker) {
                        castling = true; 
                        possibleMoves.emplace_back(newPos4); 
                    }
                }
            }
        }      
    } 
    return possibleMoves; 
}
// returns true if position is empty and false otherwise
bool checkEmpty(const vector<unique_ptr<Piece>> &  whitePieces, const vector<unique_ptr<Piece>> &  blackPieces, const Pos& currPos, const bool color) {
    for (int i = 0; i < whitePieces.size(); i++) {
        if (whitePieces.at(i)->getLocation().c == currPos.c && whitePieces.at(i)->getLocation().r == currPos.r) {
            return false; 
        }
    }
    for (int i = 0; i < blackPieces.size(); i++) {
        if (blackPieces.at(i)->getLocation().c == currPos.c && blackPieces.at(i)->getLocation().r == currPos.r) {
            return false; 
        }   
    }
    return true; 
}
