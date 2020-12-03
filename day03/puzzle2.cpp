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
uint64_t calcSlope(vector<string> grid, int rStep, int dStep) {
  uint64_t treeCount = 0;
  int x = 0;
  for (int i = 0; i < grid.size(); i += dStep) {
    int x_idx = x % grid[i].length();
    if (grid[i][x_idx] == '#') {
      treeCount++;
    }
    x += rStep;
  }
  return treeCount;
}
int main() {
  ifstream in("input");
  string lineStr;
  vector<string> grid;
  while (in) {
    getline(in, lineStr);
    if (lineStr != "") grid.push_back(lineStr);
  }
  cout << (calcSlope(grid, 1, 1) * calcSlope(grid, 3, 1) * calcSlope(grid, 5, 1) * calcSlope(grid, 7, 1) * calcSlope(grid, 1, 2)) << endl;
}
