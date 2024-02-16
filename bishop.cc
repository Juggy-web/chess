#include <iostream>
#include <map>
#include "piece.h"
#include "bishop.h"
#include "position.h"

// ctor
Bishop::Bishop(int value, char type, Pos location): Piece{value, type, location} {}

// returns a clone of piece
unique_ptr<Piece> Bishop::clone() const {
    return make_unique<Bishop>(*this);
}

// returns a vector of possible ending positions of the board
vector<Pos> Bishop::canMoveTo(const vector<unique_ptr<Piece>> & whitePieces, const vector<unique_ptr<Piece>> &  blackPieces, bool attack) {

    // store location and color
    int rpos = getLocation().r;
    int cpos = getLocation().c;
    bool color = isWhite();
    vector<Pos> possibleMoves; 

    // down and right moves
    for (int row = rpos+1, cols = cpos+1; row <= 7 && cols <= 7; row++, cols++) {
        Pos newPos = {row, cols};
        if (checkPossible(whitePieces, blackPieces, newPos, color, attack)[0] && checkPossible(whitePieces, blackPieces, newPos, color, attack)[1]) {
            possibleMoves.emplace_back(newPos); 
        } else if (checkPossible(whitePieces, blackPieces, newPos, color, attack)[0] && !(checkPossible(whitePieces, blackPieces, newPos, color, attack)[1])) {
            possibleMoves.emplace_back(newPos); 
            break;
        } else if (!(checkPossible(whitePieces, blackPieces, newPos, color, attack)[0]) && !(checkPossible(whitePieces, blackPieces, newPos, color, attack)[1])) {
            break;
        }
    }

    // up and left moves
    for (int row = rpos-1, cols = cpos-1; row >= 0 && cols >=0 ; row--, cols--) {
        Pos newPos = {row, cols};
        if (checkPossible(whitePieces, blackPieces, newPos, color, attack)[0] && checkPossible(whitePieces, blackPieces, newPos, color, attack)[1]) {
            possibleMoves.emplace_back(newPos); 
        } else if (checkPossible(whitePieces, blackPieces, newPos, color, attack)[0] && !(checkPossible(whitePieces, blackPieces, newPos, color, attack)[1])) {
            possibleMoves.emplace_back(newPos); 
            break;
        } else if (!(checkPossible(whitePieces, blackPieces, newPos, color, attack)[0]) && !(checkPossible(whitePieces, blackPieces, newPos, color, attack)[1])) {
            break;
        }
    }

    // down and left moves
    for (int row = rpos+1, cols = cpos-1; row <= 7 && cols >= 0; row++, cols--) {
        Pos newPos = {row, cols};
        if (checkPossible(whitePieces, blackPieces, newPos, color, attack)[0] && checkPossible(whitePieces, blackPieces, newPos, color, attack)[1]) {
            possibleMoves.emplace_back(newPos); 
        } else if (checkPossible(whitePieces, blackPieces, newPos, color, attack)[0] && !(checkPossible(whitePieces, blackPieces, newPos, color, attack)[1])) {
            possibleMoves.emplace_back(newPos); 
            break;
        } else if (!(checkPossible(whitePieces, blackPieces, newPos, color, attack)[0]) && !(checkPossible(whitePieces, blackPieces, newPos, color, attack)[1])) {
            break;
        }
    }

    // up and right moves
    for (int row = rpos-1, cols = cpos+1; row >= 0 && cols <= 7; row--, cols++) {
        Pos newPos = {row, cols};
        if (checkPossible(whitePieces, blackPieces, newPos, color, attack)[0] && checkPossible(whitePieces, blackPieces, newPos, color, attack)[1]) {
            possibleMoves.emplace_back(newPos); 
        } else if (checkPossible(whitePieces, blackPieces, newPos, color, attack)[0] && !(checkPossible(whitePieces, blackPieces, newPos, color, attack)[1])) {
            possibleMoves.emplace_back(newPos); 
            break;
        } else if (!(checkPossible(whitePieces, blackPieces, newPos, color, attack)[0]) && !(checkPossible(whitePieces, blackPieces, newPos, color, attack)[1])) {
            break;
        }
    }
    // return all possible moves
    return possibleMoves; 
}
