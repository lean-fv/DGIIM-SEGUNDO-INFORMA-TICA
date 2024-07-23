#include <iostream>

#include "tree.h"

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
  auto n6 = tree_1.insert_left_child(n5, 9);

  tree <int> tree_2(6);

  auto root_2 = tree_2.get_root();
  n1 = tree_1.insert_left_child(root_2, 7);
  n2 = tree_1.insert_right_sibling(n1, 8);
  n3 = tree_1.insert_left_child(n2, 9);
  n4 = tree_1.insert_right_sibling(n2, 10);
  n5 = tree_1.insert_right_sibling(n2, 11);

  cout << tree_1;
  cout << tree_2;

  tree_2.insert_left_child(n2, tree_1);

  cout << tree_2;

  return 0;
}
