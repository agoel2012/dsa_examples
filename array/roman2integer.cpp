#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
unordered_map<char, int> r2i = {{'I', 1},   {'V', 5},   {'X', 10},  {'L', 50},
                                {'C', 100}, {'D', 500}, {'M', 1000}};

int roman2Integer(string s) {
  int prev = r2i[s[0]];
  int cur = 0;
  int num = 0;
  int size = (int)s.length();
  for (int i = 1; i < size; i++) {
    cur = r2i[s[i]];
    if (prev < cur) {
      num += (-prev);
    } else {
      num += (prev);
    }

    prev = cur;
  }

  return num + prev;
}

int main(int argc, char *argv[]) {

  string s1 = "III";
  string s2 = "LVIII";
  string s3 = "MCMXCIV";
  cout << roman2Integer(s3) << endl;
  return 0;
}
