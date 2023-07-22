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

int minCoinChangesHelper(vector<int> coins, vector<int> &cache, int rem_amount,
                         vector<int> &path) {
  int N = (int)coins.size();
  if (rem_amount == 0) {
    return 0;
  }

  if (rem_amount < 0) {
    return -1;
  }

  if (cache[rem_amount] != INT_MIN) {
    return cache[rem_amount];
  }

  int min = INT_MAX;
  for (int i = 0; i < N; i++) {
    path.push_back(coins[i]);
    int result =
        minCoinChangesHelper(coins, cache, rem_amount - coins[i], path);
    if (result >= 0 && result < min) {
      // for_each(path.begin(), path.end(), [&](int coin) { cout << coin << ",";
      // }); cout << endl;
      path.clear();
      min = 1 + result;
    }
  }

  cache[rem_amount] = (min != INT_MAX) ? min : -1;
  return (cache[rem_amount]);
}

int minCoinChanges(vector<int> coins, int amount) {
  vector<int> cache(amount + 1, INT_MIN);
  vector<int> path;
  return minCoinChangesHelper(coins, cache, amount, path);
}

int main(int argc, char *argv[]) {
  vector<int> coins = {1, 2, 5};
  int amount = 11;
  cout << minCoinChanges(coins, amount) << endl;
  return 0;
}
