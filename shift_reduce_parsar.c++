#include<iostream>
#include<string.h>
#include<iomanip>
using namespace std;
void action(string c,string d){
	if(c=="r"){
		cout<<"reduce to "<<d;
	}
	else{
		cout<<"shift->"<<d;
	}
}
void print(string a,string b,string c,string d){
	a='$'+a;
	b=b+'$';
	cout<<setw(15)<<a<<setw(15)<<b<<setw(15);
	action(c,d);
	cout<<endl;
}
int main(){
	int glen;
	cout<<"enter the length of grammar : ";
	cin>>glen;
	string grammer[glen],ls[glen],rs[glen],ele;
	for(int i=0;i<glen;i++){
		cin>>grammer[i];
		int tri=0;
		rs[i]="";
		ls[i]="";
		for(int j=0;j<grammer[i].size();j++){
			if(!tri){
				ls[i]=ls[i]+grammer[i][j];
				if(grammer[i][j+1]=='-'&&grammer[i][j+2]=='>'){
					tri=1;
					j+=2;
				}
			}
			else{
				rs[i]=rs[i]+grammer[i][j];
				if(j<grammer[i].size()-1&&grammer[i][j]=='i'&&grammer[i][j+1]=='d'){
					ele=ls[i];
				}
			}
		}
	}
	string input,stack="";
	cout<<"enter the grammer to check shift reduce parser : ";
	cin>>input;
	cout<<endl<<endl<<setw(15)<<"stack"<<setw(15)<<"input"<<setw(15)<<"action"<<endl<<endl;
	for(;;){
		if(input.empty()){
			int counter=0,flag=0;
			for(int i=0;i<stack.length()-1;i++){
				if(stack[i]=='i'&&stack[i+1]=='d'){
					stack.erase(i,i+2);
					stack.insert(i,ele);
					i+=1;
					print(stack,input,"r",ele);
				}
			}
			for(int i=0;i<glen;i++){
				if(rs[i]==stack){
					stack=ls[counter];
					flag=1;
					break;
				}
			}
			if(flag){
				print(stack,input,"r",stack);
			}
			else{
				stack=stack+input[0];
				string temp="";
				temp=temp+input[0];
				input.erase(input.begin());
				print(stack,input,"s",temp);
			}
			break;
		}
		else if(stack.empty()){
			stack=stack+input[0];
			string temp="";
			temp+=input[0];
			input.erase(input.begin());
		}
		else if(!stack.empty()){
			int counter=0,flag=0;
			for(int i=0;i<stack.length()-1;i++){
				if(stack[i]=='i'&&stack[i+1]=='d'){
					stack.erase(i,i+2);
					stack.insert(i,ele);
					i+=1;
					print(stack,input,"r",ele);
				}
			}
			for(int i=0;i<glen;i++){
				if(rs[i]==stack){
					stack=ls[counter];
					flag=1;
					break;
				}
			}
			if(flag){
				print(stack,input,"r",ls[counter]);
			}
			else{
				stack=stack+input[0];
				string temp="";
				temp=temp+input[0];
				input.erase(input.begin());
				print(stack,input,"s",temp);
			}
		}
	}
	return 0;
}
