#ifndef BISHOP_HPP
#define BISHOP_HPP

#include "ChessPiece.hpp"
class Bishop: public ChessPiece {

public:
  Bishop(Colour _colour, ChessBoard* _board, PieceType _type) : ChessPiece(_colour, _board, _type) {  }
  int generate_valid_moves(string current_coords);
  ~Bishop() {}
};

#endif
