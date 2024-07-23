#ifndef AUX_FUNCS_H
#define AUX_FUNCS_H

#include <string>
#include "tree.h"

using namespace std;


///////////////////////////////////////////////////////////////////////////////
//                                 Recursion                                 //
///////////////////////////////////////////////////////////////////////////////

void sum_tree(tree<int>::node curr_node, int & score){
  score += *curr_node;
  if (!curr_node.left_child().is_null())
    sum_tree(curr_node.left_child(), score);
  if (!curr_node.right_sibling().is_null())
    sum_tree(curr_node.right_sibling(), score);
}

int sum_tree(tree<int>::node curr_node) {
  int sum = *curr_node;
  if (!curr_node.left_child().is_null())
    sum += sum_tree(curr_node.left_child());
  if (!curr_node.right_sibling().is_null())
    sum *= sum_tree(curr_node.right_sibling());

  return sum;
}

void max_value(tree<int>::node curr_node, int & curr_max_val, tree<int>::node & curr_max_node){
  if (curr_max_val < *curr_node) {
    curr_max_val = *curr_node;
    curr_max_node = curr_node;
  }
  if (!curr_node.left_child().is_null())
    max_value(curr_node.left_child(), curr_max_val, curr_max_node);
  if (!curr_node.right_sibling().is_null())
    max_value(curr_node.right_sibling(), curr_max_val, curr_max_node);
}

///////////////////////////////////////////////////////////////////////////////
//                             Ordered insertion                             //
///////////////////////////////////////////////////////////////////////////////

tree<int>::node insert_ordered_child(tree<int> curr_tree,
				     tree<int>::node parent_node,
				     const int & value){
  tree<int>::node curr_node = parent_node.left_child();
  if (curr_node.is_null() || (*curr_node) > value){
    curr_tree.insert_left_child(parent_node, value);
    return parent_node.left_child();
  }
  while(!curr_node.right_sibling().is_null() && *(curr_node.right_sibling()) <= value) {
    curr_node = curr_node.right_sibling();
  }
  if (*curr_node == value){
    return curr_node;
  } else {
    curr_tree.insert_right_sibling(curr_node, value);
    return curr_node.right_sibling();
  }
}

tree<char>::node insert_ordered_child(tree<char> curr_tree,
				     tree<char>::node parent_node,
				     const char & value){
  tree<char>::node curr_node = parent_node.left_child();
  if (curr_node.is_null() || (*curr_node) > value){
    curr_tree.insert_left_child(parent_node, value);
    return parent_node.left_child();
  }
  while(!curr_node.right_sibling().is_null() && *(curr_node.right_sibling()) <= value) {
    curr_node = curr_node.right_sibling();
  }
  if (*curr_node == value){
    return curr_node;
  } else {
    curr_tree.insert_right_sibling(curr_node, value);
    return curr_node.right_sibling();
  }
}

void insert_word(tree<char> & dict_tree,
		 const string & word){
  tree<char>::node curr_node = dict_tree.get_root();
  for(auto curr_letter: word){
    curr_node = insert_ordered_child(dict_tree, curr_node, curr_letter);
  }
}

///////////////////////////////////////////////////////////////////////////////
//                            Dictionary structure                           //
///////////////////////////////////////////////////////////////////////////////

struct CharInfo {
  char letter;
  bool valid;

  friend std::ostream &operator<<(std::ostream &os, const CharInfo& other){
    os << other.letter << (other.valid ? "✓" : "×");
    return os;
  }
};

tree<CharInfo>::node insert_ordered_child(tree<CharInfo> curr_tree,
				     tree<CharInfo>::node parent_node,
				     const CharInfo & value){
  tree<CharInfo>::node curr_node = parent_node.left_child();
  if (curr_node.is_null() || (*curr_node).letter > value.letter){
    curr_tree.insert_left_child(parent_node, value);
    return parent_node.left_child();
  }
  while(!curr_node.right_sibling().is_null() &&
	(*curr_node.right_sibling()).letter <= value.letter) {
    curr_node = curr_node.right_sibling();
  }

  if ((*curr_node).letter == value.letter){
    return curr_node;
  } else {
    curr_tree.insert_right_sibling(curr_node, value);
    return curr_node.right_sibling();
  }
}

void insert_word_with_valid(tree<CharInfo> & dict_tree,
			    const string & word){
  tree<CharInfo>::node curr_node = dict_tree.get_root();
  CharInfo charinfo = {' ', false};
  for(auto curr_letter: word){
    charinfo.letter = curr_letter;
    curr_node = insert_ordered_child(dict_tree, curr_node, charinfo);
  }

  (*curr_node).valid = true;
}

#endif /* AUX_FUNCS_H */
