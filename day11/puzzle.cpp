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

int checkneighbour(const vs& seats, ll r, ll c, ll rd, ll cd) {
  while (1) {
    r += rd;
    c += cd;
    if (!(r >= 0 && r < seats.size() && c >= 0 && c < seats[0].length())) {
      return 0;
    }
    if (seats[r][c] == 'L') {
      return 0;
    }
    if (seats[r][c] == '#') {
      return 1;
    }  
  }
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

  vs seats;
  for (ll i = 0, n = lines.size(); i < n; i += 1) {
    string line = lines[i];
    seats.pb(line);
  }

  vs updated;
  while (1) {
    updated = seats;
    for (ll r = 0; r < seats.size(); r++) {
      for (ll c = 0; c < seats.size(); c++) {
        // size_t neigh = 0;
        // for (ll nr = max(r-1, (ll)0); nr <= min(r+1, (ll)(seats.size()-1)); nr++) {
        //   for (ll nc = max(c-1, (ll)0); nc <= min(c+1, (ll)(seats[0].length()-1)); nc++) {
        //     if ((nr != r || nc != c) && seats[nr][nc] == '#') {
        //       neigh++;
        //     } 
        //   }
        // }
        // if (neigh == 0 && seats[r][c] == 'L') {
        //   updated[r][c] = '#';
        // } else if (neigh >= 4 && seats[r][c] == '#') {
        //   updated[r][c] = 'L';
        // }
        ll neigh = 0;
        for (ll rd = -1; rd <= 1; rd++) {
          for (ll cd = -1; cd <= 1; cd++) {
            if (rd != 0 || cd != 0) {
              neigh += checkneighbour(seats, r, c, rd, cd);
            }
          }
        }
        if (neigh == 0 && seats[r][c] == 'L') {
          updated[r][c] = '#';
        } else if (neigh >= 5 && seats[r][c] == '#') {
          updated[r][c] = 'L';
        } 
      }
    }
    if (updated == seats) {
      break;
    }
    seats = updated;
  }

  ll count = 0;
  for (auto s : seats) {
    for (auto c : s) {
      if (c == '#') {
        count++;
      }
    }
  }
  cout << count << endl;
}

