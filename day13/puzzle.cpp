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

ll modpow(ll a, ll exp, ll m) {
  ll prod = 1;
  while (exp > 0) {
    prod *= a;
    prod %= m;
    exp--;
  }
  return prod;
}

// m prime
ll modinv(ll a, ll m) {
  return modpow(a, m-2, m);
}

int main() {
  ifstream in("input");
  ll go;
  in >> go;
  vs busStrs;
  string line;
  in >> line;
  istringstream lineIn(line);
  string segment;
  while(std::getline(lineIn, segment, ',')) {
    busStrs.push_back(segment);
  }
  vi buses;
  for (auto bs : busStrs) {
    if (bs != "x") {
      buses.pb(atoi(bs.c_str()));
    } else {
      buses.pb(-1); // signal value - no restrictions
    }
  }

  ll M = accumulate(allof(buses), (ll)1, [](ll acc, ll val) {
    return val < 0 ? acc : val*acc;
  });

  ll answer = 0;
  for (ll i = 0; i < buses.size(); i += 1) {
    if (buses[i] < 0) {
      continue;
    }
    ll m = buses[i];
    ll a = (((i/m)*m+m)-i) % m; // trying to normalize
    ll b = M / m;
    ll bp = modinv(b, m);
    answer += a * b * bp;
  }
  answer %= M;
  cout << answer << endl;
  // ll bustaken = -1;
  // ll bustime = INF;
  // for (auto bus : buses) {
  //   if (go % bus == 0) {
  //     bustaken = bus;
  //     bustime = go;
  //     break;
  //   }
  //   ll time = (go / bus) * bus + bus;
  //   if (time < bustime) {
  //     bustime = time;
  //     bustaken = bus;
  //   }
  // }
  // cout << bustaken * (bustime - go) << endl;
}

