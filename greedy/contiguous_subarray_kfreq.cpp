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

int contiguousSubarrayKFreq(vector<int> &nums, int K) {
  int N = (int)(nums.size());
  // Use a hashmap to store sum, freq pair
  unordered_map<int, int> freq{{0, 0}};
  int sumSoFar = 0, result = 0;
  for (int i = 0; i < N; i++) {
    sumSoFar += nums[i];
    if (sumSoFar == K) {
      result = result + 1;
    }

    if (freq.count(sumSoFar - K)) {
      result += freq[sumSoFar - K];
    }

    freq[sumSoFar]++;
  }

  return result;
}

bool contiguousSubarray2Size(vector<int> &nums, int K) {
  int N = (int)(nums.size());
  // Use a hashmap to store sum to index pair
  // Sum is a multiple of K
  // Length of subarray is atleast = 2;
  unordered_map<int, int> s2i{{0, 0}};
  int start = 0, end = 0, s = 0;
  int sumSoFar = 0;
  for (int i = 0; i < N; i++) {
    sumSoFar += nums[i];
    if (!s2i.count(sumSoFar % K)) {
      s2i[sumSoFar % K] = i + 1;
      s = i;
    } else if (s2i[sumSoFar % K] < i) {
      end = i;
      start = s;
      cout << "Start, End of Sum % K: [" << start << ", " << end << "]" << endl;
      return true;
    }
  }

  start = end = -1;
  cout << "Start, End of Sum % K: [" << start << ", " << end << "]" << endl;
  return false;
}

int maxSumSubarrayKSum(vector<int> &nums, int K) {
  int N = (int)(nums.size());
  // Use a hashmap to store sum to index pair
  // Sum - K is == 0 to find target
  // Length of subarray can be anything
  // Calculate maxSum when finding another pair where Sum - K == 0
  unordered_map<int, int> s2i{{0, 0}};
  int sumSoFar = 0;
  int result = -1;
  for (int i = 0; i < N; i++) {
    sumSoFar += nums[i];
    if (sumSoFar == K) {
      result = i + 1;
    }

    if (!s2i.count(sumSoFar)) {
      s2i[sumSoFar] = i;
    }

    if (s2i.count(sumSoFar - K)) {
      result = max(result, abs(i - s2i[sumSoFar - K]));
    }
  }

  return ((result != -1) ? result : 0);
}

int main(int argc, char *argv[]) {

  vector<int> nums1 = {1, 1, 1};
  int K1 = 2;
  vector<int> nums2 = {1, 2, 3};
  int K2 = 3;
  cout << contiguousSubarrayKFreq(nums1, K1) << endl;
  cout << contiguousSubarrayKFreq(nums2, K2) << endl;
  vector<int> nums3 = {23, 2, 4, 6, 7};
  int K3 = 6;
  vector<int> nums4 = {23, 2, 6, 4, 7};
  int K4 = 6;
  cout << contiguousSubarray2Size(nums3, K3) << endl;
  cout << contiguousSubarray2Size(nums4, K4) << endl;

  vector<int> nums5 = {1, -1, 5, -2, 3};
  int K5 = 3;
  vector<int> nums6 = {-2, -1, 2, 1};
  int K6 = 1;
  cout << maxSumSubarrayKSum(nums5, K5) << endl;
  cout << maxSumSubarrayKSum(nums6, K6) << endl;

  return 0;
}
