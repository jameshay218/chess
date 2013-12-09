#include "Rook.hpp"

#include <iostream>

using namespace std;
int Rook::generate_valid_moves(string current_coords) {
  available_moves.clear();
  // cout << "Checking rook moves at " << current_coords  << endl;
  //  cout << "Number of available moves: " << available_moves.size() << endl;
  check_in_line(current_coords);
  //  cout << "Number of available moves: " << available_moves.size() << endl;
  return available_moves.size();
}
