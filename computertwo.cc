#include <vector>
#include <iostream>
#include <map>
#include <cstdlib>
#include <ctime>
#include "computertwo.h"
#include "computerone.h"

std::vector<Pos> ComputerTwo::getMove(const std::map<Pos,std::vector<Pos>> & whiteMoves, const std::map<Pos,std::vector<Pos>> & blackMoves, bool whiteTurn, const std::map<Pos, std::vector<Pos>> & whiteAttackMoves, const std::map<Pos, std::vector<Pos>> & blackAttackMoves, const std::vector<unique_ptr<Piece>> & whitePieces, const std::vector<unique_ptr<Piece>> & blackPieces, const std::map<Pos,std::vector<Pos>> & whiteChecks, const std::map<Pos,std::vector<Pos>> & blackChecks) const {

    ComputerOne compOne {}; 

    std::vector<Pos> loco; 
    // white color
    if (whiteTurn) {

        std::map<Pos,std::vector<Pos>> whiteAttackMovesFiltered; 
        std::map<Pos,std::vector<Pos>> whiteChecksFiltered; 
        
        // seed random number
        std::srand(static_cast<unsigned int>(std::time(nullptr)));   
        // get legal attack moves
        for (auto& i : whiteAttackMoves) {

            if (!(i.second.empty())) {

                whiteAttackMovesFiltered.insert({i.first, i.second}); 

            }

        }
        // get legal check moves
        for (auto& i : whiteChecks) {

            if (!(i.second.empty())) {

                whiteChecksFiltered.insert({i.first, i.second}); 

            }

        }
        // if attack moves are available 
        if (!whiteAttackMovesFiltered.empty()) {

            int movesLen = whiteAttackMovesFiltered.size(); 
            //  get random attack move
            int randomMapIndex = std::rand() % movesLen;
            int counter = 0; 
            
            for (auto& p : whiteAttackMovesFiltered) {

                if (counter == randomMapIndex) {
                    
                    if (p.second.empty()) {

                        break;

                    }
                    // store random attack move
                    int vectorLen = p.second.size(); 
                    int randomVectorIndex = std::rand() % vectorLen;

                    loco.emplace_back(p.first);  
                    loco.emplace_back(p.second.at(randomVectorIndex));  
                    break; 

                }

                counter++; 

            }

        }

        // if no capturing moves then look for checks
        if (loco.empty() && !whiteChecksFiltered.empty()) {

            int randomCheckIndex = std::rand() % whiteChecksFiltered.size();
            int counter = 0; 

            for (auto& i : whiteChecksFiltered) {

                if (counter == randomCheckIndex) {

                    if (i.second.empty()) {

                        break;

                    }
                    // store random check move
                    int vectorLen = i.second.size(); 
                    int randomVectorIndex = std::rand() % vectorLen;

                    loco.emplace_back(i.first);  
                    loco.emplace_back(i.second.at(randomVectorIndex));  
                    break; 

                }

                counter++; 

            }

        }
        // if no attack move is found 
        if (loco.empty()) { 

            return compOne.getMove(whiteMoves, blackMoves, whiteTurn, whiteAttackMoves, blackAttackMoves, whitePieces, blackPieces, whiteChecks, blackChecks); 

        } else {
        
            return loco;

        }

    } else { // black color

        std::map<Pos,std::vector<Pos>> blackAttackMovesFiltered; 
        std::map<Pos,std::vector<Pos>> blackChecksFiltered; 
        
        // seed random number
        std::srand(static_cast<unsigned int>(std::time(nullptr)));   
        // get legal attack moves
        for (auto& i : blackAttackMoves) {

            if (!(i.second.empty())) {

                blackAttackMovesFiltered.insert({i.first, i.second}); 

            }

        }
        // get legal check moves
        for (auto& i : blackChecks) {

            if (!(i.second.empty())) {

                blackChecksFiltered.insert({i.first, i.second}); 

            }

        }

        // if attack moves are available 
        if (!blackAttackMovesFiltered.empty()) {

            int movesLen = blackAttackMovesFiltered.size(); 

            int randomMapIndex = std::rand() % movesLen;
            int counter = 0; 

            for (auto& p : blackAttackMovesFiltered) {

                if (counter == randomMapIndex) {

                    if (p.second.empty()) {

                        break;

                    }

                    int vectorLen = p.second.size(); 
                    int randomVectorIndex = std::rand() % vectorLen;
                    // store random attack move
                    loco.emplace_back(p.first);  
                    loco.emplace_back(p.second.at(randomVectorIndex));  
                    break; 

                }

                counter++; 

            }

        }

        // if no capturing moves then look for checks
        if (loco.empty() && !blackChecksFiltered.empty()) {

            int randomCheckIndex = std::rand() % blackChecksFiltered.size();
            int counter = 0; 

            for (auto& i : blackChecksFiltered) {

                if (counter == randomCheckIndex) {

                    if (i.second.empty()) {

                        break;

                    }
                    // store random check move
                    int vectorLen = i.second.size(); 
                    int randomVectorIndex = std::rand() % vectorLen;

                    loco.emplace_back(i.first);  
                    loco.emplace_back(i.second.at(randomVectorIndex));  
                    break; 

                }

                counter++; 

            }

        }

        // if no attack move is found
        if (loco.empty()) { 

            return compOne.getMove(whiteMoves, blackMoves, whiteTurn, whiteAttackMoves, blackAttackMoves, whitePieces, blackPieces, whiteChecks, blackChecks); 

        } else {
        
            return loco;

        }

    }
}   

// return random piece for pawn promotion
char ComputerTwo::getPromotion(bool whiteTurn) const {

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
