#include<bits/stdc++.h>
#include<ctype.h>
#include<map>
#include<iterator>
#include<vector>

using namespace std;
map <string, vector<string> > production;
map <string, vector<string> > :: iterator it;
map <string, vector<string> > :: iterator iter;
vector<string> :: iterator i;
map <string,vector<char> > first;
map <string,vector<char> > follow;
map <string, vector<char> > :: iterator first_it;
map <string, vector<char> > :: iterator follow_it;
vector<char> :: iterator t;
vector<char> :: iterator follow_copy_it;

bool hasNull = false;

void printProductions(){
    for(it = production.begin(); it != production.end(); ++it){
            cout<<"Production "<<it->first<<": ";
            for(i = it->second.begin();  i != it->second.end(); ++i){
                cout<<*i<<" ";
            }
            cout<<endl;
          }
}
void printFirst(){

    for(first_it = first.begin(); first_it != first.end(); ++first_it){
            cout<<"First for Production "<<first_it->first<<": ";
             int visited[26] = {0};
            for(t = first_it->second.begin();  t != first_it->second.end(); ++t){
                    char c = *t;
                    if(visited[c-'a']==1){

                    }else{
                        visited[c-'a']= 1;
                        cout<<c<<" ";
                    }

            }

            cout<<endl;
          }
}
void printFollow(){
    for(follow_it = follow.begin(); follow_it != follow.end(); ++follow_it){
            cout<<"Follow for Production "<<follow_it->first<<": ";
            for(t = follow_it->second.begin();  t != follow_it->second.end(); ++t){
                    cout<<*t<<" ";
            }
            cout<<endl;
          }
}
void getTerminal(string lhs,string symbol){
    vector<string> :: iterator d;

    for(d = production[symbol].begin(); d != production[symbol].end(); ++d){
            string temp = *d;
            if(temp[0]== '#'){
                hasNull = true;
            }else if(!isupper(temp[0]) || temp[0]=='+' || temp[0]== '*' || temp[0]=='/' ||temp[0]=='-'){
                first[lhs].push_back(temp[0]);
            }else{
                for(int j=0;j<temp.length();j++){
                     if(hasNull==true && islower(temp[j])){
                        first[lhs].push_back(temp[j]);
                     }else if(isupper(temp[j])){
                         string str(1,temp[j]);
                         getTerminal(lhs,str);
                    }
                }
            }
    }
    return;
}
void calculateFirst(){
    for(it = production.begin(); it!=production.end(); ++it){

        for(i = it->second.begin(); i!= it->second.end();++i){
                string str = *i;
                if(str[0]=='#'){
                    hasNull = true;
                }else if(!isupper(str[0]) || str[0]=='+' || str[0]== '*' || str[0]=='/' || str[0]=='-'){
                    first[it->first].push_back(str[0]);
                }else{
                    for(int p=0;p<str.length();++p){
                        if(hasNull == true && islower(str[p])){
                            first[it->first].push_back(str[p]);
                        }else if(isupper(str[p])){
                             string st(1, str[p]);
                             getTerminal(it->first,st);
                            }
                    }
                }
        }
        if(hasNull==true){
             first[it->first].push_back('#');
             hasNull = false;
            }
    }
return;


}
bool containsNull(string symbol){
    vector<string> :: iterator g;

 for(g = production[symbol].begin();  g!= production[symbol].end(); ++g){
                string temp  = *g;
                for(int var = 0; var<temp.length();var++){
                            if(temp[var]=='#'){
                                return true;
                            }else if(isupper(temp[var])){
                                string s(1,temp[var]);
                                bool value = containsNull(s);
                                if(value==true){
                                    return true;
                                }

                            }
                }

          }
          return false;
}
void copyFollow(string lhs, string symbol){
        for(follow_copy_it = follow[lhs].begin(); follow_copy_it != follow[lhs].end();++follow_copy_it){

            if(std::find(follow[symbol].begin(),follow[symbol].end(),*follow_copy_it)==follow[symbol].end()){
                follow[symbol].push_back(*follow_copy_it);
            }
        }
        return;
}
void copyFirsttoFollow(string from, string to){
     for(follow_copy_it = first[from].begin(); follow_copy_it != first[from].end();++follow_copy_it){
            if(*follow_copy_it=='#'){
                continue;
            }
            if(std::find(follow[to].begin(),follow[to].end(),*follow_copy_it)==follow[to].end()){
                follow[to].push_back(*follow_copy_it);
            }
        }
        return;
}

void calculateFollow(){
    follow["S"].push_back('$');
     for(it = production.begin(); it != production.end(); ++it){
           for(iter = production.begin(); iter!=production.end();++iter){
                for(i= iter->second.begin(); i!=iter->second.end();++i){
                        string temp = *i;

                        for(int c=0;c<temp.length();c++){
                            string str(1,temp[c]);
                            if(str==it->first){
                                if(c==temp.length()-1 && containsNull(str)){
                                         copyFollow(iter->first,str);
                                    }
                                    if(c!=temp.length()-1 && (islower(temp[c+1])|| temp[c+1]=='+' || temp[c+1]=='-' || temp[c+1]== '*' || temp[c+1]=='/')){
                                        follow[it->first].push_back(temp[c+1]);
                                        c++;
                                        break;
                                    }
                                    if(c!=temp.length()-1 && isupper(temp[c+1])){
                                        string from(1,temp[c+1]);
                                        string to(1,temp[c]);
                                        copyFirsttoFollow(from,to);
                                    }
                            }
                        }
                }
           }
          }
}

int main(){
    string str[40],l,r,line;
    ifstream myfile ("Input_First_Follow4.txt");
    if (myfile.is_open())
      {
        while ( getline (myfile,line) )
        {
            char *dup = strdup(line.c_str());
			l = strtok(dup, "->");
			r = strtok(NULL,"->");
            production[l].push_back(r);
        }
        myfile.close();
      }


   /*************************************************************************************/
    /*Print Productions*/
     printProductions();
   /*************************************************************************************/
   /***************************************************************************************/
    /*Calculating First of the Grammar given*/
    calculateFirst();
    /**************************************************************************************/
     cout<<"************************************************************************"<<endl;
    /******************************************************************************************/
    /*Printing the first of the grammar*/
    printFirst();
    /****************************************************************************************/
     cout<<"***********************************************************************"<<endl;

    calculateFollow();

    /***************************************************************************************/
    /*Printing the Follow of the grammar*/
    printFollow();
    /***************************************************************************************/
return 0;
}
