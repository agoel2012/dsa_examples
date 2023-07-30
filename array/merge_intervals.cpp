#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

void print(vector<vector<int>> result) {
  cout << "Intervals: " << endl;
  int n = result.size();
  for (int i = 0; i < n; i++) {
    int m = result[i].size();
    for (int j = 0; j < m; j++) {
      cout << result[i][j] << ",";
    }

    cout << endl;
  }
  cout << endl;
}

vector<vector<int>> mergeIntervals(vector<vector<int>> &intervals) {
  vector<vector<int>> result;
  // Sort increasing order by start of the interval
  sort(intervals.begin(), intervals.end(), [&](vector<int> l, vector<int> r) {
    return ((l[0] <= r[0]) ? true : false);
  });
  stack<vector<int>> current;
  current.push(intervals[0]);
  for (int i = 1; i < (int)(intervals.size()); i++) {
    if (!current.empty()) {
      auto top = current.top();
      if (top[1] >= intervals[i][0]) {
        top[1] = max(intervals[i][1], top[1]);
        current.pop();
        current.push(top);
      } else {
        current.push(intervals[i]);
      }
    }
  }

  while (!current.empty()) {
    auto top = current.top();
    result.push_back(top);
    current.pop();
  }

  return result;
}

class Pair {
public:
  int first, second;
  Pair(int x, int y) {
    first = x;
    second = y;
  }
};

vector<Pair> merge_intervals(vector<Pair> &v) {
  vector<Pair> result;
  int N = (int)v.size();
  if (N <= 1) {
    result = v;
    return result;
  }

  int j = 0;
  int i = 1;
  for (i = 1; i < N; i++) {
    if (v[j].second < v[i].first) {
      result.push_back(v[j]);
      j = i;
    } else {
      v[j].second = max(v[j].second, v[i].second);
      v[j].first = min(v[j].first, v[i].first);
    }
  }

  if (j == i) {
    result.push_back(v[i]);
  } else {
    result.push_back(v[j]);
  }

  return result;
}

int main(int argc, char *argv[]) {

  vector<vector<int>> intervals = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
  vector<vector<int>> intervals2 = {{1, 4}, {4, 5}};

  print(mergeIntervals(intervals));
  print(mergeIntervals(intervals2));

  vector<Pair> intervals3;
  intervals3.push_back(Pair(1, 3));
  intervals3.push_back(Pair(2, 6));
  intervals3.push_back(Pair(8, 10));
  intervals3.push_back(Pair(15, 18));
  auto result = merge_intervals(intervals3);
  for (auto i = 0; i < (int)result.size(); i++) {
    cout << result[i].first << "," << result[i].second << endl;
  }

  return 0;
}
