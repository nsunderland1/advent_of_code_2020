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

const ll ROUNDS = 100;
const ll INPUT_SIZE = 9;

inline ll norm(ll n) { return (n-1) % INPUT_SIZE + 1; }
inline ll prev(ll n) { return norm(n + INPUT_SIZE - 1);}
inline ll next(ll n) { return norm(n + 1); }

struct Node {
  Node* prev;
  Node* next;
  ll label;
};

Node* find_label(Node* start, ll label) {
  Node* current = start;
  do {
    if (label == current->label) {
      return current;
    }
    current = current->next;
  } while (current != start);
  cout << "CANT FIND " << label << endl;
  throw "Could not find label";
}

void print_state(Node* head) {
  Node* cur = head;
  do {
    cout << cur->label << " ";
    cur = cur->next;
  } while (cur != head);
  cout << endl;
}

int main() {
  // vi input = {3,8,9,1,2,5,4,6,7};
  vector<ll> input = {9,5,2,4,3,8,7,1,6};
  vector<Node*> cups;

  for (ll i = 0; i < input.size(); i++) {
    cups.pb(new Node());
    cups.back()->label = input[i];
  }

  for (ll i = 0; i < input.size(); i++) {
    cups[i]->next = cups[(i + 1) % INPUT_SIZE];
    cups[i]->prev = cups[(i + INPUT_SIZE - 1) % INPUT_SIZE];
  }

  Node* current = cups[0];
  for (ll move = 0; move < ROUNDS; move++) {
    ll dest = prev(current->label);
    Node* remhead = current->next;
    vi exclude = {remhead->label, remhead->next->label, remhead->next->next->label};
    for (ll i = 0; i < 3; i++) {
      if (find(allof(exclude), dest) != exclude.end()) {
        dest = prev(dest);
      }
    }
    Node* rejoin = remhead->next->next->next;
    current->next = rejoin;
    rejoin->prev = current;

    Node* dest_node = find_label(current, dest);
    Node* dest_next = dest_node->next;
    dest_node->next = remhead;
    remhead->prev = dest_node;
    remhead->next->next->next = dest_next;
    dest_next->prev = remhead->next->next->next;

    current = rejoin;
  }
  print_state(current);
}

