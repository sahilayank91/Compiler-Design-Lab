#include <iostream>
#include <bits/stdc++.h>
#include <ctype.h>
#include <string.h>
#include <string>
using namespace std;

map<string,vector<string> > production;
map<string, vector<string> > first;
map<string, vector<string> > follow;
map<pair<string, string>, int> arr;
vector<string> symbol;

int flag = 0;

void printProductions(){
    map <string, vector<string> > :: iterator it;
    vector<string> :: iterator i;

    for(it = production.begin(); it != production.end(); ++it){
            cout<<"Production "<<it->first<<": ";
            for(i = it->second.begin();  i != it->second.end(); ++i){
                cout<<*i<<" ";
            }
            cout<<endl;
          }
}

void printFirst(){

    cout<<"First:  "<<endl;
    map <string, vector<string> > :: iterator it;
    vector<string> :: iterator i;

    for(it = first.begin(); it != first.end(); ++it){
            cout<<"First of Production "<<it->first<<": ";
            for(i = it->second.begin();  i != it->second.end(); ++i){
                cout<<*i<<" ";
            }
            cout<<endl;
          }
}

void printFollow(){
        cout<<"Follow:  "<<endl;

    map <string, vector<string> > :: iterator it;
    vector<string> :: iterator i;

    for(it = follow.begin(); it != follow.end(); ++it){
            cout<<"Follow of Production "<<it->first<<": ";
            for(i = it->second.begin();  i != it->second.end(); ++i){
                cout<<*i<<" ";
            }
            cout<<endl;
          }
}
string hasTerminal(string lhs,string symbol){
    vector<string> :: iterator it;
    for(it=production[lhs].begin();it != production[lhs].end();++it){
        string temp = *it;
        string str(1,temp[0]);
        if(str==symbol){
            return temp;
        }else if(isupper(temp[0])){
            for(int i=0;i<temp.length();++i){
                 string st(1,temp[0]);
                 string text=hasTerminal(st,symbol);
                    if(text.length()>0){
                        return text;
                    }
            }

        }
    }
    return "";
}

void createTable(){
    map<string, vector<string> > :: iterator p;
    vector<string>:: iterator it;

    for(p = production.begin(); p!=production.end();++p){
        for(it = symbol.begin(); it!=symbol.end();++it){
            arr[make_pair(p->first,*it)]=0;
        }
    }
}

void createParsingTable(){
    vector<string> :: iterator i;
    map<string, vector<string> > :: iterator p;
    map<string, vector<string> > :: iterator first_it;
    map<string, vector<string> > :: iterator follow_it;
    vector<string> :: iterator j;
    for(p=first.begin();p!=first.end();++p){
        for(i = p->second.begin();i!=p->second.end();++i){
           string temp = *i;
           if(temp[0]=='#'){
                /*If null copy production to each terminal in  the follow*/

                for(j = follow[p->first].begin();j!=follow[p->first].end();++j){

                        if(arr[{p->first,*j}]==0){
                              arr[{p->first,*j}]=1;
                        }else{
                              flag = 1;
                              return;
                        }
                }
           }
           if(arr[{p->first,*i}] == 0 ){
             arr[{p->first,*i}] = 1;
           }else{
                flag=1;
                return;
           }
        }
    }
}

void printParsingTable(){
map<pair<string, string>, int> :: iterator it;
vector<string> :: iterator i;

for(it=arr.begin();it!=arr.end();++it){
      pair <string,string> pt = it->first;
      cout<<"M["<<pt.first<<","<<pt.second<<"]:"<<it->second<<"  ";
}}

void printSymbol(){
vector<string> :: iterator i;
cout<<"The symbol are: ";
for(i = symbol.begin();i!=symbol.end();++i){
    cout<<*i<<"  ";
}
}

void createSymbolTable(){
    map<string, vector<string> > :: iterator it;
    vector<string> :: iterator i;

    for(it = first.begin(); it!= first.end();++it){
        for(i = it->second.begin();i!=it->second.end(); ++i){
            if(std::find(symbol.begin(),symbol.end(),*i)==symbol.end()){
                symbol.push_back(*i);
            }
        }
    }

     for(it=follow.begin(); it!= follow.end();++it){
        for(i = it->second.begin();i!=it->second.end(); ++i){
            if(std::find(symbol.begin(),symbol.end(),*i)==symbol.end()){
                symbol.push_back(*i);
            }
        }
    }
}

int main(){
    string l,r,line;
ifstream myfile ("first.txt");
    if (myfile.is_open())
      {
        while ( getline (myfile,line) )
        {
            char *dup = strdup(line.c_str());
			l = strtok(dup, "->");
			r = strtok(NULL,"->");
            first[l].push_back(r);
        }
        myfile.close();
      }

ifstream file ("follow.txt");
    if (file.is_open())
      {
        while ( getline (file,line) )
        {
            char *dup = strdup(line.c_str());
			l = strtok(dup, "->");
			r = strtok(NULL,"->");
            follow[l].push_back(r);
        }
        file.close();
      }

ifstream mfile ("production.txt");
    if (mfile.is_open())
      {
        while ( getline (mfile,line) )
        {
            char *dup = strdup(line.c_str());
			l = strtok(dup, "->");
			r = strtok(NULL,"->");
            production[l].push_back(r);
        }
        mfile.close();
      }


printProductions();
cout<<"*************************************************************"<<endl;
printFirst();
cout<<"*************************************************************"<<endl;

printFollow();
cout<<"*************************************************************"<<endl;

createSymbolTable();
createTable();
createParsingTable();


cout<<"Checking for Multiple entries in the Parsing table using a Boolean Flag...."<<endl;
printParsingTable();
cout<<endl<<"*************************************************************"<<endl;

cout<<"Result: "<<endl;
if(flag==0){
    cout<<"This is LL1 Grammar"<<endl;

}else{
    cout<<"This is not a LL1 Grammar"<<endl;
}
return 0;
}
