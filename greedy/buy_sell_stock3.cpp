#include <climits>
#include <iostream>
#include <vector>

using namespace std;

int maxProfitsIter(vector<int> &prices) {
  int N = prices.size();
  int result = 0;
  vector<int> leftProfit(N + 1, 0);
  vector<int> rightProfit(N + 1, 0);
  int min_buy = prices[0];
  int max_sell = prices[N - 1];
  for (int i = 1; i < N; i++) {
    leftProfit[i] = max(prices[i] - min_buy, leftProfit[i - 1]);
    min_buy = min(min_buy, prices[i]);
  }

  for (int i = N - 2; i >= 0; i--) {
    rightProfit[i] = max(rightProfit[i + 1], max_sell - prices[i]);
    max_sell = max(max_sell, prices[i]);
  }

  for (int i = 0; i < N; i++) {
    result = max(result, leftProfit[i] + rightProfit[i + 1]);
  }

  return result;
}

int maxProfitsDPHelperCooldown(vector<int> &prices, vector<vector<int>> &memo,
                               int startIndex, int prevChoice) {
  int N = (int)prices.size();
  // Base case
  if (startIndex == N) {
    return 0;
  }

  // Cached case
  if (memo[startIndex][prevChoice] != INT_MIN) {
    return memo[startIndex][prevChoice];
  }

  // Recursive case: 1-BUY, 0-SELL, 2-COOLDOWN
  if (prevChoice == 1) {
    // 1 -> 0 -> 2 -> 1
    // Not 1
    // 0 -> 2 -> 1
    // Not 0
    // 2 -> 1
    memo[startIndex][prevChoice] =
        max(-prices[startIndex] + maxProfitsDPHelperCooldown(
                                      prices, memo, startIndex + 1, 0 /*SELL*/),
            maxProfitsDPHelperCooldown(prices, memo, startIndex + 1,
                                       prevChoice /*NOT BUY*/));
  } else if (prevChoice == 0) {
    memo[startIndex][prevChoice] = max(
        maxProfitsDPHelperCooldown(prices, memo, startIndex + 1,
                                   prevChoice /*NOT BUY */),
        prices[startIndex] + maxProfitsDPHelperCooldown(
                                 prices, memo, startIndex + 1, 2 /*COOLDOWN*/));
  } else {
    memo[startIndex][prevChoice] = max(
        maxProfitsDPHelperCooldown(prices, memo, startIndex + 1,
                                   prevChoice /*NOT COOLDOWN*/),
        maxProfitsDPHelperCooldown(prices, memo, startIndex + 1, 1 /*BUY*/));
  }

  return memo[startIndex][prevChoice];
}

int maxProfitsDPHelper(vector<int> &prices, vector<vector<vector<int>>> &memo,
                       int startIndex, int prevChoice, int curLen) {
  int N = (int)prices.size();
  // Base case
  if (curLen == 2 || startIndex == N) {
    return 0;
  }

  // Cached case
  if (memo[startIndex][prevChoice][curLen] != INT_MIN) {
    return memo[startIndex][prevChoice][curLen];
  }

  // Recursive case 1 ==> BUY, 0 ==> SELL
  if (prevChoice == 1) {
    memo[startIndex][prevChoice][curLen] = max(
        -prices[startIndex] +
            maxProfitsDPHelper(prices, memo, startIndex + 1, 0, curLen),
        maxProfitsDPHelper(prices, memo, startIndex + 1, prevChoice, curLen));
  } else {
    memo[startIndex][prevChoice][curLen] = max(
        prices[startIndex] +
            maxProfitsDPHelper(prices, memo, startIndex + 1, 1, curLen + 1),
        maxProfitsDPHelper(prices, memo, startIndex + 1, prevChoice, curLen));
  }

  return memo[startIndex][prevChoice][curLen];
}

// Backtracking + Memoization
int maxProfitsDP(vector<int> &prices) {
  int P = (int)(prices.size());
  int C = 2; // 0 or 1
  int T = 2; // length of transcation history is 2
  // cache is 3D of number of prices * # of choices * length of transaction thus
  // far
  vector<vector<vector<int>>> memo(
      P + 1, vector<vector<int>>(C + 1, vector<int>(T + 1, INT_MIN)));
  return maxProfitsDPHelper(prices, memo, 0 /* startIndex */,
                            1 /* prev choice */, 0 /* length of transaction */);
}

int maxProfitsDPCooldown(vector<int> &prices) {
  int P = (int)(prices.size());
  int C = 3; // 0 or 1 or 2
  // cache is 2D of number of prices * # of choices
  // far
  vector<vector<int>> memo(P + 1, vector<int>(C + 1, INT_MIN));
  return maxProfitsDPHelperCooldown(prices, memo, 0 /* startIndex */,
                                    1 /* prev choice */);
}

int main(int argc, char *argv[]) {
  vector<int> prices = {3, 3, 5, 0, 0, 3, 1, 4};
  cout << maxProfitsDP(prices) << endl;
  cout << maxProfitsIter(prices) << endl;
  vector<int> prices2 = {2, 4, 1};
  cout << maxProfitsIter(prices2) << endl;
  cout << maxProfitsDP(prices2) << endl;
  vector<int> prices3 = {3, 2, 6, 5, 0, 3};
  cout << maxProfitsDP(prices3) << endl;
  vector<int> prices4 = {1, 2, 3, 0, 2};
  cout << maxProfitsDPCooldown(prices4) << endl;
  return 0;
}
