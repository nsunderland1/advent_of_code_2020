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

const ll GOAL = 30000000;

int main() {
  ifstream in("input");
  vi nums;
  string segment;
  ll num;
  while(std::getline(in, segment, ',')) {
    istringstream segIn(segment);
    segIn >> num;
    nums.pb(num);
  }

  vi seen(GOAL, -1);
  ll last = 0;
  for (ll i = 0; i < nums.size(); i++) {
    seen[nums[i]] = i;
  }

  for (ll i = nums.size(); i < GOAL-1; i++) {
    if (seen[last] < 0) {
      seen[last] = i;
      last = 0;
    } else {
      ll tmp = i - seen[last];
      seen[last] = i;
      last = tmp;
    }
  }
  cout << last << endl;
}

