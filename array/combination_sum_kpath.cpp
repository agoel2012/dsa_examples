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

bool sumHelper(vector<int> arr, vector<int> &path, int target, int startIndex) {
  // Base case
  if (target == 0 && path.size() == 3) {
    for_each(path.begin(), path.end(), [](int item) { cout << item << endl; });
    return true;
  }

  if (target < 0 || path.size() > 3) {
    return false;
  }

  bool result = false;
  for (int i = startIndex; i < (int)arr.size(); i++) {
    path.push_back(arr[i]);
    if (sumHelper(arr, path, target - arr[i], i + 1)) {
      result = true;
      return result;
    }

    path.pop_back();
  }

  return result;
}

bool find_sum_of_three(vector<int> arr, int required_sum) {
  sort(arr.begin(), arr.end());
  vector<int> path;
  return sumHelper(arr, path, required_sum, 0);
}

int main(int argc, char *argv[]) {
  /** Test usecase */
  vector<pair<int, int>> candidates = {{3, 7}, {3, 9}, {4, 1}};
  for (int i = 0; i < (int)(candidates.size()); i++) {
    int k = candidates[i].first;
    int n = candidates[i].second;
    printCombinations(combinationSum(n, k));
  }

  cout << find_sum_of_three({3, 7, 1, 2, 8, 4, 5}, 20) << endl;

  return 0;
}
