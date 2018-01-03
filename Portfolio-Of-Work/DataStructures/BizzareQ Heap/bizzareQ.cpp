//Wesley Taylor
//CPSC 2430
//bizzareQ.cpp
//11/9/2015

using namespace std;

#include "bizzareQ.h"
#include <iostream>

bizzareQ::bizzareQ()
{
  arraySize = 2;    //sets array size it was set low to allow for many resizing
  Loc = 0;          // intiates Loc to zero we will increment before we insert
  array = new int[arraySize];  //pointer to dtnamic array so we can resize
}

bizzareQ::~bizzareQ()
{
  delete array;
}

void bizzareQ::print()
{
  for(int i = 1; i < Loc; i++)
	cout << array[i] << ' ';
  cout << endl;
}
void bizzareQ::enque(int value)
{
  Loc++;
  if(Loc >= arraySize-1)
  	resize();
  array[Loc] = value;
  moveUp(Loc);

}

void bizzareQ::moveUp(int Location)
{
  bool moved = true;  //Exit condition for while loop
  if(Location == 1){
   	return;
  }else{
	while(Location > 1 && moved){
	  if(array[Location] > array[Location/2]){
		swap(array[Location/2], array[Location]);
		Location = Location/2;
	  }else
		moved = false;
	}
  }
}

void bizzareQ::swap(int& into, int& from)
{
  int temp = into;  // holder for swap
  into = from;
  from = temp;
}

void bizzareQ::resize()
{
  int* nArray = new int[arraySize*2];   //creats the new array for info to go
  for(int j = 0; j < arraySize; j++)
	nArray[j] = array[j];
  delete array;                         // deletes the old array
  array = nArray;
  arraySize = 2*arraySize;
}
  
int bizzareQ::deque()
{
  int rValue = array[1];              // Value to be returned whien it is deque
  array[1] = array[Loc];
  moveDown(1);
  Loc--;
  return rValue;
}

void bizzareQ::moveDown(int index)
{
  while(index < Loc){
	if(array[2*index] > array[(2*index) + 1]){
	  swap(array[2*index], array[index]);
	  index = 2*index;
	}else{
	  swap(array[(2*index) + 1], array[index]);
	  index = (2* index) + 1;
	}
  }
}

void bizzareQ::flush()
{
  int index ;
  for(int i= Loc; i >0 ; i--){
	if(i == Loc && array[i]% 2 != 0){
	  Loc--;
	}else if(array[i]% 2 != 0){
	  swap(array[i], array[Loc]);
	  Loc--;
	}
  }
  for(int n = Loc; n > 0; n--){
	moveUp(n);
  }
  Loc++;
}
