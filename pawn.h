#ifndef __PAWN_H__
#define __PAWN_H__

#include <iostream>
#include <memory>
#include <map>
#include "piece.h"

using namespace std;

class Pawn: public Piece {
    public:
        Pawn(int value, char type, Pos location); // Pawn constructor
        unique_ptr<Piece> clone() const override; // returns clone of piece 
        bool setEnPassant(bool val) override; // Changes the value of enPassant
        vector<Pos> canMoveTo(const vector<unique_ptr<Piece>> &  whitePieces, const vector<unique_ptr<Piece>> &  blackPieces, bool attack) override; // Determines all the possible end locations for a given piece based on it's behevaior 
};

#endif
