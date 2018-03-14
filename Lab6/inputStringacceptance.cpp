#include<bits/stdc++.h>

using namespace std;

int checkAcceptance(string inputString,map<char,map<char,set<string> > > &parseTable,char startSymbol)
{
    inputString += '$';
    stack<char> programStack;
    programStack.push('$');
    programStack.push(startSymbol);
    int inputStringIndex = 0;
    int isAccepted = 1;
    while(!programStack.empty() && inputStringIndex < inputString.length())
    {
        char stackTop = programStack.top();
        programStack.pop();
        if(stackTop == inputString[inputStringIndex])
        {
            inputStringIndex++;
            continue;
        }
        map<char,set<string> >::iterator cell = parseTable[stackTop].find(inputString[inputStringIndex]);
        if(cell != parseTable[stackTop].end())
        {
            string production = (*parseTable[stackTop][inputString[inputStringIndex]].begin());
            for(int i=production.length()-1;i>=0;i--)
                if(production[i] != '~') programStack.push(production[i]);
        }
        else break;
    }
    if(!programStack.empty() || inputStringIndex != inputString.length()) isAccepted = 0;
    return isAccepted;
}

void completeParseTable(map<char,map<char,set<string> > > &parseTable, map<char,map<char,int> > &follow)
{
    for(map<char,map<char,set<string> > >::iterator it = parseTable.begin();it != parseTable.end();it++)
    {
        char left = (*it).first;
        map<char,set<string> > row = (*it).second;
        map<char,set<string> >::iterator temp = row.find('~');
        if(temp != row.end())
        {
            map<char,int> followLeft = follow[left];
            for(map<char,int>::iterator bt = followLeft.begin();bt != followLeft.end();bt++)
            {
                if((*bt).first == '$')
                {
                    for(set<string>::iterator gt = (*temp).second.begin();gt != (*temp).second.end();gt++)
                    {
                        parseTable[left]['$'].insert(*gt);
                    }
                }
                else
                {
                    parseTable[left][(*bt).first].insert("~");
                }
            }
            parseTable[left].erase('~');
        }
    }
}

void findFirst(char left,vector<string> &v,map<char,map<char,int> > &first,map<char,pair<int,vector<string> > > &productions,map<char,map<char,set<string> > > &parseTable)
{
    int size = v.size();
    for(int i=0;i<size;i++)
    {
        int length = v[i].length(),j=0;
        for(j=0;j<length;j++)
        {
            if(!isupper(v[i][j]))
            {
                first[left][v[i][j]];
                parseTable[left][v[i][j]].insert(v[i]);
                break;
            }
            else
            {
                if(v[i][j] == left)
                {
                    if(first[left].find('~') == first[left].end()) break;
                    else continue;
                }
                if(productions[v[i][j]].first == 0) findFirst(v[i][j],productions[v[i][j]].second,first,productions,parseTable);
                if(productions[v[i][j]].first == 1)
                {
                    map<char,int> requiredNonTerminalFirst = first[v[i][j]];
                    int toContinue = 0;
                    for(map<char,int>::iterator it = requiredNonTerminalFirst.begin();it != requiredNonTerminalFirst.end();it++)
                    {
                        if((*it).first == '~')
                        {
                            toContinue = 1;
                            parseTable[left]['~'].insert(v[i]);
                            continue;
                        }
                        first[left][(*it).first];
                        parseTable[left][(*it).first].insert(v[i]);
                    }
                    if(!toContinue) break;
                }
                else break;
            }
        }
        if(j == length)
        {
            first[left]['~'];
            parseTable[left]['~'].insert(v[i]);
        }
    }
    productions[left].first = 1;
}

void findFollow(char right,vector<pair<char,string> > &v,map<char,map<char,int> > &follow,map<char, pair<int,vector<pair<char,string> > > > &charRHS,map<char,map<char,int> > &first)
{
    int size = v.size();
    for(int i=0;i<size;i++)
    {
        pair<char,string> prod = v[0];
        v.erase(v.begin());
        char prodLHS = prod.first;
        string prodRHS = prod.second;
        int length = prodRHS.length(),j=0;
        for(j=0;j<length;j++)
        {
            if(prodRHS[j] == right)
            {
                int k;
                for(k=j+1;k<length;k++)
                {
                    if(!isupper(prodRHS[k]))
                    {
                        follow[right][prodRHS[k]];
                        break;
                    }
                    else
                    {
                        map<char,int> temp = first[prodRHS[k]];
                        int hasNULL = 0;
                        for(map<char,int>::iterator it = temp.begin();it != temp.end();it++)
                        {
                            if((*it).first == '~')
                            {
                                hasNULL = 1;
                                continue;
                            }
                            follow[right][(*it).first];
                        }
                        if(!hasNULL) break;
                    }
                }

                if(k == length)
                {
                    if(prodRHS[j] != prodLHS)
                    {
                        if(charRHS[prodLHS].first == 0)
                        {
                            findFollow(prodLHS,charRHS[prodLHS].second,follow,charRHS,first);
                        }
                        if(charRHS[prodLHS].first == 1)
                        {
                            map<char,int> temp = follow[prodLHS];
                            for(map<char,int>::iterator it = temp.begin();it != temp.end();it++)
                            {
                                follow[right][(*it).first];
                            }
                        }
                    }
                }
                j = k;
            }
        }
    }
    charRHS[right].first = 1;
}

int main()
{
    cout<<"NOTE : '~' is taken as the NULL Production and '$' is the Input Termination Symbol(Input Right-End Marker).\n"<<endl;
	ifstream in;
	in.open("checkIfInputStringIsAcceptedByLL1GrammarInput.txt");
	int t,cases = 0;
	in>>t;
	while(t--)
	{
	    cases++;
	    cout<<"Grammar "<<cases<<" : "<<endl;

		int n;
		char startSymbol;
		in>>n>>startSymbol;
		string prods[n];
		for(int i=0;i<n;i++)in>>prods[i];
		for(int i=0;i<n;i++)cout<<prods[i]<<endl;
		cout<<endl;

		map<char,pair<int,vector<string> > > productions;
		for(int i=0;i<n;i++)
        {
            string left,right;
            int position = 0;
            position = prods[i].find(":");
            left = prods[i].substr(0, position);
            productions[left[0]].first = 0;
            right = prods[i].substr(position+1);
            position = right.find("|");
            string temp;
            while(position != -1)
            {
                temp = right.substr(0,position);
                right = right.substr(position+1);
                if(temp.find(left)) productions[left[0]].second.push_back(temp);
                else productions[left[0]].second.insert(productions[left[0]].second.begin(),temp);
                position = right.find("|");
            }
            productions[left[0]].second.push_back(right);
        }

        map<char,map<char,int> > first,follow;
        map<char, pair<int,vector<pair<char,string> > > > charRHS;
        map<char,map<char,set<string> > > parseTable;

        for(map<char,pair<int,vector<string> > >::iterator it = productions.begin();it != productions.end();it++)
        {
            vector<string> v = (*it).second.second;
            if((*it).second.first == 0) findFirst((*it).first,v,first,productions,parseTable);

            int size = v.size();
            for(int i=0;i<size;i++)
            {
                int length = v[i].length();
                for(int j=0;j<length;j++)
                {
                    if(isupper(v[i][j]))
                    {
                        if(charRHS.find(v[i][j]) == charRHS.end())
                        {
                            vector<pair<char,string> > temp;
                            charRHS[v[i][j]] = make_pair(0,temp);
                        }
                        charRHS[v[i][j]].second.push_back(make_pair((*it).first,v[i]));
                    }
                }
            }
        }

		cout<<"First : "<<endl;
        for(map<char,map<char,int> >::iterator it = first.begin();it != first.end();it++)
        {
            map<char,int> firstSet = (*it).second;
            cout<<(*it).first<<"\t:\t{ ";
            for(map<char,int>::iterator mt = firstSet.begin();mt != firstSet.end();)
            {
                cout<<((*mt).first);
                mt++;
                if(mt != firstSet.end()) cout<<", ";
            }
            cout<<" }"<<endl;
        }
		cout<<endl;

		follow[startSymbol]['$'];
        for(map<char, pair<int,vector<pair<char,string> > > >::iterator it = charRHS.begin();it != charRHS.end();it++)
        {
            vector<pair<char,string> > v = (*it).second.second;
            if((*it).second.first == 0) findFollow((*it).first,v,follow,charRHS,first);
        }

		cout<<"Follow : "<<endl;
        for(map<char,map<char,int> >::iterator it = follow.begin();it != follow.end();it++)
        {
            map<char,int> followSet = (*it).second;
            cout<<(*it).first<<"\t:\t{ ";
            for(map<char,int>::iterator mt = followSet.begin();mt != followSet.end();)
            {
                cout<<((*mt).first);
                mt++;
                if(mt != followSet.end()) cout<<", ";
            }
            cout<<" }"<<endl;
        }

        completeParseTable(parseTable,follow);

        cout<<endl<<"Parse Table : "<<endl;
        int isLL1 = 1;
        for(map<char,map<char,set<string> > >::iterator it = parseTable.begin();it != parseTable.end();it++)
        {
            cout<<((*it).first)<<"\n";
            map<char,set<string> > temp = (*it).second;
            for(map<char,set<string> >::iterator gt = temp.begin();gt != temp.end();gt++)
            {
                cout<<((*gt).first)<<" : ";
                set<string> prodList = (*gt).second;
                int size = prodList.size();
                if(size > 1) isLL1 = 0;
                set<string>::iterator st;
                for(st = prodList.begin();st != prodList.end();)
                {
                    cout<<(*st);
                    st++;
                    if(st != prodList.end())cout<<", ";
                }
                cout<<"\t\n";
            }
            cout<<endl;
        }
        if(isLL1) cout<<"This Grammar is LL(1) Grammar."<<endl<<endl;
        else cout<<"This Grammar is not LL(1) Grammar."<<endl<<endl;

        int queries;
        in>>queries;
        for(int i=0;i<queries;i++)
        {
            string inputString;
            in>>inputString;
            if(isLL1)
            {
                int accepted = checkAcceptance(inputString,parseTable,startSymbol);
                if(accepted) cout<<"The input string \""<<inputString<<"\" is ACCEPTED by this LL(1) Grammar."<<endl;
                else cout<<"The input string \""<<inputString<<"\" is NOT ACCEPTED by this LL(1) Grammar."<<endl;
            }
        }
        cout<<"\n===============================================================================================\n\n";
	}
	return 0;
}
