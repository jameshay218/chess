#ifndef CHESSBOARD_HPP
#define CHESSBOARD_HPP

#include <iostream>
#include <map>
#include <string>

using namespace std;

enum PieceType{ pawn, rook, knight, bishop, queen, king };
enum Colour {white, black, empty_square};


class ChessPiece;

class ChessBoard {
  Colour turn;
  bool game_in_progress;

protected:
  map<string, ChessPiece*> board; 
  map<string, ChessPiece*> start_board;
  string black_king_position;
  string white_king_position;

public:
  typedef map<string, ChessPiece*>::iterator map_itr; 
  ChessBoard();
  ~ChessBoard();
  void submitMove(string start_coords, string dest_coords);
  bool check_coordinates(string coords);
  Colour contains_piece(string coords);
  bool in_check(string piece_position, Colour player_turn);
  bool in_checkmate(Colour player_turn);
  void change_king_position(string destination_coordinates, Colour piece_colour);
  bool move_piece(string start_coords, string dest_coords, bool simulate, bool &PieceTaken);
  void resetBoard();
  void output_error(int error, string start_coords);
  void output_piece(PieceType piece, Colour colour);
};

    
#endif 
    
 
