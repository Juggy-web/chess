#ifndef _HUMAN_H_
#define _HUMAN_H_
#include <vector>
#include <map>
#include <string>
#include "player.h"

class Human : public Player {
 public:
  // returns move specified by user
  vector<Pos> getMove(const map<Pos,vector<Pos>> & whiteMoves, const map<Pos,vector<Pos>> & blackMoves, bool whiteTurn, const std::map<Pos,std::vector<Pos>> & whiteAttackMoves, const std::map<Pos,std::vector<Pos>> & blackAttackMoves, const std::vector<unique_ptr<Piece>> & whitePieces, const std::vector<unique_ptr<Piece>> & blackPieces, const std::map<Pos,std::vector<Pos>> & whiteChecks, const std::map<Pos,std::vector<Pos>> & blackChecks) const override;
  // return piece speciefied by user for pawn promotion
  char getPromotion(bool whiteTurn) const override;
};

#endif
