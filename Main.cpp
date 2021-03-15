#include "Commands.h"

int main(int argc, char *argv[]) {
  string command_head = argv[1];

  if (command_head == "-i") {
    string command = argv[3];
    ifstream input_file(argv[2]);

    if (command == "-encode") {
      Encode(input_file, "encoding.txt", "tree.txt",
             "code_table.txt");
    } else {
      Decode(input_file, "encoding.txt", "tree.txt");
    }
  } else if (command_head == "-s") {
    ShowCharacterCode(argv[2][0]);
  } else {
    PrintBinaryTree();
  }

  return 0;
}
