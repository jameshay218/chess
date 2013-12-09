#ifndef ROOK_HPP
#define ROOK_HPP

#include "ChessPiece.hpp"

class Rook: public ChessPiece {

public:
  Rook(Colour _colour, ChessBoard* _board, PieceType _type) : ChessPiece(_colour, _board, _type){  }
  int generate_valid_moves(string current_coords);
  ~Rook() {};
};

#endif
