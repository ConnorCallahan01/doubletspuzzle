#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include "graph.h"
using namespace std;

void doubletsOfFive(graph<string>& g, string a, string b);

int main() {
  ifstream input;
  input.open("knuth.txt");
  graph<string> g;
  string word;
  while (input >> word) {
    g.add_vertex(word);
    int temp = 0;
    for(size_t i = 0;i<g.size();i++) {
      for(size_t j =0;j<5;j++) {
        if (word[j] == g[i][j]) {
          temp++;
        }
      }
      if (temp == 4) {
        g.add_edge(g.size()-1, i);
      }
    }
  }
  string a, b;

  a = "black";
  b = "white";
  doubletsOfFive(g, a, b);

  a = "tears";
  b = "smile";
  doubletsOfFive(g, a, b);

  a = "small";
  b = "giant";
  doubletsOfFive(g, a, b);

  a = "stone";
  b = "money";
  doubletsOfFive(g, a, b);

  a = "angel";
  b = "devil";
  doubletsOfFive(g, a, b);

  a = "amino";
  b = "rights";
  doubletsOfFive(g, a, b);

  a = "amigo";
  b = "signs";
  doubletsOfFive(g, a, b);
}

void doubletsOfFive(graph<string>& g, string a, string b) {
size_t anum, bnum;
  for (size_t i = 0;i < g.size();i++) {
    if (g[i] == a) {
      anum = i;
    }
    if (g[i] == b) {
      bnum = i;
    }
  }

  vector<int> v = g.shortest_path(anum,bnum);

  cout << "Doublet puzzle with words " << a << " and " << b << ":" << endl;
  for (auto e: v) {
    cout << g[e] << " ";
  }
  cout << endl;
}
