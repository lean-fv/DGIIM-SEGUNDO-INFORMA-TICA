#include <iostream>
#include <string>

#include "tree.h"
#include "aux_funcs.h"

using namespace std;

int main(int argc, char *argv[])
{
  tree <int> tree_1(0);

  auto root_1 = tree_1.get_root();
  tree<int>::node inserted_node;

  inserted_node = insert_ordered_child(tree_1, root_1, 2);
  insert_ordered_child(tree_1, root_1, 3);
  insert_ordered_child(tree_1, root_1, 1);

  insert_ordered_child(tree_1, inserted_node, 5);
    insert_ordered_child(tree_1, inserted_node, 4);
    insert_ordered_child(tree_1, inserted_node, 4);

    cout << tree_1;

  tree <char> dictionary(0);
  insert_word(dictionary, "amo");
  insert_word(dictionary, "ama");
  insert_word(dictionary, "ala");
  insert_word(dictionary, "alado");
  insert_word(dictionary, "boina");

  cout << dictionary;
  return 0;

}
