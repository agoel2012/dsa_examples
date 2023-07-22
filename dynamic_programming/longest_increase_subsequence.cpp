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

int lis(vector<int> nums) {

  int N = (int)(nums.size());
  vector<int> cache(N, 1);
  int result = 1;

  for (int i = 1; i < N; i++) {
    for (int j = 0; j < i; j++) {
      if (nums[i] > nums[j]) {
        cache[i] = max(cache[i], 1 + cache[j]);
      }
    }

    result = max(result, cache[i]);
  }

  return result;
}

int main(int argc, char *argv[]) {
  vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
  vector<int> nums2 = {0, 1, 0, 3, 2, 3};
  cout << lis(nums) << endl;
  cout << lis(nums2) << endl;
  return 0;
}
