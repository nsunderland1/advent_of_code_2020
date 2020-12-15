#include <stdio.h>
#include <stdlib.h>
#define GOAL 30000000

int main() {
  int nums[] = {1,0,18,10,19,6};
  int* seen = malloc(GOAL * sizeof(int));
  for (int i = 0; i < 6; i++) {
    seen[nums[i]] = i;
  }
  for (int i = 6; i < GOAL; i++) {
    seen[i] = -1;
  }

  int last = 0;
  for (int i = 6; i < GOAL-1; i++) {
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
  // ifstream in("input");
  // vi nums;
  // string segment;
  // ll num;
  // while(std::getline(in, segment, ',')) {
  //   istringstream segIn(segment);
  //   segIn >> num;
  //   nums.pb(num);
  // }

  // vi seen(GOAL, -1);
  // ll last = 0;
  // for (ll i = 0; i < nums.size(); i++) {
  //   seen[nums[i]] = i;
  // }

  // for (ll i = nums.size(); i < GOAL-1; i++) {
  //   if (seen[last] < 0) {
  //     seen[last] = i;
  //     last = 0;
  //   } else {
  //     ll tmp = i - seen[last];
  //     seen[last] = i;
  //     last = tmp;
  //   }
  // }
  // cout << last << endl;
}

