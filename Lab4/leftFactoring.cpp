// A Program to find the longest common
// prefix of the given words

#include<bits/stdc++.h>
#include<string>
#include<string.h>
#include<iostream>
using namespace std;

// Alphabet size (# of symbols)
#define ALPHABET_SIZE (26)

// Converts key current character into index
// use only 'a' through 'z' and lower case
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

// Trie node
struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];

    // isLeaf is true if the node represents
    // end of a word
    bool isLeaf;
};

// Returns new trie node (initialized to NULLs)
struct TrieNode *getNode(void)
{
    struct TrieNode *pNode = new TrieNode;

    if (pNode)
    {
        int i;

        pNode->isLeaf = false;

        for (i = 0; i < ALPHABET_SIZE; i++)
            pNode->children[i] = NULL;
    }

    return pNode;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just marks leaf node
void insert(struct TrieNode *root, string key)
{
    int length = key.length();
    int index;

    struct TrieNode *pCrawl = root;

    for (int level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

        pCrawl = pCrawl->children[index];
    }

    // mark last node as leaf
    pCrawl->isLeaf = true;
}

// Counts and returns the number of children of the
// current node
int countChildren(struct TrieNode *node, int *index)
{
    int count = 0;
    for (int i=0; i<ALPHABET_SIZE; i++)
    {
        if (node->children[i] != NULL)
        {
            count++;

*index = i;
        }
    }
    return (count);
}

// Peform a walk on the trie and return the
// longest common prefix string
string walkTrie(struct TrieNode *root)
{
    struct TrieNode *pCrawl = root;
    int index;
    string prefix;

    while (countChildren(pCrawl, &index) == 1 &&
            pCrawl->isLeaf == false)
    {
        pCrawl = pCrawl->children[index];
        prefix.push_back('a'+index);
    }
    return (prefix);
}

// A Function to construct trie
void constructTrie(string arr[], int n, struct TrieNode *root)
{
    for (int i = 0; i < n; i++)
        insert (root, arr[i]);
    return;
}

// A Function that returns the longest common prefix
// from the array of strings
string commonPrefix(string arr[], int n)
{
    struct TrieNode *root = getNode();
    constructTrie(arr, n, root);

    // Perform a walk on the trie
    return walkTrie(root);
}

// Driver program to test above function
int main()
{

    cout<<"Please Use Only Lower case letters for the input at RHS"<<endl;
    string str[50];
	string prod[50];
	int k=0;
      /*Reading the file */
      string line;
      ifstream myfile ("inputLeftFactoring.txt");
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
  cout<<"The input is: "<<endl;
  for(int i=0;i<k;i++){
	  cout<<str[i]<<endl;
	  }




	/*Stack to store the processed productions*/

	string arr[50];
	int p=0;
	string l,r;

	int flag=0;
	char *temp;
    /*creating function to remove left recursion*/
	for(int i=0;i<k;i++){
		char *dup = strdup(str[i].c_str());
		l = strtok(dup, "->");
		r = strtok(NULL,"->");

		dup = strdup(r.c_str());
		temp = strtok(dup,"|");

		cout<<endl<<"Production with "<<l<<":"<<endl;


        /*Stored all the productions in the stack*/
		while(temp){
            arr[p++] = temp;
            temp = strtok(NULL,"|");
		}

        string ans = commonPrefix(arr, p);
        cout<<"The common Prefix is: "<<ans<<endl;

            if(ans.length() && p > 1){
                cout<<l<<"->"<<ans<<l<<"'"<<endl;
                for(int j=0;j<p;j++){


                    char *pch = strdup(arr[j].c_str());
                    char *an = strdup(ans.c_str());
                    pch = strstr(pch,an);
                    if(pch){
                        std::string str2 = arr[j].substr(ans.length());
                        if(str2.length()){
                            cout<<l<<"->"<<str2<<l<<"'"<<endl;
                            flag=1;
                        }
                    }else{
                        cout<<l<<"->"<<arr[j]<<endl;
                    }
                }

            }else{
                cout<<"There was no need of Left Factoring (No Ambiguity Found)"<<endl;

            }


            if(flag==1){
                cout<<l<<"->"<<"NULL"<<endl;
            }
            flag=0;


            p=0;

            free(dup);
		}



    return (0);
}
