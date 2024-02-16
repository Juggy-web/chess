#ifndef __DISPLAYMOVES_H__
#define __DISPLAYMOVES_H__
#include "position.h"
#include "convertor.h"
#include <vector>
#include <map>
#include <iostream>
#include <string>

using namespace std;

class DisplayMoves final {
    Convertor c;
    public:
    // prints list of all moves
    void print(const map<Pos,vector<Pos>> & moves);
};

#endif
