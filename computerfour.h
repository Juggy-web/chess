#ifndef _COMPUTERFOUR_H_
#define _COMPUTERFOUR_H_
#include <vector>
#include <string>
#include <map>
#include "player.h"

class ComputerFour : public Player {
  // return value corresponding to specific piece
  int getValue (const Pos & position, const std::vector<unique_ptr<Piece>> & pieces) const;
  // return best attacking move based on value 
  std::vector<Pos> getBestAttackMove(const std::map<Pos,std::vector<Pos>> & attackMoves, const std::vector<unique_ptr<Piece>> & oppositePieces) const; 
 public:
  // returns best attacking or evading move based on piece values
  vector<Pos> getMove(const map<Pos,vector<Pos>> & whiteMoves, const map<Pos,vector<Pos>> & blackMoves, bool whiteTurn, const std::map<Pos,std::vector<Pos>> & whiteAttackMoves, const std::map<Pos,std::vector<Pos>> & blackAttackMoves, const std::vector<unique_ptr<Piece>> & whitePieces, const std::vector<unique_ptr<Piece>> & blackPieces, const std::map<Pos,std::vector<Pos>> & whiteChecks, const std::map<Pos,std::vector<Pos>> & blackChecks) const override;
  // return random piece for pawn promotion
  char getPromotion(bool whiteTurn) const override;
};

#endif
