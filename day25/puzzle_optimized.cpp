#include <iostream>
using namespace std;

using ll = uint64_t;

// copied and pasted from StackOverflow :)
ll modexp(ll base, ll exp, int mod) {
  ll res = 1;
  while (exp > 0) {
    if (exp % 2 == 1)
      res = (res * base) % mod;
    exp = exp >> 1;
    base = (base * base) % mod;
  }
  return res;
}

ll transform(ll subject, ll loop_size) {
  return modexp(subject, loop_size, 20201227);
}

const ll INITIAL = 7;

int main() {
  ll pkey1 = 11239946;
  ll pkey2 = 10464955;
  ll xform = INITIAL;
  for (ll i = 2; ; i++) {
    xform = (xform * INITIAL) % 20201227;
    if (xform == pkey1) {
      cout << transform(pkey2, i) << endl;
      return 0;
    } else if (xform == pkey2) {
      cout << transform(pkey1, i) << endl;
      return 0;
    }
  }
}

