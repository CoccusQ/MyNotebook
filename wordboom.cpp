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
	cout<<"�����룺";
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
		cout<<"ѡ��[0]����һ���� [1]�׳�һ����"<<endl;
		cin>>choice;
		if(choice=='0'){
			addWords();
			writeFile();
		}
		else if(choice=='1'){
			readWords();
		}
		cout<<"�˳���[0]�� [1]��"<<endl;
		cin>>choice;
		if(choice=='0')break;
		else if(choice=='1')system("cls");
	}
	return 0;
} 
