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

int minCostTicketsHelper(vector<int> days, vector<int> &cache,
                         vector<int> costs, unordered_set<int> valid,
                         int cur_day) {
  int N = (int)days.size();
  if (cur_day > days[N - 1]) {
    return 0;
  }

  if (valid.count(cur_day) == 0) {
    return minCostTicketsHelper(days, cache, costs, valid, cur_day + 1);
  }

  if (cache[cur_day] != INT_MIN) {
    return cache[cur_day];
  }

  // 3 choices on any given day, taken the min of it
  int one_day =
      costs[0] + minCostTicketsHelper(days, cache, costs, valid, cur_day + 1);
  int seven_day =
      costs[1] + minCostTicketsHelper(days, cache, costs, valid, cur_day + 7);
  int thirty_day =
      costs[2] + minCostTicketsHelper(days, cache, costs, valid, cur_day + 30);
  cache[cur_day] = min(one_day, min(seven_day, thirty_day));
  return cache[cur_day];
}

int minCostTickets(vector<int> days, vector<int> costs) {
  int N = (int)days.size();
  vector<int> cache(N + 1, INT_MIN);
  unordered_set<int> valid;
  for_each(days.begin(), days.end(), [&](int day) { valid.insert(day); });
  return minCostTicketsHelper(days, cache, costs, valid, 1);
}

int main(int argc, char *argv[]) {
  vector<int> days1 = {1, 4, 6, 7, 8, 20};
  vector<int> cost1 = {2, 7, 15};
  vector<int> days2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 30, 31};
  vector<int> cost2 = {2, 7, 15};
  cout << minCostTickets(days1, cost1) << endl;
  cout << minCostTickets(days2, cost2) << endl;
  return 0;
}
