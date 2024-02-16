#ifndef _COMPUTERTWO_H_
#define _COMPUTERTWO_H_
#include <vector>
#include <string>
#include <map>
#include "player.h"

class ComputerTwo : public Player {
  // Pos getKing (const std::vector<unique_ptr<Piece>> & pieces, bool isWhite) const; 
 public:
  // returns attacking move, and if none is found then random move
  vector<Pos> getMove(const map<Pos,vector<Pos>> & whiteMoves, const map<Pos,vector<Pos>> & blackMoves, bool whiteTurn, const std::map<Pos,std::vector<Pos>> & whiteAttackMoves, const std::map<Pos,std::vector<Pos>> & blackAttackMoves, const std::vector<unique_ptr<Piece>> & whitePieces, const std::vector<unique_ptr<Piece>> & blackPieces, const std::map<Pos,std::vector<Pos>> & whiteChecks, const std::map<Pos,std::vector<Pos>> & blackChecks) const override;
  // return random piece for pawn promotion
  char getPromotion(bool whiteTurn) const override;
};

#endif
