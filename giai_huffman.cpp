#include<iostream>
#include<fstream>
#include<math.h>
#include<map>
#include<stack>
using namespace std;
map<string, char> code;
int get_size(string x){
	int ans=0;
	for(int i=0;i<x.size();i++){
	ans+=(x[i]-'0')*pow(10,x.size()-i-1);
	}
	return ans;
}
string slove_1(char x){
	int b=x;
	stack<string> bnr;
	string ans="";
while(b!=0){
	if(b%2==0)
	bnr.push("0");
	else
	bnr.push("1");
	b/=2;
}

for(int i=0;i<7-bnr.size();i++){
	ans+="0";	
}
	while(!bnr.empty()){
	ans+=bnr.top();	
	bnr.pop();
	}
	return ans;
}
void slove(map<string,char> &code){

	string name;
	cin>>name;
	ifstream f(name);
	if(f==nullptr){
		cout<<"ERROR";
		exit(1);
	}
	string nd,line;
	int tt;
	getline(f,line);
tt=get_size(line);	
	getline(f,line);
int size=get_size(line);
for(int i=0;i<size;i++){
getline(f,line);
nd=line.substr(1,line.size());
code[nd]=line[0];
}
nd="";
char character;
while (f.get(character)) { 
 nd+=slove_1((char)character-40);
}
string temp="";
string ans="";
for(int i=0;i<nd.size()-tt;i++){
	if(code.find(temp)!=code.end())
	{
	if(code[temp]!='~')
	ans+=code[temp];
	else
	ans+="\n";
		temp="";		
	}
 temp+=nd[i];

}
/// viet lai vao file
int index_1=name.find('.');	
	string file_name=name.substr(0,index_1);
f.close();
file_name+="_1.txt";
ofstream f_1(file_name);
f_1<<ans;
f_1.close();
}


int main(){
	slove(code);
	return 0;
}
