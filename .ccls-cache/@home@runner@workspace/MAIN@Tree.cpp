#include <bits/stdc++.h>
using namespace std;

struct TreeNode{
  int val;
  TreeNode* left;
  TreeNode* right;

  TreeNode(int x): val(x), left(nullptr), right(nullptr){}
};

int main(){
  TreeNode* root = new TreeNode(5);
  root->left = new TreeNode(10);
  root->right = new TreeNode(6);

  
  return 0;
}