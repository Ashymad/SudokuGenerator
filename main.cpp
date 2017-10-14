#include <iostream>

#include "sudoku.h"

using namespace std;

int main(){
  srand(time(NULL));
	
  SudokuBoard Sb;
  int isolved;
  string answer;
  Sb.randomize(100, true);
  Sb.print();
  Sb.solve(Sb, false ,isolved, answer);
  if (isolved == 1){
    SudokuBoard(answer).print();
    cout << "This is the only answer." << endl;
  }
  else if (isolved > 1)
    cout << "There is more answers than one answer." << endl;
  else 
    cout << "Unsolvable!" << endl;

  return 0;
}
