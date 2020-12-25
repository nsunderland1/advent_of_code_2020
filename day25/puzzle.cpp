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

vs split(const string& str, char c) {
  string segment;
  istringstream in(str);
  vs pieces;
  while (getline(in, segment, c)) {
    pieces.pb(segment);
  }
  return pieces;
}

// copied and pasted from StackOverflow :)
long long modular(long long base, long long exp, int mod) {
   long long res = 1;
   while (exp > 0) {
      if (exp % 2 == 1)
         res= (res * base) % mod;
      exp = exp >> 1;
      base = (base * base) % mod;
   }
   return res;
}

ll transform(ll subject, ll loop_size) {
  return modular(subject, loop_size, 20201227);
}

const ll INITIAL = 7;

int main() {
  ll pkey1 = 11239946;
  ll pkey2 = 10464955;
  ll loop1 = -1, loop2 = -1;

  for (ll i = 2; ; i++) {
    ll xform = transform(INITIAL, i);
    if (xform == pkey1) {
      loop1 = i;
    } else if (xform == pkey2) {
      loop2 = i;
    }
    if (loop1 != -1 && loop2 != -1) break;
  }

  cout << transform(pkey1, loop2) << " " << transform(pkey2, loop1) << endl;
}

