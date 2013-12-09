#include"Bishop.hpp"

#include <iostream>

using namespace std;
int Bishop::generate_valid_moves(string current_coords) {
  available_moves.clear();
  //  cout << "Number of available moves: " << available_moves.size() << endl;
  // cout << "Checking bishop moves" << endl;
  check_diagonal(current_coords);
  // cout << "Number of available moves: " << available_moves.size() << endl;
  return available_moves.size();
}
