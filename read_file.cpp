#include<bits/stdc++.h>
#include<fstream>
using namespace std;

int main(){
	string line;
	ifstream fin;
	fin.open("words.txt");
	while(fin){
		getline(fin, line);
		cout<<line<<" "<<line.size()<<endl;
	}
	fin.close();
}