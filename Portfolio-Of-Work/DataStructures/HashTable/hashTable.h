//Wesley Taylor
//CPSC 2430
//Hashtable.h
//11/18/2015

using namespace std;
#include<fstream>
#include<iostream>
#include<string>
#include<queue>
#ifndef HASHTABLE_H
#define HASHTABLE_H

const int STORE_SIZE = 5;
const int TABLE_SIZE = 5000;
const int NUM_OF_COM = 15;
const string OUTPUT = "p5.output.txt";
class hashTable
{
  // Node to help hand collisions
  struct HNode
  {
	string word;  // where we will store the word
	int count;    // how many time the word was in the book
	int wordLength;  // how long the word is
	HNode* next;   // next pointer
  };
  //This class allows me to compare HNode objects
  class Compare
  {
  public:
	bool operator()(HNode* a, HNode* b);
  };
  HNode* table[TABLE_SIZE]; //Declares a table of size 5000
  int hash(string word);
  //HASH FUNCTION
  //breaks the word down into a key
  priority_queue <HNode*,vector<HNode*>, Compare> heap;
  //heap DR dingle approved the use of the STL
  hashTable(const hashTable* RHS);
  //Supressed copying
  hashTable* operator=(const hashTable*& RHS);
  //supressed copying
  void  heapify();
  //
  string lower(string word);
  //PRE:word may have upper case
  //POST: word will be lower case
  void insLower(string word);
  //word will be inserted into hashTable
 public:
  //Public struct which gives me access to information without revealing
  //the actual data in the table
  struct PrintNode
  {
	string word;   // word to be printed
	int count;     // how many time that word is in the table
  };
  hashTable();
  //CONSTRUCTOR
  //sets array of pointers to null
  ~hashTable();
  //DESTRUCTOR
  PrintNode** mostCommon(int count);
  //Count is the number of words you want to return
  void insert(string word);
  //inserts a word into a hash table
  //cals toLower
  bool search(string word);
  //Looks in the hash table for a word
  void print(int count, int count2);
  //Will output into a file the amount of words in book1 and in book2
  // will write the quantity request most occuring words
  // in p5.output.txt
  // POST: p5.output.txt will be created or overwritten
  
  
};
#endif
