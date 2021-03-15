#ifndef UTILITIES_H
#define UTILITIES_H
#include "BinaryTree.h"

// Appends a line to a file
void PrintLineToText(const string &file_name, const string &line) {
  ofstream output_file;
  output_file.open(file_name, ios_base::app);
  output_file << line << endl;
}

// Created for sorting frequencies
bool CompareByValue(const pair<char, int> &a, const pair<char, int> &b) {
  return a.second < b.second;
}

// Finds the index where the new tree, which is created from merging,
// will be inserted
int FindPosition (vector<pair<BinaryTree, int>> &bt_vector, int value) {
  int position{0};

  // Traverses elements until find a value that is bigger than or
  // equals to the tree's value
  for (auto &it : bt_vector) {
    if (it.second >= value) {
      break;
    }
    position++;
  }

  return position;
}

// Merges two given trees with a '.' root node
pair<BinaryTree, int> MergeTrees(pair<BinaryTree, int> &left,
                                 pair<BinaryTree, int> &right) {
  BinaryTree *binary_tree_left = &left.first;
  int value_left = left.second;
  BinaryTree *binary_tree_right = &right.first;
  int value_right = right.second;

  BinaryTree binary_tree('.');
  binary_tree.AttachLeftSubtree(*binary_tree_left);
  binary_tree.AttachRightSubtree(*binary_tree_right);

  pair<BinaryTree, int> paired(binary_tree, value_left + value_right);
  return paired;
}

void CreateHuffmanCodingTree(vector<pair<BinaryTree, int>> &bt_vector) {
  // When size of the vector is 1, that means the Huffman tree is created
  while (bt_vector.size() != 1) {
    pair<BinaryTree, int> new_pair = MergeTrees(bt_vector[0], bt_vector[1]);

    bt_vector.erase(bt_vector.begin(), bt_vector.begin() + 2);
    bt_vector.insert(bt_vector.begin() +
                     FindPosition(bt_vector, new_pair.second), new_pair);
  }
}

#endif
