#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <bits/stdc++.h>
using namespace std;

typedef struct line{
  string title;
  short int id;
  string repetition;
  double value;
};


string readCSV(char* csvarg);
vector<line> parserCSV(string csv);
int parserTitle(string);
bool compareLine(line l1, line l2);
void writeFile(vector<line>, string);

enum {title, nr, vr, repetiton, module, value};

int main(int nArgs, char* args[]){
  if(nArgs != 3){
    cout<<nArgs<<"Arguments must be $csvfile $outfile";
    return 0;
  }
  string csv = readCSV(args[1]);
  vector<line> container = parserCSV(csv);
  writeFile(container, args[2]);
  return 0;
}

vector<line> parserCSV(string csv){
  vector<line> container;
  line l;
  stringstream ss(csv);
  string linebuff = "";
  string token = "";
  getline(ss, token);
  int i = 0;
  int num = 0;
  while(getline(ss, linebuff)){
    stringstream linestream(linebuff);
    for(int i = 0; getline(linestream, token, ',')&&i<6; i++){
      cout<<i<<endl;
      switch(i){
        case 0:
          l.title = token;
          l.id = parserTitle(token);
          break;
        case 3:
          l.repetition = token;
          break;
        case 5:
          l.value = stod(token);
          container.push_back(l);
          break;
      }
    }
  }

  sort(container.begin(), container.end(), compareLine);
  for(int i = 0; i<container.size(); i++){
    cout<<container[i].title<<endl;
  }
  return container;
}

int parserTitle(string title){
  string id;
  stringstream tmp(title);
  getline(tmp, id, '-');
  getline(tmp, id, '-');
  return stoi(id);
}

string readCSV(char* csvarg){
  ifstream csv;
  csv.open(csvarg);
  string buffer;
  stringstream tmp;
  tmp << csv.rdbuf();
  buffer = tmp.str();
  csv.close();

  return buffer;
}

bool compareLine(line l1, line l2){
  return (l1.id < l2.id);
}

void writeFile(vector<line> container, string outtitle){
  ofstream outfile;
  const int repetition = 5;
  outfile.open(outtitle);
  for(int i = 0; i<(container.size()/repetition); i++){
    for(int k = 0; k < repetition; k++){
      outfile<<container[(i*repetition) + k].value<<" ";
    }
    outfile<<endl;
  }
  outfile.close();
}
