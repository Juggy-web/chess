#include <iostream>
#include <map>
#include "piece.h"
#include "queen.h"
#include "position.h"

// ctor
Queen::Queen(int value, char type, Pos location): Piece{value, type, location} {}
// Clones a queen piece
unique_ptr<Piece> Queen::clone() const {
    return make_unique<Queen>(*this);
}
// Determines all the possible end locations for a given queen based on it's behevaior 
vector<Pos> Queen::canMoveTo(const vector<unique_ptr<Piece>> &  whitePieces, const vector<unique_ptr<Piece>> &  blackPieces, bool attack) {
    // set location 
    int rpos = getLocation().r;
    int cpos = getLocation().c;
    bool color = isWhite();
    vector<Pos> possibleMoves; 

    // down
    for (int row = rpos+1; row <= 7; row++) {
        Pos newPos = {row, cpos};
        if (checkPossible(whitePieces, blackPieces, newPos, color, attack)[0] && checkPossible(whitePieces, blackPieces, newPos, color, attack)[1]) {
            possibleMoves.emplace_back(newPos); 
        } else if (checkPossible(whitePieces, blackPieces, newPos, color, attack)[0] && !(checkPossible(whitePieces, blackPieces, newPos, color, attack)[1])) {
            possibleMoves.emplace_back(newPos); 
            break;
        } else if (!(checkPossible(whitePieces, blackPieces, newPos, color, attack)[0]) && !(checkPossible(whitePieces, blackPieces, newPos, color, attack)[1])) {
            break;
        }
    }

    // up
    for (int row = rpos-1; row >= 0; row--) {
        Pos newPos = {row, cpos};
        if (checkPossible(whitePieces, blackPieces, newPos, color, attack)[0] && checkPossible(whitePieces, blackPieces, newPos, color, attack)[1]) {
            possibleMoves.emplace_back(newPos); 
        } else if (checkPossible(whitePieces, blackPieces, newPos, color, attack)[0] && !(checkPossible(whitePieces, blackPieces, newPos, color, attack)[1])) {
            possibleMoves.emplace_back(newPos); 
            break;
        } else if (!(checkPossible(whitePieces, blackPieces, newPos, color, attack)[0]) && !(checkPossible(whitePieces, blackPieces, newPos, color, attack)[1])) {
            break;
        }
    }

    // right
    for (int cols = cpos+1; cols <= 7; cols++) {
        Pos newPos = {rpos, cols};
        if (checkPossible(whitePieces, blackPieces, newPos, color, attack)[0] && checkPossible(whitePieces, blackPieces, newPos, color, attack)[1]) {
            possibleMoves.emplace_back(newPos); 
        } else if (checkPossible(whitePieces, blackPieces, newPos, color, attack)[0] && !(checkPossible(whitePieces, blackPieces, newPos, color, attack)[1])) {
            possibleMoves.emplace_back(newPos); 
            break;
        } else if (!(checkPossible(whitePieces, blackPieces, newPos, color, attack)[0]) && !(checkPossible(whitePieces, blackPieces, newPos, color, attack)[1])) {
            break;
        }
    }

    // left
    for (int cols = cpos-1; cols >= 0; cols--) {
        Pos newPos = {rpos, cols};
        if (checkPossible(whitePieces, blackPieces, newPos, color, attack)[0] && checkPossible(whitePieces, blackPieces, newPos, color, attack)[1]) {
            possibleMoves.emplace_back(newPos); 
        } else if (checkPossible(whitePieces, blackPieces, newPos, color, attack)[0] && !(checkPossible(whitePieces, blackPieces, newPos, color, attack)[1])) {
            possibleMoves.emplace_back(newPos); 
            break;
        } else if (!(checkPossible(whitePieces, blackPieces, newPos, color, attack)[0]) && !(checkPossible(whitePieces, blackPieces, newPos, color, attack)[1])) {
            break;
        }
    }

    // down and right
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

    // up and left 
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

    // down and left
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

    // up and right 
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

    // return moves
    return possibleMoves; 

}
