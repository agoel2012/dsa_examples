#include <iostream>
#include <vector>

using namespace std;

class TreeNode {
public:
  int val;
  TreeNode *right;
  TreeNode *left;
  int height;
  TreeNode() : val(-1), right(nullptr), left(nullptr), height(0) {}
  TreeNode(int v) : val(v), right(nullptr), left(nullptr), height(0) {}
  TreeNode(int v, TreeNode *l, TreeNode *r) : val(v), right(r), left(l), height(0) {}
}; // class TreeNode

class Tree {
public:
  TreeNode *root;
  Tree(TreeNode *r) : root(r) {}
  Tree() : root(nullptr) {}
  int getDepth(TreeNode *root) {
      return ((root->height) ? root->height : 0);
  }

  // Rotate functions: RR or RL topology
  TreeNode *leftRotate(TreeNode *y) {
	  //	    y
	  //	    	  x
	  //	    t
	  TreeNode *x = y->right;
	  TreeNode *t = x->left;
	  // make x the new root, x's left is y and y's right is T
	  x->left = y;
	  y->right = t;
	  x->height = 1 + max(getDepth(x->left), getDepth(x->right));
	  y->height = 1 + max(getDepth(y->left), getDepth(y->right));
	  return x;
  }

  // LL or LR topology:
  // 		y
  //	 x
  //	 	t
  TreeNode *rightRotate(TreeNode *y) {
	TreeNode *x = y->left;
	TreeNode *t = x->right;
	// make x the new root, x's right is y and y's left is T
	x->right = y;
	y->left = t;
	x->height = 1 + max(getDepth(x->left), getDepth(x->right));
	y->height = 1 + max(getDepth(y->left), getDepth(y->right));
	return x;
  }

  TreeNode *insertAVL(TreeNode *root, int val) {
	  if (root == nullptr) {
		  return (new TreeNode(val));
	  }

	  if (val < root->val) {
		  root->left = insertAVL(root->left, val);
	  } else {
		  root->right = insertAVL(root->right, val);
	  }

	  int hLeft = getDepth(root->left);
	  int hRight = getDepth(root->right);
	  root->height = 1 + max(hLeft, hRight);
	  // Balance Factor is between [-1, 1]
	  if (abs(hLeft - hRight) < 2) {
		  // Balanced
		  return root;
	  }

	  // Balance Factor > 1, LL, LR
	  if ((hLeft - hRight) > 1 && val < root->left->val) {
		 return rightRotate(root);
	  } else if ((hLeft - hRight) > 1 && val > root->left->val) {
		  root->left = leftRotate(root->left);
		  return rightRotate(root);
	  }

	  // Balance Factor < 1, RR, RL
	  if ((hLeft - hRight) < 1 && val > root->right->val) {
		  return leftRotate(root);
	  } else if ((hLeft - hRight) < 1 && val < root->right->val) {
		  root->right = rightRotate(root->right);
		  return leftRotate(root);
	  }

	  return root;
  }

  void inorderAVL(TreeNode *root) {
    if (root == nullptr) {
      return;
    }

    // Left, Node, Right
    inorderAVL(root->left);
    cout << root->val << "\t";
    inorderAVL(root->right);
  }

}; // class Tree

int main(int argc, char *argv[]) {

	return 0;
}

