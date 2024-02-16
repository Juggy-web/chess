#include <iostream>
#include <map>
#include "piece.h"


using namespace std;

    // Basic piece constructor
    Piece::Piece(int value, char type, Pos location): value{value}, type{type}, location{location}, firstMove{true}, enPassant{false} {}

    // Virtual piece destructor
    Piece::~Piece() {}

    // Returns the symbol repersenting the piece type
    char Piece::getType() const {
        return type;
    }

    // Sets the type of a piece
    void Piece::setType(char newType){
        type = newType;
    }

    // Returns true if a piece is on the white team, false otherwise
    bool Piece::isWhite() const {
        if(type >= 'a') {
            return false;
        } else {
            return true;
        }
    }

    // Sets the position of a piece
    void Piece::setLocation(int r, int c) {
        location.r = r;
        location.c = c;
    }

    // Returns the position of a piece
    Pos Piece::getLocation() const {
        return location;
    }

    // Returns the int value of a given piece
    int Piece::getValue() const {
        return value;
    }

    // Sets the int value of a given piece
    void Piece::setValue(int newValue) {
        value = newValue;
    }

    // Returns the value of firstMove
    bool Piece::getFirstMove() const {
        return firstMove;
    }

    // Sets the value of first move
    void Piece::setFirstMove() {
        firstMove = false;
    } 

    // Checks if it's possible to go to given square
    vector<bool> Piece::checkPossible(const vector<unique_ptr<Piece>>& whitePieces, const vector<unique_ptr<Piece>>& blackPieces, const Pos& currPos, const bool color, bool attack) const {
        vector<bool> ret;
        for (int i = 0; i < whitePieces.size(); i++) {
            if (whitePieces.at(i)->getLocation() == currPos) {
                if (color) {
                    ret.emplace_back(false);
                    ret.emplace_back(false);
                    return ret;
                } else {
                    ret.emplace_back(true);
                    ret.emplace_back(false);
                    return ret;
                }
            }
        }
        for (int i = 0; i < blackPieces.size(); i++) {
            if (blackPieces.at(i)->getLocation() == currPos) {
                if (!color) {
                    ret.emplace_back(false);
                    ret.emplace_back(false);
                    return ret;
                } else {
                    ret.emplace_back(true);
                    ret.emplace_back(false);
                    return ret;
                }
            }   
        }

        if (attack) {
            ret.emplace_back(false);
            ret.emplace_back(true);
            return ret;
        }

        ret.emplace_back(true);
        ret.emplace_back(true);
        return ret;
        
    }

    // Returns the value of enPassant
    bool Piece::getEnPassant() {
        return enPassant;
    } 

    // Changes the value of enPassant
    bool Piece::setEnPassant(bool val) { // Default behavior for changing enPassant value of a piece
        enPassant = false;
    }

    // Overloaded output operator for piece
    ostream& operator<<(ostream& out, const Piece& p) {
        return out << p.type;
    }
    
