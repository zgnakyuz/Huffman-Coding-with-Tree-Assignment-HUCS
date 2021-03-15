#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <bits/stdc++.h>

using namespace std;

class Node {
 public:
  Node() = default;
  explicit Node(const char &item, Node *left = nullptr, Node *right = nullptr)
  :item_(item), left_child_(left), right_child_(right) {}

  Node *get_left_child() {return left_child_;}
  Node *get_right_child() {return right_child_;}
  char get_node_item() const {return item_;}

 private:
  char item_{};
  Node *left_child_{};
  Node *right_child_{};

  friend class BinaryTree;
};

class BinaryTree {
 public:
  BinaryTree();
  explicit BinaryTree(const char &rootItem);

  bool is_empty() {return root_ == nullptr;}
  Node *get_root() {return root_;}

  void CreateTreeFromFile(ifstream &tree_file);
  void TraverseFile(ifstream &tree_file, Node *&node);
  void PreorderPrint(Node *node, string output);
  void PreorderSave(Node *node, ofstream &output_file);
  void Inorder(Node *node, const string &code, map<char, string> &code_table);
  void AttachLeftSubtree(BinaryTree &tree);
  void AttachRightSubtree(BinaryTree &tree);
  void DestroyTree(Node *&node);

 private:
  Node *root_{};
};

BinaryTree::BinaryTree() {
  root_ = nullptr;
}

BinaryTree::BinaryTree(const char &rootItem) {
  Node *node = new Node(rootItem);
  root_ = node;
}

void BinaryTree::AttachLeftSubtree(BinaryTree &tree) {
  if (!is_empty() && (root_->left_child_ == nullptr)) {
    root_->left_child_ = tree.root_;
  }
}

void BinaryTree::AttachRightSubtree(BinaryTree &tree) {
  if (!is_empty() && (root_->right_child_ == nullptr)) {
    root_->right_child_ = tree.root_;
  }
}

// Traverses a tree by inorder. In addition, create codes for chars and saves
// them to the code table. Codes are generated by adding "0" to code when
// traversed to left and adding "1" to code when traversed to right.
void BinaryTree::Inorder(Node *node, const string& code,
                         map<char, string> &code_table) {
  if (node != nullptr) {
    Inorder(node->left_child_, code + "0", code_table);

    if (node->item_ != '.') {
      code_table[node->item_] = code;
    }

    Inorder(node->right_child_, code + "1", code_table);
  }
}

// Destroys the tree's nodes in the heap
void BinaryTree::DestroyTree(Node *&node) {
  if (node != nullptr) {
    DestroyTree(node->left_child_);
    DestroyTree(node->right_child_);
    delete node;
    node = nullptr;
  }
}

// Saves the tree (and NULL subtrees of the leaves) to a text file
// by using preorder traverse
void BinaryTree::PreorderSave(Node *node, ofstream &output_file) {
  if (node != nullptr) {
    output_file << node->item_ << endl;
    PreorderSave(node->left_child_, output_file);
    PreorderSave(node->right_child_, output_file);
  } else {
    output_file << "NULL" << endl;
  }
}

// Traverses tree file and construct nodes
void BinaryTree::TraverseFile(ifstream &tree_file, Node *&node) {
  string line;
  if (!getline(tree_file, line)) {
    return;
  }

  if (line != "NULL") {
    node = new Node(line[0]);
    TraverseFile(tree_file, node->left_child_);
    TraverseFile(tree_file, node->right_child_);
  }
}

// Created for starting the TraverseFile function with the root
void BinaryTree::CreateTreeFromFile(ifstream &tree_file) {
  TraverseFile(tree_file, root_);
}

// Prints the tree by using preorder traversal
void BinaryTree::PreorderPrint(Node *node, string output) {
  if (node != nullptr) {
    cout << output + "(" + node->item_ + ")" << endl;
    PreorderPrint(node->left_child_, "   " + output);
    PreorderPrint(node->right_child_, "   " + output);
  }
}

#endif