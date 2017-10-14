#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <thread>
#include <chrono>
#include "sudoku.h"

using namespace std;

namespace {

  string cutstr(const string & s, int a, int b){
    stringstream ss;
    for (int i = a; i <= b; i++)
      ss << s[i];
    return ss.str();
  }

  bool minInRange(int & min, int & pos, const vector<int> & vec, int a, int b){
    vector<int>::const_iterator it;
    for (it = vec.begin(); it != vec.end(); it++){
      if (*it < b && *it > a){
	min = *it;
	pos = it - vec.begin();
	break;
      }
    }
    if (it == vec.end())
      return false;
    for (; it != vec.end(); it++){
      if (*it < b && *it > a && *it < min){
	min = *it;
	pos = it - vec.begin();
      }
    }
    return true;
  }

  string vint2str(const vector<int> & vint){
    stringstream ss;
    for (int e : vint)
      ss << static_cast<char>(e + '0');
    return ss.str();
  }

  int moreRand(int level){
    for (int i = rand() % level; i > 0; i--)
      rand();
    return rand();
  }

  vector<int> findElPos(const vector<int> & vec, int el){
    vector<int> pos;
    for (int i = 0; i < vec.size(); i++){
      if (vec[i] == el)
	pos.push_back(i);
    }
    return pos;
  }

  template<typename T>

  typename vector<T>::const_iterator vecRand(const vector<T> & vec){
    int r = rand();
    float p = static_cast<float>(RAND_MAX) / static_cast<float>(vec.size());
    for (unsigned int i = 1; i < vec.size() + 1; i++){
      if (static_cast<float>(r) < p*static_cast<float>(i)+1.0f){
	return vec.begin() + i - 1;
      }
    }
  }

  vector<int> str2vint(const string & str){
    vector<int> vint;
    for (char e : str)
      vint.push_back(static_cast<int>(e - '0'));
    return vint;
  }

  void printbool(bool b){
    if (b)
      cout << "true";
    else
      cout << "false";
  }

  bool checkstr(const string & sqs, char val){
    for (char c : sqs)
      if (c == val)
	return true;
    return false;
  }

}
  
SudokuBoard::SudoSq::SudoSq(const string & s) :sqs(s) {};

bool SudokuBoard::SudoSq::checksq(char val){
  return checkstr(sqs, val);
}

bool SudokuBoard::SudoSq::checkrow(int num,char val){
  return checkstr(cutstr(sqs, num * 3, num * 3 + 2), val);
}

string SudokuBoard::SudoSq::str(){
  return sqs;
}

bool SudokuBoard::SudoSq::isempty(int x, int y){
  return sqs[x + 3 * y] == '0';
}

void SudokuBoard::SudoSq::insert(int x, int y, int val){
  sqs[x + 3 * y] = val + '0';
}

void SudokuBoard::SudoSq::printrow(int num){
  string row = cutstr(sqs, num * 3, num * 3 + 2);
  replace(row.begin(), row.end(),'0','.');
  cout << row;
}

bool SudokuBoard::SudoSq::checkcol(int num, char val){
  return sqs[num] == val ||
    sqs[num + 3] == val ||
    sqs[num + 6] == val;
}

SudokuBoard::SudokuBoard(){
  for (int i = 0; i < 9; i++)
    board.push_back(SudoSq("000000000"));
}

SudokuBoard::SudokuBoard(const string & brd){
  for (int i = 0; i < 3; i++){
    for (int j = 0; j < 3; j++){
      stringstream ss;
      ss << cutstr(brd, i * 27 + 3 * j, i * 27 + 3 * j + 2)
	 << cutstr(brd, i * 27 + 3 * j + 9, i * 27 + 3 * j + 11)
	 << cutstr(brd, i * 27 + 3 * j + 18, i * 27 + 3 * j + 20);
      board.push_back(SudoSq(ss.str()));
    }
  }
}

bool SudokuBoard::canBePlaced(int x, int y, int val){
  int sqNum = x / 3 + 3 * (y / 3);
  val = val + '0';
  if (!board[sqNum].isempty(x - 3 * (x / 3), y - 3 * (y / 3))){
    //cout << "full";
    return false;
  }
  if (board[sqNum].checksq(val)){
    //cout << "square";
    return false;
  }
  for (int sqI = 3 * (y / 3); sqI < 3 * (y / 3) + 3; sqI++){
    if (board[sqI].checkrow(y - (y / 3) * 3, val)){
      //cout << "row";
      return false;
    }
  }
  for (int sqI = x / 3; sqI < x / 3 + 9; sqI += 3){
    if (board[sqI].checkcol(x - (x / 3) * 3, val)){
      //cout << "column";
      return false;
    }
  }
  return true;
}

void SudokuBoard::place(int x, int y, int val){
  board[x / 3 + 3 * (y / 3)].insert(x - ( x / 3 ) * 3, y - ( y / 3 ) * 3, val);
}

SudokuBoard SudokuBoard::place(SudokuBoard SB, int x, int y, int val){
  SB.board[x / 3 + 3 * (y / 3)].insert(x - (x / 3) * 3, y - (y / 3) * 3, val);
  return SB;
}

string SudokuBoard::str(){
  stringstream ss;
  for (int i = 0; i < 9; i++){
    ss << cutstr(board[(i / 3) * 3].str(), i * 3 - (i / 3) * 9, i * 3 + 2 - (i / 3) * 9)
       << cutstr(board[(i / 3) * 3 + 1].str(), i * 3 - (i / 3) * 9, i * 3 + 2 - (i / 3) * 9)
       << cutstr(board[(i / 3) * 3 + 2].str(), i * 3 - (i / 3) * 9, i * 3 + 2 - (i / 3) * 9);
  }
  return ss.str();
}

void SudokuBoard::placeRandom(int count)
{
  vector<pair<int, int>> vecp;
  for (int i = 0; i < 9; i++){
    for (int j = 0; j < 9; j++){
      vecp.push_back(make_pair(i, j));
    }
  }
  for (int i = 0; i < 81; i++){
    vector<pair<int,int>>::const_iterator p = vecRand(vecp);
    vector<int> vec;
    for (int j = 0; j < 9; j++){
      if (canBePlaced(p->first, p->second, j))
	vec.push_back(j);
    }
    if (vec.size() > 0)
      place(p->first, p->second, *vecRand(vec));
    if (--count == 0)
      return;
    vecp.erase(p);
  }
}

void SudokuBoard::randomize(int difficulty,bool verbose, int max_threads){
  SudokuBoard();
  if (verbose) 
    cout << "Commencing randomization..." << endl;
  //placeRandom(rand() % 3 + 1);
  int solvc;
  string answ;
  if (verbose) {
    cout << "Starting step 1..." << endl;
  }
  //system("cls");
  //print();
  vector<thread> threads;
		
  SudokuBoard SB = SudokuBoard(str());
  for (int i{ 0 }; answ.size() < 1;i++){
    if (i < max_threads)
      {
	threads.push_back(thread([&, SB](){
	      srand(time(NULL));
	      solve(SB, true, solvc, answ);
	    }));
      }
    this_thread::sleep_for(chrono::seconds(1));
  }
  for (int i = 0; i < threads.size(); i++){
    if (threads[i].joinable()){
      cout << "Killing thread " << i << endl;
      threads[i].join();
      threads[i].~thread();
    }
  }
  if (verbose)
    cout << "Step 1 complete..." << endl;
  *this = SudokuBoard(answ);
  vector<pair<int, int>> vecp;
  for (int i = 0; i < 9; i++){
    for (int j = 0; j < 9; j++){
      vecp.push_back(make_pair(i, j));
    }
  }
  if (verbose){
    cout << "Starting step 2..." << endl;
  }
  int maxsize{(difficulty * 81) / 100 };
  while (vecp.size() > (81 - maxsize)){
    vector<pair<int, int>>::const_iterator p = vecRand(vecp);
    solvc = 0;
    solve(place(*this,p->first, p->second, 0) , false, solvc, answ);
    if (solvc == 1)
      place(p->first, p->second, 0);
    if (verbose)
      cout << (((81 - vecp.size()) * 100) / maxsize) << "% complete.\r";
    vecp.erase(p);
  }
  if (verbose)
    cout << "100% complete." << endl;
}

vector<int> SudokuBoard::possibleMoves(){
  vector<int> posMov(81,0);

  for (int x = 0; x < 9; x++){
    for (int y = 0; y < 9; y++){
      for (int val = 1; val < 10; val++){
	if (canBePlaced(x, y, val)){
	  posMov[x + 9 * y]++;
	}
      }
    }
  }
  return posMov;
}

void SudokuBoard::solve(SudokuBoard SB, bool random,int & solvedcount, string & SolvedBoard){
  if (SolvedBoard.size() < 1)
    solvedcount = 0;
  else if (random)
    return;
  if (solvedcount > 1)
    return;
  vector<int> posmov = SB.possibleMoves();
  int min, pos;
  if (minInRange(min, pos, posmov, 0, 10)){
    if (!random){
      for (int i = 1; i < 10; i++){
	if (SB.canBePlaced(pos - (pos / 9) * 9, pos / 9, i)){
	  solve(place(SB, pos - (pos / 9) * 9, pos / 9, i), false, solvedcount, SolvedBoard);
	}
      }
    }
    else {
      vector<int> posplace;
      vector<int>::const_iterator it;
      pos = *vecRand(findElPos(posmov,min));
      for(int i = 1; i < 10; i++){
	if (SB.canBePlaced(pos - (pos / 9) * 9, pos / 9, i)){
	  posplace.push_back(i);
	}
      }
      while (posplace.size() > 0){
	it = vecRand(posplace);
	solve(place(SB, pos - (pos / 9) * 9, pos / 9, *it), true, solvedcount, SolvedBoard);
	posplace.erase(it);
      }
    }
  }
  else {
    if (!minInRange(min, pos, str2vint(SB.str()), -1, 1)){
      ++solvedcount;
      SolvedBoard = SB.str();
      return;
    }
  }
}

void SudokuBoard::print(){
  cout << "+-----+-----+-----+" << endl;
  for (int i = 0; i < 3; i++){
    for (int j = 0; j < 3; j++){
      cout << "| ";
      for (int k = 0; k < 3; k++){
	board[k + 3 * i].printrow(j);
	cout << " | ";
      }
      cout << endl;
    }
    cout << "+-----+-----+-----+" << endl;
  }
}
