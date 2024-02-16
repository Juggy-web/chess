#include <iostream>
#include <map>
#include <vector>
#include "knight.h"

using namespace std;

// Knight constructor
Knight::Knight(int value, char type, Pos location): Piece{value, type, location} {}
// returns clone of piece
unique_ptr<Piece> Knight::clone() const {
    return make_unique<Knight>(*this);
}
// Determines all the possible end locations for a given piece based on it's behevaior 
vector<Pos> Knight::canMoveTo(const vector<unique_ptr<Piece>> &  whitePieces, const vector<unique_ptr<Piece>> &  blackPieces, bool attack) {
    // calculate all possible positions
    vector<Pos> results;
    vector<bool> attacks;
    for(int i = 0; i < 8; i++) {
        attacks.emplace_back(false);
    }
    Pos tempPos = location;
    tempPos.r+=2;
    tempPos.c++;
    results.emplace_back(tempPos);
    tempPos = location;
    tempPos.r+=2;
    tempPos.c--;
    results.emplace_back(tempPos);
    tempPos = location;
    tempPos.r++;
    tempPos.c+=2;
    results.emplace_back(tempPos);
    tempPos = location;
    tempPos.r++;
    tempPos.c-=2;
    results.emplace_back(tempPos);
    tempPos = location;
    tempPos.r-=2;
    tempPos.c++;
    results.emplace_back(tempPos);
    tempPos = location;
    tempPos.r-=2;
    tempPos.c--;
    results.emplace_back(tempPos);
    tempPos = location;
    tempPos.r--;
    tempPos.c+=2;
    results.emplace_back(tempPos);
    tempPos = location;
    tempPos.r--;
    tempPos.c-=2;
    results.emplace_back(tempPos);
    // if knight is white
    if(isWhite()) {
        // check if position is empty
        for (int i = 0; i < whitePieces.size(); i++) { 
            for(int x = 0; x < results.size(); x++) {
                if(results[x] == whitePieces[i]->getLocation()) {
                    results[x].r = -1;
                    results[x].c = -1;
                }
            }
        }
        // get attack moves
        if(attack) {
            for (int i = 0; i < blackPieces.size(); i++) { 
                for(int x = 0; x < results.size(); x++) {
                    if(results[x] == blackPieces[i]->getLocation()) {
                        attacks[x] = true;
                    }
                }
            }
            

            for(int i = 0; i < results.size(); i++) {
                if(!attacks[i]) {
                    results[i].r = -1;
                    results[i].c = -1;
                }
            }
        }
        
    } else { // black knight
        for (int i = 0; i < blackPieces.size(); i++) { 
            for(int x = 0; x < results.size(); x++) {
                if(results[x] == blackPieces[i]->getLocation()) {
                    results[x].r = -1;
                    results[x].c = -1;
                }
            }
        }
        // get attack moves
        if(attack) {
            for (int i = 0; i < whitePieces.size(); i++) { 
                for(int x = 0; x < results.size(); x++) {
                    if(results[x] == whitePieces[i]->getLocation()) {
                        attacks[x] = true;
                    }
                }
            }

            for(int i = 0; i < results.size(); i++) {
                if(!attacks[i]) {
                    results[i].r = -1;
                    results[i].c = -1;
                }
            }
        }
    }
    // return valid moves
    vector<Pos> validMoves;
    for(int i = 0; i < results.size(); i++) {
        if(results[i].r >= 0 && results[i].c >= 0 && results[i].r <= 7 && results[i].c <= 7) {
            validMoves.emplace_back(results[i]);
        }
    }
    
    return validMoves;

}
