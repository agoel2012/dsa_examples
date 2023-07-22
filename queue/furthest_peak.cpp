#include <deque>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

int furthestPeak(vector<int> &buildings, int bricks, int ladders) {
  priority_queue<int, deque<int>, greater<int>> pq; // minheap
  int N = (int)(buildings.size());
  for (int i = 0; i < N - 1; i++) {
    int climb = buildings[i + 1] - buildings[i];
    if (climb <= 0) {
      continue;
    }

    // Use ladder to allocate the max climbs
    pq.push(climb);
    int qsize = (int)pq.size();
    if (qsize <= ladders) {
      continue;
    }

    // Use bricks to allocate the minimum climbs
    bricks = bricks - pq.top();
    pq.pop();
    if (bricks < 0) {
      return i;
    }
  }

  return buildings.size() - 1;
}

int main(int argc, char *argv[]) {
  vector<int> buildings = {4, 12, 2, 7, 3, 18, 20, 3, 19};
  int bricks = 10;
  int ladders = 2;
  cout << furthestPeak(buildings, bricks, ladders) << endl;
  return 0;
}
