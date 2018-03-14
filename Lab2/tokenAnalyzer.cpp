/*
 * Write a program to calculate the token in the text given
 */

#include <iostream>
#include <bits/stdc++.h>
#include <map>
#include <iterator>

using namespace std;

 map <string, string> dict;
 
 /*Single character operator*/
 map.insert(pair <string, string> ("+", "Addition Operator"));
 map.insert(pair <string, string> ("-", "Subtraction Operator"));
 map.insert(pair <string, string> ("/", "Division Operator"));
 map.insert(pair <string, string> ("*", "Multiplication Operator"));
 map.insert(pair <string, string> ("=", "Equal Operator"));
 map.insert(pair <string, string> ("%", "Percentage Operator"));
 map.insert(pair <string, string> ("<", "Less Than Operator"));
 map.insert(pair <string, string> (">", "Greater than Operator"));
 map.insert(pair <string, string> ("?", "Question Operator"));
 map.insert(pair <string, string> (":", "Colon Operator"));
 map.insert(pair <string, string> (";", "Semi Colon Operator"));
 map.insert(pair <string, string> ("|", "Pipe Operator"));
 map.insert(pair <string, string> ("{", "Left Curly Brace Operator"));
 map.insert(pair <string, string> ("}", "Right Curly Brace Operator"));
 map.insert(pair <string, string> ("(", "Left Paranthesis"));
 map.insert(pair <string, string> (")", "Right Paranthesis"));
 map.insert(pair <string, string> ("&", "And Operator"));
 map.insert(pair <string, string> ("&", "And Operator"));
 map.insert(pair <string, string> (",", "Comma Operator"));
 map.insert(pair <string, string> ("[", "Opening Square brackets"));
 map.insert(pair <string, string> ("]", "Closing Square Brackets"));

 /*Double character Pointer*/
 map.insert(pair <string, string> ("<<", "Left Shift Operator"));
 map.insert(pair <string, string> (">=", "Greater than equal to"));
 map.insert(pair <string, string> ("<=", "Less than equal to"));
 map.insert(pair <string, string> ("==", "Equality Comparison Operator"));
 map.insert(pair <string, string> ("++", "Increment"));
 map.insert(pair <string, string> ("--", "Decrement"));
 
int main(){

	freopen("input.c","r",stdin);
	char c;
	bool isIden=false,isNumber=false,isOperator=false,isString=false;
	long count=0;
	const string operators="+-*/=><!&|%^?:",term=",;(){}";
	char ch;
	 map<string, string>::iterator it ;
	while(cin.get(c)){	
		if(c=='\\'&&isString)
		{
		cerr<<"back";
			cin.get(c);
		}
		else if(c=='\"')
		{
		cerr<<"quote";
			if(isString)
			{
				isString=false;
			}
			else
			{
				count++;
				isString=true;
			}
		}
		else if(isString)
		{
		debug(count);
		debug(c);
			continue;
		}
		else if(isalpha(c)||c=='_')
		{
			cerr<<"alpha";
			it = mp.find(c);
			if(it == mp.end())
				cout << "Key-value pair";
				cout << "Key-value pair present : "
												<< it->first << "->" << it->second ;

			
			
			
			
			if(!isIden)
			{
				count++;
				isIden=true;
			}
		}
		else if(isdigit(c))
		{
		cerr<<"digi";
			if((!isNumber&&!isIden)||c=='.')
			{
				count++;
				isNumber=true;
			}
		}
		else if(isblank(c))
		{
		cerr<<"blank";
			isIden=isNumber=isOperator=isString=false;
		}
		else if(operators.find(c)!=string::npos)
		{
		cerr<<"opera";
			if(!isOperator)
			{
				count++;
				isIden=isNumber=isOperator=isString=false;
				isOperator=true;
			}
		}
		else if(term.find(c)!=string::npos)
		{
		cerr<<"term";
			count++;
			isIden=isNumber=isOperator=isString=false;
		}
		debug(count);
		debug(c);
	}
	cout<<count<<endl;
	return 0;
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	}

