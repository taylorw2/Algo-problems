//Wesley taylor
//CPSC 2430
//HashTable.cpp
//11/18/2015

using namespace std;

#include "hashTable.h"
#include <iostream>
#include <string>
#include <cctype>

hashTable::hashTable()
{
  for(int i = 0; i < TABLE_SIZE; i++)
	table[i] = NULL;
};

hashTable::~hashTable()
{
  HNode* delptr;   // to delete nodes
  for(int i = 0; i < TABLE_SIZE; i++){
	if(table[i]){
	  while(table[i]){
		delptr = table[i];
		table[i]= table[i]->next;
		delete delptr;
	  }
	}
  }
}

int hashTable::hash(string word)
{
  int count = 0;  //ascii value of word
  for(int i = 0; i < word.length();i++)
	if(word[i] >= 'a' && word[i] <= 'z')
	count += word[i];
  count = count % TABLE_SIZE;
  return count;
}

string hashTable::lower(string word)
{
  for(int i = 0; i < word.length(); i++){
	if(word[i] >= 'A' || word[i] <= 'Z'){
	  word[i] = tolower(word[i]);
	}
	
  }
  return word;
}

void hashTable::insLower(string word)
{
  int key;   // location in hashtable
  HNode* temp;  //creator pointer
  bool inTable = true;    // exit condition for while loop
  if( word == "")
	return;
  if(word == " ")
	return;
  if(word.length() < 5)
	return;
  word = lower(word);
  key = hash(word);
  if(!table[key]){
	temp = new HNode;
	temp->word = word;
	temp->count = 1;
	temp->wordLength = word.length();
	temp->next = table[key];
	table[key] = temp;
  }else{
	temp = table[key];
	while(inTable && temp->word != word ){
	  temp= temp->next;
	  if(!temp)
		inTable = false;
	}
	if(!inTable){
	  temp = new HNode;
	  temp->word = word;
	  temp->count = 1;
	  temp->wordLength = word.length();
	  temp->next = table[key];
	  table[key] = temp;
	}else{
	  temp->count++;
	}
  }
}




void hashTable::insert(string word)
{
  string temp;  // lowered word
  if(word.length() >= 5){
	word = lower(word);
	for(int i = 0; i < word.length(); i++){
	  if(word[i] <'a' || word[i] >'z'){
		if(word[i] == '-'){
		  insLower(temp);
		  temp = "";
		}else if( word[i] == '\''){
		  insLower(temp);
		  i = word.length();
		}else {
		  i = word.length();
		}
	  }else{
		temp+= word[i];
	  }
	}
	if(temp != " " )
	  insLower(temp);
	return;
  }
}	  
  

bool hashTable::search(string word)
{
  word= lower(word);
  int key = hash(word); //location in table
  HNode* walker = NULL;  //search walker
  if(!table[key])
	return false;
  else{
	walker = table[key];
	while(walker && walker->word != word)
	  walker = walker->next;
	if(!walker)
	  return false;
	else
	  return true;
  }
}


void hashTable::heapify()
{
  HNode* walker;  //walker to find node to push into heap
  for(int i =0; i < TABLE_SIZE; i++){
	walker = table[i];
	while(walker){
	  heap.push(walker);
	  walker = walker->next;
	}
  }
}
hashTable::PrintNode** hashTable::mostCommon(int count)
{
  PrintNode* temp;  // Creation pointer
  PrintNode** array;  // array in order of most common word in heap
  int loc = 0; // where we are in the array
  array = new PrintNode*[count];
  heapify();
  for(int i = 0; i< count; i++){
	array[i]= NULL;
  }
  while(loc < count && !heap.empty()){
	temp = new PrintNode;
	temp->word = heap.top()->word;
	temp->count = heap.top()->count;
	heap.pop();
	array[loc] = temp;
	loc++;
  }
  return array;
}

bool hashTable::Compare::operator()(HNode* a, HNode* b)
{
  return a->count < b->count;
}

void hashTable::print(int count, int count2)
{
  int index = 0;  // what index is to be printed
  ofstream outfile;  // where we are printing
  outfile.open(OUTPUT);
  PrintNode** freq = mostCommon(15);  // print Node array
  outfile << "Total Words file 1 :" << count << endl;
  outfile << "Total Words file 2 :" << count2 << endl;
  while( index < NUM_OF_COM && freq[index]){ 
	outfile << freq[index]->word;
	outfile <<' ' << freq[index]->count << endl;
	index++;
  }
    outfile.close();
}
