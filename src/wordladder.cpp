// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "queue.h"
#include "stack.h"
#include <set>
#include "lexicon.h"

using namespace std;
const string ERROR_MSG="Can't open the file specified, please try again: ";
const string PROMPT_FILE_MSG="Grid input file name? ";
string promptUserFile(ifstream & infile, string prompt= "");
//bool isInDictionary(Lexicon &lex, string word);
void buildWordLadder(Lexicon &lex, string word, string word2, Queue<Stack<string>> & mydict);
bool CheckUsedWords(string word, set<string> &myset);
int main() {

    ifstream infile;
    promptUserFile(infile,PROMPT_FILE_MSG);
    Lexicon dict(infile);
    cout<<dict.size()<<endl;
    cout <<"Enter a word: ";
    string word1;
    string word2;
    getline(cin,word1);
    cout <<"Enter a second word: ";
    getline (cin,word2);
    Queue<Stack<string>> queue;
    buildWordLadder(dict ,word1, word2, queue);



    cout << "Have a nice day." << endl;
    return 0;
}

string promptUserFile(ifstream &infile, string prompt){
    while (true) {
        cout << prompt;
        string filename;
        getline(cin, filename);
        infile.open(filename.c_str());
        if (!infile.fail()) return filename;
        // infile.clear();
        cout<<ERROR_MSG <<endl;
        if (prompt=="") prompt = PROMPT_FILE_MSG;

    }

}
//bool isInDictionary(Lexicon &lex, string word){
//   return lex.contains(word);
// }


void buildWordLadder(Lexicon &lex, string word, string word2, Queue<Stack<string>> & mydict){
    string xword=word2;
    set<string> usedWords;
    Stack<string>mystack;
    usedWords.insert(word);
    usedWords.insert(word2);
    int i=0;
    while (true){
        //if (xword==word) goto endloop;
        for (i=0; i<=word.length(); i++){
            for (char c='a';c<='z';c++){
                xword[i]=c;
                bool inDictionary=lex.contains(xword);
                if (inDictionary){
                    bool checkUsedWords=(usedWords.find(xword)==usedWords.end())? true:false;
                    if (checkUsedWords){
                        mystack.push(xword);
                        usedWords.insert(xword);
                        mydict.enqueue(mystack);}

                    if (xword==word) goto endloop;
                }
            } if (!mystack.isEmpty()) {xword[i]=word[i];}
            else {
                string temp=mystack.pop();
                xword[i]=temp[i];
            }

        }
        i=0;
    }
endloop:
    cout<<"The shortest path from the word "<<word<< " to the "<<word2<< " is: \n";
    while (!mydict.isEmpty()){
        cout<< mydict.dequeue().pop()<<"->";
    }
}

bool CheckUsedWords(string word, set<string>& myset){
    if (myset.find(word)==myset.end()) return true;
    return false;

}

