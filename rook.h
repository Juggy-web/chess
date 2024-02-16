#ifndef __ROOK_H__
#define __ROOK_H__

#include <iostream>
#include <map>
#include <memory>
#include "piece.h"

using namespace std;

class Rook : public Piece {
    public:
        Rook(int value, char type, Pos location); // Rook constructor
        unique_ptr<Piece> clone() const override; // Clones a rook piece
        vector<Pos> canMoveTo(const vector<unique_ptr<Piece>> &  whitePieces, const vector<unique_ptr<Piece>> &  blackPieces, bool attack) override; // Determines all the possible end locations for a given piece based on it's behevaior 
};

#endif
