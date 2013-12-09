#include "ChessPiece.hpp"

using namespace std;

int ChessPiece::check_valid_moves(string destination_coords) {
  if (find(available_moves.begin(), available_moves.end(), destination_coords) == available_moves.end()) {
    return 1; //The specified move is not within valid moves
  }
  return 0; 
}

void ChessPiece::check_in_line(string current_coords) {
  string temp = "A1";
  vector<string> temp_moves;

  for(int index = 1; index <= 4; index++) {
    temp_moves.clear();    
    switch (index) {
    case 1:
      for (temp[0] = current_coords[0] + 1, temp[1] = current_coords[1]; 
	   temp[0] <= 'H' ; 
	   temp[0]++) {
	temp_moves.push_back(temp);
      }
      break;
    case 2:
      for (temp[0] = current_coords[0] - 1, temp[1] = current_coords[1]; 
	   temp[0] >= 'A' ; 
	   temp[0]--) {
	temp_moves.push_back(temp);
      }
      break;
    case 3:
      for (temp[1] = current_coords[1] + 1, temp[0] = current_coords[0]; 
	   temp[1] <= '8' ; 
	   temp[1]++) {
	temp_moves.push_back(temp);
      }
      break;
    case 4:
      for (temp[1] = current_coords[1] - 1, temp[0] = current_coords[0]; 
	   temp[1] >= '1' ; 
	   temp[1]--) {
	temp_moves.push_back(temp);
      }
      break;
    }
    
    for (vector<string>::iterator i = temp_moves.begin(); i != temp_moves.end(); i++) {
      if (chess_board->check_coordinates(*i) == true) {
	if (chess_board->contains_piece(*i) == empty_square) {
	  available_moves.push_back(*i);
	}
      	else if (chess_board->contains_piece(*i) == get_colour() ) {
	  break;
	}
	else {
	  available_moves.push_back(*i);
	  break;
	}
      }
    }
  }
}


void ChessPiece::check_diagonal(string current_coords) {
  string temp = "A1";
  vector<string> temp_moves;

  for(int index = 1; index <= 4; index++) {
    temp_moves.clear();    
    
    switch (index) {
    case 1:
      for (temp[0] = current_coords[0] + 1, temp[1] = current_coords[1] + 1; 
	   temp[0] <= 'H' || temp[1] <= '8'; 
	   temp[0]++, temp[1]++) 
	{
	  temp_moves.push_back(temp);
	}
      break;
    case 2:
      for (temp[0] = current_coords[0] - 1, temp[1] = current_coords[1] + 1; 
	   temp[0] >= 'A' || temp[1] <= '8'; 
	   temp[0]--, temp[1]++) 
	{
	  temp_moves.push_back(temp);
	}
      break;
    case 3:
      for (temp[0] = current_coords[0] + 1, temp[1] = current_coords[1] - 1; 
	   temp[0] <= 'H' || temp[1] >= '1' ; 
	   temp[0]++, temp[1]--) 
	{
	  temp_moves.push_back(temp);
	}
      break;
    case 4:
      for (temp[0] = current_coords[0] - 1, temp[1] = current_coords[1] - 1; 
	   temp[0] >= 'A' || temp[1] >= '1';
	   temp[0]--, temp[1]--) 
	{
	  temp_moves.push_back(temp);
	}
      break;
    }

    for (vector<string>::iterator i = temp_moves.begin(); i != temp_moves.end(); i++) {
      if (chess_board->check_coordinates(*i) == true) { 
	if (chess_board->contains_piece(*i) == empty_square) {
	  available_moves.push_back(*i);
	}
	else if (chess_board->contains_piece(*i) == get_colour()) {
	  break;
	}
	else {
	  available_moves.push_back(*i);
	  break;
	}
      } 
    }
  }
}
