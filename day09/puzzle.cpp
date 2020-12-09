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

  vi nums;
  for (ll i = 0, n = lines.size(); i < n; i += 1) {
    string line = lines[i];
    istringstream lineIn(line);
    ll num;
    lineIn >> num;
    nums.pb(num);
  }

  // for (ll guess = 25; guess < nums.size(); guess++) {
  //   bool found = false;
  //   for (int i = guess - 25; i < guess; i += 1) {
  //     for (int j = i + 1; j < guess; j += 1) {
  //       if (i != j && nums[i] + nums[j] == nums[guess]) {
  //         found = true;
  //       }
  //     }
  //   }
  //   if (!found) {
  //     cout << nums[guess] << endl;
  //     break;
  //   }
  // }
  ll p1ans = 619;
  // not generally correct (should stop before p1ans) but good enough here
  for (ll len = 2; len < p1ans; len++) {
    for (ll i = 0; i < p1ans; i++) {
      auto low = nums.begin() + i;
      auto high = nums.begin() + i + len;
      ll sum = accumulate(low, high, 0);
      if (sum == 675280050) {
        cout << *min_element(low, high) + *max_element(low, high) << endl;
        exit(0);
      }
    }
  }
}

