#ifndef PAWN_HPP
#define PAWN_HPP

#include "ChessPiece.hpp"
#include <string>
#include <map>

class Pawn : public ChessPiece {
private: 
  /* Unlike the other pieces, the pawn is given its start square, which may 
     be referred to when generating valid moves (allowing the pawn to move
     two squares if it has not yet moved from its start square) */
  string start_square;
  
public:
  int generate_valid_moves(const string current_coords);
  Pawn(Colour _colour, ChessBoard* _board, PieceType _type, string _square) 
    : ChessPiece(_colour, _board, _type),  start_square(_square) {  };
  ~Pawn() {};
};

#endif
