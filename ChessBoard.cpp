#include "ChessBoard.hpp"

#include "Pawn.hpp"
#include "Rook.hpp"
#include "Knight.hpp"
#include "Bishop.hpp"
#include "Queen.hpp"
#include "King.hpp"

#include <iostream>
#include <map>
#include <string>

using namespace std;

ChessBoard::ChessBoard() {
  string square = "A1";
  Colour piece_colour = white;
 
  for(int i = 0; i <= 1; i++) {
    if (piece_colour == white) { 
      square[1] = '2';
    }
    else { 
      square[1] = '7';
    }
    for (square[0]= 'A'; square[0] <= 'H'; square[0]++) {
      start_board[square] = new Pawn(piece_colour, this, pawn, square);
    }
    piece_colour = static_cast<Colour>(!piece_colour);
  }
  for(int i = 0; i <= 1; i++) {
    if (piece_colour == white) { 
      square[1] = '1';
    }
    else { 
      square[1] = '8';
    }

    for(square[0] = 'A'; square[0] <= 'H'; square[0]++) {
      switch(square[0]) {
      case 'A': start_board[square] = new Rook(piece_colour, this, rook); break;
      case 'B':   start_board[square] = new Knight(piece_colour, this, knight);
	break;
      case 'C':    start_board[square] = new Bishop(piece_colour, this, bishop);
	break;
      case 'D':   start_board[square] = new Queen(piece_colour, this, queen); 
	break;
      case 'E': start_board[square] = new King(piece_colour, this, king);
	change_king_position(square, piece_colour); break;
      case 'F':  start_board[square] = new Bishop(piece_colour, this, bishop); 
	break;
      case 'G':  start_board[square] = new Knight(piece_colour, this, knight); 
	break;
      case 'H': start_board[square] = new Rook(piece_colour, this, rook); break;
      default: break;
      }
    }  
    piece_colour = static_cast<Colour>(!piece_colour);
  }
  resetBoard();
}


void ChessBoard::resetBoard() {
  game_in_progress = true;
  black_king_position = "E8";
  white_king_position = "E1";
  turn = white;
  board.clear();
  board = start_board;
  cout << "A new chess game is started!" << endl;
}

ChessBoard::~ChessBoard() {
  for(map_itr itr = start_board.begin(); itr != start_board.end(); ++itr) {
    delete itr->second;
    itr->second = NULL;
  }
  
  start_board.clear();
 
}

void ChessBoard::submitMove(string start_coords, string dest_coords) {
  bool check = false;
  bool piece_taken = false;
  map_itr itr = board.find(start_coords);
  try
    {
      if(game_in_progress == false) throw 1;
      if(contains_piece(start_coords) == empty_square) throw 2;
      if (contains_piece(start_coords) != turn) throw 3;
      if (start_coords == dest_coords) throw 4;
      if (check_coordinates(start_coords) == false 
	  || check_coordinates(dest_coords) == false) throw 5;
      if((itr->second->generate_valid_moves(start_coords) == 0) 
	 || (itr->second->check_valid_moves(dest_coords) != 0)) throw 6;
      if(move_piece(start_coords, dest_coords, false, piece_taken) == false) 
	throw 7;
      throw 0;
    }
  catch (int error) {
    if (error != 0) {
      output_error(error, start_coords);
      return;
    }  
  }
  if((turn == white && in_check(black_king_position, white) == true) 
     || (turn == black && in_check(white_king_position, black) == true)) {
    check = true;
  }
 
  if(in_checkmate(turn) == true) {
    if (check == true) {
      if (turn == black) 
	cout << "White";
      else 
	cout << "Black";
      cout << " is in checkmate" << endl;
    }
    else {    
      cout << "The game ends in stalemate" << endl;
      return;
    }
    game_in_progress = false;
  }
  else if (check == true) {
    if (turn == black) 
      cout << "White";
    else 
      cout << "Black";
    cout << " is in check" << endl;
  }
  turn = static_cast<Colour>(!turn);
  return;
}

bool ChessBoard::check_coordinates(string coords) {
  if(coords.length() != 2 || coords[0] < 'A' || coords[0] > 'H' 
     || coords[1] < '1' || coords[1] > '8') {
    return false;
  }
  return true;
}


Colour ChessBoard::contains_piece(string coords) {
  map_itr iterator = board.find(coords);
  if(iterator == board.end() || iterator->second == NULL) 
    return empty_square;
  else 
    return iterator->second->get_colour();
}

void ChessBoard::change_king_position(string destination_coordinates, 
				      Colour piece_colour) {
  if(piece_colour == white) {
    white_king_position = destination_coordinates;
  }
  else {
    black_king_position = destination_coordinates;
  }
  
}


bool ChessBoard::in_check(string piece_pos, Colour player_turn) {
  string temp = "A1";
  for(map_itr itr = board.begin(); itr != board.end(); ++itr) {
    if (itr->second != NULL && itr->second->get_colour() == player_turn) {
      temp = itr->first;
      itr->second->generate_valid_moves(temp);
      if(itr->second->check_valid_moves(piece_pos) == 0) {
	return true;
      }
    }
  }
  return false;
}

bool ChessBoard::in_checkmate(Colour player_turn) {
  string piece_coords = "A1";
  string test_move = "A1";
  bool piece_taken = false;  
  vector<string> move_tester;
  for(map_itr itr = board.begin(); itr != board.end(); ++itr) {
    if (itr->second != NULL && itr->second->get_colour() != player_turn) {
      piece_coords = itr->first;
      itr->second->generate_valid_moves(piece_coords);
      move_tester = itr->second->get_available_moves();
      if (move_tester.size() != 0) {
	for (vector<string>::iterator move_itr = move_tester.begin(); 
	     move_itr != move_tester.end(); ++move_itr) {
	  test_move = *move_itr;
	  turn = static_cast<Colour>(!turn);
	  if(move_piece(piece_coords, test_move, true, piece_taken) == true) {
	    turn = static_cast<Colour>(!turn);
	    return false;
	  }
	  turn = static_cast<Colour>(!turn);
	}
      }
    }
  }
  return true;
}

bool ChessBoard::move_piece(string start_coords, string dest_coords, 
			   bool simulate, bool &PieceTaken) {
  map_itr dest_itr = board.find(dest_coords);
  map_itr start_itr = board.find(start_coords);
  ChessPiece* moving_piece = 0;
  ChessPiece* taken_piece = 0; 
  
  if (start_itr->second == NULL) {
    return false;
  }
  moving_piece = start_itr->second;

  if (contains_piece(dest_coords) == static_cast<Colour>(!turn)) {
    PieceTaken = true;
    taken_piece = dest_itr->second;
    board[dest_coords] = NULL;   
  }
 
  board[dest_coords] = moving_piece;
  board[start_coords] = NULL;
 
  if(moving_piece->get_type() == king) {
    change_king_position(dest_coords, turn);
  }  
  if ((turn == white && in_check(white_king_position, black) == true) 
      || (turn == black && in_check(black_king_position, white) == true)) {
    board[start_coords] = moving_piece;
    board[dest_coords] = NULL;
    if (PieceTaken == true) {
      board[dest_coords] = taken_piece;
    }
    if(moving_piece->get_type() == king) {
      change_king_position(start_coords, turn);
    }  
  
    return false;
  }

  if (simulate == false) {
    output_piece(moving_piece->get_type(), moving_piece->get_colour());
    cout << " moves from " << start_coords << " to " << dest_coords;
    if (PieceTaken) {
      cout << " taking ";
      output_piece(taken_piece->get_type(), taken_piece->get_colour());
    }
    cout << endl;
  }
  else {
    if(moving_piece->get_type() == king) {
      change_king_position(start_coords, turn);
    }  
    board[start_coords] = moving_piece;
    if (PieceTaken == true)      
      board[dest_coords] = taken_piece;
    else 
      board[dest_coords] = NULL;
  }
  return true;
}

void ChessBoard::output_error(int error, string start_coords) {
  map_itr itr = board.find(start_coords);         
  switch (error) {
  case 1: cout << "The game is over!" << endl; break;
  case 2: cout << "There is no piece at position " << start_coords << "!" 
	       << endl;  break;
  case 3: cout << "It is not your turn to move!" << endl;  break;
  case 4: cout << "Invalid move. Destination coordinates must differ from "
	       << "starting coordinates." << endl; break;
  case 5: cout << "Invalid coordinates." << endl; break;
  case 6: output_piece(itr->second->get_type(), itr->second->get_colour());
    cout << " cannot move to " << start_coords << "!" << endl; break;
  case 7: output_piece(itr->second->get_type(), itr->second->get_colour());
    cout << " cannot move there - puts you in check" << endl; break;
  default: cout << "Unknown error" << endl;
    break;
  }
}

void ChessBoard::output_piece(PieceType piece, Colour colour) {
  if (colour == white) 
    cout << "White's ";
  else 
    cout << "Black's ";
  switch (piece) {
  case pawn: cout << "Pawn"; break;
  case rook: cout << "Rook"; break;
  case knight: cout << "Knight"; break;
  case bishop: cout << "Bishop"; break;
  case queen: cout << "Queen"; break;
  case king: cout << "King"; break;
  default: cout << "Piece";
  }
}
