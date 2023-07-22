#include <algorithm>
#include <cmath>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
// Greedy algorithm

int maxSumSubarray(vector<int> &nums) {
  int N = (int)(nums.size());
  // Kadane's algorithm for finding subarray with the maximum sum
  // Start, End is the subarray contiguous bounds
  int start = 0, end = 0, s = 0;
  int sumSoFar = 0, maxSum = 0;
  for (int i = 0; i < N; i++) {
    sumSoFar += nums[i];
    if (sumSoFar > maxSum) {
      maxSum = sumSoFar;
      start = s;
      end = i;
    }

    if (sumSoFar < 0) {
      sumSoFar = 0;
      s = i + 1;
    }
  }

  cout << "Start, End of MaxSumSubarray: [" << start << ", " << end << "]"
       << endl;
  return maxSum;
}

int main(int argc, char *argv[]) {

  vector<int> nums1 = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
  vector<int> nums2 = {1};
  vector<int> nums3 = {5, 4, -1, 7, 8};
  cout << maxSumSubarray(nums1) << endl;
  cout << maxSumSubarray(nums2) << endl;
  cout << maxSumSubarray(nums3) << endl;
  return 0;
}
