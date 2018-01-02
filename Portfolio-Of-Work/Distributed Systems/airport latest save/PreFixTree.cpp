#include "PreFixTree.h"
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

Prefix_Tree::Prefix_Tree(){
	root = new PTNode();
	root->isWord = false;
	root->count = 0;
	root->latitude = 0;
	root->longitude = 0;
}

void destroy(PTNode* root){
	for(auto itor : root->children){ //call destroy for each subtree
		destroy(root->children[itor.first]);
	}
	delete root;
}
Prefix_Tree::~Prefix_Tree(){
	destroy(root);
}

void insert_word_helper(PTNode *root, string word, double latitude, double longitude){
	if(word.size() == 0){//at end of word
		root->isWord = true;
		root->count += 1;
		root->latitude = latitude;
		root->longitude = longitude;
	}else{//add another letter
		root->count += 1;
		char cur_char = word[0];
		if((root->children).find(cur_char) == (root->children).end()){
			//No Node for current leeter, make a new one
			PTNode *child = new PTNode();
			child->isWord = false;
			child->count = 0;
			child->latitude = 0;
			child->longitude = 0;
			(root->children)[cur_char] =  child;
		}
		//recursive call slicing off first letter
		insert_word_helper(root->children[cur_char], word.substr(1), 
					latitude, longitude);
	}
}

void Prefix_Tree::insert_word(string word, double latitude, double longitude){
	transform(word.begin(), word.end(), word.begin(), ::tolower);
	insert_word_helper(this->root, word, latitude, longitude);
}
//int find_word_helper(PTNode* root, string word, double &latitude, double &longitude);
//int finish_word(PTNode* root, double &latitude, double &longitude){
//	char cur_char = root->children.begin()->first;
//	return find_word_helper(root->children[cur_char], "", latitude, longitude);
        
	
	
//}
int find_word_helper(PTNode* root, string word, double &latitude, double &longitude){
	if(word.size() == 0){//hit end of given input
		if(root->isWord){//need to return locatioin
	
			latitude = root->latitude;
			longitude = root->longitude;
			return 0;
		}else if(root->count != 1){
			return 1; //ambiguous
		}
		char cur_char = root->children.begin()->first;
		return find_word_helper(root->children[cur_char], "", latitude, longitude);
		//return finish_word(root, latitude, longitude);//we need to finish the word
	}else{
		char cur_char = (char) word[0];
		if((root->children).find(cur_char) != (root->children).end()){
			return find_word_helper(root->children[cur_char], //dig deeper
				word.substr(1) , latitude, longitude);
		}
	}
	return 2; //run off the tree, no city matches
	
}
int Prefix_Tree::find_word(string word, double &latitude, double &longitude){
	transform(word.begin(), word.end(), word.begin(), ::tolower);
	return find_word_helper(this->root, word, latitude, longitude);
}
/*
int main(){
	Prefix_Tree pft;
	double x = 73.234;
	double y = 93.11;
	pft.insert_word("Hello", x, y);
	pft.insert_word("hi", x, y);
	pft.insert_word("Cat flames", 3.2, 4.2);
	x = 0;
	y = 0;
	int ret = 0;
	ret = pft.find_word("Hi" , x, y);
	printf("%d\n", ret);
	ret = pft.find_word("Hiasdjflkasjdflaksdf" , x, y);
	printf("%d\n", ret);
	ret = pft.find_word("H" , x, y);
	printf("%d\n", ret);
	ret = pft.find_word("cat" , x, y);
	printf("%s%f\n", "x: ", x);
	printf("%s%f\n", "y: ", y);
	ret = pft.find_word("hello" , x, y);
	printf("%s%f\n", "x: ", x);
	printf("%s%f\n", "y: ", y);
	return 0;
}
*/
