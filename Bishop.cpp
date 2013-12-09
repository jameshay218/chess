#include"Bishop.hpp"

#include <iostream>

using namespace std;
int Bishop::generate_valid_moves(const string current_coords) {
  available_moves.clear();
  check_diagonal(current_coords);
  return available_moves.size();
}
