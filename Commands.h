#ifndef COMMANDS_H
#define COMMANDS_H
#include "Utilities.h"

void Encode(ifstream &input_file, const string &encoding_file_name,
            const string &tree_file_name, const string &code_table_file_name) {
  // Emptying txts
  ofstream encoding_file_clean(encoding_file_name);
  ofstream tree_file_clean(tree_file_name);
  ofstream code_table_clean(code_table_file_name);
  encoding_file_clean.close();
  tree_file_clean.close();
  code_table_clean.close();

  string line;
  getline(input_file, line);
  transform(line.begin(), line.end(), line.begin(), ::tolower);
  map<char, int> frequencies;
  for (auto &ch : line) {  // Finding frequencies of chars and recording
    frequencies[ch]++;
  }

  vector<pair<char, int>> sorted_freqs;
  sorted_freqs.reserve(frequencies.size());
  for (auto &it : frequencies) {
    sorted_freqs.emplace_back(it);
  }
  // (Stable) sorting freqs by their values
  sort(sorted_freqs.begin(), sorted_freqs.end(), CompareByValue);

  // Making binary trees from chars and adding them to a new vector
  vector<pair<BinaryTree, int>> bt_vector;
  for (auto &it : sorted_freqs) {
    char key = it.first;
    int value = it.second;

    bt_vector.emplace_back(BinaryTree(key), value);
  }

  // After creating the Huffman tree, the only element in the vector
  // will be the Huffman tree
  CreateHuffmanCodingTree(bt_vector);

  map<char, string> code_table;
  // Getting the code table from the Huffman tree by using inorder traverse
  bt_vector[0].first.Inorder(bt_vector[0].first.get_root(), "", code_table);

  // Encoding the input
  string code;
  for (auto &ch : line) {
    code += code_table[ch];
  }

  cout << code << endl;  // Output
  // Saving the code to a file
  PrintLineToText(encoding_file_name, code);

  // Saving tree to a file
  Node *node = bt_vector[0].first.get_root();
  ofstream output_file;
  output_file.open(tree_file_name, ios_base::app);
  bt_vector[0].first.PreorderSave(node, output_file);
  output_file.close();

  // Saving code table to a file
  output_file.open(code_table_file_name, ios_base::app);
  for (auto &it : code_table) {
    string output_line(1, it.first);
    output_line += " " + it.second;
    PrintLineToText(code_table_file_name, output_line);
  }

  // Deleting the tree nodes
  bt_vector[0].first.DestroyTree(node);
}

void Decode(ifstream &input_file, const string &encoding_file_name,
            const string& tree_file_name) {
  ifstream tree_file(tree_file_name);

  BinaryTree binary_tree;
  binary_tree.CreateTreeFromFile(tree_file);  // Reads tree from file

  ifstream encoding_file(encoding_file_name);
  string code;
  getline(encoding_file, code);

  // Decode phase
  Node *node = binary_tree.get_root();
  string result;
  for (auto &ch : code) {
    // If the item is a letter, add it to the result and return to the root
    if (node->get_node_item() != '.') {
      result += node->get_node_item();
      node = binary_tree.get_root();
    }

    if (ch == '0') {
      node = node->get_left_child();
    } else {
      node = node->get_right_child();
    }
  }
  result += node->get_node_item();  // Additional, for the last item

  // Deleting nodes from the heap
  node = binary_tree.get_root();
  binary_tree.DestroyTree(node);

  cout << result << endl;  // Output
}

void ShowCharacterCode(char character) {
  ifstream code_table_file("code_table.txt");
  string line;
  string encoding;
  while (getline(code_table_file, line)) {
    if (line[0] == character) {
      encoding = line.substr(2, line.length() - 2);
    }
  }

  cout << encoding << endl;
}

void PrintBinaryTree() {
  BinaryTree binary_tree;
  ifstream tree_file("tree.txt");
  binary_tree.CreateTreeFromFile(tree_file);  // Reads tree from file
  binary_tree.PreorderPrint(binary_tree.get_root(), "+- ");  // Output

  // Deleting nodes from the heap
  Node *node = binary_tree.get_root();
  binary_tree.DestroyTree(node);
}

#endif
