#include <deque>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

int trappingWater2(vector<vector<int>> &heightMap) {
  int M = (int)heightMap.size();
  int N = (int)heightMap[0].size();
  int result = 0;
  int level = 0;
  vector<vector<int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
  vector<vector<bool>> visited(M + 1, vector<bool>(N + 1, false));

  // {Height, Row, Col}
  auto cmpfn = [&](vector<int> l, vector<int> r) { return l[0] >= r[0]; };
  priority_queue<vector<int>, deque<vector<int>>, decltype(cmpfn)> pq(cmpfn);
  // Border cells cannot store water and mark as visited
  for (int i = 0; i < M; i++) {
    vector<int> row1 = {heightMap[i][0], i, 0};
    pq.push(row1);
    vector<int> row2 = {heightMap[i][N - 1], i, N - 1};
    pq.push(row2);
    visited[i][0] = true;
    visited[i][N - 1] = true;
  }

  for (int i = 0; i < N; i++) {
    vector<int> col1 = {heightMap[0][i], 0, i};
    pq.push(col1);
    vector<int> col2 = {heightMap[M - 1][i], M - 1, i};
    pq.push(col2);
    visited[0][i] = true;
    visited[M - 1][i] = true;
  }

  // Iterate over the queue
  while (!pq.empty()) {
    auto top = pq.top();
    pq.pop();
    int height = top[0];
    int row = top[1];
    int col = top[2];
    // Make sure we are processing one level at a time
    level = max(level, height);
    // Iterate to 4D neighbors for a given r, c
    for (auto dir : directions) {
      row = row + dir[0];
      col = col + dir[1];
      // Only visit unvisited and safe r, c
      if (row >= 0 && row <= M - 1 && col >= 0 && col <= N - 1 &&
          !visited[row][col]) {
        visited[row][col] = true;
        // Only when cur < level's max height, we can trap water
        if (heightMap[row][col] < level) {
          result += (level - heightMap[row][col]);
        }

        // Push smaller height into the queue to visit its neighbors
        vector<int> nw = {heightMap[row][col], row, col};
        pq.push(nw);
      }
    }
  }

  return result;
}

int main(int argc, char *argv[]) {
  vector<vector<int>> heightmap = {{3, 3, 3, 3, 3},
                                   {3, 2, 2, 2, 3},
                                   {3, 2, 1, 2, 3},
                                   {3, 2, 2, 2, 3},
                                   {3, 3, 3, 3, 3}};
  cout << trappingWater2(heightmap) << endl;
  return 0;
}
