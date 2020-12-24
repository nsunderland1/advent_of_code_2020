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

const ll DAYS = 100;

vs split(const string& str, char c) {
  string segment;
  istringstream in(str);
  vs pieces;
  while (getline(in, segment, c)) {
    pieces.pb(segment);
  }
  return pieces;
}

set<pii> neighbours(const pii& pos) {
  auto [x, y] = pos;
  return {
    mp(x+1,y+1),
    mp(x+2,y),
    mp(x+1,y-1),
    mp(x-1,y-1),
    mp(x-2,y),
    mp(x-1,y+1)
  };
}

ll count_black(const set<pii>& nbs, const set<pii>& black) {
  ll count = 0;
  for (auto pos : nbs) {
    if (black.contains(pos)) count++;
  }
  return count;
}

int main() {
  ifstream in("input");
  vs lines;
  string lineStr;

  while (in) {
    getline(in, lineStr);
    if (IGNORE_EMPTY_LINES && lineStr == "") continue;
    lines.pb(lineStr);
  }
  set<pii> black;
  for (ll i = 0, n = lines.size(); i < n; i += 1) {
    string line = lines[i];
    pii pos = mp(0, 0);
    ll& x = pos.X;
    ll& y = pos.Y;
    for (ll j = 0; j < line.length();) {
      if (line[j] == 'e') {
        x += 2;
        j++;
      } else if (line[j] == 'w') {
        x -= 2;
        j++;
      } else {
        if (line[j] == 'n') {
          y += 1;
        } else {
          y -= 1;
        }
        if (line[j+1] == 'e') {
          x += 1;
        } else {
          x -= 1;
        }
        j += 2;
      }
    }
    auto it = find(allof(black), pos);
    if (it != black.end()) {
      black.erase(it);
    } else {
      black.insert(pos);
    }
  }
  set<pii> tiles = black;

  for (auto tile : black) {
    tiles.merge(neighbours(tile));
  }

  for (ll day = 0; day < DAYS; day++) {
    set<pii> updated_black = black;  
    for (auto tile : tiles) {
      auto nbs = neighbours(tile);
      ll black_neighbour_count = count_black(nbs, black);
      if (black.contains(tile)) {
        if (black_neighbour_count == 0 || black_neighbour_count > 2) {
          updated_black.erase(tile);
        }
      } else if (black_neighbour_count == 2) {
        updated_black.insert(tile);
      }
    }
    for (auto tile : updated_black) {
      tiles.merge(neighbours(tile));
    }
    black = updated_black;
  }
  cout << black.size() << endl;
}

