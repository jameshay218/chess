#include "ChessPiece.hpp"

using namespace std;

/* Checks if a given square is within the piece's valid move set */
bool ChessPiece::check_valid_moves(string destination_coords) {
  if (find(available_moves.begin(), available_moves.end(), 
	   destination_coords) == available_moves.end()) {
    return true;
  }
  return false; 
}

/* Creates an array of coordinates stemming from the start square in each of 
   the four possible directions. These squares are then check sequentially and
   added to the valid move set if they are a legal move (excluding a check for
   check). Note that if any piece is found in this line, then the next line is
   checked */
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
    /* Iterates through the line of strings produced above */
    for (vector<string>::iterator i = temp_moves.begin(); 
	 i != temp_moves.end(); i++) {
      /* Adds the coordinate to the valid move set if the square is empty or
	 contains an opposing player's piece. If any piece is hit, then stop
	 checking this line */
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

/* Checks all of the four diagonal lines for valid moves similarly to the 
   "check_in_line" function */
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

    for (vector<string>::iterator i = temp_moves.begin(); 
	 i != temp_moves.end(); i++) {
      
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
