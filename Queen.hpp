#ifndef QUEEN_HPP
#define QUEEN_HPP

#include "ChessPiece.hpp"
class Queen: public ChessPiece {

public:
  Queen(Colour _colour, ChessBoard* _board, PieceType _type) : ChessPiece(_colour, _board, _type) {  }
  int generate_valid_moves(const string current_coords);
  ~Queen() {}
};


#endif
