#include<bits/stdc++.h>
#include <fstream>
using namespace std;
const int alphabetSize = 26;

struct TrieNode{
	TrieNode* children[alphabetSize];
	bool isEndOfWord;
	TrieNode(){
		for(int i=0; i<alphabetSize; i++){
			children[i] = nullptr;
		}
		isEndOfWord = false;
	}
};

class Trie{
	TrieNode* root;
public:
	Trie(){
		root = new TrieNode();
	};
	void insert(string word);
	void display();
	bool checkIfInTrie(string word);
};

bool isUpper(char c){
	return c-'A' >= 0 && c-'A' <=25;
}

void Trie::insert(string word){
	TrieNode* temp = this->root;
	for(int i=0; i<word.size(); i++){
		int index;
		if(isUpper(word[i])){
			index = word[i] - 'A';
		}
		else{
			index = word[i] - 'a';
		}
		if(temp->children[index] == nullptr){
			temp->children[index] = new TrieNode();
		}
		temp = temp->children[index];
	}
	temp->isEndOfWord = true;
}

void displayUtil(TrieNode* root, string s=""){
	if(root->isEndOfWord){
		cout<<s<<endl;
	}
	for(int i=0; i<alphabetSize; i++){
		if(root->children[i] != nullptr){
			displayUtil(root->children[i], s + char(i + 'a'));
		}
	}
}

void Trie::display(){
	TrieNode* temp = this->root;
	displayUtil(temp);
}

bool Trie::checkIfInTrie(string word){
	TrieNode* temp = this->root;
	for(int i=0; i<word.size(); i++){
		int index;
		if(isUpper(word[i])){
			index = word[i] - 'A';
		}
		else{
			index = word[i] - 'a';
		}
		if(temp->children[index] != nullptr){
			temp = temp->children[index];
		}
		else{
			return false;
		}
	}
	return temp->isEndOfWord;
}

int main(){
	string line;
	ifstream fin;
	fin.open("words.txt");
	Trie* trie = new Trie();
	int c = 0;
	printf("File opened\n");
	while(fin){
		getline(fin, line);
		//cout<<line<<endl;
		trie->insert(line);
		c += 1;
		// printf("inserting\n");
		// if(c > 1000){
		// 	break;
		// }
	}
	//trie->display();
	fin.close();
	printf("Total words inserted: %d\n", c);
	fin.open("testing_words.txt");
	printf("Testing begin...\n");
	while(fin){
		getline(fin, line);
		//cout<<"Looking for "<<line<<" "<<line.size()<<endl;
		if(trie->checkIfInTrie(line)){
			cout<<"Found: "<<line<<endl;
		}
		else{
			cout<<"Not Found: "<<line<<endl;
		}
	}
	fin.close();
}