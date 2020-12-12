#include <bits/stdc++.h>
#include <regex>
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

  vector<pair<char, ll>> instructions;
  for (ll i = 0, n = lines.size(); i < n; i += 1) {
    string line = lines[i];
    istringstream lineIn(line);
    char dir;
    ll val;
    lineIn >> dir;
    lineIn >> val;
    instructions.pb(mp(dir, val));
  }
  ll startx = 0, starty = 0;
  ll shipx = startx, shipy = starty;
  ll x = 10, y = 1;

  vector<pair<ll, ll>> dirs = {
    {1, 0}, {1, -1},
    {0, -1}, {-1, -1},
    {-1, 0}, {-1, 1},
    {0, 1}, {1, 1}
  };
  ll curDirIndex = dirs.size()-1; // NE
  for (auto & instr : instructions) {
    switch (instr.X) {
      case 'N':
        y += instr.Y;
        break;
      case 'S':
        y -= instr.Y;
        break;
      case 'E':
        x += instr.Y;
        break;
      case 'W':
        x -= instr.Y;
        break;
      case 'F':
        shipx += instr.Y * (x - shipx);
        shipy += instr.Y * (y - shipy);
        break;
      case 'L':
      case 'R':
        if (shipx == x && shipy == y) {
          continue;
        }

    }
    // ll dx = 0, dy = 0;
    // switch (instr.X) {
    //   case 'L':
    //     dir-=instr.Y/90;
    //     break;
    //   case 'R':
    //     dir+=instr.Y/90;
    //     break;
    //   case 'N':
    //     dy = 1;
    //     break;
    //   case 'S':
    //     dy = -1;
    //     break;
    //   case 'E':
    //     dx = 1;
    //     break;
    //   case 'W':
    //     dx = -1;
    //     break;
    //   case 'F': {
    //     if (dir == 0) {
    //       dy = 1;
    //     } else if (dir == 1) {
    //       dx = 1;
    //     } else if (dir == 2) {
    //       dy = -1;
    //     } else if (dir == 3) {
    //       dx = -1;
    //     }
    //     break;
    //   } 
    // }
    // dir = (dir + 4000) % 4;
    // x += dx * instr.Y;
    // y += dy * instr.Y;
  }
  cout << abs(x - startx) + abs(y - starty) << endl;
}

