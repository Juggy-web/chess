#include <iostream>
#include "textdisplay.h"

using namespace std;

// Constructs a new textDisplay of size 8x8 (values ranging from 0,0 to 8,8)
TextDisplay::TextDisplay(bool pieces) {
    // adding all pieces in positions
    for(int r = 0; r < boardSize; r++) {
        vector<char> row;
        for(int c = 0; c < boardSize; c++) {
            if (pieces) {
                if(r == 0) {
                    if (c == 0 || c == 7) {
                        row.emplace_back('r');
                    } else if (c == 1 || c == 6) {
                        row.emplace_back('n');
                    } else if (c == 2 || c == 5) {
                        row.emplace_back('b');
                    } else if (c == 3) {
                        row.emplace_back('q');
                    } else if (c == 4) {
                        row.emplace_back('k');
                    }
                } else if (r == 1) {
                    row.emplace_back('p');
                } else if (r == 6) {
                    row.emplace_back('P');
                } else if (r == 7) {
                    if (c == 0 || c == 7) {
                        row.emplace_back('R');
                    } else if (c == 1 || c == 6) {
                        row.emplace_back('N');
                    } else if (c == 2 || c == 5) {
                        row.emplace_back('B');
                    } else if (c == 3) {
                        row.emplace_back('Q');
                    } else if (c == 4) {
                        row.emplace_back('K');
                    }
                } else if ((r%2 == 0 && c%2 == 0) || (r%2 != 0 && c%2 != 0)) {
                    row.emplace_back(' ');
                } else {
                    row.emplace_back('_');
                }    
            } else if ((r%2 == 0 && c%2 == 0) || (r%2 != 0 && c%2 != 0)) {
                row.emplace_back(' ');
            } else {
                row.emplace_back('_');
            }    
        }
        theDisplay.emplace_back(row);
    }
}

// Updates the textDisplay object
void TextDisplay::notify(const Pos& start, const Pos& end, char symbol) {
    char startEmpty, endSym;
    endSym = symbol;
    if(endSym == '_') {
        if((end.r%2 == 0 && end.c%2 == 0) || (end.r%2 != 0 && end.c%2 != 0)) {
            endSym = ' ';
        }
    }
    if((start.r%2 == 0 && start.c%2 == 0) || (start.r%2 != 0 && start.c%2 != 0)) {
        startEmpty = ' ';
    } else {
        startEmpty = '_';
    }
    theDisplay[start.r][start.c] = startEmpty; // The spot where the piece moved from becomes empty
    theDisplay[end.r][end.c] = endSym; // The spot where the piece ended up is refrshed
    
}

// Deletes a TextDisplay
TextDisplay::~TextDisplay() {}

// Outputs a textDisplay to a given ostream
ostream &operator<<(ostream &out, const TextDisplay &td) {
  int rowNum = 8;
  for(int r = 0; r < td.boardSize; r++) {
    out << rowNum-r << " ";
    for (int c = 0; c < td.boardSize; c++) {
      out << td.theDisplay[r][c];
    }
    out << endl;
  }
  char letter = 'a';
  out << endl << "  ";
  for(int i = 0; i < td.boardSize; i++) {
    out << static_cast<char>(letter+i);
  }
  return out;
}
