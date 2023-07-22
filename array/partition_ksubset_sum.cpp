#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
// Backtracking + Memoization for time-completixity

bool backtrackDfsSubsets(vector<int> nums, unordered_map<string, bool> &cache,
                         string &path, int targetSubset, int curSubset,
                         int targetSum, int curSum, int startIndex) {
  int N = nums.size();
  // Base case
  if (curSum > targetSum) {
    return false;
  }

  if (curSubset == targetSubset - 1) {
    return true;
  }

  // Cachced case
  if (cache.count(path)) {
    return cache[path];
  }

  // Recursive case
  if (curSum == targetSum) {
    cache[path] = backtrackDfsSubsets(nums, cache, path, targetSubset,
                                      curSubset + 1, targetSum, 0, 0);
    return cache[path];
  }

  for (int i = startIndex; i < N; i++) {
    if (path[i] == '0') {
      path[i] = '1';

      if (backtrackDfsSubsets(nums, cache, path, targetSubset, curSubset,
                              targetSum, curSum + nums[i], i + 1)) {
        return cache[path] = true;
      }

      path[i] = '0';
    }
  }

  return cache[path] = false;
}

bool canPartitionSubsetsHelper(vector<int> nums, int k, int target_sum) {
        int N = nums.size();
	unordered_map<string, bool> cache;
	string path(N, '0');
	return backtrackDfsSubsets(nums, cache, path, k, 0, target_sum, 0, 0);
}

bool canPartitionKSubsets(vector<int> &nums, int k) {
  int totalArraySum = 0;
  int n = nums.size();

  for (int i = 0; i < n; ++i) {
    totalArraySum += nums[i];
  }

  // If total sum not divisible by k, we can't make subsets.
  if (totalArraySum % k != 0) {
    return false;
  }

  // Sort in decreasing order.
  sort(nums.begin(), nums.end(), greater<int>());

  int targetSum = totalArraySum / k;
  return canPartitionSubsetsHelper(nums, k, targetSum);
}

int main(int argc, char *argv[]) {

  vector<int> nums1 = {4, 3, 2, 3, 5, 2, 1};
  int k1 = 4;

  vector<int> nums2 = {1, 2, 3, 4};
  int k2 = 3;

  cout << ((canPartitionKSubsets(nums1, k1)) ? "True" : "False") << endl;
  cout << ((canPartitionKSubsets(nums2, k2)) ? "True" : "False")  << endl;
  return 0;
}
