//Wesley Taylor
// CPSC 2430
// primeDupBST.cpp
// 10/28/2015

#include <fstream>
#include <math.h>
#include <iostream>
#include <stack>
#include "primeDupBSt.h"
#include <cstdlib>
using namespace std;

primeDupBST:: primeDupBST()
{
  root = NULL;
}

primeDupBST:: ~primeDupBST()
{
  clear(root);
}

void primeDupBST::clear(TNode*& root)
{
  TNode* delPTR; //ensures we dont loose the node before its deleted
  if(!root)
	return;
  else{
	clear(root->left);
	clear(root->right);
	delPTR = root;
	root = NULL;
	delete delPTR;
  }
}

int primeDupBST::getRand(int highBound, int low)
{
  int value;
  value = rand()% highBound +low;
  return value;
}

bool primeDupBST::isPrime(int number)
{
  bool isPrime = false;
  for(int i = 2; i <= sqrt(number);i++)
	if(number%i == 0)
	  return isPrime;
  return true;
}	
void primeDupBST::insert(int value)
{
  
  bool InTree = search(value);
  TNode* walker = root;
  bool inserted = false;
  if(!root){
	root = new TNode;
 	root->data = value;
	inserted = true;
  }
  if(!isPrime(value)&& InTree)
	 return;
  else{
	while(!inserted){
	  if(isPrime(value) && walker->data == value){
		walker->count++;
		inserted = true;
	  }else{
		if(walker->data >= value){
		  if(walker->left)
			walker = walker->left;
		  else{
			walker->left = new TNode;
			walker->left->data = value;
			inserted = true;
		  }
		}else{
		  if(walker->right)
			walker= walker->right;
		  else{
			walker->right = new TNode;
			walker->right->data = value;
			inserted = true;
		  }
		}
	  }
	}	  
  }
}
void primeDupBST::inOrderTrav(TNode* root, ofstream& outfile)
{
  if(!root)
	return;
  inOrderTrav(root->left, outfile);
  outfile << root->data << " " ;
  inOrderTrav(root->right, outfile);
  return;
}

void primeDupBST::inOrderTrav(TNode* root)
{
  if(!root)
	return;
  inOrderTrav(root->left);
  cout << root->data << " " ;
  inOrderTrav(root->right);
  return;
}

bool primeDupBST::search(int value)
{
  TNode* walker = root;
  bool found = false;
  bool InTree = true;
  if(!root)
	InTree = false;
  while(!found && InTree){
	if(walker->data == value){
	  found = true;
	}else if(walker->data > value && walker->left)
	  walker = walker->left;
	else if(walker->data > value && !walker->left)
	  InTree = false;
	else if(walker->data < value && walker->right){
	  walker= walker->right;
	}else
	  InTree = false;
  }
  return InTree;
}

void primeDupBST::PreTrav(TNode* root, ofstream& outfile)
{
  TNode* walker = root;
  stack< TNode* > s;
  int count = 0;
  do{
	if(walker){
	  s.push(walker);
	  //handle root
	  outfile << walker->data << ' ';
	  walker= walker ->left;
	}else{
	  walker = s.top();
	  s.pop();
	  walker = walker->right;
	}
  }while(!s.empty()|| walker);
  outfile << endl;
}

void primeDupBST::PreTrav(TNode* root)
{
  TNode* walker = root;
  stack< TNode* > s;
  int count = 0;
  do{
	if(walker){
	  s.push(walker);
	  //handle root
	  cout << walker->data << ' ';
	  walker= walker ->left;
	}else{
	  walker = s.top();
	  s.pop();
	  walker = walker->right;
	}
  }while(!s.empty()|| walker);
}

//PRECONDITION: value must be in tree
void primeDupBST:: removeHelper(TNode*& root, int value)
{
  TNode* delPtr;
  int minRST;
  if(!root)
	return;
  else{ // Move to the target
	if(root->data > value)
	  removeHelper(root->left, value);
	else if(root->data < value)
	  removeHelper(root->right, value);
	else{
	  if(!root->left && !root->right){  //NO CHILD
		if(isPrime(value) && root->count > 0)
		  root->count--;
		else{
		  delPtr = root;
		  root= NULL;
		  delete delPtr;
		}
	  }else if(!root->left && root->right){ //Right Child
		if(isPrime(value) && root->count >0){  
		}else{
		  delPtr = root;
		  root = root->right;
		  delete delPtr;
		}
	  }else if(!root->right && root->left){  //Left Child
		if(isPrime(value) && root->count >0){
		  root->count--;
		}else{  
		  delPtr = root;
		  root= root->left;
		  delete delPtr;
		}
	  }else{   //two Childred
		minRST = findMinRST(root); //Forces one of the above conditions
		removeHelper(root, minRST);
		root->data = minRST;
	  }
	} 
  }
}


int primeDupBST:: findMinRST(TNode* root)
{
  TNode* delPTR;
  int RST;  // minimun in the Right sub tree
  TNode* walker = root;
  walker = walker->right;
  while(walker->left)
	walker = walker->left;
  RST = walker->data;
  return RST;
}

void primeDupBST:: remove(int value)
{
 bool InTree;
  InTree = search(value);
  if(!InTree)
	return;
  else{
	removeHelper(root, value);
  }
}

void primeDupBST:: writeToFile()
{
  ofstream outfile;
  outfile.open("p3output.txt");
  outfile << "preorder Taversal " << endl;
  PreTrav(root ,outfile);
  outfile << endl << "inOrder Traversal" << endl;
  inOrderTrav(root, outfile);
  outfile.close();
}

void primeDupBST::printIOT()
{
  inOrderTrav(root);
  }

void primeDupBST::printPOT()
{
  PreTrav(root);
}


/*void primeDupBST:: removeHelper(TNode*& root, int value)
{
  bool found = false;
   TNode* prev;
   TNode* walker = root;
   int RSTmin;
 	while(!found){
	  if(value == walker->data)
		found = true;
	  else if(value < walker->data){
		prev = walker;
		walker = walker->left;
	  }else{
		prev = walker;
		walker = walker->right;
	  }
	}
   	if(root == walker)
	  
	if( walker && !walker->right && !walker->left){
	  delete walker;
	  //	  prev->right =NULL;
	  //}else if(prev->left== walker && !walker->right && !walker->left){
	  // delete walker;
	   // prev->left =NULL;
	}else if(prev->right == walker && walker->left && !walker->right){
	  prev->right = walker->left;
	  delete walker;
	}else if(prev->left == walker && walker->left && !walker->right){
	  prev->left = walker->left;
	  delete walker;
	}else if(prev->left == walker && walker->right && !walker->left){
	  prev->left = walker -> right;
	  delete walker;
	}else if(prev->right == walker && walker->right&&!walker->left){
	  prev->right = walker->right;
	  delete walker;
	}else{
	  RSTmin = findMinRST(walker);
	  walker->data = RSTmin;
	  removeHelper(walker->right, RSTmin);
	}
	return;
}*/
