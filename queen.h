#ifndef __QUEEN_H__
#define __QUEEN_H__

#include <iostream>
#include <map>
#include <memory>
#include "piece.h"

using namespace std;

class Queen : public Piece {
    public:
        Queen(int value, char type, Pos location); // Queen constructor
        unique_ptr<Piece> clone() const override; // Clones a queen piece
        vector<Pos> canMoveTo(const vector<unique_ptr<Piece>> &  whitePieces, const vector<unique_ptr<Piece>> &  blackPieces, bool attack) override; // Determines all the possible end locations for a given queen based on it's behevaior 
};

#endif
