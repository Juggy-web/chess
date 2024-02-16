#ifndef __BOARD_H__
#define __BOARD_H__

#include "position.h"
#include "piece.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"

#include "knight.h"
#include "pawn.h"
#include "bishop.h"
#include "rook.h"
#include "queen.h"
#include "king.h"
#include <vector>
#include <map>
#include <memory>

using namespace std;

class Board {
    bool castleRight = false; // Indicates if a move castles right
    bool castleLeft = false; // Indicates if a move castles left
    bool whiteTurn = true; // True if white turn, false if black turn
    bool enPassantMove = false; // Indicates if a move is an enpassant
    bool setUpCalled = false; // Indicates if board has been manipulated with setup 
    Pos enPassantPos; // Records the pos of a move captured by enPassant
    Pos castlePos; // Records the pos of a rook involved in a castle move
    vector<unique_ptr<Piece>> whitePieces; // Holds pointers to all current white pieces
    vector<unique_ptr<Piece>> blackPieces; // Holds pointers to all current black pieces
    map<Pos,vector<Pos>> nextWhiteMoves; // Map associating white current positions with a vector of all their legal end positions
    map<Pos,vector<Pos>> nextBlackMoves; // Map associating black current positions with a vector of all their legal end positions
    map<Pos,vector<Pos>> nextWhiteAttacks; // Map associating white current positions with a vector of all their legal attack move end positions
    map<Pos,vector<Pos>> nextBlackAttacks; // Map associating black current positions with a vector of all their legal attack move end positions
    map<Pos,vector<Pos>> nextWhiteChecks; // Map associating white current positions with a vector end positions of all their legal moves which will put black in check
    map<Pos,vector<Pos>> nextBlackChecks; // Map associating black current positions with a vector end positions of all their legal moves which will put white in check
    vector<vector<unique_ptr<Piece>>> pastWhiteStates; // Vector of past states of the white pieces
    vector<vector<unique_ptr<Piece>>> pastBlackStates; // Vector of past states of the black pieces
    unique_ptr<TextDisplay> td; // Pointer to textDisplay
    unique_ptr<GraphicsDisplay> gd; // Pointer to graphicsDisplay

 public:
    Board(); // Board Constructor
    ~Board(); // Board Destructor

    void clear(); // Clear all pieces from board
    void init(Xwindow& xw, bool pieces); // Initialize board in starting position
    King& getKing(bool isWhite); // Returns a reference to the king of an indicated team
    bool isCheck(const Piece& p); // Check if a given king is in check
    bool isStalemate(bool whiteTurn); // Check if board is in stalemate
    bool getTurn() const; // Returns who's turn it is, true for white, false for black
    void setTurn(bool whiteTurn); // Sets which player plays next
    void storeCurState(); // Stores the current state of the board
    void allNextMoves(bool isWhite); // Updates white/black nextMoves and white/back nextAttacks with all possible end positions according to peice behaviors
    void updateNextMoves(bool isWhite); // Updates white/black nextMoves and white/back nextAttacks with all legal end positions according to peice behaviors and isCheck()
    void updateChecks(bool isWhite); // Updates white/black nextChecks with all legal end positions according to peice behaviors and isCheck()
    bool tryMove(Pos start, Pos end); // Attemps a move from start to end
    void undoMove(); // Reverts the state of the board to undo a move
    map<Pos,vector<Pos>> getNextMoves(bool isWhite); // Returns a given team's nextMoves
    map<Pos,vector<Pos>> getNextAttacks(bool isWhite); // Returns a given team's nextAttacks
    map<Pos,vector<Pos>> getNextChecks(bool isWhite); // Returns a given team's nextChecks
    bool isCapture(Pos start, Pos end); // Determines if a move from start to end is a capture
    bool isCastling(bool isWhite, Pos start, Pos end); // Determines if a move from start to end is a castling move
    void doMove(Pos start, Pos end); // Performs a move from start to end
    bool isCheckmate(const Piece& p); // Check if a given king is in checkmate
    void removePiece(const Pos posToRemove); // Removes a piece at posToRemove from the board or does nothing if the position is empty
    void addPiece(const Pos posToAdd, char symbol); // Adds a piece of type symbol to posToAdd on the board
    bool setUpConditions(); // Checks if set up conditions are satisfied
    char pieceAtLocation(Pos end, bool isWhite); // Returns the symbol of a piece at a given location
    void setSetup(); // Sets setUpCalled to true
    bool getSetup() const; // Returns the value of setUpCalled
    vector<unique_ptr<Piece>>& getPieces(bool white); // Returns a reference to the vector of piece pointers for white or black team
    friend std::ostream &operator<<(std::ostream &out, const Board &b); // Output operator for a board 
};

#endif
