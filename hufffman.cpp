#include<iostream>
#include <queue>
#include<map>
#include<fstream>
using namespace std;
map<char,string> huffman;
class minheap{
  public:		
	int num;
	char chacter;

	minheap* left;
	minheap* right;
  
	minheap (char chacter,int num){
		this->chacter=chacter;
		this->num=num;
	
	    left=nullptr;
	   right= nullptr;
	}

};
void swap(int &a,int& b){
	int temp=a;
	a=b;
	b=temp;
}
void swap(char &a,char& b){
	int temp=a;
	a=b;
	b=temp;
}

/// buid huffmantree
void heapfy(char mes[],int nums[],int size){
	int index=size-1;
	while(index>=0){
		
	int temp=index;
	while(temp>0){
		int par=(temp-1)/2;

	if(par>=0&&nums[temp]<nums[par])	
{

		swap(nums[temp],nums[par]);
		swap(mes[temp],mes[par]);
}
	temp=par;
	}
	index--;	
	}

}
void insert_heapfy(char mes[],int nums[],int& size,int vaule){
	size++;
	int index=size-1;
	nums[index]=vaule;
	mes[index]='~';
	while(index>=0){
		int par=(index-1)/2;
	if(par>=0&&nums[par]>nums[index]){
		swap(nums[par],nums[index]);
		swap(mes[par],mes[index]);
	index=par;	
	}
		else 
		break;
	}
}
///// xoa min heap
void dele_heafy(char mes[],int nums[],int& size){
	swap(nums[0],nums[size-1]);
	swap(mes[0],mes[size-1]);
	size--;
	int index=0;
	while(index<size){
	int left=index*2+1;
	int right=(index+1)*2;
	if(left<size&&nums[left]<nums[index]&&(right>=size||nums[left]<=nums[right]))
	{
		swap(nums[left],nums[index]);
		swap(mes[left],mes[index]);
		index=left;
	}
	else if(right<size&&nums[right]<nums[index]&&(left>=size||nums[right]<nums[left	])){
		swap(nums[right],nums[index]);
		swap(mes[right],mes[index]);
		index=right;
	}
	else break;
	}
	
}

/////// tao code cho key
	void huffmancode(minheap* root,string s,map<char,string>& huffman){
	if(root==nullptr)
	return;

	if(root->chacter!='~'){
	huffman[root->chacter]=s;	
	}
	 huffmancode(root->left,s+"0",huffman);
	 huffmancode(root->right,s+"1",huffman);	
	}
	
	
	
	
	/// tap cay huffman
	minheap* BuildHuffMantree(char mes[],int nums[],int size,map<char,int> mes_and_num){
	heapfy(mes,nums,size);
	/// dua num ve dang min heap, mes di theo nums
	map <char,minheap*> chacter;
	//// dia chi chua node
	queue<minheap*> q;
	///////// dia chi chua $
	
	while(size>1){
		minheap* temp1;	
	if(mes[0]!='~')
		{
		temp1	=new minheap(mes[0],nums[0]);
			chacter[mes[0]]=temp1;
		}
	else {
		temp1=q.front();
		q.pop();
	}
	dele_heafy(mes,nums,size);
	minheap* temp2;
	if(mes[0]!='~')
		{
		 temp2	=new minheap(mes[0],nums[0]);	
		chacter[mes[0]]=temp2;
		}
	else {
		temp2=q.front();
		q.pop();
	}
	int sum=temp1->num+temp2->num;
	minheap* root=new minheap('~',sum);
	root->left=temp1;
	root->right=temp2;
	q.push(root);
	dele_heafy(mes,nums,size);
	insert_heapfy(mes,nums,size,temp1->num+temp2->num);
	}
	
	minheap* root=q.front();
	string s="";

	huffmancode(root,s,huffman);

	}
///// doc file	
int pow(int x,int y){
	if(y==0)
	return 1;
	return x*pow(x,y-1);
}
int slove_1(string new_mes){
	int ans=0;
	int size=new_mes.size();
	for(int i=0;i<size;i++){
	ans+=(new_mes[i]-'0')*pow(2,size-i-1);	
	}
	//// chuyen nhi phan sang thap phan
	return ans;
}
slove(int *new_mes_code,string huffcode,int size){
	int d=huffcode.size()%7;
	
	if(d!=0){	
		for(int i=0;i<7-d;i++){
			huffcode+='0';
		}
	}
string* new_mes=new string [size]();
for(int i=0;i<huffcode.size();i++){
new_mes[i/7]+=huffcode[i];
}
 for(int i=0;i<size;i++){
 	new_mes_code[i]=slove_1(new_mes[i]);	
 }
 ///// new_mes_code ma thap phan de chuyen doi ASCII
 delete [] new_mes;
}
void mes_num(string name) 
{ 
	int index_1=name.find('.');	
	string file_name=name.substr(0,index_1+1);
file_name+="zip";
	map<char,int> mes_and_num;
ifstream f(name);
/// mo file

if(!f.is_open())
{
	cout<<"can't open 1";
	exit(1);
}

string nd;  /// noidung 
string line;/// dong

while(getline(f,line)){

nd+=line;
nd+='\n';
//// lay noi dung tung dong	
}
f.close();
for(auto i:nd){
if(mes_and_num.find(i)==mes_and_num.end()){
mes_and_num[i]=1;	
}	
else{	
mes_and_num[i]++;	
}
}
char mes[100];
int nums[100],index=0;

for(auto i : mes_and_num){

	mes[index]=i.first;
	nums[index++]=i.second;
}

int size=index;

BuildHuffMantree(mes,nums,size,mes_and_num);
/////// huffman map<char, string >
string huffcode="";
for(auto i:nd){
huffcode+=huffman[i];	
}
	
int size_new;
if(huffcode.size()%7==0)
size_new=huffcode.size()/7;
else
size_new=(huffcode.size()/7)+1;	

int *new_mes_code=new int[size_new];
slove(new_mes_code,huffcode,size_new);
char * new_mes=new char[size_new];
for(int i=0;i<size_new;i++){
new_mes[i]=new_mes_code[i];

}

delete [] new_mes_code;
ofstream f_1(file_name);

if(!f_1.is_open()){
	cout<<"can't open";
	exit(1);
}
int dem=0;
f_1<<huffcode.size()%7<<endl;
f_1<<huffman.size()<<endl;
for(auto i: huffman){
	if(i.first!='\n')
	f_1<<i.first<<i.second<<endl;
	else
	f_1<<"~"<<i.second<<endl;
}
for(int i=0;i<size_new;i++){	
f_1.put((char)new_mes[i]+40);
}
f_1.close();
}
int main(){

string name;
cin>>name;
	
mes_num(name);
return 0;

}
