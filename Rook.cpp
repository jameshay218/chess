#include "Rook.hpp"

#include <iostream>

using namespace std;
int Rook::generate_valid_moves(string current_coords) {
  available_moves.clear();
  check_in_line(current_coords);
  return available_moves.size();
}
