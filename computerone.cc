#include <vector>
#include <iostream>
#include <map>
#include <cstdlib>
#include <ctime>
#include "computerone.h"

// return random move
std::vector<Pos> ComputerOne::getMove(const std::map<Pos,std::vector<Pos>> & whiteMoves, const std::map<Pos,std::vector<Pos>> & blackMoves, bool whiteTurn, const std::map<Pos,std::vector<Pos>> & whiteAttackMoves, const std::map<Pos,std::vector<Pos>> & blackAttackMoves, const std::vector<unique_ptr<Piece>> & whitePieces, const std::vector<unique_ptr<Piece>> & blackPieces, const std::map<Pos,std::vector<Pos>> & whiteChecks, const std::map<Pos,std::vector<Pos>> & blackChecks) const {

    std::vector<Pos> loco; 

    // seed random number
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // white color
    if (whiteTurn) {

        int movesLen = whiteMoves.size(); 
        bool foundNonEmpty = false; 

    // keep going until piece with a legal move is found
    while (!foundNonEmpty) {
        // generate random number
        int counter = 0; 
        int randomMapIndex = std::rand() % movesLen; 
        // go through white moves
        for (auto& p : whiteMoves) {
            // if random index is found
            if (counter == randomMapIndex) {
                // if no legal moves
                if (p.second.empty()) {

                    break;

                }

                int vectorLen = p.second.size(); 
                int randomVectorIndex = std::rand() % vectorLen;
                // store move
                loco.emplace_back(p.first);  
                loco.emplace_back(p.second.at(randomVectorIndex)); 
                foundNonEmpty = true;  

                break; 

            }

            counter++; 

        }

    }

    } else { // black color
        
        int movesLen = blackMoves.size(); 
        bool foundNonEmpty = false; 
        // keep going until piece with a legal move is found
        while (!foundNonEmpty) {
        // generate random number
        int counter = 0; 
        int randomMapIndex = std::rand() % movesLen; 
        // go through black moves
        for (auto& p : blackMoves) {
            // if random index is found
            if (counter == randomMapIndex) {
                // if no legal moves
                if (p.second.empty()) {

                    break;

                }

                int vectorLen = p.second.size(); 
                int randomVectorIndex = std::rand() % vectorLen;
                // store move
                loco.emplace_back(p.first);  
                loco.emplace_back(p.second.at(randomVectorIndex)); 
                foundNonEmpty = true;  

                break; 

            }

            counter++; 

        }

    }

    }
    
    // return move
    return loco;
 
}   

// return random piece for pawn promotion
char ComputerOne::getPromotion(bool whiteTurn) const {

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::vector<char> whitePieces = {'R', 'N', 'B', 'Q'}; 
    std::vector<char> blackPieces = {'r', 'n', 'b', 'q'};  

    int random = std::rand() % whitePieces.size(); 

    if (whiteTurn) {
        return whitePieces.at(random);
    } else {
        return blackPieces.at(random);
    }

}
