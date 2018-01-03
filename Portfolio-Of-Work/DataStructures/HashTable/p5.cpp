//Wesley Taylor
//CPSC 2430
//P5.cpp
//11/30/2015

using namespace std;

#include <iostream>
#include <string>
#include "hashTable.h"
#include <fstream>
#include <sstream>

void welcome();
// Greeting message
void handleRead(string fileName, hashTable &table, int& count);
//takes in a filename
//takes in a table
//takes in the ncount
//will read in a line and break it into astring will increment the count for
//every word
void print(hashTable &table);
//print the 20 most common words
// also print how many words are in each book
void goodbye();
//good bye message
const string FILE_ONE = "War_and_Peace.txt";
const string FILE_TWO = "Great_Expectations.txt";
const int NUM_OF_MOST_COMMON = 15;
int main()
{
  int countF1 = 0;   //fist book word count
  int countF2 = 0;   // second book word count
  hashTable table;   // the hashTable object
  welcome();
  handleRead(FILE_ONE, table, countF1);
  handleRead(FILE_TWO, table, countF2);
  table.print(countF1, countF2);
  goodbye();
}

void welcome()
{
  cout << " Hello welcome to word counter" << endl;
}

void goodbye()
{
  cout << " Have a good day"  << endl;
}

void handleRead(string fileName, hashTable &table, int& count)
{
  string line;
  string word;
  ifstream infile;
  infile.open(fileName);
  while(getline(infile,line)){
	stringstream s(line);
	while(s >> word){
	  count++;
	  table.insert(word);
	}
	
  }
  infile.close();
}

  
