// Wesley Taylor
// CPSC 2430
// p1.cpp
// 10/5/2015

#include <iostream>
#include "tPS.h"
#include <fstream>

using namespace std;

void welcome();
void goodBye();

// precondition: You need to have p1input.txt or some other file with numbers in a column to use
//              to have this function
int handleReadFile(TPS& stack);
// Will get the values from the file and push the numbers taht match the condition
// on to the stack. Then will close the file. 

// Precondition Stack Must have at least a single element in to pop.
void writeFile(TPS& stack);
// post condition will crate a file named p1output.txt

const string FILENAME = "p1input.txt";

main()
{
  TPS stack1;
  welcome();
  handleReadFile(stack1);
  writeFile(stack1);
  goodBye();
  
  return 0;

}

void welcome()
{
  cout << "Welcome to the Transform Prime Stack program" << endl;
}

void goodBye()
{
  cout << "THANK YOU! Have a good day." << endl;
  cout << "press enter to exit the program" << endl;
  cin.ignore();
}

int handleReadFile(TPS &stack)
{
  int value;        // value from file
  string file;      // string that allows for any filename
  ifstream infile;  
  cout << "Please enter the name of the file you wish to open" << endl;
  cout << "press n to use default file. " ;
  cin >> file;
  cin.ignore();
  if(file == "n")
	file = FILENAME;
  infile.open(file.c_str());
  if(infile.fail()){
	cout << "Cannot find file Program closing" << endl;
	return 0;
  }
  while(!infile.eof()){
	infile >> value;
	stack.push(value);
  }
  infile.close();
  return 0;
}

void writeFile(TPS &stack)
{
  int value;         //value to be written to the file
  ofstream outFile;  
  outFile.open("p1output.txt");
  while(stack.pop(value))
	outFile << value << endl;
  cout <<"The stack has been written to p1output.txt" << endl;
  outFile.close();
}
