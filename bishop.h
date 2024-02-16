#ifndef __BISHOP_H__
#define __BISHOP_H__

#include <iostream>
#include <map>
#include <memory>
#include "piece.h"

using namespace std;

class Bishop : public Piece {
    public:
        // ctor
        Bishop(int value, char type, Pos location); 
        // returns a clone of piece
        unique_ptr<Piece> clone() const override;
        // returns a vector of possible ending positions of the board
        vector<Pos> canMoveTo(const vector<unique_ptr<Piece>> &  whitePieces, const vector<unique_ptr<Piece>> &  blackPieces, bool attack) override; // Determines all the possible end locations for a given piece based on it's behevaior 
};

#endif
