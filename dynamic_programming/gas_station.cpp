#include <climits>
#include <iostream>
#include <vector>

using namespace std;

int canCompleteCircuitGas(vector<int> &gas, vector<int> &cost) {
  // Kadane's algorithm for calculating max sum of a sub-array using prefixSum
  // Here when then maxCost changes, cache the index
  int currMax = 0, totalGain = 0, end = 0, start = 0, s = 0;

  for (int i = 0; i < (int)gas.size(); i++) {

    int curr = gas[i] - cost[i];
    if (curr > curr + currMax) {
      currMax = curr;
      start = s;
      end = i;
    } else {
      currMax = curr + currMax;
    }

    if (curr < 0) {
      s = i + 1;
    }

    totalGain += curr;
  }

  cout << "Start, End: " << start << ", " << end << endl;
  return totalGain >= 0 ? end : -1;
}

int main(int argc, char *argv[]) {

  vector<int> gas = {1, 2, 3, 4, 5};
  vector<int> cost = {3, 4, 5, 1, 2};
  cout << canCompleteCircuitGas(gas, cost) << endl;
  return 0;
}
