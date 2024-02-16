#include <vector>
#include <iostream>
#include <map>
#include <cstdlib>
#include <ctime>
#include "computerthree.h"
#include "computerone.h"
#include "computertwo.h"

std::vector<Pos> ComputerThree::getMove(const std::map<Pos,std::vector<Pos>> & whiteMoves, const std::map<Pos,std::vector<Pos>> & blackMoves, bool whiteTurn, const std::map<Pos, std::vector<Pos>> & whiteAttackMoves, const std::map<Pos, std::vector<Pos>> & blackAttackMoves, const std::vector<unique_ptr<Piece>> & whitePieces, const std::vector<unique_ptr<Piece>> & blackPieces, const std::map<Pos,std::vector<Pos>> & whiteChecks, const std::map<Pos,std::vector<Pos>> & blackChecks) const {

    ComputerOne compOne {}; 
    ComputerTwo compTwo {}; 

    std::vector<Pos> loco; 

    // white color
    if (whiteTurn) {
        // get random attacking move from black team
        std::vector<Pos> blackAttackLoco = compTwo.getMove(whiteMoves, blackMoves, whiteTurn, whiteAttackMoves, blackAttackMoves, whitePieces, blackPieces, whiteChecks, blackChecks); 

        int movesLen = whiteMoves.size(); 
    
        // seed random number
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
            // go through white moves
            for (auto& p : whiteMoves) {
                // find targetted white piece
                if (p.first == blackAttackLoco.at(1)) {
                    // if targetted piece has no legal moves
                    if (p.second.empty()) {

                        break;

                    }

                    int vectorLen = p.second.size(); 
                    int randomVectorIndex = std::rand() % vectorLen;
                    // move targetted white piece to random location 
                    loco.emplace_back(p.first);  
                    loco.emplace_back(p.second.at(randomVectorIndex));  

                    break; 

                }

            }
        // if no evading move is found then look for attacking move
        if (loco.empty()) {

            return compTwo.getMove(whiteMoves, blackMoves, whiteTurn, whiteAttackMoves, blackAttackMoves, whitePieces, blackPieces, whiteChecks, blackChecks);

        } else {

            return loco; 

        }

    } else { // black color
        // get random white attacking move
        std::vector<Pos> whiteAttackLoco = compTwo.getMove(whiteMoves, blackMoves, whiteTurn, whiteAttackMoves, blackAttackMoves, whitePieces, blackPieces, whiteChecks, blackChecks); 

        int movesLen = blackMoves.size(); 
    
        // seed random number generator 
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
            // go through white moves
            for (auto& p : blackMoves) {
                // find targetted black piece
                if (p.first == whiteAttackLoco.at(1)) {

                    if (p.second.empty()) {

                        break;

                    }

                    int vectorLen = p.second.size(); 
                    int randomVectorIndex = std::rand() % vectorLen;
                    // move targetted black piece to random location 
                    loco.emplace_back(p.first);  
                    loco.emplace_back(p.second.at(randomVectorIndex));  

                    break; 

                }

            }
        // if no evading move is found
        if (loco.empty()) {

            return compTwo.getMove(whiteMoves, blackMoves, whiteTurn, whiteAttackMoves, blackAttackMoves, whitePieces, blackPieces, whiteChecks, blackChecks);

        } else {

            return loco; 

        }

    }

}   

// return random piece for pawn promotion
char ComputerThree::getPromotion(bool whiteTurn) const {

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
