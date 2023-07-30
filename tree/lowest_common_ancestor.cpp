#include <iostream>
#include <vector>

using namespace std;

class TreeNode {
public:
  int val;
  TreeNode *right;
  TreeNode *left;
  TreeNode() : val(-1), right(nullptr), left(nullptr) {}
  TreeNode(int v) : val(v), right(nullptr), left(nullptr) {}
  TreeNode(int v, TreeNode *l, TreeNode *r) : val(v), right(r), left(l) {}
}; // class TreeNode

class Tree {
public:
  TreeNode *root;
  Tree(TreeNode *r) : root(r) {}
  Tree() : root(nullptr) {}
  int getDepth(TreeNode *root) {
    if (root == nullptr) {
      return 0;
    }

    TreeNode *tmp = root;
    int heightLeft = 0, heightRight = 0;
    while (tmp != nullptr) {
      tmp = tmp->left;
      heightLeft++;
    }

    tmp = root;
    while (tmp != nullptr) {
      tmp = tmp->right;
      heightRight++;
    }

    return (1 + max(heightLeft, heightRight));
  }

  TreeNode *successorNode(TreeNode *root) {
    // N = Node->Right, then N->Left
    if (root == nullptr) {
      return nullptr;
    }

    TreeNode *tmp = root->right;
    if (tmp == nullptr) {
      return nullptr;
    }

    while (tmp->left != nullptr) {
      tmp = tmp->left;
    }

    return tmp;
  }

  void inorderBST(TreeNode *root) {
    if (root == nullptr) {
      return;
    }

    // Left, Node, Right
    inorderBST(root->left);
    cout << root->val << "\t";
    inorderBST(root->right);
  }

  void preorderBST(TreeNode *root) {
    if (root == nullptr) {
      return;
    }

    // Node, Left, Right
    cout << root->val << "\t";
    inorderBST(root->left);
    inorderBST(root->right);
  }

  void postorderBST(TreeNode *root) {
    if (root == nullptr) {
      return;
    }

    // Left, Right, Node
    inorderBST(root->left);
    inorderBST(root->right);
    cout << root->val << "\t";
  }

  TreeNode *insertBST(TreeNode *root, int val) {
    if (root == nullptr) {
      return (new TreeNode(val));
    }

    if (val < root->val) {
      root->left = insertBST(root->left, val);
    } else if (val > root->val) {
      root->right = insertBST(root->right, val);
    } else {
      // Don't allow for duplicate, return the node found
      return root;
    }

    return root;
  }

  TreeNode *searchBST(TreeNode *root, int key) {
    if (root == nullptr || root->val == key) {
      return (root);
    }

    if (key < root->val) {
      return searchBST(root->left, key);
    } else {
      return searchBST(root->right, key);
    }
  }

  TreeNode *deleteBST(TreeNode *root, int val) { 
	 if (root == nullptr) {
		return root;
	 }

	 if (val < root->val) {
		root->left = deleteBST(root->left, val);
	 } else if (val > root->val) {
 		root->right = deleteBST(root->right, val);
	 } else {
 		// 4 scenarios
		if (!root->left && !root->right) {
		// Leaf node i.e left, right are null, just delete that node
			delete root;
			root = nullptr;
		} else if (!root->left && root->right) {
		// Leaf node 1 i.e left is null, right is not null, copy right's value into node, delete right
			root->val = root->right->val;
			delete root->right;
			root->right = nullptr;
		} else if (root->left && !root->right) {
		// Leaf node 2 i.e left is not null, right is null, copy left's value into node, delete left
			root->val = root->left->val;
			delete root->left;
			root->left = nullptr;
		} else {
		// Leaf node 3 i.e left is not null, right is not null, find successor node and copy suc's value into node, delete successor
			TreeNode *suc = successorNode(root);
			root->val = suc->val;
			root->right = deleteBST(root->right, val);
		}
	}

	return root;	 
  }
}; // class Tree

TreeNode *lowestCommonAncestorHelper(TreeNode *node, int p, int q) {
  if (node == nullptr) {
    return node;
  }

  // Matching case
  if (node->val == p || node->val == q) {
    return node;
  }

  TreeNode *left = lowestCommonAncestorHelper(node->left, p, q);
  TreeNode *right = lowestCommonAncestorHelper(node->right, p, q);
  if (left && right) {
    return node;
  }

  if (left && !right) {
    return left;
  }

  if (!left && right) {
    return right;
  }

  return nullptr;
}

TreeNode *lowestCommonAncestorArray(TreeNode *root, vector<TreeNode *> nodes) {
  if (root == nullptr) {
    return nullptr;
  }

  TreeNode *lca = nodes[0];
  for (int i = 1; i < (int)(nodes.size()); i++) {
    lca = lowestCommonAncestorHelper(root, lca->val, nodes[i]->val);
  }

  return lca;
}

TreeNode *lowestCommonAncestor(TreeNode *root, int p, int q) {
  return lowestCommonAncestorHelper(root, p, q);
}

int main(int argc, char *argv[]) {
  TreeNode *root = new TreeNode();
  vector<TreeNode *> nodes;
  auto LCA = lowestCommonAncestor(root, 1, 2);
  cout << LCA->val << endl;
  LCA = lowestCommonAncestorArray(root, nodes);
  cout << LCA->val << endl;
  return 0;
}
