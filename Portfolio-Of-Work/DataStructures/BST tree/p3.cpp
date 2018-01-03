//Wesley Taylor
//CPSC 2430
//primeDupDST p3.cpp
//10/28/2015

#include <cstdlib>
#include <iostream>
#include "primeDupBSt.h"
using namespace std;

main()
{
  srand(time(0));
  primeDupBST bst;  // creats a BST
  int high ;        // number of integeras possible in rand
  int low ;         // minimum value possible in the rand
  int value;        // value looking for or deleteing
  int numOfNodes;   // howm manynodes in tree
  cout << "please enter how many numbers you want in your random generator.";
  cin >> high;
  cout << endl;
  cout << "What number would you like for your generator to start at.";
  cin >> low;
  cout << "how many numbers do you want in your tree? ";
  cin >> numOfNodes;
  for(int i = 0; i<numOfNodes; i++){
	value = bst.getRand(high, low);
	bst.insert(value);
  }
  for(int j= 0; j < 10; j++){
	value = bst.getRand(high, low);
	bst.remove(value);
  }
  bst.writeToFile();
}
