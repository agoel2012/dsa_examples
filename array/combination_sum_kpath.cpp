#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

void printCombinations(vector<vector<int>> result) {
  cout << "Combinations: " << endl;
  int n = result.size();
  for (int i = 0; i < n; i++) {
    int m = result[i].size();
    for (int j = 0; j < m; j++) {
      cout << result[i][j] << ",";
    }

    cout << endl;
  }
  cout << endl;
}

void combinationSumHelper(int target_sum, size_t target_path, int startIndex,
                          vector<int> &path, vector<vector<int>> &result) {
  // Base case
  if (target_sum == 0 && path.size() == target_path) {
    result.push_back(path);
    return;
  }

  if (startIndex > 9) {
    return;
  }

  if (target_sum < 0) {
    return;
  }

  // Recursive case
  for (int i = startIndex; i <= 9; i++) {
    // Take choice
    path.push_back(i);
    // Backtrack
    combinationSumHelper(target_sum - i, target_path, i + 1, path, result);
    // drop choice
    path.pop_back();
  }
}

vector<vector<int>> combinationSum(int n, int k) {
  vector<vector<int>> result;
  vector<int> path;
  combinationSumHelper(n, (size_t)k, 1, path, result);
  return result;
}

int main(int argc, char *argv[]) {
  /** Test usecase */
  vector<pair<int, int>> candidates = {{3, 7}, {3, 9}, {4, 1}};
  for (int i = 0; i < (int)(candidates.size()); i++) {
    int k = candidates[i].first;
    int n = candidates[i].second;
    printCombinations(combinationSum(n, k));
  }

  return 0;
}
