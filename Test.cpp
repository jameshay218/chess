if (containsPiece(dest_coords) != 2) {
  PieceTaken = true;
  temp = itr->second;
  board.erase(dest_coords);
 }

board[dest_coords] = board[start_coords];
board.erase(start_coords);
itr = board.find(dest_coords);

