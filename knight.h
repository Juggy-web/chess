#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include <iostream>
#include <map>
#include <memory>
#include "piece.h"

using namespace std;

class Knight: public Piece {
    public:
        Knight(int value, char type, Pos location); // Knight constructor
        unique_ptr<Piece> clone() const override; // returns clone of piece
        vector<Pos> canMoveTo(const vector<unique_ptr<Piece>> &  whitePieces, const vector<unique_ptr<Piece>> &  blackPieces, bool attack) override; // Determines all the possible end locations for a given piece based on it's behevaior 
};

#endif
