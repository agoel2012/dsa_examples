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

int minEditDistances(string s1, string s2) {
  int M = s1.length();
  int N = s2.length();
  vector<vector<int>> cache(M + 1, vector<int>(N + 1, 0));
  for (int word1Index = 0; word1Index <= M; word1Index++) {
    cache[word1Index][0] = word1Index;
  }

  for (int word2Index = 0; word2Index <= N; word2Index++) {
    cache[0][word2Index] = word2Index;
  }

  for (int i = 1; i <= M; i++) {
    for (int j = 1; j <= N; j++) { 
      if (s1[i-1] == s2[j-1]) {
        cache[i][j] = cache[i - 1][j - 1];
      } else {
        cache[i][j] =
            1 + min(cache[i - 1][j], min(cache[i][j - 1], cache[i - 1][j - 1]));
      }
    }
  }

  return cache[M][N];
}

int main(int argc, char *argv[]) {
  string s1 = "horse";
  string s2 = "ros";
  cout << minEditDistances(s1, s2) << endl;
  return 0;
}
