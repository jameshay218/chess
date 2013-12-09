#include "King.hpp"

#include <iostream>

using namespace std;
int King::generate_valid_moves(const string current_coords) {
  available_moves.clear();
  string temp = "A1";
 
  /* Generates the 8 possible moves for the king, and adds the move
     to the valid move set if any of these moves may be made legally
     (excluding a check for check) */
  for (int i = 1; i <= 8; i++) {
    switch(i) {
    case 1:
      temp[0] = current_coords[0];
      temp[1] = current_coords[1] + 1;
      break;
    case 2:
      temp[0] = current_coords[0];
      temp[1] = current_coords[1] - 1;
      break;
    case 3:
      temp[0] = current_coords[0] + 1;
      temp[1] = current_coords[1];
      break; 
    case 4:
      temp[0] = current_coords[0] - 1;
      temp[1] = current_coords[1];
      break;
    case 5:
      temp[0] = current_coords[0] - 1;
      temp[1] = current_coords[1] - 1;
      break;
    case 6:
      temp[0] = current_coords[0] + 1;
      temp[1] = current_coords[1] + 1;
      break; 
    case 7:
      temp[0] = current_coords[0] + 1;
      temp[1] = current_coords[1] - 1;
      break;
    case 8:
      temp[0] = current_coords[0] - 1;
      temp[1] = current_coords[1] + 1;
      break;
    }

    if (chess_board->check_coordinates(temp) == true 
	&& chess_board->contains_piece(temp) != get_colour()) {
      available_moves.push_back(temp);
    }     
  }
  return available_moves.size();
}
