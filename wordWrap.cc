//1 args from command line, positive int, default 25
//stdin sequence of words
//word vs rest line: word longer go to next new line
//word vs empty line: longer break

#include <iostream>
#include <string>
#include <sstream>

using std::string;
using std::cin;
using std::cout;
using std::istringstream;
using std::endl;

void wordWrap(int line = 25);
void printWord(string word, int& rest, int line);

void wordWrap(int line){

  string word = "";
  int rest = line;
  bool empty = true;
  while(cin >> word){
    empty = false;
    printWord(word, rest, line);
  }
  if(!empty) cout << endl;
  return;
}

void printWord(string word, int& rest, int line){
 
  if(0 == rest){
    cout << endl;
    rest = line;
   }

  int wlength = word.length();
  
  //can fit
  if(rest > wlength){
    if(rest != line){
      cout <<" ";
      rest --;
    }
    cout << word;
    rest -= wlength;
  }

  else if(rest == wlength && rest == line){
    cout << word;
    rest -= wlength;
  }

  //not fit, at new line, chop 
  else if(rest == line){
    cout << word.substr(0, line);  
    rest -= rest;
    printWord(word.substr(line), rest, line);
  }

  //not fit, at rest of line
  else{
    rest = 0;
    printWord(word, rest, line);
  }

  return;
} 


int main(int argc, char* argv[]){
  if(1 == (argc -1)){
    string s = argv[argc -1];
    istringstream is {s};
    int length = 0;
    is >> length;
    wordWrap(length);
  }
  else wordWrap();

  return 0;
}


