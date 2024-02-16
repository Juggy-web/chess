#include <vector>
#include <iostream>
#include <map>
#include <sstream>
#include "human.h"
#include "convertor.h"

// returns move specified by user
std::vector<Pos> Human::getMove(const std::map<Pos,std::vector<Pos>> & whiteMoves, const std::map<Pos,std::vector<Pos>> & blackMoves, bool whiteTurn, const std::map<Pos,std::vector<Pos>> & whiteAttackMoves, const std::map<Pos,std::vector<Pos>> & blackAttackMoves, const std::vector<unique_ptr<Piece>> & whitePieces, const std::vector<unique_ptr<Piece>> & blackPieces, const std::map<Pos,std::vector<Pos>> & whiteChecks, const std::map<Pos,std::vector<Pos>> & blackChecks) const {

    // initalize variables and get input
    std::string startingLocation;
    std::string endingLocation;
    Convertor convert; 

    std::vector<Pos> loco; 
    
    // store 2 locations
    cin >> startingLocation >> endingLocation; 

    // store move
    loco.emplace_back(convert.stringToPos(startingLocation));
    loco.emplace_back(convert.stringToPos(endingLocation));

    return loco;

}   

char Human::getPromotion(bool whiteTurn) const {
    char newPiece;

    while (cin >> newPiece) {

        if (whiteTurn) { // ensure legal white piece

            if (newPiece == 'Q' || newPiece == 'N' || newPiece == 'R' || newPiece == 'B') {
                
                return newPiece;

            } else { // if piece is not valid

                cout << "Enter a valid piece for pawn promotion!" << endl;

            }

        } else { // ensure legal black piece

            if (newPiece == 'q' || newPiece == 'n' || newPiece == 'r' || newPiece == 'b') {

                return newPiece;

            } else { // if piece is not valid

                cout << "Enter a valid piece for pawn promotion!" << endl;

            }

        }
        
    } 
    // return newPiece;
}
