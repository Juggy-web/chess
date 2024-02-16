#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <vector>
#include <map>
#include "position.h"
#include "piece.h"

using namespace std; 

class Player {
 public:
  // returns legal move 
  virtual vector<Pos> getMove(const map<Pos,vector<Pos>> & whiteMoves, const map<Pos,vector<Pos>> & blackMoves, bool whiteTurn, const std::map<Pos,std::vector<Pos>> & whiteAttackMoves, const std::map<Pos,std::vector<Pos>> & blackAttackMoves, const std::vector<unique_ptr<Piece>> & whitePieces, const std::vector<unique_ptr<Piece>> & blackPieces, const std::map<Pos,std::vector<Pos>> & whiteChecks, const std::map<Pos,std::vector<Pos>> & blackChecks) const = 0;
  // returns piece for pawn promotion 
  virtual char getPromotion(bool whiteTurn) const = 0;
  // Virtual destructor
  virtual ~Player();  
};

#endif
