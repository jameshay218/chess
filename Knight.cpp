#include "Knight.hpp"

#include <iostream>

using namespace std;
int Knight::generate_valid_moves(const string current_coords) {
  available_moves.clear();
  string temp = "A1"; 
  
  /* Generates all of the 8 possible moves for the knight, and checks if 
     the knight may legally move to any of these squares */
  for(int i = 1; i <= 8; i++) {
    switch(i) {
    case 1:
      temp[0] = current_coords[0] + 1;
      temp[1] = current_coords[1] + 2;
      break;
    case 2:
      temp[0] = current_coords[0] + 2;
      temp[1] = current_coords[1] + 1;
      break;
    case 3:
      temp[0] = current_coords[0] + 2;
      temp[1] = current_coords[1] - 1;
      break; 
    case 4:
      temp[0] = current_coords[0] + 1;
      temp[1] = current_coords[1] - 2;
      break;
    case 5:
      temp[0] = current_coords[0] - 1;
      temp[1] = current_coords[1] - 2;
      break;
    case 6:
      temp[0] = current_coords[0] - 2;
      temp[1] = current_coords[1] - 1;
      break; 
    case 7:
      temp[0] = current_coords[0] - 2;
      temp[1] = current_coords[1] + 1;
      break;
    case 8:
      temp[0] = current_coords[0] - 1;
      temp[1] = current_coords[1] + 2;
      break;
    }

    if(chess_board->check_coordinates(temp) == true 
       && chess_board->contains_piece(temp) != get_colour()) {
      available_moves.push_back(temp);
    }
  }
  return available_moves.size();
}
