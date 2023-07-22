#include <climits>
#include <iostream>
#include <vector>

using namespace std;

int trappingWater1(vector<int> &buildings) {

  int N = (int)(buildings.size());
  int result = 0;
  vector<int> maxLeft(N + 1, 0);
  vector<int> maxRight(N + 1, 0);
  maxLeft[0] = buildings[0];
  maxRight[N - 1] = buildings[N - 1];
  for (int i = 1; i < N; i++) {
    maxLeft[i] = max(maxLeft[i - 1], buildings[i]);
  }

  for (int i = N - 2; i >= 0; i--) {
    maxRight[i] = max(maxRight[i + 1], buildings[i]);
  }

  for (int i = 1; i < N - 1; i++) {
    result += min(maxLeft[i], maxRight[i]) - buildings[i];
  }

  return result;
}

int main(int argc, char *argv[]) {

  vector<int> buildings1 = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
  vector<int> buildings2 = {4, 2, 0, 3, 2, 5};
  cout << trappingWater1(buildings1) << endl;
  cout << trappingWater1(buildings2) << endl;
  return 0;
}
