#include "board.h"
#include <memory>

using namespace std;

// Board Constructor
Board::Board() {}

// Board Destructor
Board::~Board() {
}

// Clear all pieces from board
void Board::clear() {
    whitePieces.clear();
    blackPieces.clear();
    nextWhiteMoves.clear();
    nextBlackMoves.clear();
}

// Initialize board in starting position
void Board::init(Xwindow& xw, bool pieces) {
    bool castle = true;
    bool whiteTurn = true;
    
    if (pieces) {
        td = make_unique<TextDisplay>(true);
        gd = make_unique<GraphicsDisplay>(xw, true);
        Pos r1p{0,0};
        auto r1 = make_unique<Rook>(5,'r',r1p);
        blackPieces.emplace_back(move(r1));

        Pos n1p{0,1};
        auto n1 = make_unique<Knight>(3,'n',n1p);
        blackPieces.emplace_back(move(n1));

        Pos b1p{0,2};
        auto b1 = make_unique<Bishop>(3,'b',b1p);
        blackPieces.emplace_back(move(b1));

        Pos qp{0,3};
        auto q = make_unique<Queen>(9,'q',qp);
        blackPieces.emplace_back(move(q));

        Pos kp{0,4};
        auto k = make_unique<King>(-1,'k',kp);
        blackPieces.emplace_back(move(k));

        Pos b2p{0,5};
        auto b2 = make_unique<Bishop>(3,'b',b2p);
        blackPieces.emplace_back(move(b2));

        Pos n2p{0,6};
        auto n2 = make_unique<Knight>(3,'n',n2p);
        blackPieces.emplace_back(move(n2));

        Pos r2p{0,7};
        auto r2 = make_unique<Rook>(5,'r',r2p);
        blackPieces.emplace_back(move(r2));

        for (int i = 0; i < 8; ++i) {
            Pos pp{1,i};
            auto p = make_unique<Pawn>(1,'p',pp);
            blackPieces.emplace_back(move(p));
        }

        for (int i = 0; i < 8; ++i) {
            Pos pp{6,i};
            auto P = make_unique<Pawn>(1,'P',pp);
            whitePieces.emplace_back(move(P));
        }

        Pos R1p{7,0};
        auto R1 = make_unique<Rook>(5,'R',R1p);
        whitePieces.emplace_back(move(R1));

        Pos N1p{7,1};
        auto N1 = make_unique<Knight>(3,'N',N1p);
        whitePieces.emplace_back(move(N1));

        Pos B1p{7,2};
        auto B1 = make_unique<Bishop>(3,'B',B1p);
        whitePieces.emplace_back(move(B1));

        Pos Qp{7,3};
        auto Q = make_unique<Queen>(9,'Q',Qp);
        whitePieces.emplace_back(move(Q));

        Pos Kp{7,4};
        auto K = make_unique<King>(-1,'K',Kp);
        whitePieces.emplace_back(move(K));

        Pos B2p{7,5};
        auto B2 = make_unique<Bishop>(3,'B',B2p);
        whitePieces.emplace_back(move(B2));

        Pos N2p{7,6};
        auto N2 = make_unique<Knight>(3,'N',N2p);
        whitePieces.emplace_back(move(N2));

        Pos R2p{7,7};
        auto R2 = make_unique<Rook>(5,'R',R2p);
        whitePieces.emplace_back(move(R2));
    } else {
        td = make_unique<TextDisplay>(false);
        gd = make_unique<GraphicsDisplay>(xw, false);
    }
}

// Returns a reference to the king of an indicated team
King& Board::getKing(bool isWhite) {
    if (isWhite) {
        for (auto & i : whitePieces) {
            if (i->getType() == 'K') {
                return dynamic_cast<King&>(*i);
            }
        }
    } else {
        for (auto & i : blackPieces) {
            if (i->getType() == 'k') {
                return dynamic_cast<King&>(*i);
            }
        }
    }
}

// Check if a given king is in check
bool Board::isCheck(const Piece& p) {
    Pos l = p.getLocation();
    if (p.isWhite()) {
        allNextMoves(false);
        for (const auto &i:nextBlackMoves) {
            for (const auto &j : i.second) {
                if (j == l) {
                    return true;
                }
            }
        }
        return false;
    } else {
        allNextMoves(true);
        for (const auto &i:nextWhiteMoves) {
            for (const auto &j : i.second) {
                if (j == l) {
                    return true;
                }
            }
        }
        return false;
    }
}

// Check if board is in stalemate
bool Board::isStalemate(bool whiteTurn) {
    if (whiteTurn) {
        updateNextMoves(whiteTurn);
        for (auto& i:nextWhiteMoves) {
            if (!i.second.empty()) {
                return false;
            }
        }
        return true;
    } else {
        updateNextMoves(whiteTurn);
        for (auto& i:nextBlackMoves) {
            if (!i.second.empty()) {
                return false;
            }
        }
        return true;
    }
}

// Returns who's turn it is, true for white, false for black
bool Board::getTurn() const {
    return whiteTurn;
}

// Sets which player plays next
void Board::setTurn(bool newTurn) {
    whiteTurn = newTurn;
}

// Stores the current state of the board
void Board::storeCurState() {
    vector<unique_ptr<Piece>> tempWhitePieces;
    vector<unique_ptr<Piece>> tempBlackPieces;
    for(int i = 0; i < whitePieces.size(); i++) {
        tempWhitePieces.push_back(whitePieces[i]->clone());
    }
    for(int i = 0; i < blackPieces.size(); i++) {
        tempBlackPieces.push_back(blackPieces[i]->clone());
    }
    pastWhiteStates.emplace_back(move(tempWhitePieces));
    pastBlackStates.emplace_back(move(tempBlackPieces));
}

// Updates white/black nextMoves and white/back nextAttacks with all possible end positions according to peice behaviors
void Board::allNextMoves(bool isWhite) {
    if (isWhite) {
        nextWhiteMoves.clear();
        for (int i = 0; i < whitePieces.size(); ++i) {
            nextWhiteMoves.insert({whitePieces[i]->getLocation(), whitePieces[i]->canMoveTo(whitePieces, blackPieces, false)});
        }
        nextWhiteAttacks.clear();
        for (int i = 0; i < whitePieces.size(); ++i) {
            nextWhiteAttacks.insert({whitePieces[i]->getLocation(), whitePieces[i]->canMoveTo(whitePieces, blackPieces, true)});
        }
    } else {
        nextBlackMoves.clear();
        for (int i = 0; i < blackPieces.size(); ++i) {
            nextBlackMoves.insert({blackPieces[i]->getLocation(), blackPieces[i]->canMoveTo(whitePieces, blackPieces, false)});
        }
        nextBlackAttacks.clear();
        for (int i = 0; i < blackPieces.size(); ++i) {
            nextBlackAttacks.insert({blackPieces[i]->getLocation(), blackPieces[i]->canMoveTo(whitePieces, blackPieces, true)});
        }
    }
}

// Updates white/black nextMoves and white/back nextAttacks with all legal end positions according to peice behaviors and isCheck()
void Board::updateNextMoves(bool isWhite) {
    if (isWhite) {
        allNextMoves(isWhite);
        for (auto& i:nextWhiteMoves) {
            if (!i.second.empty()) {
                for (auto it = i.second.begin(); it != i.second.end();) {
                    storeCurState();
                    doMove(i.first,*it);
                    allNextMoves(!isWhite);
                    if (isCheck(getKing(true))) {
                        it = i.second.erase(it);
                    } else {
                        ++it;
                    }
                    undoMove();
                }
            }
        }
        //King Castling
        if(!setUpCalled) {
            for (auto& i:nextWhiteMoves) {
                Pos whiteKingPos = {7,4};
                if (i.first == whiteKingPos && getKing(true).getFirstMove()) {
                    bool left = false;
                    bool right = false;
                    if (!i.second.empty()) {
                        for (int j = 0; j < i.second.size(); j++) {
                            Pos leftCastleMid = {7,3};
                            Pos rightCastleMid = {7,5};
                            if (i.second[j] == leftCastleMid) {
                                left = true;
                            } else if (i.second[j] == rightCastleMid) {
                                right = true;
                            }
                        }
                        if (!left) {
                            Pos leftCastleEnd = {7,2};
                            for (auto it = i.second.begin(); it != i.second.end();++it) {
                                if (*it == leftCastleEnd) {
                                    it = i.second.erase(it);
                                    break;
                                }
                            }
                        } if (!right) {
                            Pos rightCastleEnd = {7,6};
                            for (auto it = i.second.begin(); it != i.second.end();++it) {
                                if (*it == rightCastleEnd) {
                                    it = i.second.erase(it);
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    
        for (auto& i:nextWhiteAttacks) {
            if (!i.second.empty()) {
                for (auto it = i.second.begin(); it != i.second.end();) {
                    storeCurState();
                    doMove(i.first,*it);
                    if (isCheck(getKing(true))) {
                        it = i.second.erase(it);
                    } else {
                        ++it;
                    }
                    undoMove();
                }
            }
        }
    } else {
        allNextMoves(isWhite);
        for (auto& i:nextBlackMoves) {
            if (!i.second.empty()) {
                for (auto it = i.second.begin(); it != i.second.end();) {
                    storeCurState();
                    doMove(i.first,*it);
                    allNextMoves(!isWhite);
                    if (isCheck(getKing(false))) {
                        it = i.second.erase(it);
                    } else {
                        ++it;
                    }
                    undoMove();
                }
            }
        }

        //King Castling
        if(!setUpCalled) {
            for (auto& i:nextBlackMoves) {
                Pos blackKingPos = {0,4};
                if (i.first == blackKingPos && getKing(false).getFirstMove()) {
                    bool left = false;
                    bool right = false;
                    if (!i.second.empty()) {
                        for (int j = 0; j < i.second.size(); j++) {
                            Pos leftCastleMid = {0,3};
                            Pos rightCastleMid = {0,5};
                            if (i.second[j] == leftCastleMid) {
                                left = true;
                            } else if (i.second[j] == rightCastleMid) {
                                right = true;
                            }
                        }
                        if (!left) {
                            Pos leftCastleEnd = {0,2};
                            for (auto it = i.second.begin(); it != i.second.end();++it) {
                                if (*it == leftCastleEnd) {
                                    it = i.second.erase(it);
                                    break;
                                }
                            }
                        } if (!right) {
                            Pos rightCastleEnd = {0,6};
                            for (auto it = i.second.begin(); it != i.second.end();++it) {
                                if (*it == rightCastleEnd) {
                                    it = i.second.erase(it);
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    

        for (auto& i:nextBlackAttacks) {
            if (!i.second.empty()) {
                for (auto it = i.second.begin(); it != i.second.end();) {
                    storeCurState();
                    doMove(i.first,*it);
                    if (isCheck(getKing(false))) {
                        it = i.second.erase(it);
                    } else {
                        ++it;
                    }
                    undoMove();
                }
            }
        }
    }
}

// Updates white/black nextChecks with all legal end positions according to peice behaviors and isCheck()
void Board::updateChecks(bool isWhite) {
    if(isWhite) {
        nextWhiteChecks.clear();
        for (int i = 0; i < whitePieces.size(); ++i) {
            nextWhiteChecks.insert({whitePieces[i]->getLocation(), whitePieces[i]->canMoveTo(whitePieces, blackPieces, false)});
        }
        for (auto& i:nextWhiteChecks) {
            if (!i.second.empty()) {
                for (auto it = i.second.begin(); it != i.second.end();) {
                    storeCurState();
                    doMove(i.first,*it);
                    if (isCheck(getKing(true))) {
                        it = i.second.erase(it);
                    } else {
                        ++it;
                    }
                    undoMove();
                }
            }
        }
    } else {
        nextBlackChecks.clear();
        for (int i = 0; i < blackPieces.size(); ++i) {
            nextBlackChecks.insert({blackPieces[i]->getLocation(), blackPieces[i]->canMoveTo(whitePieces, blackPieces, false)});
        }
        for (auto& i:nextBlackChecks) {
            if (!i.second.empty()) {
                for (auto it = i.second.begin(); it != i.second.end();) {
                    storeCurState();
                    doMove(i.first,*it);
                    if (isCheck(getKing(false))) {
                        it = i.second.erase(it);
                    } else {
                        ++it;
                    }
                    undoMove();
                }
            }
        }
    }
}

// Attemps a move from start to end
bool Board::tryMove(Pos start, Pos end) {
    bool validStart = false;
    bool validEnd = false;
    char c;
    if (whiteTurn) {
        for (int i = 0; i < whitePieces.size(); ++i) {
            if (start == whitePieces[i]->getLocation()) {
                validStart = true;
                c = whitePieces[i]->getType();
                break;
            }
        }
        if (!validStart) {
            return false;
        }
        for (const auto&i : nextWhiteMoves.at(start)) {
            if (i == end) {
                validEnd = true;
                break;
            }
        }
        if (!validEnd) {
            return false;
        }
    } else {
        for (int i = 0; i < blackPieces.size(); ++i) {
            if (start == blackPieces[i]->getLocation()) {
                validStart = true;
                c = blackPieces[i]->getType();
                break;
            }
        }
        if (!validStart) {
            return false;
        }
        for (const auto&i : nextBlackMoves.at(start)) {
            if (i == end) {
                validEnd = true;
                break;
            }
        }
        if (!validEnd) {
            return false;
        }
    }
    doMove(start,end);
    td->notify(start, end, c);
    gd->notify(start,end,c);
    if(enPassantMove) {
        td->notify(enPassantPos, enPassantPos, '_');
        gd->notify(enPassantPos, enPassantPos, '_');
        enPassantMove = false;
    }
    Pos rookTo;
    Pos rookFrom;
    if(castleLeft && whiteTurn) {
        rookTo.r = 7;
        rookTo.c = 3;
        rookFrom.r = 7;
        rookFrom.c = 0;
        td->notify(rookFrom, rookFrom, '_');
        gd->notify(rookFrom, rookFrom, '_');
        td->notify(rookTo, rookTo, 'R');
        gd->notify(rookTo, rookTo, 'R');
        castleLeft = false;
    } else if (castleLeft && !whiteTurn) {
        rookTo.r = 0;
        rookTo.c = 3;
        rookFrom.r = 0;
        rookFrom.c = 0;
        td->notify(rookFrom, rookFrom, '_');
        gd->notify(rookFrom, rookFrom, '_');
        td->notify(rookTo, rookTo, 'r');
        gd->notify(rookTo, rookTo, 'r');
        castleLeft = false;
    } else if (castleRight && whiteTurn) {
        rookTo.r = 7;
        rookTo.c = 5;
        rookFrom.r = 7;
        rookFrom.c = 7;
        td->notify(rookFrom, rookFrom, '_');
        gd->notify(rookFrom, rookFrom, '_');
        td->notify(rookTo, rookTo, 'R');
        gd->notify(rookTo, rookTo, 'R');
        castleRight = false;
    } else if (castleRight && !whiteTurn) {
        rookTo.r = 0;
        rookTo.c = 5;
        rookFrom.r = 0;
        rookFrom.c = 7;
        td->notify(rookFrom, rookFrom, '_');
        gd->notify(rookFrom, rookFrom, '_');
        td->notify(rookTo, rookTo, 'r');
        gd->notify(rookTo, rookTo, 'r');
        castleRight = false;
    }
    updateNextMoves(whiteTurn);
    updateNextMoves(!whiteTurn);
    return true;
}

// Reverts the state of the board to undo a move
void Board::undoMove() {
    castleLeft = false;
    castleRight = false;
    enPassantMove = false;
    if (!pastWhiteStates.empty()) {
        whitePieces = move(pastWhiteStates[(pastWhiteStates.size()-1)]);
        pastWhiteStates.pop_back();
    }
    if (!pastBlackStates.empty()) {
        blackPieces = move(pastBlackStates[(pastBlackStates.size()-1)]);
        pastBlackStates.pop_back();
    }
}

// Returns a given team's nextMoves
map<Pos,vector<Pos>> Board::getNextMoves(bool isWhite) {
    updateNextMoves(isWhite);
    if (isWhite) { 
        return nextWhiteMoves;
    } else {
        return nextBlackMoves;
    }
}

// Returns a given team's nextAttacks
map<Pos,vector<Pos>> Board::getNextAttacks(bool isWhite) {
    updateNextMoves(isWhite); 
    if (isWhite) {
        return nextWhiteAttacks;
    } else {
        return nextBlackAttacks;
    }
}

// Returns a given team's nextChecks
map<Pos,vector<Pos>> Board::getNextChecks(bool isWhite) {
    updateNextMoves(isWhite);
    updateChecks(isWhite);
    if(isWhite) {
        for (auto& i:nextWhiteChecks) {
            if (!i.second.empty()) {
                for (auto it = i.second.begin(); it != i.second.end();) {
                    storeCurState();
                    doMove(i.first,*it);
                    updateNextMoves(true);
                    if (isCheck(getKing(false))) {
                        ++it;
                    } else {
                        it = i.second.erase(it);
                    }
                    undoMove();
                }
            }
        }
        return nextWhiteChecks;
    } else {
        for (auto& i:nextBlackChecks) {
            if (!i.second.empty()) {
                for (auto it = i.second.begin(); it != i.second.end();) {
                    storeCurState();
                    doMove(i.first,*it);
                    updateNextMoves(false);
                    if (isCheck(getKing(true))) {
                        ++it;
                    } else {
                        it = i.second.erase(it);
                    }
                    undoMove();
                }
            }
        }
        return nextBlackChecks;
    }
 }

// Determines if a move from start to end is a capture
bool Board::isCapture(Pos start, Pos end) {
    if (whiteTurn) {
        for (const auto& i:nextWhiteAttacks) {
            if (i.first == start) {
                for (const auto& j:i.second) {
                    if (j == end) {
                        return true;
                    }
                }
            }
        }
        return false;
    } else {
        for (const auto& i:nextBlackAttacks) {
            if (i.first == start) {
                for (const auto& j:i.second) {
                    if (j == end) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
}

// Determines if a move from start to end is a castling move
bool Board::isCastling(bool isWhite, Pos start, Pos end) {
    if(isWhite) {
        if (getKing(true).getFirstMove() && getKing(true).getLocation() == start) {
            if((start.c - end.c) == 2) {
                castleLeft = true;
                return true;
            } else if((start.c - end.c) == -2) {
                castleRight = true;
                return true;
            }
        }
    } else {
        if (getKing(false).getFirstMove() && getKing(false).getLocation() == start) {
            if((start.c - end.c) == 2) {
                castleLeft = true;
                return true;
            } else if((start.c - end.c) == -2) {
                castleRight = true;
                return true;
            }
        }
    }
    return false;
}

// Performs a move from start to end
void Board::doMove(Pos start, Pos end) {
    bool captured = false;
    if (whiteTurn) {
        for (auto it = blackPieces.begin(); it != blackPieces.end(); ++it) {
            if ((*it)->getLocation() == end) {
                blackPieces.erase(it);
                captured = true;
                break;
            }
        }
        if(!setUpCalled) { // Enpassant and castling only if setup has not been called
            if (!captured) {
                if (isCapture(start,end)) {
                    for (auto it = blackPieces.begin(); it != blackPieces.end(); ++it) {
                        Pos p{start.r,end.c};
                        enPassantPos = p;
                        enPassantMove = true;
                        if ((*it)->getLocation() == p) {
                            blackPieces.erase(it);
                            break;
                        }
                    }
                }
            }
        
            if(isCastling(true, start, end)) {
                Pos rookPos;
                Pos rookEnd;
                rookPos.r = 7;
                rookEnd.r = 7;
                if(castleLeft) {
                    rookPos.c = 0;
                    rookEnd.c = 3;
                } else {
                    rookPos.c = 7;
                    rookEnd.c = 5;
                }
                for (const auto & i:whitePieces) {
                    if (i->getLocation() == rookPos) {
                        i->setFirstMove();
                        i->setLocation(rookEnd.r, rookEnd.c);
                        break;
                    }
                }
            }
        }

        for (const auto & i:whitePieces) {
            if (i->getLocation() == start) {
                if(!setUpCalled) {
                    if(i->getEnPassant()) {
                    i->setEnPassant(false);
                    }
                    if(i->getFirstMove() && (end.c == start.c) && ((start.r - end.r) == 2)) {
                        i->setEnPassant(true);
                    }
                }
                i->setFirstMove();
                i->setLocation(end.r, end.c);
                break;
            }
        }
        
    } else {
        for (auto it = whitePieces.begin(); it != whitePieces.end(); ++it) {
            if ((*it)->getLocation() == end) {
                whitePieces.erase(it);
                captured = true;
                break;
            }
        }
        if(!setUpCalled) {
            if (!captured) {
                if (isCapture(start,end)) {
                    for (auto it = whitePieces.begin(); it != whitePieces.end(); ++it) {
                        Pos p{start.r,end.c};
                        enPassantPos = p;
                        enPassantMove = true;
                        if ((*it)->getLocation() == p) {
                            whitePieces.erase(it);
                            break;
                        }
                    }
                }
            }
            if(isCastling(false, start, end)) {
                Pos rookPos;
                Pos rookEnd;
                rookPos.r = 0;
                rookEnd.r = 0;
                if(castleLeft) {
                    rookPos.c = 0;
                    rookEnd.c = 3;
                } else {
                    rookPos.c = 7;
                    rookEnd.c = 5;
                }
                for (const auto & i:blackPieces) {
                    if (i->getLocation() == rookPos) {
                        i->setFirstMove();
                        i->setLocation(rookEnd.r, rookEnd.c);
                        break;
                    }
                }
            }
        }
        for (auto const& i:blackPieces) {
            if (i->getLocation() == start) {
                if(!setUpCalled) {
                    if(i->getEnPassant()) {
                    i->setEnPassant(false);
                    }
                    if(i->getFirstMove() && (end.c == start.c) && ((end.r - start.r) == 2)) {
                    i->setEnPassant(true);
                    }
                }
                i->setFirstMove();
                i->setLocation(end.r, end.c);
                break;
            }
        }     
    }
}

// Check if a given king is in checkmate
bool Board::isCheckmate(const Piece & p) {
    if(p.isWhite()) {
        setTurn(!whiteTurn);
        updateNextMoves(true);
        setTurn(!whiteTurn);
        for (const auto& i:nextWhiteMoves) {
            if ((i.second).size() > 0) {
                return false;
            }
        }
    } else {
        setTurn(!whiteTurn);
        updateNextMoves(false);
        setTurn(!whiteTurn);
        for (const auto& i:nextBlackMoves) {
            if ((i.second).size() > 0) {
                return false;
            }
        }
    }
    return true;
}

// Removes a piece at posToRemove from the board or does nothing if the position is empty
void Board::removePiece(const Pos posToRemove) { 
    for (auto it = blackPieces.begin(); it != blackPieces.end(); ++it) {
            if ((*it)->getLocation() == posToRemove) {
                blackPieces.erase(it);
                td->notify(posToRemove, posToRemove, '_');
                gd->notify(posToRemove, posToRemove, '_');
                break;
            }
    }
    for (auto it = whitePieces.begin(); it != whitePieces.end(); ++it) {
            if ((*it)->getLocation() == posToRemove) {
                whitePieces.erase(it);
                td->notify(posToRemove, posToRemove, '_');
                gd->notify(posToRemove, posToRemove, '_');
                break;
            }
    }
}

// Adds a piece of type symbol to posToAdd on the board
 void Board::addPiece(const Pos posToAdd, char symbol) {
    removePiece(posToAdd);
        if(symbol == 'K') {
            auto K = make_unique<King>(-1,'K',posToAdd);
            whitePieces.emplace_back(move(K));
        } else if (symbol == 'R') {
            auto R = make_unique<Rook>(5,'R',posToAdd);
            whitePieces.emplace_back(move(R));
        } else if (symbol == 'Q') {
            auto Q = make_unique<Queen>(9,'Q',posToAdd);
            whitePieces.emplace_back(move(Q));
        } else if (symbol == 'N') {
            auto N = make_unique<Knight>(3,'N',posToAdd);
            whitePieces.emplace_back(move(N));
        } else if (symbol == 'B') {
            auto B = make_unique<Bishop>(3,'B',posToAdd);
            whitePieces.emplace_back(move(B));
        } else if (symbol == 'P') {
            auto P = make_unique<Pawn>(1,'P',posToAdd);
            whitePieces.emplace_back(move(P));
        } else if(symbol == 'k') {
            auto k = make_unique<King>(-1,'k',posToAdd);
            blackPieces.emplace_back(move(k));
        } else if (symbol == 'r') {
            auto r = make_unique<Rook>(5,'r',posToAdd);
            blackPieces.emplace_back(move(r));
        } else if (symbol == 'q') {
            auto q = make_unique<Queen>(9,'q',posToAdd);
            blackPieces.emplace_back(move(q));
        } else if (symbol == 'n') {
            auto n = make_unique<Knight>(3,'n',posToAdd);
            blackPieces.emplace_back(move(n));
        } else if (symbol == 'b') {
            auto b = make_unique<Bishop>(3,'b',posToAdd);
            blackPieces.emplace_back(move(b));
        } else if (symbol == 'p') {
            auto p = make_unique<Pawn>(1,'p',posToAdd);
            blackPieces.emplace_back(move(p));
        }
        td->notify(posToAdd, posToAdd, symbol);
        gd->notify(posToAdd, posToAdd, symbol);

    for(auto & i:whitePieces) {
        if(i->getType() == 'K') {
            i->setFirstMove();
        }
    }
    for(auto & i:blackPieces) {
        if(i->getType() == 'k') {
            i->setFirstMove();
        }
    }
 }

// Checks if set up conditions are satisfied
bool Board::setUpConditions() {
    int blackKingCount = 0;
    int whiteKingCount = 0;
    
    for(const auto & i:blackPieces) {
        if(i->getType() == 'k') {
            blackKingCount++;
        }
        if(i->getType() == 'p' && (i->getLocation().r == 0 || i->getLocation().r == 7)) {
            return false;
        }
    }
    for(const auto & i:whitePieces) {
        if(i->getType() == 'K') {
            whiteKingCount++;
        }
        if(i->getType() == 'P' && (i->getLocation().r == 0 || i->getLocation().r == 7)) {
            return false;
        }
    }
    if(blackKingCount != 1 || whiteKingCount != 1) {
        return false;
    } else {
        updateNextMoves(true);
        updateNextMoves(false);
        if(isCheck(getKing(true)) || isCheck(getKing(false))) {
            return false;
        }
    }
    getKing(true).setFirstMove();
    getKing(false).setFirstMove();
    return true;
}

// Returns the symbol of a piece at a given location
char Board::pieceAtLocation(Pos end, bool isWhite) {
    if(isWhite) {
        for(const auto & i:whitePieces) {
            if(i->getLocation() == end) {
                return i->getType();
            }
        }
    } else {
        for(const auto & i:blackPieces) {
            if(i->getLocation() == end) {
                return i->getType();
            }
        }
    }
     
}

// Sets setUpCalled to true
void Board::setSetup() {
    setUpCalled = true;
}

// Returns the value of setUpCalled
bool Board::getSetup() const {
    return setUpCalled;
}

// Returns a reference to the vector of piece pointers for white or black team
vector<unique_ptr<Piece>>& Board::getPieces(bool white) {
    if (white) {
        return whitePieces; 
    } else {
        return blackPieces;
    }
} 

// Output operator for a board 
ostream &operator<<(ostream &out, const Board &b) {
   out << *b.td;  
   return out;
}
