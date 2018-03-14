#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

int main(){
	
	string str[10];
	int k=0;		
  /*Reading the file */	
  string line;
  ifstream myfile ("inputleftRecursion");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
	  str[k] = line;
	  k++;	
    }
    myfile.close();
  }	
  
  /*Printing what is read from the file*/
 /* for(int i=0;i<k;i++){
	  cout<<str[i]<<endl;  
	  }
	*/
	
	string l,r;
	char *temp;
	int flag=0;
	
	
	/*Stack to store the processed productions*/
	
	stack <string> st;
	cout<<endl<<"The productions with no left Recursion are: "<<endl<<endl;
	/*creating function to remove left recursion*/
	for(int i=0;i<k;i++){
		char *dup = strdup(str[i].c_str());
		l = strtok(dup, "->");
		r = strtok(NULL,"->");
		
		dup = strdup(r.c_str());
		temp = strtok(dup,"|");
		
		cout<<endl<<"Production with "<<l<<":"<<endl;
			
		while(temp){
			if(temp[0]==l[0]){
				flag=1;
				/*Printing the production with no left recursion*/
				cout<<l<<"'"<<"->"<<temp+1<<l<<"'"<<endl;			
				cout<<l<<"'"<<"->"<<"NULL"<<endl;
				}else if(flag==1){
				
				/*If there was left recursion in the previous production of the same production*/
				
				std::string s(temp);
				st.push(l+"->" +temp + l);
				
				//cout<<l<<"->"<<temp<<l<<"'"<<endl;
				
		}else{
			/*If there was no left recursion in the production*/
			//cout<<l<<"->"<<temp<<endl;
			std::string s(temp);
			st.push(l+"->"+s);
			
			}
			 temp = strtok(NULL,"|");
		}
		
		if(flag==1){
			while (!st.empty())
			{
				cout <<st.top() <<l<<"'"<<endl;
				st.pop();
			}
			}else{
				cout<<"There was no Left Recursion in the production"<<endl<<endl;	
				}
		
		/*Removing flag to get into the second production*/
		flag=0;		
		
		free(dup);
		}
	
	

	
	
	
	
	return 0;
	}
