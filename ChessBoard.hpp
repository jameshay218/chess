#ifndef CHESSBOARD_HPP
#define CHESSBOARD_HPP

#include <iostream>
#include <map>
#include <string>

using namespace std;

/* Each piece keeps track of it's own type */
enum PieceType{ pawn, rook, knight, bishop, queen, king };

/* A square my contain a white or black piece, or might be empty */
enum Colour {white, black, empty_square};


class ChessPiece;

class ChessBoard {
private:
  Colour turn; /* Keeps track of if it is black or white's turn */
  bool game_in_progress; /* If the game is not in progress (ie. has ended), 
			    then no moves may be submitted until the board
			    is reset */

protected:
  map<string, ChessPiece*> board; /* The board upon which the game is played */
  map<string, ChessPiece*> start_board; /* Template board which retains all of
					   pieces in their starting positions */
  string black_king_position; /* Tracks the position of the black king */
  string white_king_position; /* Tracks the position of the white king */

public:
  typedef map<string, ChessPiece*>::iterator map_itr; /* Defines a map iterator
							 for use throughout the
							 program */

  /*======================= Chessboard Constructor ===========================*/
  /* Constructs new chess pieces for each starting square on the chessboard,
     and then resets the board to allow a new game to be played */
  ChessBoard();
 

  /*======================= Chessboard Destructor ============================*/
  /* Iterates through the start_board and deletes all of the chess pieces. The
     chess boards are then cleared */
  ~ChessBoard();


 /*========================== Reset Chessboard ===============================*/
  /* Sets the playing board back to the start_board, returns the kings to their
     start positions, sets the turn to be white, and restarts the game */
  void resetBoard();


  /*============================ Submit Move =================================*/
  /* This function takes a starting coordinate and destination coordinate.
     Helper functions are then called to check that the coordinates satisfy all
     of the necessary criteria (ie. moving a piece of the correct colour; 
     the coordinates are valid; that the game has not ended; if checkmate, 
     stalemate or check have been reached). */
  void submitMove(string start_coords, string dest_coords);


  /*---------------------------- Check Coordinates ---------------------------*/
  /* Checks that the given coordinates are of the form "XY" where X is a 
     character from A to H and Y is a number from 1 to 8 */
  bool check_coordinates(string coords);


/*---------------------------- Contains Piece --------------------------------*/
/* Checks if a given coordinate contains a piece, and returns the colour of
   that piece (empty_square if square is empty) */
  Colour contains_piece(string coords);


/*---------------------------- Check for Check -------------------------------*/
/* Checks all of the valid moves for all of a given player's pieces, and
   returns true if that player's king position is within the valid moves of one
   of the other player's pieces (ie. if the opposing player could take a given
   player's king in the next turn). Otherwise returns false */
  bool in_check(string piece_position, Colour player_turn);


/*-------------------------- Check for Valid Moves ---------------------------*/
/* Returns true if a given player can make no legal moves. All of the player's
   pieces are checked for valid moves, and each of these moves are simulated.
   a check for check is made following each simulated move to ensure that the
   move is legal. If all of the generated valid moves are simulated
   unsuccessfully, the function returns true, signifying that the given player
   is in stalemate (and if that player is also in check, they are in checkmate)
*/
  bool no_valid_moves(Colour player_turn);


/*-------------------------- Change king position ----------------------------*/
/* Changes the recorded position of a given player's king following that king
   being moved */
  void change_king_position(string destination_coordinates, Colour piece_colour);


/*------------------------------- Move Piece ---------------------------------*/
/* Returns true if the piece at a given start coordinate can successfully move
   to a given destination coordinate without putting that player in check.
   The function may be passed the "simulate" flag, causes the given move to be
   reversed at the end of the function. If the simulate flag is set to false,
   the move is completed and a suitable message is displayed */
  bool move_piece(string start_coords, string dest_coords, bool simulate);

  
/*------------------------------ Output Error -------------------------------*/
/* Outputs a suitable error message to the standard output stream */
  void output_error(int error, string start_coords, string dest_coords);


/*------------------------------ Output Piece -------------------------------*/
/* Outputs the colour and type of a piece to the standard output stream */
  void output_piece(PieceType piece, Colour colour);
};

    
#endif 
    
 
