#ifndef SUDOKU_H
#define SUDOKU_H

#include <string>
#include <vector>

class SudokuBoard{
  
  class SudoSq{
    
    std::string sqs;
    
  public:

    SudoSq(const std::string & s);
    
    bool checksq(char val);
    
    bool checkrow(int num,char val);
    
    std::string str();
    
    bool isempty(int x, int y);
    
    void insert(int x, int y, int val);
    
    void printrow(int num);
    
    bool checkcol(int num, char val);
    
  };
  
  std::vector<SudoSq> board;

public:

  SudokuBoard();

  SudokuBoard(const std::string & brd);

  bool canBePlaced(int x, int y, int val);
	
  void place(int x, int y, int val);

  SudokuBoard place(SudokuBoard SB, int x, int y, int val);

  std::string str();

  void placeRandom(int count);

  void randomize(int difficulty,bool verbose, int max_threads);

  std::vector<int> possibleMoves();

  void solve(SudokuBoard SB, bool random,int & solvedcount, std::string & SolvedBoard);

  void print();
  
};

#endif
