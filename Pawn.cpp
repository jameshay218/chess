#include "Pawn.hpp"

#include <iostream>

using namespace std;

int Pawn::generate_valid_moves(const string current_coords) {
  available_moves.clear();
  string temp = "A1";
  int colour_modifier;
   
  /* Moves the pawn down if black, and up if white */
  if(get_colour() == white)
    colour_modifier = 1;
  else 
    colour_modifier = -1;
  
  
  temp[0] = current_coords[0]; 
  temp[1] = current_coords[1] + colour_modifier;
  
  /* Check straight ahead */
  if (chess_board->check_coordinates(temp) == true 
      && chess_board->contains_piece(temp) == empty_square) {
    available_moves.push_back(temp);
  }
 
  /* If piece hasn't moved and square directly infront is free, 
     check two squares ahead */
  if(chess_board->contains_piece(temp) == empty_square) {
    temp[1] = current_coords[1] + 2*colour_modifier;
    if (chess_board->check_coordinates(temp) == true 
	&& current_coords == start_square 
	&& chess_board->contains_piece(temp) == empty_square) {
      available_moves.push_back(temp);
    }
  }

  /* Check diagonals for opposing player's pieces */
  temp[0] = current_coords[0] + 1;
  temp[1] = current_coords[1] + colour_modifier;

  if (chess_board->check_coordinates(temp) == true 
      && chess_board->contains_piece(temp) == static_cast<Colour>(!colour)) {
    available_moves.push_back(temp);
  }

  temp[0] = current_coords[0] - 1;
  temp[1] = current_coords[1] + colour_modifier;
  
  if (chess_board->check_coordinates(temp) == true 
      && chess_board->contains_piece(temp) == static_cast<Colour>(!colour)) {
    available_moves.push_back(temp);
  }
  return available_moves.size();
}
