#include <climits>
#include <iostream>
#include <vector>

using namespace std;

int waysBuildings(string s) {

  int N = (int)(s.length());
  int result = 0;
  vector<int> leftZeros(N, 0);
  vector<int> leftOnes(N, 0);
  vector<int> rightZeros(N, 0);
  vector<int> rightOnes(N, 0);
  int one = 0;
  int zero = 0;
  for (int i = 0; i < N; i++) {
    if (s[i] == '0') {
      zero++;
      leftOnes[i] = one;
    } else {
      one++;
      leftZeros[i] = zero;
    }
  }

  one = 0;
  zero = 0;
  for (int i = N - 1; i >= 0; i--) {
    if (s[i] == '0') {
      zero++;
      rightOnes[i] = one;
    } else {
      one++;
      rightZeros[i] = zero;
    }
  }

  for (int i = 0; i < N; i++) {
    if (s[i] == '0') {
      result += leftOnes[i] * rightOnes[i];
    } else {
      result += leftZeros[i] * rightZeros[i];
    }
  }

  return result;
}

int waysBuildingDPHelper(string s, vector<vector<vector<int>>> &memo,
                         int startIndex, int prevChoice, int curLen) {
  int N = (int)s.length();
  // Base case
  if (curLen == 3) {
    return 1;
  }

  if (startIndex == N) {
    return 0;
  }

  // Cached case
  if (memo[startIndex][prevChoice][curLen] != INT_MIN) {
    return memo[startIndex][prevChoice][curLen];
  }

  // Recursive case
  if (prevChoice != (s[startIndex] - '0')) {
    memo[startIndex][prevChoice][curLen] =
        waysBuildingDPHelper(s, memo, startIndex + 1, (s[startIndex] - '0'),
                             curLen + 1) +
        waysBuildingDPHelper(s, memo, startIndex + 1, prevChoice, curLen);
  } else {
    memo[startIndex][prevChoice][curLen] =
        waysBuildingDPHelper(s, memo, startIndex + 1, prevChoice, curLen);
  }

  return memo[startIndex][prevChoice][curLen];
}

// Backtracking + Memoization
int waysBuildingsDP(string s) {
  int S = (int)(s.length());
  int C = 2; // 0 or 1
  int B = 3; // length of building is 3
  // cache is 3D of length of string * # of choices * length of building thus
  // far
  vector<vector<vector<int>>> memo(
      S + 1, vector<vector<int>>(C + 1, vector<int>(B + 1, INT_MIN)));
  return waysBuildingDPHelper(s, memo, 0 /* startIndex */, 2 /* prev choice */,
                              0 /* length of building */);
}

int main(int argc, char *argv[]) {
  string s1 = "11100";
  string s2 = "001101";
  cout << waysBuildings(s1) << endl;
  cout << waysBuildings(s2) << endl;
  cout << waysBuildingsDP(s2) << endl;
  return 0;
}
