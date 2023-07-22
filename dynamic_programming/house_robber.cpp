#include <iostream>
#include <vector>

using namespace std;

int robHouse(vector<int> &nums) {

  int N = (int)(nums.size());
  vector<int> Sum(N + 1, 0);

  Sum[0] = nums[0];
  Sum[N - 1] = nums[N - 1];

  for (int i = N - 2; i >= 0; i--) {
    Sum[i] = max(Sum[i + 1], Sum[i + 2] + nums[i]);
  }

  return Sum[0];
  // S[0] = nums[0]
  // S[1] = nums[1]
  // i >= 2
  // S[i] = max(S[i-2] + num[i], S[i-1])
}

int main(int argc, char *argv[]) {

  vector<int> candidates1 = {1, 2, 3, 1};
  vector<int> candidates2 = {2, 7, 9, 3, 1};
  cout << robHouse(candidates1) << endl;
  cout << robHouse(candidates2) << endl;
  return 0;
}
