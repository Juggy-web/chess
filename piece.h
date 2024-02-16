#ifndef __PIECE_H__
#define __PIECE_H__

#include <vector>
#include <map>
#include <iostream>
#include "position.h"
#include <memory>

using namespace std;

class Piece {
    protected:
        int value; // Integer value of a piece
        char type; // Type of piece (i.e K, k , Q, q ...)
        Pos location; // Current location of the piece
        bool firstMove; // True if the piece has not made it's first move, false otherwise
        bool enPassant; // If a piece can enPassant
    public:
        Piece(int value, char type, Pos location); // Basic piece constructor
        virtual ~Piece(); // Virtual piece destructor
        virtual unique_ptr<Piece> clone() const = 0;
        char getType() const; // Returns the symbol repersenting the piece type
        void setType(char newType); // Sets the type of a piece
        bool isWhite() const; // Returns true if a piece is on the white team, false otherwise
        void setLocation(int r, int c); // Sets the position of a piece
        Pos getLocation() const; // Returns the position of a piece
        int getValue() const; // Returns the int value of a given piece
        void setValue(int newValue); // Sets the int value of a given piece
        bool getFirstMove() const; // Returns the value of firstMove
        void setFirstMove(); // Sets the value of first move
        bool getEnPassant(); // Returns the value of enPassant
        virtual bool setEnPassant(bool val); // Changes the value of enPassant
        virtual vector<Pos> canMoveTo(const vector<unique_ptr<Piece>> & whitePieces, const vector<unique_ptr<Piece>> & blackPieces, bool attack) = 0; // Determines all the possible end locations for a given piece based on it's behevaior 
        vector<bool> checkPossible(const vector<unique_ptr<Piece>>& whitePieces, const vector<unique_ptr<Piece>>& blackPieces, const Pos& currPos, const bool color, bool attack) const; // Checks if it's possible to go to given square
        friend ostream& operator<<(ostream&, const Piece& p); // Overloaded output operator for piece
};

#endif
