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

int backtrackDfs(vector<int> &nums, vector<vector<int>> &cache, int startIndex,
                 int curSum, int target, int totalSum) {
  int N = (int)nums.size();
  if (startIndex == N) {
    return (curSum == target) ? 1 : 0;
  }

  if (curSum > target) {
    return 0;
  }

  if (cache[startIndex][totalSum + curSum] != INT_MIN) {
    return cache[startIndex][totalSum + curSum];
  }

  cache[startIndex][totalSum + curSum] =
      backtrackDfs(nums, cache, startIndex + 1, curSum + nums[startIndex],
                   target, totalSum) +
      backtrackDfs(nums, cache, startIndex + 1, curSum - nums[startIndex],
                   target, totalSum);

  return cache[startIndex][totalSum + curSum];
}

int targetSum(vector<int> &nums, int target) {
  int totalSum = 0;
  int N = (int)nums.size();
  for_each(nums.begin(), nums.end(), [&](int item) { totalSum += item; });
  vector<vector<int>> cache(N + 1, vector<int>((2 * totalSum + 1), INT_MIN));
  return backtrackDfs(nums, cache, 0, 0, target, totalSum);
}

int main(int argc, char *argv[]) {
  vector<int> nums1 = {1, 1, 1, 1, 1};
  int target1 = 3;
  vector<int> nums2 = {1};
  int target2 = 1;
  cout << targetSum(nums1, target1) << endl;
  cout << targetSum(nums2, target2) << endl;
  return 0;
}
