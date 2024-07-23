#include <iostream>
#include <string>

#include "tree.h"
#include "aux_funcs.h"

using namespace std;

int main(int argc, char *argv[])
{
  tree <CharInfo> dictionary({0, false});

  insert_word_with_valid(dictionary, "amo");
  insert_word_with_valid(dictionary, "ama");
  insert_word_with_valid(dictionary, "ala");
  insert_word_with_valid(dictionary, "alado");
  insert_word_with_valid(dictionary, "boina");
  insert_word_with_valid(dictionary, "alma");

  cout << dictionary;

  for (auto it = dictionary.begin_preorder(); it != dictionary.end_preorder(); ++it) {
    cout << *it << endl;
  }
  return 0;

}
