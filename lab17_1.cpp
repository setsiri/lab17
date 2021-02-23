#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename,vector<string> &names,vector<int> &scores,vector<char> &grades){
	ifstream source(filename.c_str());
	string textline;
	while(getline(source,textline)){
	const char *text = textline.c_str();
	char format[]="%[^:]: %d %d %d";
	char name[100];
    int a,b,c;
        sscanf(text,format,name,&a,&b,&c);
        names.push_back(name);
        int sum=a+b+c;
        scores.push_back(sum);
        grades.push_back(score2grade(sum));

    }


}

void getCommand(string &command,string &key){
    cout<<"Please input your command: ";
    string input;
    getline(cin,input);
    char format[]="%s %[^:]";
    char c[100],k[100];
    sscanf(input.c_str(),format,c,k);
    command = c;
    key = k;
}

void searchName(vector<string> names,vector<int> scores,vector<char> grades,string key){
	cout << "---------------------------------\n";
	int count=0;
	for(unsigned int i=0;i<names.size();i++){
		if(key==toUpperStr(names[i])){
			cout<<names[i]<<"'s score = "<<scores[i]<<endl<<names[i]<<"'s grade = "<<grades[i]<<endl;
			count++;
		}
	}
	if(count==0)cout<<"Cannot found."<<endl;
	cout << "---------------------------------\n";
}

void searchGrade(vector<string> names,vector<int> scores,vector<char> grades,string key){
	cout << "---------------------------------\n";
	int count =0;
	char A = key[0];
	for(unsigned int i=0;i<names.size();i++){
		if(A==grades[i]){
			cout<<names[i]<<" ("<<scores[i]<< ")"<<endl;
			count++;
		}
	}
	if(count==0)cout<<"Cannot found."<<endl;
	cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}