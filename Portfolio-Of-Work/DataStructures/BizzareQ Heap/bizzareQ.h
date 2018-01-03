//Wesley Taylor
//CPSC 2430
//bizzareQ.h
//11/9/2015

#ifndef BIZZAREQ_H
#define BIZZAREQ_H

class bizzareQ
{
 private:
  int* array;      //Pointer to array
  int arraySize;   //size of the array
  int Loc;         //Place in the array

  void moveUp(int Location);
  //Helper function for enque and flush;
  //takes in the location of the value and moves it up to its proper Location
  //in the heap
  void moveDown(int index);
  //Helper function for Deque
  //needs to take in index so we can move down to proper spot in the array as
  //the value moves through the heap
  void heapify();
  //Sorts a array into a Max heap
  void swap(int& into, int& from);
  //Obvious
  void resize();
  //Doubles the size of the current array and copies the data over
  bizzareQ(const bizzareQ* RHS);
  //Copy constructor has been supressed
  bizzareQ* operator=(const bizzareQ*& RHS);
  //overloaded = operator has been supressed
  
 public:
  bizzareQ();
  //Constructor
  //POST
  //Will create a heap object that has the folloing methods
  ~bizzareQ();
  //Destructor
  //Deletes the array on the heap
  void enque(int value);
  //Inserts at the bottom of the array and moves the value up to proper
  //location
  int deque();
  //takes the highest value and then fixes the heap
  void flush();
  //Pulls all odd values out of the heap and resorts the heap into proper order
  void print();
  //Output function that will output the Heap onto the console
};

#endif
