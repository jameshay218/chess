#ifndef CHESSPIECE_HPP
#define CHESSPIECE_HPP

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include "ChessBoard.hpp"

using namespace std;

class ChessPiece {

protected:
  Colour colour;
  ChessBoard* chess_board;
  PieceType type; 
  vector<string> available_moves;

public: 
  ChessPiece(Colour _colour, ChessBoard* _board, PieceType _type) : colour(_colour), chess_board(_board), type(_type){ }
  virtual int generate_valid_moves(string current_coords) = 0;
  int check_valid_moves(string destination_coords);
  void check_in_line(string current_coords);
  void check_diagonal(string current_coords);
  vector<string> get_available_moves() {return available_moves;}
  PieceType get_type() {return type;}
  Colour get_colour() {return colour;}
  virtual ~ChessPiece() {};
};
#endif
