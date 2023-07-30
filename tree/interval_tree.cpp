#include <climits>
#include <iostream>
#include <vector>

using namespace std;

class IntervalTreeNode {
public:
  int start;
  int end;
  int middle;
  IntervalTreeNode *left;
  IntervalTreeNode *right;
  IntervalTreeNode()
      : start(INT_MAX), end(INT_MIN), middle(-1), left(nullptr),
        right(nullptr) {}
  IntervalTreeNode(int s, int e, int m)
      : start(s), end(e), middle(m), left(nullptr), right(nullptr) {}
  IntervalTreeNode(int s, int e, int m, IntervalTreeNode *l,
                   IntervalTreeNode *r)
      : start(s), end(e), middle(m), left(l), right(r) {}
};

class IntervalTree {
public:
  IntervalTreeNode *root;
  IntervalTree() : root(nullptr) {}
  void add(IntervalTreeNode *node, int start, int end) {
    if (end < node->middle) {
      // Go left as interval is before middle of cur interval
      if (node->left) {
        add(node->left, start, end);
      } else {
        node->left = new IntervalTreeNode(start, end, ((start + end) / 2));
      }
    } else if (start > node->middle) {
      // Go right as interval is after middle of cur interval
      if (node->right) {
        add(node->right, start, end);
      } else {
        node->right = new IntervalTreeNode(start, end, ((start + end) / 2));
      }
    } else {
      // Add to the current interval
      node->start = min(start, node->start);
      node->end = max(end, node->end);
    }
  }

  vector<vector<int>> get(IntervalTreeNode *node) {
    vector<vector<int>> result;
    if (node == nullptr) {
      return result;
    }

    // Merge sort divide and conquer
    auto left_intervals = get(node->left);
    auto right_intervals = get(node->right);

    bool inserted = false;
    for (auto interval : left_intervals) {
      // [intvl.s, intvl.e node.start node.end]
      if (interval[1] < node->start) {
        result.push_back(interval);
      } else {
        // Overlap: [intvl.s node.s intvl.e node.end]
        vector<int> tmp;
        tmp.push_back(min(interval[0], node->start));
        tmp.push_back(node->end);
        result.push_back(tmp);
        inserted = true;
        break;
      }
    }

    if (!inserted) {
      // incase no overlap found, add node.s, node.e at the tail of result
      vector<int> tmp;
      tmp.push_back(node->start);
      tmp.push_back(node->end);
      result.push_back(tmp);
    }

    for (auto interval : right_intervals) {
      int N = (int)result.size();
      if (interval[0] <= node->end) {
        // Overlap: [node.start intvl.s node.end intvl.e]
        result[N - 1][1] = max(node->end, interval[1]);
      } else {
        // [node.start, node.end intvl.s intvl.e]
        result.push_back(interval);
      }
    }

    return result;
  }
};

// Interval Tree: O(N) for add, O(log N) for merge
// Traditional merge and insert, it is O(1) for add, O(NlogN) for sort and then
// O(N) for merge In-place Merge and Insert, it is O(N) for merge
vector<vector<int>> insert(vector<vector<int>> intervals,
                           vector<int> newInterval) {
  vector<vector<int>> result;

  // Add to the tree
  IntervalTree *tree = new IntervalTree();
  for (auto interval : intervals) {
    if (!tree->root) {
      tree->root = new IntervalTreeNode(interval[0], interval[1],
                                        ((interval[0] + interval[1]) / 2));
    } else {
      tree->add(tree->root, interval[0], interval[1]);
    }
  }

  tree->add(tree->root, newInterval[0], newInterval[1]);

  // Query for the newInterval
  return tree->get(tree->root);
}

int main(int argc, char *argv[]) {
  vector<vector<int>> intervals = {};
  vector<int> newInterval = {};
  insert(intervals, newInterval);
  return 0;
}
