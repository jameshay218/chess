#include "Queen.hpp"

#include <iostream>

using namespace std;
int Queen::generate_valid_moves(string current_coords) {
  available_moves.clear();
  check_in_line(current_coords);
  check_diagonal(current_coords);
  return available_moves.size();
}
