#include <iostream>
#include <string>

using namespace std;

int main() {
  string coords;

  cin >> coords;
  cout << "You entered: " << coords << endl;
    
  char rank;
  char file;

  if(coords.length() != 2) {
    cout << "Checkpoint 1. Invalid coordinates" << endl;
    return 0;
  }
     
  cout << "Rank: " << coords.at(1) << endl;
  file = coords.at(0);
  rank = coords.at(1);

  cout << "Coords length is: " << coords.length() << endl;
  cout << "File: " << file << endl;
  cout << "Rank: " << rank << endl;

  if (file < 'A' || file > 'H') {
    cout << "Checkpoint 2. Invalid coordinates" << endl;
    return 0;
  }

  if (rank < '1' || rank > '8') {
    cout << "Checkpoint 3. Invalid coordinates" << endl;
    return 0;
  }

  cout << "Your coordinates are fine" << endl;
  return 0;

}
