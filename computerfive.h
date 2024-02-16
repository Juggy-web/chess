#ifndef _COMPUTERFIVE_H_
#define _COMPUTERFIVE_H_
#include <vector>
#include <string>
#include <map>
#include "player.h"

class ComputerFive : public Player {
  int getValue(const Pos & position, const std::vector<unique_ptr<Piece>> & pieces) const; 
 public:
  // returns best attacking or evading move based on piece values
  vector<Pos> getMove(const map<Pos,vector<Pos>> & whiteMoves, const map<Pos,vector<Pos>> & blackMoves, bool whiteTurn, const std::map<Pos,std::vector<Pos>> & whiteAttackMoves, const std::map<Pos,std::vector<Pos>> & blackAttackMoves, const std::vector<unique_ptr<Piece>> & whitePieces, const std::vector<unique_ptr<Piece>> & blackPieces, const std::map<Pos,std::vector<Pos>> & whiteChecks, const std::map<Pos,std::vector<Pos>> & blackChecks) const override;
  // return random piece for pawn promotion
  char getPromotion(bool whiteTurn) const override;
};

#endif
