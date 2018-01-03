//Wesley Taylor
//CPSC 2430
//tPS.h
//9/26/2015

#ifndef TPS_H
#define TPS_H
class TPS
{
 private:
  int* array;     // The array where vvalues will be stored
  bool isFull;    // Flag to tell my when the array is full
  int  loc;       // location in the array
  int arraySize;  // how big the array is

  void copy(const TPS& rhs);
  // the section of code that actually copies data for Overload=
  // and copyconstructor

  bool isPrime(int number);  
  //Checks to see if the Value truely is a prime number
  
  void resize();
  //resizes the array
  
 public:
  //Constructor
  TPS();

  //Copy Constructor
  TPS(const TPS &object);

  //overloaded assignment opperator
  TPS& operator=(const TPS &rhs);

  //Destructor
  ~TPS();
  
  bool push(int value);
  // Checks to see if the array needs to be resized then checks
  // if the  number is prime then calls handleprime and loads the returned value in to
  // the array

  bool pop(int& value);
  //pulls the last value inserted into the stack

  void view();

  int handlePrime(int primeNum);
  //finds the prime preeceding the given prime number then decrements it by 1
  
};
#endif

  
