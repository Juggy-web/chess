#include <cstdlib>
#include <ctime>
#include <memory>
#include "computerfour.h"
#include "computerfive.h"
#include "piece.h"

using namespace std;

map<Pos, vector<Pos>> getMatches(map<Pos, vector<Pos>> attackMoves, map<Pos, vector<Pos>> checkMoves) {
    map<Pos, vector<Pos>> matches;
    for (auto& i : attackMoves) {
        for (auto& j : checkMoves) {
            if (i.first == j.first) {
                vector<Pos> ends;
                for (auto& k : i.second) {
                    for (auto& l : j.second) {
                        if (k == l) {
                            ends.emplace_back(k);
                        }
                    }
                }
                matches.emplace(i.first, ends);
            }
        }
    }

    return matches; 

}

vector<Pos> ComputerFive::getMove(const map<Pos,vector<Pos>> & whiteMoves, const map<Pos,vector<Pos>> & blackMoves, bool whiteTurn, const std::map<Pos,std::vector<Pos>> & whiteAttackMoves, const std::map<Pos,std::vector<Pos>> & blackAttackMoves, const std::vector<unique_ptr<Piece>> & whitePieces, const std::vector<unique_ptr<Piece>> & blackPieces, const std::map<Pos,std::vector<Pos>> & whiteChecks, const std::map<Pos,std::vector<Pos>> & blackChecks) const {

    ComputerFour compFour {}; 

    vector<Pos> loco; 

    if (whiteTurn) {

        map<Pos, vector<Pos>> matches = getMatches(whiteAttackMoves, whiteChecks); 
        
        if (!matches.empty()) {

        int maxValue = 0; 

        for (auto& i : matches) {

            for (auto& j : i.second) {
                // store highest value capturing move 
                if (getValue(j, blackPieces) > maxValue) {

                    maxValue = getValue(j, blackPieces); 

                    if (!loco.empty()) {

                        loco.clear(); 

                    }

                    loco.emplace_back(i.first);
                    loco.emplace_back(j);

                }

            }

        }

        }

    } else {

        map<Pos, vector<Pos>> matches = getMatches(blackAttackMoves, blackChecks); 
        
        if (!matches.empty()) {

            int maxValue = 0; 

            for (auto& i : matches) {

                for (auto& j : i.second) {
                    // store highest value capturing move 
                    if (getValue(j, whitePieces) > maxValue) {

                        maxValue = getValue(j, whitePieces); 

                        if (!loco.empty()) {

                            loco.clear(); 

                        }

                        loco.emplace_back(i.first);
                        loco.emplace_back(j);

                    }

                }

            }

        }

    }

    if (loco.empty()) {

        return compFour.getMove(whiteMoves, blackMoves, whiteTurn, whiteAttackMoves, blackAttackMoves, whitePieces, blackPieces, whiteChecks, blackChecks);

    } else {

        return loco; 

    }

}

// return random piece for pawn promotion
char ComputerFive::getPromotion(bool whiteTurn) const {

    if (whiteTurn) {
        return 'Q';
    } else {
        return 'q';
    }

}

int ComputerFive::getValue (const Pos & position, const std::vector<unique_ptr<Piece>> & pieces) const {

    for (auto& i : pieces) {

        if (position == i->getLocation()) {

            return i->getValue(); 

        }

    }
        return 0;

}
