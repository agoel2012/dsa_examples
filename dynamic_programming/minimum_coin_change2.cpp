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

int minCoinChangesHelper(vector<int> coins, vector<vector<int>> &cache,
                         int rem_amount, int startIndex) {
  int N = (int)coins.size();
  if (rem_amount == 0) {
    return 1;
  }

  if (startIndex == N) {
    return 0;
  }

  if (rem_amount < 0) {
    return 0;
  }

  if (cache[startIndex][rem_amount] != INT_MIN) {
    return cache[startIndex][rem_amount];
  }

  if (coins[startIndex] > rem_amount) {
    return cache[startIndex][rem_amount] =
               minCoinChangesHelper(coins, cache, rem_amount, startIndex + 1);
  }

  // Recursive Case
  int result = minCoinChangesHelper(
                   coins, cache, rem_amount - coins[startIndex], startIndex) +
               minCoinChangesHelper(coins, cache, rem_amount, startIndex + 1);

  cache[startIndex][rem_amount] = result;
  return (cache[startIndex][rem_amount]);
}

int minCoinChanges2(vector<int> coins, int amount) {
  int N = (int)coins.size();
  vector<vector<int>> cache(N + 1, vector<int>(amount + 1, INT_MIN));
  return minCoinChangesHelper(coins, cache, amount, 0);
}

int main(int argc, char *argv[]) {
  vector<int> coins = {1, 2, 5};
  int amount = 5;
  cout << minCoinChanges2(coins, amount) << endl;
  return 0;
}
