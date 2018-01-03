//Wesley Taylor
//CPSC 2430
//tPS.cpp
//9/26/2015

#include "tPS.h"
#include <math.h>
#include <iostream>
using namespace std;

TPS::TPS()
{
  isFull = false;
  loc = 0;
  arraySize = 10;
  array = new int[10];
}

TPS::TPS(const TPS &object)
{
  array = new int[object.arraySize];
  copy(object);
}

TPS& TPS:: operator=(const TPS& rhs)
{
  if(this != &rhs)
  {
	delete[] array;
	array = new int[rhs.arraySize];
	copy(rhs);
  }
  return *this;
}

void TPS::copy(const TPS& rhs)
{
  isFull=rhs.isFull;
  loc= rhs.loc;
  arraySize = rhs.arraySize;
  for(int i =0; i < rhs.arraySize; i++)
	array[i] = rhs.array[i];
}

void TPS::resize()
{
  int* destinationArray = new int[arraySize*2];
  for(int i = 0; i < arraySize; i++)
	destinationArray[i] = array[i];
  delete[] array;
  array = destinationArray;
  arraySize = arraySize*2;
}
  
TPS::~TPS()
{
  delete[] this->array;
}

bool TPS::push(int value)
{
   if(isFull)
	 resize();
   if(value > 2){
	 if(value == 3){
	   array[loc] = 1;
	   if(loc == arraySize)
		 isFull = true;
	 }else if(isPrime(value)){
	   value = handlePrime(value);
	   array[loc] = value;
	   loc++;
	   if(loc == arraySize)
		 isFull = true;
	 }
	 return true;
   }
   return false;
}

bool TPS::isPrime(int number)
{
  bool isPrime = false;
  for(int i = 2; i <= sqrt(number);i++)
	if(number%i == 0)
	  return isPrime;
  return true;
}

int TPS::handlePrime(int primeNum)
{
  int count = 0;
  int trunkedVal;
  bool primeFound = false;
  int divisor = 2;
  primeNum = primeNum -2;
  while(!primeFound){
	  divisor++;
	  if(primeNum % divisor == 0){
		primeNum -= 2;
		divisor = 2;
	  }
	  primeFound = (divisor >= sqrt(primeNum));
  }
  return (primeNum-1);
  
}
	  
bool TPS::pop(int& value)
{
  if(loc > 0){
	loc--;
	value = array[loc];
    return true;
  }else
	return false;
}

void TPS::view()
{
  for(int i = loc; i >= 0; i--)
	cout << array[i] << endl;
}
  


