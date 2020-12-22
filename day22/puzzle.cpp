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

using Deck = deque<ll>;

void transfer(Deck& from, Deck& to) {
  ll top = to.front();
  to.pop_front();
  ll bot = from.front();
  from.pop_front();
  to.pb(top);
  to.pb(bot);
}

ll score(const Deck& deck) {
  ll tot= 0;
  ll i = 1;
  for (auto it = deck.crbegin(); it != deck.crend(); it++) {
    tot += *it * i;
    i++;
  }
  return tot;
}

string round_id(const Deck& deck1, const Deck& deck2) {
  string res('0', deck1.size() + deck2.size() + 1);
  auto string_it = res.begin();
  for (ll card: deck1) {
    *string_it = (char)card;
    string_it++;
  }
  *string_it = '|';
  string_it++;
  for (ll card: deck2) {
    *string_it = (char)card;
    string_it++;
  }
  return res;
}

enum class GameResult { P1, P2 };

GameResult play_combat(Deck& deck1, Deck& deck2) {
  unordered_set<string> previous_rounds;

  while (deck1.size() > 0 && deck2.size() > 0) {
    string round = round_id(deck1, deck2);
    if (previous_rounds.contains(round)) {
      return GameResult::P1;
    }
    previous_rounds.insert(round);

    ll draw1 = deck1.front();
    deck1.pop_front();
    ll draw2 = deck2.front();
    deck2.pop_front();

    GameResult winner;
    if (deck1.size() >= draw1 && deck2.size() >= draw2) {
      Deck subdeck1, subdeck2;
      copy_n(deck1.cbegin(), draw1, back_inserter(subdeck1));
      copy_n(deck2.cbegin(), draw2, back_inserter(subdeck2));
      winner = play_combat(subdeck1, subdeck2);
    } else {
      winner = draw1 > draw2 ? GameResult::P1 : GameResult::P2;
    }

    Deck& winning_deck = winner == GameResult::P1 ? deck1 : deck2;
    auto [win_card, lose_card] = winner == GameResult::P1 ? mp(draw1, draw2) : mp(draw2, draw1);
    winning_deck.pb(win_card);
    winning_deck.pb(lose_card);
  }

  return deck1.size() > 0 ? GameResult::P1 : GameResult::P2;
}

int main() {
  ifstream in("input");
  string trash;
  
  Deck deck1, deck2;
  array<Deck*, 2> decks = {&deck1, &deck2};
  for (auto* deck : decks) {
    getline(in, trash);
    while (1) {
      ll card;
      in >> card;
      if (in.fail()) break;
      deck->pb(card);
    }
    in.clear();
  }

  // while (deck1.size() > 0 && deck2.size() > 0) {
  //   ll card1 = deck1.front();
  //   ll card2 = deck2.front();
  //   if (card1 < card2) {
  //     transfer(deck1, deck2);
  //   } else {
  //     transfer(deck2, deck1);
  //   }
  // }

  GameResult winner = play_combat(deck1, deck2);
  cout << score(winner == GameResult::P1 ? deck1 : deck2) << endl;
}

