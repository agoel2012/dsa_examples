#include <climits>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

double medianValue(int size, int a, int b) {
  return ((size % 2 == 0) ? ((double)(a + b) / (2.0)) : ((double)(b)));
}

double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {
  // Brute force is to create a new array, sort and merged[middle] or
  // (merged[lower_mid] + merged[upper_mid])/2 is median To achieve log (M + N)
  // time complexity, need to create a pivot element on each of array and track
  // L, R of pivot on each and do binary search
  int m = (int)nums1.size();
  int n = (int)nums2.size();

  if (m > n) {
    return findMedianSortedArrays(nums2, nums1);
  }

  // Start binary search on the smaller
  int left = 0;
  int right = m;
  while (left <= right) {
    // Assign pivots
    int m_left = (left + right) / 2;
    int n_left = (n + m + 1) / 2 - (m_left);
    // Edge case: use INT_MIN, INT_MAX for cases when mid are either end of the
    // array:
    int n1left = (m_left == 0) ? (INT_MIN) : nums1[m_left - 1];
    int n2left = (n_left == 0) ? (INT_MIN) : nums2[n_left - 1];
    int n1right = (m_left == m) ? (INT_MAX) : nums1[m_left];
    int n2right = (n_left == n) ? (INT_MAX) : nums2[n_left];
    // condition of binary search equality
    // B: nums2[L] nums2[R]
    // A: nums1[L] nums1[R]
    if (n1left <= n2right && n2left <= n1right) {
      return medianValue(m + n, max(n1left, n2left), min(n1right, n2right));
    } else if (n1left > n2right) {
      // Gone too far right, bring back
      right = m_left - 1;
    } else if (n2left > n1right) {
      // Too behind left, bring forward
      left = m_left + 1;
    }
  }

  return 0.0;
}

int main(int argc, char *argv[]) {
  vector<int> nums1 = {1, 3};
  vector<int> nums2 = {2};
  vector<int> nums3 = {1, 2};
  vector<int> nums4 = {3, 4};
  cout << findMedianSortedArrays(nums1, nums2) << endl;
  cout << findMedianSortedArrays(nums3, nums4) << endl;
  return 0;
}
