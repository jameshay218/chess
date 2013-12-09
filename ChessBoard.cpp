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
  Colour piece_colour = white; // Specifies which colour pieces to create

  /* Creates the pawns for both players */
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
  
  /* Creates the rest of the pieces for both players */
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
      case 'B': start_board[square] = new Knight(piece_colour, this, knight);
	break;
      case 'C': start_board[square] = new Bishop(piece_colour, this, bishop);
	break;
      case 'D': start_board[square] = new Queen(piece_colour, this, queen); 
	break;
      case 'E': start_board[square] = new King(piece_colour, this, king);
	change_king_position(square, piece_colour); break;
      case 'F': start_board[square] = new Bishop(piece_colour, this, bishop); 
	break;
      case 'G': start_board[square] = new Knight(piece_colour, this, knight); 
	break;
      case 'H': start_board[square] = new Rook(piece_colour, this, rook); break;
      default: break;
      }
    }  
    piece_colour = static_cast<Colour>(!piece_colour);
  }
  /* Resets the rest of the board's properties to allow a new game to be started
   */
  resetBoard();
}


void ChessBoard::resetBoard() {
  game_in_progress = true;
  black_king_position = "E8";
  white_king_position = "E1";
  turn = white;
  board.clear(); // Clears the current board
  board = start_board; // Sets the current board to the standard start positions
  cout << "A new chess game is started!" << endl;
}



ChessBoard::~ChessBoard() {
  /* Board destructor. Loops through all of the map elements and deletes their
     values */
  for(map_itr itr = start_board.begin(); itr != start_board.end(); ++itr) {
    delete itr->second;
    itr->second = NULL;
  }
  start_board.clear();
}

void ChessBoard::submitMove(string start_coords, string dest_coords) {
  bool check = false; // Tracks whether or not the opposing player is in check
  map_itr itr = board.find(start_coords); /* Holds the map element for the
					     given start coordinate */

  /* Performs a number of checks on the provided move, throwing an error if any
     of these conditions violated */
  try
    {
      /* Throws an error if a move is submitted when the game is over */
      if(game_in_progress == false) throw 1; 
      /* Error if the given start square is empty */
      if(contains_piece(start_coords) == empty_square) throw 2;  
      /* Error if the selected piece is of the wrong colour */
      if (contains_piece(start_coords) != turn) throw 3;
      /* Error the given coordinates are the same (ie. no move) */
      if (start_coords == dest_coords) throw 4;
      /* Error if the start or destination coordinates are invalid */
      if (check_coordinates(start_coords) == false 
	  || check_coordinates(dest_coords) == false) throw 5;
      /* Error if no valid moves or if the destination square is not within the
	 selected piece's moveset */
      if((itr->second->generate_valid_moves(start_coords) == 0) 
	 || (itr->second->check_valid_moves(dest_coords) != 0)) throw 6;
      /* Error if the given move cannot be made legally, otherwise moves the 
	 piece */
      if(move_piece(start_coords, dest_coords, false) == false) 
	throw 7;
    }
  catch (int error) {
    /* If an error was found, calls a helper function to output a suitable
       error message */
    output_error(error, start_coords, dest_coords);
    return;
  }

  /* Sets the check flag if the opposing player is in check following the
     successful move */
  if((turn == white && in_check(black_king_position, white) == true) 
     || (turn == black && in_check(white_king_position, black) == true)) {
    check = true;
  }
  /* Checks if the opposing player is able to make any valid moves. If not, 
     check if the check flag has been set. Outputs the appropriate 
     message */
  if(no_valid_moves(turn) == true) {
    if (check == true) {
      if (turn == black) 
	cout << "White";
      else 
	cout << "Black";
      cout << " is in checkmate" << endl;
    }
    else {    
      cout << "The game ends in stalemate" << endl;
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
  turn = static_cast<Colour>(!turn); // Next player's turn
}

/* Checks if coordinates are within bounds */
bool ChessBoard::check_coordinates(string coords) {
  if(coords.length() != 2 || coords[0] < 'A' || coords[0] > 'H' 
     || coords[1] < '1' || coords[1] > '8') {
    return false;
  }
  return true;
}

/* Checks if a given coordinate contains a piece */
Colour ChessBoard::contains_piece(string coords) {
  map_itr iterator = board.find(coords);
  if(iterator == board.end() || iterator->second == NULL) 
    return empty_square;
  else 
    return iterator->second->get_colour();
}

/* Changes a given king's position */
void ChessBoard::change_king_position(string destination_coordinates, 
				      Colour piece_colour) {
  if(piece_colour == white) {
    white_king_position = destination_coordinates;
  }
  else {
    black_king_position = destination_coordinates;
  }
  
}

/* Checks if a given player is in check. Returns true if the position 
   of a given piece is within any of the player's valid moves */
bool ChessBoard::in_check(string piece_pos, Colour player_turn) {
  string temp = "A1";

  /* Iterates through all of the pieces on the board */
  for(map_itr itr = board.begin(); itr != board.end(); ++itr) {
    /* If the map element contains a piece of the player's colour
     generate it's valid moves and check if the given piece is within
     that move set. If so, return true */
    if (itr->second != NULL && itr->second->get_colour() == player_turn) {
      temp = itr->first;
      itr->second->generate_valid_moves(temp);

      if(itr->second->check_valid_moves(piece_pos) == false) {
	return true;
      }
    }
  }
  return false;
}

/* Similar to the "in_check" function, this function iterates through
   all pieces on the board for a given player (in this case, the
   opposing player to the one provided). The function then uses the 
   move piece function with the simulate flag set to test if any of
   these generated moves can be successfully made. If a successful move
   is simulated, the function returns false */
bool ChessBoard::no_valid_moves(Colour player_turn) {
  string piece_coords = "A1";
  string test_move = "A1";
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
	  turn = static_cast<Colour>(!turn); /* The move must be simulated in
						the context of the next
						player's turn */

	  if(move_piece(piece_coords, test_move, true) == true) {
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

/* Moves a piece by setting the value of a map element for the destination
   coordinates to the value of the map element for the start coordinates, 
   and sets the value of the start coordinate map element to NULL. If the
   simulate flag is true, then the move is reversed at the end of the 
   function (and returns true if the move was successful) */
bool ChessBoard::move_piece(string start_coords, string dest_coords, 
			   bool simulate) {
  map_itr dest_itr = board.find(dest_coords);
  map_itr start_itr = board.find(start_coords);
  ChessPiece* moving_piece = 0;
  ChessPiece* taken_piece = 0; 
  bool PieceTaken;
  
  if (start_itr->second == NULL) {
    return false;
  }
  moving_piece = start_itr->second;

  /* If the destination square contains a piece of the opposing colour,
     record that a piece has been taken and keep track of that taken
     piece */
  if (contains_piece(dest_coords) == static_cast<Colour>(!turn)) {
    PieceTaken = true;
    taken_piece = dest_itr->second;
    board[dest_coords] = NULL;   
  }
 
  board[dest_coords] = moving_piece;
  board[start_coords] = NULL;
 
  /* If a king was moved, record the king's new coordinates */
  if(moving_piece->get_type() == king) {
    change_king_position(dest_coords, turn);
  }  

  /* If the player has made a move such that they are now in check,
     reverse that move and return false */
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

  /* If the move is not a simulation, output what has happened */
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

/* Outputs a suitable error message given a provided error code */
void ChessBoard::output_error(int error, string start_coords, string dest_coords) {
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
    cout << " cannot move to " << dest_coords << "!" << endl; break;
  case 7: output_piece(itr->second->get_type(), itr->second->get_colour());
    cout << " cannot move there - puts you in check" << endl; break;
  default: cout << "Unknown error" << endl;
    break;
  }
}

/* Outputs the colour and type of a given piece */
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
