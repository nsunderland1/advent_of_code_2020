#include <stdio.h>

const int ROUNDS = 10000000;
const int NUM_CUPS = 1000000;

inline int dec(int n) { return (n + NUM_CUPS - 1) % NUM_CUPS; }

int main() {
  int input[] = {9,5,2,4,3,8,7,1,6};
  const int INPUT_SIZE = sizeof(input)/sizeof(int);
  for (int i = 0; i < INPUT_SIZE; i++) {
    input[i]--;
  }
  int next[NUM_CUPS];
  for (int i = 0; i < INPUT_SIZE-1; i++) {
    next[input[i]] = input[i+1];
  }
  next[input[INPUT_SIZE-1]] = INPUT_SIZE;

  for (int i = INPUT_SIZE; i < NUM_CUPS-1; i++) {
    next[i] = i+1;
  }
  next[NUM_CUPS-1] = input[0];

  int current = input[0];
  for (int move = 0; move < ROUNDS; move++) {
    int dest = dec(current);
    int r1 = next[current];
    int r2 = next[r1];
    int r3 = next[r2];
    while (dest == r1 || dest == r2 || dest == r3) {
      dest = dec(dest);
    }
    current = next[current] = next[r3];
    next[r3] = next[dest];
    next[dest] = r1;
  }
  printf("%lld\n", (long long)(next[0]+1) * (long long)(next[next[0]]+1));
}
