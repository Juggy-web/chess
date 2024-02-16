#ifndef __KING_H__
#define __KING_H__

#include <iostream>
#include <map>
#include <memory>
#include "piece.h"

using namespace std;

class King : public Piece {
    // private fields for king special cases
    bool castling; 
    bool isCheck; 
    public:
        // ctor
        King(int value, char type, Pos location); 
        // returns clone of piece
        unique_ptr<Piece> clone() const override;
        // returns a vector of possible ending positions of the board
        vector<Pos> canMoveTo(const vector<unique_ptr<Piece>> &  whitePieces, const vector<unique_ptr<Piece>> &  blackPieces, bool attack) override;
 
};

#endif
