//Wesley Taylor
//CPSC 2430
//P4.cpp
//11/9/2015

using namespace std;

#include "bizzareQ.h"
#include <iostream>
#include <cstdlib>


int getRand(int highBound, int low);
//returns a random number

const int MAX = 100; // MAX value for rand function
const int MIN = 1;   // Min value for randFunction

int main()
{
  srand(time(0));
  int value;                  // where rand will dump a random value
  bizzareQ heap = bizzareQ(); // creats a new heap
  for(int j= 1; j<12; j++){
	value = getRand(MAX,MIN);
	heap.enque(value);
  }
  heap.print();
  heap.flush();
  heap.print();
}

int getRand(int highBound, int low)
{
  int value;  // place for rand to dump a value
  value = rand()% highBound + low;
  return value;
}
