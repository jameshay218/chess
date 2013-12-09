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
  Colour colour; // Colour of the piece
  ChessBoard* chess_board; /* Pointer to the chess board on which the game 
			      is being played */
  PieceType type; // Records the type of the piece (eg. pawn, rook etc)
  vector<string> available_moves; /* Vector of strings to record all of the
				     moves that are available to the piece at
				     a given time */

public: 
  /*======================= Chesspiece Constructor ===========================*/
  /* Contructs a chess piece with a given colour and type on a given chessboard
   */
  ChessPiece(Colour _colour, ChessBoard* _board, PieceType _type) 
    : colour(_colour), chess_board(_board), type(_type){ }


  /*======================= Generate Valid Moves =============================*/
  /* Pure virtual function that is overriden in all of the chess piece sub
     classes. Returns the number of valid moves that the piece could make from
     a given start coordinate */
  virtual int generate_valid_moves(const string current_coords) = 0;


  /*========================== Check Valid Moves =============================*/
  /* Checks if a given coordinate is within the piece's valid move set */
  bool check_valid_moves(const string destination_coords);

  /*============================ Check In Line ===============================*/
  /* Function to check all squares in a horizontal and vertical line from a 
     given square. This function is inherited and used by the rook and queen
     pieces */
  void check_in_line(const string current_coords);

  /*=========================== Check Diagonal ===============================*/
  /* Function to check all squares in a diagnoal line from a given square. 
     This function is inherited and used by the bishop and queen pieces */
  void check_diagonal(const string current_coords);

  /*------------------------- Get Available Moves ----------------------------*/
  /* Returns the available move set for testing */
  vector<string> get_available_moves() {return available_moves;}

  /*--------------------------- Get Piece Type -------------------------------*/
  /* Returns the piece's type */
  PieceType get_type() {return type;}

  /*--------------------------- Get Piece Colour -----------------------------*/
  /* Returns a piece's colour */
  Colour get_colour() {return colour;}

 /*--------------------- Virtual ChessPiece Destructor -----------------------*/
  virtual ~ChessPiece() {};

};

#endif
