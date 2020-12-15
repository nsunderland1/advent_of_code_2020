#include <stdio.h>
#include <stdlib.h>
#define GOAL 30000000
#define INPUT_SIZE 6
int main() {
  int nums[] = {1,0,18,10,19,6};
  int* seen = malloc(GOAL * sizeof(int));
  for (int i = 0; i < INPUT_SIZE; i++) {
    seen[nums[i]] = i;
  }

  // #pragma omp parallel for
  for (int i = INPUT_SIZE; i < GOAL; i++) {
    seen[i] = -1;
  }

  int last = 0;
  for (int i = INPUT_SIZE; i < GOAL-1; i++) {
    if (seen[last] < 0) {
      seen[last] = i;
      last = 0;
    } else {
      int tmp = i - seen[last];
      seen[last] = i;
      last = tmp;
    }
  }

  printf("%d\n", last);
}

