#include <vector>
#include <iostream>
#include <map>
#include <cstdlib>
#include <ctime>
#include <memory>
#include "computerfour.h"
#include "computertwo.h"
#include "piece.h"

// returns best attacking or evading move based on piece values
std::vector<Pos> ComputerFour::getMove(const std::map<Pos,std::vector<Pos>> & whiteMoves, const std::map<Pos,std::vector<Pos>> & blackMoves, bool whiteTurn, const std::map<Pos,std::vector<Pos>> & whiteAttackMoves, const std::map<Pos, std::vector<Pos>> & blackAttackMoves, const std::vector<unique_ptr<Piece>> & whitePieces, const std::vector<unique_ptr<Piece>> & blackPieces, const std::map<Pos,std::vector<Pos>> & whiteChecks, const std::map<Pos,std::vector<Pos>> & blackChecks) const {

    ComputerTwo compTwo {}; 

    std::vector<Pos> loco; 
    // check color
    if (whiteTurn) {

        std::vector<Pos> attack = getBestAttackMove(whiteAttackMoves, blackPieces); 
        // if there is a possible attack move
        if (!attack.empty()) {

            return attack; 

        } else { // otherwise look to evade
            // get opponent's best attack move
            std::vector<Pos> bestOppAttack = getBestAttackMove(blackAttackMoves, whitePieces); 
            // if opponent has attack move
            if (!bestOppAttack.empty()) {

                std::srand(static_cast<unsigned int>(std::time(nullptr)));
                // randomly move targetted piece
                for (auto& p : whiteMoves) {

                    if (p.first == bestOppAttack.at(1)) {

                        if (p.second.empty()) {

                            break;

                        }

                        int vectorLen = p.second.size(); 
                        int randomVectorIndex = std::rand() % vectorLen;

                        loco.emplace_back(p.first);  
                        loco.emplace_back(p.second.at(randomVectorIndex));  

                        break; 

                    }
                }
            } 
        }
        // if no attack or evade moves are available 
        if (loco.empty()) {

            return compTwo.getMove(whiteMoves, blackMoves, whiteTurn, whiteAttackMoves, blackAttackMoves, whitePieces, blackPieces, whiteChecks, blackChecks);

        } else {

            return loco; 

        }

    } else { // black color
        
        std::vector<Pos> attack = getBestAttackMove(blackAttackMoves, whitePieces); 

        if (!attack.empty()) {

            return attack; 

        } else { // otherwise look to evade
            // get opponent's best attack move
            std::vector<Pos> bestOppAttack = getBestAttackMove(whiteAttackMoves, blackPieces); 
            // if there is a possible attack move
            if (!bestOppAttack.empty()) {

                std::srand(static_cast<unsigned int>(std::time(nullptr)));
            
                for (auto& p : blackMoves) {
                    // move targetted piece randomly 
                    if (p.first == bestOppAttack.at(1)) {

                        if (p.second.empty()) {

                            break;

                        }

                        int vectorLen = p.second.size(); 
                        int randomVectorIndex = std::rand() % vectorLen;

                        loco.emplace_back(p.first);  
                        loco.emplace_back(p.second.at(randomVectorIndex));  

                        break; 

                    }

                }
            } 
        }
        // if no attacking moves or evading moves are found 
        if (loco.empty()) {

            return compTwo.getMove(whiteMoves, blackMoves, whiteTurn, whiteAttackMoves, blackAttackMoves, whitePieces, blackPieces, whiteChecks, blackChecks);

        } else {

            return loco; 

        }

    }

}

// return random piece for pawn promotion
char ComputerFour::getPromotion(bool whiteTurn) const {

    if (whiteTurn) {
        return 'Q';
    } else {
        return 'q';
    }

}

// return value corresponding to specific piece 
int ComputerFour::getValue (const Pos & position, const std::vector<unique_ptr<Piece>> & pieces) const {

    for (auto& i : pieces) {

        if (position == i->getLocation()) {

            return i->getValue(); 

        }

    }

}

// return best attacking move based on value 
std::vector<Pos> ComputerFour::getBestAttackMove(const std::map<Pos,std::vector<Pos>> & attackMoves, const std::vector<unique_ptr<Piece>> & oppositePieces) const {

    std::map<Pos,std::vector<Pos>> attackMovesFiltered;
    std::vector<Pos> loco = {}; 
    
    // look through attacking moves and get all that capture
    for (auto& i : attackMoves) {

        if (!(i.second.empty())) {

            attackMovesFiltered.insert({i.first, i.second}); 

        }

    }
    // if capturing move is found
    if (!attackMovesFiltered.empty()) {

        int maxValue = 0; 

        for (auto& i : attackMovesFiltered) {

            for (auto& j : i.second) {
                // store highest value capturing move 
                if (getValue(j, oppositePieces) > maxValue) {

                    maxValue = getValue(j, oppositePieces); 

                    if (!loco.empty()) {

                        loco.clear(); 

                    }

                    loco.emplace_back(i.first);
                    loco.emplace_back(j);

                }

            }

        }

    }
    // return attacking move or blank vector corresponding to no capturing moves found 
    return loco; 

}
