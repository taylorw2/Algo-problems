#include <map>
#include <string>
#ifndef PREFIX_TREE_H
#define PREFIX_TREE_H

struct PTNode{
	bool isWord;
	int count;
	std::map<char, PTNode*> children;
	double latitude;
	double longitude;
	
};

class Prefix_Tree{
	private:
		PTNode *root;


	public:
		Prefix_Tree();
		~Prefix_Tree();
		void insert_word(std::string word, double latitude, double longitude);
		int find_word(std::string word, double &latitude, double &longitude);
		

};

#endif
