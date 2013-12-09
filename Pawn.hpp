#ifndef PAWN_HPP
#define PAWN_HPP

#include "ChessPiece.hpp"
#include <string>
#include <map>

class Pawn : public ChessPiece {
private: 
  string start_square;
  
public:
  int generate_valid_moves(string current_coords);
  Pawn(Colour _colour, ChessBoard* _board, PieceType _type, string _square) : ChessPiece(_colour, _board, _type),  start_square(_square) {  };
  ~Pawn() {};
};

#endif
