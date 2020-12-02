#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

using namespace std;

int main() {
  ifstream in("input");
  int good = 0;
  while (in) {
    int lo, hi;
    char letter;
    char trash;
    string pass;
    in >> lo;
    in >> trash;
    in >> hi;
    in >> letter;
    in >> trash;
    in >> pass;
    if ((pass[lo-1] == letter) != (pass[hi-1] == letter)) good++; 
  }
  cout << good << endl;
}
