#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <vector>
#include "observer.h"

class Piece;

class TextDisplay: public Observer {
    // private fields
    std::vector<std::vector<char>> theDisplay;
    const int boardSize = 8;
 public:
    TextDisplay(bool pieces); // ctor
    void notify(const Pos& start, const Pos& end, char symbol) override;
    ~TextDisplay(); // dtor
    // overloaded operator
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
