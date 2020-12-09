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

enum class Opcode {
  Jmp,
  Acc,
  Nop
};

Opcode to_opcode(const string& instr) {
  if (instr == "jmp") {
    return Opcode::Jmp;
  } else if (instr == "nop") {
    return Opcode::Nop;
  } else if (instr == "acc") {
    return Opcode::Acc;
  }
  throw "Bad opcode: " + instr;
}

Opcode flip_opcode(Opcode instr) {
  switch (instr) {
    case Opcode::Jmp:
      return Opcode::Nop;
    case Opcode::Nop:
      return Opcode::Jmp;
    default:
      return instr;
  }
}

struct Instr {
  Opcode op;
  ll val;
};

Instr parse_instr(const string& str) {
  istringstream in(str);
  Instr instr;
  string opstr;
  in >> opstr;
  instr.op = to_opcode(opstr);
  in >> instr.val;
  return instr;
}

struct ProgState {
  size_t pc;
  ll acc;
};

ProgState init_state() { return {.pc = 0, .acc = 0}; }

ProgState step(const vector<Instr>& code, const ProgState& state) {
  const Instr& instr = code[state.pc];
  switch (instr.op) {
    case Opcode::Nop:
      return {.pc = state.pc + 1, .acc = state.acc};
    case Opcode::Acc:
      return {.pc = state.pc + 1, .acc = state.acc + instr.val};
    case Opcode::Jmp:
      return {.pc = state.pc + instr.val, .acc = state.acc};
  }
}

const bool IGNORE_EMPTY_LINES = true;

int main() {
  ifstream in("input");
  vector<Instr> code;
  while (in) {
    string lineStr;
    getline(in, lineStr);
    if (lineStr == "") continue;
    code.pb(parse_instr(lineStr));
  }

  vector<bool> seen(code.size(), false);
  for (ll guess = 0; guess < code.size(); guess++) {
    while (code[guess].op == Opcode::Acc) {
      guess++;
    }
    code[guess].op = flip_opcode(code[guess].op); 

    ProgState state = init_state(); 
    while (state.pc < code.size()) {
      if (seen[state.pc]) {
        break;
      }
      seen[state.pc] = true;
      state = step(code, state);
    }
    code[guess].op = flip_opcode(code[guess].op);
    if (state.pc >= code.size()) {
      cout << state.acc << endl;
      break;
    }
    std::fill(allof(seen), false);
  }
}

