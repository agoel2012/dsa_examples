#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

/**
 * Legal directions are: U, D, L, R
 * Invalid is 0 --> need to distinguish backtracking case
 */
void islandDfs(vector<vector<int>> &grid, vector<vector<bool>> &visited,
               string &path, char dir, int row, int col) {
  int nrow = grid.size();
  int ncol = grid[0].size();
  if (row < 0 || col < 0 || row >= nrow || col >= ncol) {
    return;
  }

  if (!grid[row][col] || visited[row][col]) {
    return;
  }

  visited[row][col] = true;
  path += dir;
  islandDfs(grid, visited, path, 'D', row + 1, col);
  islandDfs(grid, visited, path, 'U', row - 1, col);
  islandDfs(grid, visited, path, 'R', row, col + 1);
  islandDfs(grid, visited, path, 'L', row, col - 1);
  path += '0'; // to indicate backtrack and how many times
  return;
}

/**
 * Given a 2D grid of 0, 1
 * find # of unique islands
 */
int numDistinctIslands(vector<vector<int>> &grid) {
  int n = (int)grid.size();
  int m = (int)grid[0].size();
  vector<vector<bool>> visited(n, vector<bool>(m, false));
  unordered_set<string> unique;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      string path = "";
      islandDfs(grid, visited, path, '0', i, j);
      if (unique.count(path) || path.length() == 0) {
        continue; // already seen before
      }

      unique.insert(path);
      path.clear();
    }
  }

  return unique.size();
}

int main(int argc, char *argv[]) {
  /** Test usecase */
  vector<vector<int>> grid = {
      {1, 1, 0, 0, 0}, {1, 1, 0, 0, 0}, {0, 0, 0, 1, 1}, {0, 0, 0, 1, 1}};

  vector<vector<int>> grid2 = {
      {1, 1, 0, 1, 1}, {1, 0, 0, 0, 0}, {0, 0, 0, 0, 1}, {1, 1, 0, 1, 1}};

  cout << "Grid Row = " << grid2.size() << ", Col = " << grid2[0].size()
       << endl;
  cout << numDistinctIslands(grid2) << endl;
  return 0;
}
