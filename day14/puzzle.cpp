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

vi addresses(string addr, string mask) {
  vi addrs;
  for (ll i = 0; i < addr.length(); i++) {
    vi bit;
    switch (mask[i]) {
      case '0':
        bit.pb(addr[i] == '0' ? 0 : 1);
        break;
      case '1':
        bit.pb(1);
        break;
      default:
        bit.pb(0);
        bit.pb(1);
        break;
    }
    if (i == 0) {
      addrs = bit;
    } else {
      vi newaddrs;
      for (ll& addr : addrs) {
        for (ll onebit : bit) {
          newaddrs.pb((addr << 1) + onebit);
        }
      }
      addrs = newaddrs;
    }
  }
  return addrs;
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

  string mask;
  map<ll, ll> touched;
  for (ll i = 0, n = lines.size(); i < n; i += 1) {
    string line = lines[i];
    istringstream lineIn(line);
    char trash;
    lineIn >> trash >> trash;
    if (trash == 'a') {
      lineIn >> trash >> trash >> trash;
      lineIn >> mask;
    } else {
      ll index, val;
      lineIn >> trash >> trash >> index >> trash >> trash >> val;
      string addrStr(bitset<36>(index).to_string());
      vi addrs = addresses(addrStr, mask);
      for (auto addr : addrs) {
        touched[addr] = val;
      }
    }
  }
  // map<ll, ll> touched;
  // string mask;
  // for (auto instr : code) {
  //   ll index = instr.X;
  //   if (index == -1) {
  //     mask = instr.Y;
  //   } else {
  //     string bin = instr.Y;
  //     for (ll i = 0; i < 36; i++) {
  //       if (mask[i] != 'X') {
  //         bin[i] = mask[i];
  //       }
  //     }
  //     touched[index] = bitset<36>(bin).to_ullong();
  //   }
  // }
  cout << accumulate(allof(touched), (ll)0, [](ll acc, auto el) {
    return acc + el.Y;
  }) << endl;
}

