#include <algorithm>
#include <climits>
#include <iostream>
#include <optional>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int lcs(string s1, string s2) {
  int M = s1.length();
  int N = s2.length();
  if (M > N) {
    return lcs(s2, s1);
  }

  vector<vector<int>> cache(M + 1, vector<int>(N + 1, 0));
  for (int i = N - 1; i >= 0; i--) {
    for (int j = M - 1; j >= 0; j--) {
      if (s1[j] == s2[i]) {
        cache[j][i] = 1 + cache[j + 1][i + 1];
      } else {
        cache[j][i] = max(cache[j + 1][i], cache[j][i + 1]);
      }
    }
  }

  return cache[0][0];
}

int main(int argc, char *argv[]) {
  string s1 = "abcde";
  string s2 = "ace";
  cout << lcs(s1, s2) << endl;
  return 0;
}
