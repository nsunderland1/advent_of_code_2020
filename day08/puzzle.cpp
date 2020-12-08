#include <bits/stdc++.h>
using namespace std;

#define rep(it,st,en) for(ll it=(st);it<(ll)(en);++it)
#define allof(c) (c).begin(), (c).end()
#define allof(c) (c).begin(), (c).end()
#define mt make_tuple
#define mp make_pair
#define pb push_back
#define X first
#define Y second
using ll = int64_t;
using ld = long double;
using vi = vector<ll>;
using vvi = vector<vi>;
using vs = vector<string>;
using pii = pair<ll, ll>;
const ll INF=(ll)1e9; 
const double EPS=(ld)1e-7;

const bool IGNORE_EMPTY_LINES = true;

int main() {
  ifstream in("input");
  vs lines;
  string lineStr;

  while (in) {
    getline(in, lineStr);
    if (IGNORE_EMPTY_LINES && lineStr == "") continue;
    lines.pb(lineStr);
  }

  vector<pair<string, ll>> code;
  for (ll i = 0, n = lines.size(); i < n; i += 1) {
    string line = lines[i];
    istringstream lineIn(line);
    string instr;
    ll val;
    lineIn >> instr >> val;
    code.pb(mp(instr, val));
  }

  vi cnt(code.size(), 0);
  ll acc = 0;
  ll i = 0;
  ll guess = 0;
  while (guess < code.size()) {
    while (i < code.size()) {
      auto instr = code[i];
      cnt[i]++;
      if (cnt[i] == 2) {
        break;
      }
      if (instr.X == "acc" && i == guess) break;

      string opcode;
      if (i == guess && instr.X == "nop") {
        opcode = "jmp";
      } else if (i == guess && instr.X == "jmp") {
        opcode = "nop";
      } else {
        opcode = instr.X;
      }

      if (opcode == "nop") {
        i++;
      } else if (opcode == "acc") {
        acc += instr.Y;
        i++;
      } else {
        i += instr.Y~
      }
    }
    if (i >= code.size()) {
      cout << acc << endl;
      break;
    }
    guess++;
    i = 0;
    fill(allof(cnt), 0);
    acc = 0;
  }
}

