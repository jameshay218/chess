#ifndef KING_HPP
#define KING_HPP

#include "ChessPiece.hpp"
class King: public ChessPiece {

public:
  King(Colour _colour, ChessBoard* _board, PieceType _type) : ChessPiece(_colour, _board, _type) {  }
  int generate_valid_moves(string current_coords);
  ~King() {}
};

#endif
