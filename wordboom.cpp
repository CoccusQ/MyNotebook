#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<conio.h>
using namespace std;

vector<string> word;

void openFile(){
	ifstream f("wordlist.txt");
	string str;
	while(f>>str){
		word.push_back(str);
	}
}

void writeFile(){
	ofstream f("wordlist.txt");
	for(string s:word){
		f<<s<<" ";
	}
}

void addWords(){
	string str;
	cout<<"请输入：";
	cin>>str;
	word.push_back(str); 
}

void readWords(){
	int size=word.size();
	int index=rand()%size;
	cout<<word[index]<<endl;
}

int main(){
	srand(time(NULL));
	openFile();
	char choice;
	while(true){
		cout<<"选择：[0]存入一个词 [1]抛出一个词"<<endl;
		cin>>choice;
		if(choice=='0'){
			addWords();
			writeFile();
		}
		else if(choice=='1'){
			readWords();
		}
		cout<<"退出？[0]是 [1]否"<<endl;
		cin>>choice;
		if(choice=='0')break;
		else if(choice=='1')system("cls");
	}
	return 0;
} 
