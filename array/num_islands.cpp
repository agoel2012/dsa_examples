#include <iostream>
#include <vector>

using namespace std;

void islandDfs(vector<vector<int>> &grid, int row, int col) {
  int nrow = grid.size();
  int ncol = grid[0].size();
  /* Base case */
  if (row < 0 || col < 0 || row >= nrow || col >= ncol) {
    return;
  }

  /* Visit the existing node */
  grid[row][col] = 0;
  /* Only visit the neighbor if its an island */
  if (row + 1 < nrow && grid[row + 1][col] == 1)
    islandDfs(grid, row + 1, col);

  if (row - 1 >= 0 && grid[row - 1][col] == 1)
    islandDfs(grid, row - 1, col);

  if (col + 1 < ncol && grid[row][col + 1] == 1)
    islandDfs(grid, row, col + 1);

  if (col - 1 >= 0 && grid[row][col - 1] == 1)
    islandDfs(grid, row, col - 1);

  return;
}

/**
 * Given a 2D grid of 0, 1
 * find # of unique islands
 */
int numIslands(vector<vector<int>> &grid) {
  int n = (int)grid.size();
  int m = (int)grid[0].size();
  int num_islands = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (grid[i][j] == 1) {
        num_islands++;
        islandDfs(grid, i, j);
      }
    }
  }

  return num_islands;
}

int main(int argc, char *argv[]) {
  vector<vector<int>> grid = {
      {1, 1, 0, 0, 0}, {1, 1, 0, 0, 0}, {0, 0, 0, 1, 1}, {0, 0, 0, 1, 1}};

  vector<vector<int>> grid2 = {
      {1, 1, 0, 1, 1}, {1, 0, 0, 0, 0}, {0, 0, 0, 0, 1}, {1, 1, 0, 1, 1}};

  cout << "Grid Row = " << grid2.size() << ", Col = " << grid2[0].size()
       << endl;
  cout << numIslands(grid2) << endl;
  return 0;
}
