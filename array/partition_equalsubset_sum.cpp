#include <algorithm>
#include <iostream>
#include <optional>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

bool backtrackDfsSubsets(vector<int> &nums,
                         vector<vector<optional<bool>>> &memo, int curSum,
                         int startIndex) {

  // Base case
  if (curSum == 0) {
    return true;
  }

  if (curSum < 0 || startIndex == 0) {
    return false;
  }

  // Cached case
  if (memo[startIndex][curSum] != nullopt) {
    return (memo[startIndex][curSum] == true);
  }

  // Recursive case
  bool result = backtrackDfsSubsets(nums, memo, curSum - nums[startIndex - 1],
                                    startIndex - 1) ||
                backtrackDfsSubsets(nums, memo, curSum, startIndex - 1);

  memo[startIndex][curSum] = result;
  return result;
}

bool canPartitionSubsetsHelper(vector<int> &nums, int targetSum) {
  int N = (int)(nums.size());
  vector<vector<optional<bool>>> memo(
      N + 1, vector<optional<bool>>(targetSum + 1, nullopt));
  return backtrackDfsSubsets(nums, memo, targetSum, N);
}

bool canPartition(vector<int> &nums) {
  int totalArraySum = 0;
  int n = nums.size();

  for (int i = 0; i < n; ++i) {
    totalArraySum += nums[i];
  }

  // If total sum not divisible by 2, we can't make subsets.
  if (totalArraySum % 2 != 0) {
    return false;
  }

  // Sort in decreasing order.
  sort(nums.begin(), nums.end(), greater<int>());

  int targetSum = totalArraySum / 2;
  return canPartitionSubsetsHelper(nums, targetSum);
}

int main(int argc, char *argv[]) {
  vector<int> nums1 = {4, 3, 2, 3, 5, 2, 1};
  vector<int> nums2 = {1, 2, 3, 5};
  cout << ((canPartition(nums1)) ? "True" : "False") << endl;
  cout << ((canPartition(nums2)) ? "True" : "False") << endl;
  return 0;
}
