#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "ChessPiece.hpp"
class Knight: public ChessPiece {

public:
  Knight(Colour _colour, ChessBoard* _board, PieceType _type) : ChessPiece(_colour, _board, _type) {  }
  int generate_valid_moves(const string current_coords);
  ~Knight() {}
};

#endif

