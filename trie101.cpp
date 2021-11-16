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
	TrieNode* getRoot(){
		return this->root;
	}
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

vector<string> getSuggestions(string word, Trie* trie){
	vector<string>result;
	int size = word.size();
	string temp = word;
	for(int i=size - 1; i>=0; i--){
		for(int j=0; j<26; j++){
			string wordToBeSearched = "";
			if(i == 0){
				wordToBeSearched = char(j + 'a') + word.substr(i+1, size-i-1);
			}
			else if(i == size - 1){
				//cout<<"r "<<word.substr(0,i)<<endl;
				wordToBeSearched = word.substr(0, i) + char(j + 'a');
			}
			else{
				wordToBeSearched = word.substr(0, i) + char(j + 'a') + word.substr(i+1, size - i - 1);
			}
			//cout<<wordToBeSearched<<endl;
			if(trie->checkIfInTrie(wordToBeSearched)){
				result.push_back(wordToBeSearched);
			}
		}
	}
	return result;
}

template<class T>
void displaySuggestions(vector<T>& v, int maxWords){
	int size = v.size();
	int iter = min(size, maxWords);
	for(int i=0; i<iter; i++){
		cout<<v[i]<<" ";
	}
	cout<<'\n';
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
		trie->insert(line);
		c += 1;
	}
	fin.close();
	printf("Total words inserted: %d\n\n", c);

	fin.open("testing_words.txt");
	printf("Testing begin...\n");

	bool flag = true;
	while(flag){
		cout<<"1. Test a word\n";
		cout<<"2. Exit\n";
		cout<<"Enter a code: ";
		int i;
		cin>>i;
		if(i == 1){
			cout<<"Welcome to spell check\n";
			cout<<"Enter a word to check: ";
			//string line;
			cin>>line;
			if(trie->checkIfInTrie(line)){
				cout<<"Found: "<<line<<endl<<endl;
			}
			else{
				cout<<"Not Found: "<<line<<" "<<"in the dictionary"<<endl;
				cout<<"You entered a wrong word\n";
				cout<<"Do you want suggestions(y/n): ";
				char s;
				cin>>s;
				if(s == 'y'){
					string wordEntered = "";
					if(isUpper(line[0])){
						wordEntered = char(line[0] - 'A' + 'a') + line.substr(1, line.size() - 1);
					}
					wordEntered = line;
					vector<string> words = getSuggestions(wordEntered, trie);
					cout<<"Suggestions: ";
					displaySuggestions(words, 3);
					cout<<"\n";
				}
				// else if(s == 'n'){
				// 	cout<<"Have a good life!\n";
				// }
			}
		}
		else if(i == 2){
			cout<<"Have a good day!!\n";
			flag = false;
		}
		else{
			cout<<"Warning! [Wrong Code Error]: Enter correct code(1/2)\n";
		}
	}
	// while(fin){
	// 	getline(fin, line);
	// 	//cout<<"Looking for "<<line<<" "<<line.size()<<endl;
	// 	if(trie->checkIfInTrie(line)){
	// 		cout<<"Found: "<<line<<endl;
	// 	}
	// 	else{
	// 		cout<<"Not Found: "<<line<<endl;
	// 		cout<<"You entered a wrong word\n";
	// 		cout<<"Do you want suggestions(y/n): ";
	// 		char s;
	// 		cin>>s;
	// 		if(s == 'y'){
	// 			string wordEntered = "";
	// 			if(isUpper(line[0])){
	// 				wordEntered = char(line[0] - 'A' + 'a') + line.substr(1, line.size() - 1);
	// 			}
	// 			vector<string> words = getSuggestions(wordEntered, trie);
	// 			cout<<"Suggestions: ";
	// 			displaySuggestions(words, 3);
	// 		}
	// 		else if(s == 'n'){
	// 			cout<<"Have a good life!\n";
	// 		}
	// 	}
	// }
	fin.close();
}