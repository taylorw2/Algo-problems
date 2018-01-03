// Wesley Taylor
// CPSC 2430
// P2.cpp
// 10/20/2015

#include <iostream>
#include <math.h>
using namespace std;

struct Node  // This Struck dets up the structure of my linked list nodes
{
  int data;  // holds the values that will keep my list sorted
  Node* next;// the pointer that points to the next node in the list
};

Node* traversal(Node* head, int target);
// Takes in the head of a linked list and moves through the list
// and ends right before the target
// RETURNS: a pointer that is located right before the target value


void insert(Node*& head, int dataValue);
// PRECONDITION:: for this assignmnet isPrime and handlePrime must be called
// before insert can be called to keep the integrity of the prime list
// Takes in the refrence to the head of a linked list
// also takes in a value to be inserted into a node and put into its
// location in order in the list
int deletion(Node* head, int value);
// will delete a the first node to appear in the list with the desired value
// it
void deallocation(Node*& head);
// Deletes every node in the list and assigns head with NULL
void readList(Node* head);
// outputs every value in the list
bool isPrime(int number);
//Determins if a number is prime
int handlePrime(int primeNum);
//PRECONDITION: isPrime must be called before this to ensure a prime# is
// being inserted into this function
// Will return the previous prime to the inserted prime number minus 1

main()
{
  Node* head = NULL; // Head of the list
  for(int i = 3; i < 50; i++){
	  insert(head, i);
  }
  
  readList(head);
  deletion(head, 2);
  readList(head);
  deallocation(head);
  cout << head;
  return 0;  
}

bool isPrime(int number)
{
  for(int i =2; i<=sqrt(number); i++)
	if(number% i ==0)
	  return false;
  return true;
}

int handlePrime(int primeNum)
{
  bool primeFound = false; // Bool control variable
  int divisor = 2;         // the Divisor for the mod opperator
  if(primeNum ==3)
	return 1;
  primeNum -=2;
  while(!primeFound){
	divisor++;
	if(primeNum % divisor == 0 && primeNum != 3){
	  primeNum -= 2;
	  divisor = 2;
	}
	primeFound = (divisor >= sqrt(primeNum));
  }
  return (primeNum -1);
}

void insert(Node*& head, int dataValue)
{
  if(isPrime(dataValue)){
	dataValue = handlePrime(dataValue);
	Node* tempPtr = new Node;  // temp pointer hold node that was just created
	Node* walker;              // pointer that will iterate through the list
	tempPtr->data = dataValue;
	if(!head || tempPtr->data < head->data){
	  tempPtr->next = head;
	  head = tempPtr;
	}else{
	  walker = traversal(head, tempPtr->data);
	  tempPtr -> next = walker -> next;
	  walker -> next = tempPtr;
	}
  }
}
void readList(Node* head)
{
  Node* walker = head;  // Pointer that will walk through the list
  while(walker){
	cout << walker -> data << endl;;
	walker = walker -> next;
  }
}

Node* traversal(Node* head, int target)
{
  Node* walker = head;  // pointer that will walk through the list
  while(walker->next && target > walker->next->data)
	walker = walker -> next;
  return walker;
}

int deletion(Node* head, int value)
{
  Node* walker = traversal(head, value); // pointer that walks through the list
  Node* delPtr = walker-> next;   // pointer that marks the item to be deleted
  if(delPtr){
	walker-> next = delPtr ->next;
	delete delPtr;
  }
}

void deallocation(Node*& head)
{
  Node* delPtr;  // pointer that marks the item to be deleted
  while(head){
	delPtr = head;
	head = head -> next;
	delete delPtr;
  }
}
