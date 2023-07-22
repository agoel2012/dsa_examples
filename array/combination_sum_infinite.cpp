#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

void printCombinations(vector<vector<int>> result) {
  int n = result.size();
  for (int i = 0; i < n; i++) {
    int m = result[i].size();
    for (int j = 0; j < m; j++) {
      cout << result[i][j] << ",";
    }

    cout << endl;
  }
}

void combinationSumHelper(vector<int> nums, int target, int startIndex,
                          int curSum, vector<int> &path,
                          vector<vector<int>> &result) {
  // Base case
  if (curSum == target) {
    result.push_back(path);
    return;
  }

  if (startIndex > (int)nums.size()) {
    return;
  }

  if (curSum > target) {
    return;
  }

  // Recursive case
  for (int i = startIndex; i < (int)nums.size(); i++) {
    // Take choice
    path.push_back(nums[i]);
    // Backtrack
    combinationSumHelper(nums, target, i, curSum + nums[i], path, result);
    // drop choice
    path.pop_back();
  }
}

vector<vector<int>> combinationSum(vector<int> &nums, int target) {
  vector<vector<int>> result;
  vector<int> path;
  combinationSumHelper(nums, target, 0, 0, path, result);
  return result;
}

int main(int argc, char *argv[]) {
  /** Test usecase */
  vector<int> candidates1 = {2, 3, 6, 7};
  int target1 = 7;
  vector<int> candidates2 = {2, 3, 5};
  int target2 = 8;
  vector<int> candidates3 = {2};
  int target3 = 1;
  printCombinations(combinationSum(candidates1, target1));
  printCombinations(combinationSum(candidates2, target2));
  printCombinations(combinationSum(candidates3, target3));
  return 0;
}
