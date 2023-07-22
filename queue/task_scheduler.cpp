#include <deque>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

int taskSchedulerTime(vector<int> &tasks, int cooldown) {
  unordered_map<int, int> freq;       // frequency map
  priority_queue<int, deque<int>> pq; // maxheap;
  for (auto task : tasks) {
    freq[task]++;
  }

  for (auto [key, value] : freq) {
    pq.push(value);
  }

  int n = 0;
  int busy_time = 0;
  while (!pq.empty()) {
    vector<int> pending;
    n = cooldown + 1;
    while (!pq.empty() && n > 0) {
      auto top = pq.top();
      pq.pop();
      if (top > 1) {
        pending.push_back(top - 1);
      }
      busy_time++;
      --n;
    }

    for (auto ftask : pending) {
      pq.push(ftask);
    }

    if (pq.empty()) {
      break;
    }

    busy_time += n;
  }

  return busy_time;
}

int main(int argc, char *argv[]) {
  vector<int> tasks = {1, 1, 1, 2, 2, 2};
  int cooldown = 2;
  vector<int> tasks2 = {1, 1, 1, 1, 1, 1, 2, 3, 4, 5, 6, 7};
  int cooldown2 = 2;
  cout << taskSchedulerTime(tasks, cooldown) << endl;
  cout << taskSchedulerTime(tasks2, cooldown2) << endl;
  return 0;
}
