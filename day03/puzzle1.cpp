#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main() {
  ifstream in("input");
  string lineStr;
  vector<string> grid;
  while (in) {
    getline(in, lineStr);
    if (lineStr != "") grid.push_back(lineStr);
  }
  int treecount = 0;
  int x = 0;
  for (int i = 0; i < grid.size(); i++) {
    if (grid[i][x % grid[i].length()] == '#') {
      treecount++;
    }
    x += 3;
  }
  cout << treecount;
}
