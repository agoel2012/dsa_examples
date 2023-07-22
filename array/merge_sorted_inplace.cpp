#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

void mergeInplace(vector<int> &nums1, int m, vector<int> &nums2, int n) {
  return;
}

int main(int argc, char *argv[]) {
  /** Test usecases */
  vector<int> nums1 = {1, 2, 3, 0, 0, 0};
  int n1 = 3;
  vector<int> nums2 = {2, 5, 6};
  int n2 = 3;

  vector<int> nums3 = {1};
  int n3 = 1;
  vector<int> nums4;
  int n4 = 0;

  vector<int> nums5 = {0};
  int n5 = 0;
  vector<int> nums6 = {1};
  int n6 = 1;
  print(mergeInplace(nums1, n1, nums2, n2));
  print(mergeInplace(nums3, n3, nums4, n4));
  print(mergeInplace(nums5, n5, nums6, n6));
  return 0;
}
