#include <iostream>
#include "tree.h"
#include "aux_funcs.h"

using namespace std;

int main(int argc, char *argv[])
{
  tree <int> tree_1(0);

  auto root_1 = tree_1.get_root();
  auto n1 = tree_1.insert_left_child(root_1, 1);
  auto n2 = tree_1.insert_right_sibling(n1, 2);
  auto n3 = tree_1.insert_left_child(n2, 3);
  auto n4 = tree_1.insert_right_sibling(n2, 4);
  auto n5 = tree_1.insert_right_sibling(n2, 5);

  cout << tree_1;

  int total_sum = 0;
  sum_tree(root_1, total_sum);

  cout << "Tree total sum: " << total_sum << endl;

  int max_tree_val = 0;
  tree<int>::node max_node;
  max_value(root_1, max_tree_val, max_node);

  cout << "Max value in tree: " << max_tree_val << endl;
  cout << "Is max value in n2?: " << (n2 == max_node) << endl;
  cout << "Is max value in n5?: " << (n5 == max_node) << endl;

  return 0;
}
