#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  ifstream input("input");

  vector<int> nums;
  int input_line;
  while (input >> input_line) {
    nums.push_back(input_line);
  }
  try {
    for (int i = 0; i < nums.size(); i += 1) {
      for (int j = 0; j < nums.size(); j += 1) {
        for (int k = 0; k < nums.size(); k += 1) {
          int ni = nums[i], nj = nums[j], nk = nums[k];
          if (i != j && j != k && i != k && ni + nj + nk == 2020) {
            cout << "The numbers are " << ni << ", " << nj << " and " << nk << endl;
            throw ni * nj * nk;
          } 
        }
      }
    }
  } catch (int product) {
    cout << "The product is " << product << endl;
  }
}