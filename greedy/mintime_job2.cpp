#include <algorithm>
#include <cmath>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
// Greedy algorithm

int minTimeFinishJobs2(vector<int> &jobs, vector<int> &workers) {
  int result = 0;
  int N = (int)(jobs.size());
  sort(workers.begin(), workers.end(), greater<int>());
  sort(jobs.begin(), jobs.end(), greater<int>());

  for (int i = 0; i < N; i++) {
    result = max(result, (int)ceil(jobs[i] / workers[i]));
  }

  return result;
}

int main(int argc, char *argv[]) {

  vector<int> jobs1 = {5, 2, 4};
  vector<int> workers1 = {1, 7, 5};
  vector<int> jobs2 = {3, 18, 15, 9};
  vector<int> workers2 = {6, 5, 1, 3};
  cout << minTimeFinishJobs2(jobs1, workers1) << endl;
  cout << minTimeFinishJobs2(jobs2, workers2) << endl;
  return 0;
}
