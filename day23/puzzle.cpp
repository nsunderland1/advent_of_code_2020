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

const ll ROUNDS = 10000000;
const ll NUM_CUPS = 1000000;

inline ll norm(ll n) { return (n-1) % NUM_CUPS + 1; }
inline ll prev(ll n) { return norm(n + NUM_CUPS - 1);}
inline ll next(ll n) { return norm(n + 1); }

struct Node {
  Node* prev;
  Node* next;
  ll label;
};

Node* find_label(const unordered_map<ll, Node*>& lookup, ll label) {
  return lookup.find(label)->second;
}

void print_state(Node* head) {
  cout << head << endl;
  Node* cur = head;
  int i = 0;
  do {
    cout << cur->label << " ";
    cur = cur->next;
    i++;
    if (i > 10) break;
  } while (cur != head);
  cout << endl;
}


int main() {
  vi input = {9,5,2,4,3,8,7,1,6};
  vector<Node*> cups;

  Node* one;
  for (ll i = 0; i < input.size(); i++) {
    cups.pb(new Node());
    cups.back()->label = input[i];
    if (input[i] == 1) {
      one = cups.back();
    }
  }

  cups.reserve(NUM_CUPS);
  for (ll i = input.size(); i < NUM_CUPS; i++) {
    Node* cup = new Node();
    cup->label = i+1;
    cups.pb(cup);
  }

  for (ll i = 0; i < NUM_CUPS; i++) {
    cups[i]->next = cups[(i + 1) % NUM_CUPS];
    cups[i]->prev = cups[(i + NUM_CUPS - 1) % NUM_CUPS];
  }
  unordered_map<ll, Node*> lookup;
  for (Node* ptr : cups) {
    lookup.insert(mp(ptr->label, ptr));
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

    Node* dest_node = find_label(lookup, dest);
    Node* dest_next = dest_node->next;
    dest_node->next = remhead;
    remhead->prev = dest_node;
    remhead->next->next->next = dest_next;
    dest_next->prev = remhead->next->next->next;

    current = rejoin;
  }

  cout << one->next->label * one->next->next->label << endl; 
}

