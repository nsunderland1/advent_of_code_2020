#include <bits/stdc++.h>
using namespace std;

#define rep(it,st,en) for(ll it=(st);it<(ll)(en);++it)
#define allof(c) (c).begin(), (c).end()

const bool IGNORE_EMPTY_LINES = true;

using ll = int64_t;
using ld = long double;

int main() {
  ifstream in("input");
  vector<string> lines;
  string lineStr;

  while (in) {
    getline(in, lineStr);
    if (IGNORE_EMPTY_LINES && lineStr == "") continue;
    lines.push_back(lineStr);
  }

  for (size_t i = 0, n = lines.size(); i < n; i += 1) {
    string line = lines[i];
    istringstream lineIn(line);
  }
}

