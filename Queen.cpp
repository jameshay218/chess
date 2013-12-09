#include "Queen.hpp"

#include <iostream>

using namespace std;

/* Uses the inherited check_in_line and check_diagonal functions to generate
   the valid move set. Note that the queen functions as a rook and bishop
   combined */
int Queen::generate_valid_moves(const string current_coords) {
  available_moves.clear();
  check_in_line(current_coords);
  check_diagonal(current_coords);
  return available_moves.size();
}
