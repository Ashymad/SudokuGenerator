#include <iostream>

#include "sudoku.h"

using namespace std;

int main(){
  srand(time(NULL));
	
  SudokuBoard Sb;
  int isolved;
  string answer;

  // This method creates a random Sudoku board with only one solution
  // SudokuBoard::randomize(int difficulty_percent, bool verbose, int max_threads_at_once)
  Sb.randomize(100, true, 4); 

  Sb.print();

  // This method solves Sudoku                           
  // SudokuBoard::solve(SudokuBoard sudokuBoard, bool place_digits_randomly, int number_of_solutions, string solution)
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
