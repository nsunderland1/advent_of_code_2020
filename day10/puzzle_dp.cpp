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

  vi jolts = {0};
  for (ll i = 0, n = lines.size(); i < n; i += 1) {
    string line = lines[i];
    istringstream lineIn(line);
    ll jolt;
    lineIn >> jolt;
    jolts.pb(jolt);
  }
  sort(allof(jolts));
  jolts.pb(jolts[jolts.size() - 1] + 3);
  // ll ct1 = 0, ct3 = 0;
  // for (size_t i = 0; i < jolts.size() - 1; i++) {
  //   const ll diff = jolts[i+1] - jolts[i];
  //   if (diff == 1) {
  //     ct1++;
  //   } else if (diff == 3) {
  //     ct3++;
  //   }
  // }
  vi dp(jolts.size(), 0);
  dp[jolts.size()-1] = 1;
  for (ll i = jolts.size()-2; i >= 0; i--) {
    for (ll j = i + 1; j < jolts.size(); j++) {
      if (jolts[j]-jolts[i] > 3) {
        break;
      }
      dp[i] += dp[j];
    }
  }
  cout << dp[0] << endl;
}

