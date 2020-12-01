#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char** argv) {
  char* filename = argv[1];
  ifstream input(filename);

  vector<int> nums;
  int input_line;
  while (input >> input_line) {
    nums.push_back(input_line);
  }
  cout << nums.size() << endl;
  try {
    for (int i = 0; i < nums.size(); i += 1) {
      for (int j = 0; j < nums.size(); j += 1) {
        if (i != j && nums[i] + nums[j] == 2020) {
          cout << "The numbers are " << nums[i] << " and " << nums[j] << endl;
          throw nums[i] * nums[j];
        }
      }
    }
  } catch (int product) {
    cout << "The product is " << product << endl;
  }
}