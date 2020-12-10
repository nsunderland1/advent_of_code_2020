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

int brute(vi jolts, size_t start) {
  ll cnt = 0;
  if (start == jolts.size() - 1) {
    return 1;
  }
  cnt += brute(jolts, start + 1);
  if (start == jolts.size() - 2) {
    return cnt;
  }
  cnt += brute(jolts, start + 2);
  if (start == jolts.size() - 3) {
    return cnt;
  }
  cnt += brute(jolts, start + 3);
  return cnt;
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
  vvi partitions;
  vi partition;
  ll i = 0;
  while (i < jolts.size()) {
    do {
      partition.pb(jolts[i]);
      i++;
    } while (i < jolts.size() && jolts[i] - jolts[i-1] != 3);
    partitions.pb(partition);
    partition.clear();
  }
  ll prod = 1;
  for (auto part : partitions) {
    prod *= brute(part, 0);
  }
  cout << prod << endl;
}

