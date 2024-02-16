#include <iostream>
#include <map>
#include "piece.h"
#include "rook.h"
#include "position.h"
// Rook constructor
Rook::Rook(int value, char type, Pos location): Piece{value, type, location} {}
// Clones a rook piece
unique_ptr<Piece> Rook::clone() const {
    return make_unique<Rook>(*this);
}
// Determines all the possible end locations for a given piece based on it's behevaior 
vector<Pos> Rook::canMoveTo(const vector<unique_ptr<Piece>> &  whitePieces, const vector<unique_ptr<Piece>> &  blackPieces, bool attack) {
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
    // return moves
    return possibleMoves; 

}
