/**
 * @file dictionary.cpp
 * @brief  Fichero de implementación de los métodos clase Dictionary.
 * @authors Antonio Cantillo Molina & Leandro Jorge Fernández Vega
 * @date December, 2022
 */

#include <string>
#include <vector>
#include <utility>
#include <set>
#include "dictionary.h"
#include <cmath>
#include "tree.h"

///////////////////////////////////////////////////////////////////////////////
//                             Private functions                             //
///////////////////////////////////////////////////////////////////////////////

Dictionary::node Dictionary::findLowerBoundChildNode(char character, Dictionary::node current) {
  node prev_child, curr_child = current.left_child();

  for (; !curr_child.is_null() && (*curr_child).character <= character; curr_child = curr_child.right_sibling()){
    prev_child = curr_child;
    if ((*curr_child).character == character) {
      return curr_child;
    }
  }
  if (!prev_child.is_null()) {
    return prev_child;
  }
  return current;
}

Dictionary::node Dictionary::insertCharacter(char character, Dictionary::node current) {
  node insertion_position = findLowerBoundChildNode(character, current);
  if (insertion_position == current){
    this->words.insert_left_child(current, char_info(character));
    return insertion_position.left_child();
  } else if ((*insertion_position).character != character){
    this->words.insert_right_sibling(insertion_position, char_info(character));
    return insertion_position.right_sibling();
  } else {
    return insertion_position;
  }
}

int Dictionary::getOccurrences(node curr_node, char c) {

    int contador=0;

    if (curr_node.is_null()) {
        return 0;
    }
    else {
        if((*curr_node).character == c) contador++;

        if (!(curr_node.left_child().is_null())) {
            contador+=getOccurrences(curr_node.left_child(), c);
        }
        if (!(curr_node.right_sibling().is_null())) {
            contador+=getOccurrences(curr_node.right_sibling(), c);
        }
    }
    return contador;
}

std::pair<int, int> Dictionary::getTotalUsages(node curr_node, char c) {

    int usages = 0, words_counter = 0;

    pair<int, int>p(usages,words_counter);
    pair<int, int>aux1(usages,words_counter);
    pair<int, int>aux2(usages,words_counter);

    if (!curr_node.is_null()) {
        if (!(curr_node.left_child().is_null())) {

            aux1 = getTotalUsages(curr_node.left_child(), c);
            p.first += aux1.first;
            p.second += aux1.second;
        }
        if (!(curr_node.right_sibling().is_null())) {

            aux2 = getTotalUsages(curr_node.right_sibling(), c);
            p.first += aux2.first;
            p.second += aux2.second;
        }

        if ((*curr_node).character==c) p.first+=aux1.second;
        if ((*curr_node).valid_word) {
            p.second++;
            if((*curr_node).character==c) p.first++;
        }
    }

    return p;
}

///////////////////////////////////////////////////////////////////////////////
//                              Public functions                             //
///////////////////////////////////////////////////////////////////////////////

Dictionary::Dictionary() {
  this->words.set_root(char_info());
  this->total_words = 0;
}

Dictionary::Dictionary(const Dictionary &other) {
  this->words = other.words;
  this->total_words = other.total_words;
}

Dictionary::~Dictionary() {
  this->words.clear();
}

bool Dictionary::exists(const std::string & word) {
  node current = this->words.get_root();
  for (int i = 0; i < word.size(); ++i){
    current = this->findLowerBoundChildNode(word[i], current);
    if ((*current).character != word[i]) {
      return false;
    }
  }

  return (*current).valid_word;
}

bool Dictionary::insert(const std::string &word) {
  node current = this->words.get_root();
  for (int i = 0; i < word.size(); ++i){
    current = this->insertCharacter(word[i], current);
  }

  if (!(*current).valid_word) {
    (*current).valid_word = true;
    this->total_words++;
    return true;
  }

  return false;
}

bool Dictionary::erase(const std::string & val){
  node current = this->words.get_root();
  for (int i = 0; i < val.size(); ++i){
    current = this->findLowerBoundChildNode(val[i], current);
    if ((*current).character != val[i]) {
      return false;
    }
  }
  if ((*current).valid_word){
    (*current).valid_word = false;
    this->total_words--;
    return true;
  }
  return false;
}

Dictionary &Dictionary::operator=(const Dictionary &dic){
  if (this != &dic){
    this->words.clear();
    this->words = dic.words;
    this->total_words = dic.total_words;
  }
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
//                               I/O overload                                //
///////////////////////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream &os, const Dictionary &dict){
  for(Dictionary::iterator it = dict.begin();it != dict.end(); ++it){
    os << *it << std::endl;
  }
  return os;
}

std::istream& operator>>(std::istream &is, Dictionary &dict){
  std::string curr_word;
  while (getline(is, curr_word)){
    dict.insert(curr_word);
  }
  return is;
}

///////////////////////////////////////////////////////////////////////////////
//                            Recursive counters                             //
///////////////////////////////////////////////////////////////////////////////

int Dictionary::getOccurrences(const char c){return getOccurrences(words.get_root(),c);}

int Dictionary::getTotalUsages(const char c){return getTotalUsages(words.get_root(),c).first;}

///////////////////////////////////////////////////////////////////////////////
//                                 Iterator                                  //
///////////////////////////////////////////////////////////////////////////////

Dictionary::iterator::iterator() {}

Dictionary::iterator::iterator(tree<char_info>::const_preorder_iterator iter) {
    this->iter=iter;
    curr_word="";
}

Dictionary::iterator::iterator(const Dictionary::iterator& other) {
    iter=other.iter;
    curr_word="";
}

std::string Dictionary::iterator::operator*() {return curr_word;}

Dictionary::iterator &Dictionary::iterator::operator++() {

    int old_level=iter.get_level();

    do {
        ++iter;
        if (iter.get_level()!=0) {
            if (old_level < iter.get_level()) {
                curr_word.push_back((*iter).character);
                old_level++;
            } else if (old_level > iter.get_level()) {
                old_level -= iter.get_level();
                for (int i = 0; i <= old_level; i++) curr_word.pop_back();
                curr_word.push_back((*iter).character);
                old_level = iter.get_level();

            } else {
                curr_word.pop_back();
                curr_word.push_back((*iter).character);
            }
        }
    } while(iter.get_level()!=0 && !(*iter).valid_word);

    return (*this);
}

bool Dictionary::iterator::operator==(const iterator &other) {return iter==other.iter;}

bool Dictionary::iterator::operator!=(const iterator &other) {return !(iter==other.iter);}

Dictionary::iterator Dictionary::begin() const {
    Dictionary::iterator iter(words.cbegin_preorder());
    ++iter;
    return iter;
}

Dictionary::iterator Dictionary::end() const {return Dictionary::iterator(words.cend_preorder());}

///////////////////////////////////////////////////////////////////////////////
//                            Letters Iterator                               //
///////////////////////////////////////////////////////////////////////////////


Dictionary::possible_words_iterator Dictionary::possible_words_begin(vector<char> available_characters) const {
    Dictionary::possible_words_iterator iter(words.get_root(),available_characters);
    ++iter;
    return iter;
}

Dictionary::possible_words_iterator Dictionary::possible_words_end() const {vector<char> characters; return Dictionary::possible_words_iterator();} //Hacer

Dictionary::possible_words_iterator::possible_words_iterator() {
    current_word="";
    current_node=node();
}

Dictionary::possible_words_iterator::possible_words_iterator(node current_node, vector<char> available_letters) {
    this->current_node=current_node;
    this->current_word="";
    this->available_letters=multiset<char>(available_letters.begin(),available_letters.end());
}

Dictionary::possible_words_iterator::possible_words_iterator(const possible_words_iterator &other){
    this->current_node=other.current_node;
    this->current_word=other.current_word;
    this->available_letters=other.available_letters;
}

Dictionary::possible_words_iterator &Dictionary::possible_words_iterator::operator=(const Dictionary::possible_words_iterator &other) {
    if(this!=&other){
        this->current_node=other.current_node;
        this->current_word=other.current_word;
        this->available_letters=other.available_letters;
        //this->level=other.level;
    }
    return *this;
}

bool Dictionary::possible_words_iterator::operator==(const Dictionary::possible_words_iterator &other) const {
    return ((this->current_node==other.current_node) && (this->available_letters==other.available_letters)
           && (this->level==other.level) && (this->current_word==other.current_word));
}

bool Dictionary::possible_words_iterator::operator!=(const Dictionary::possible_words_iterator &other) const {return !(*this==other);}

bool Dictionary::possible_words_iterator::validNode (node curr_node) {
    multiset<char>::iterator it = available_letters.find((*curr_node).character);
    return (it != available_letters.end() && !curr_node.is_null());
}

void Dictionary::possible_words_iterator::nextNode() {
    node auxiliar;

    if ((*current_node).character == 0) {
        if (validNode(current_node.left_child())) {
            auxiliar=current_node.left_child();
            current_word+=(*auxiliar).character;
            available_letters.erase(available_letters.find((*auxiliar).character));
        }
        else {
            auxiliar = current_node.left_child();
            while (!validNode(auxiliar) && !(auxiliar.right_sibling().is_null())) auxiliar = auxiliar.right_sibling();
            current_word+=(*auxiliar).character;
            available_letters.erase(available_letters.find((*auxiliar).character));
        }
    } //raiz
    else {
        if (current_node.left_child()==node() || !validNode(current_node.left_child())) {
            auxiliar = current_node.left_child();
            if (current_node.left_child() != node() && !auxiliar.right_sibling().is_null()) {
                while (!validNode(auxiliar) && !(auxiliar.right_sibling().is_null()))
                    auxiliar = auxiliar.right_sibling();
                current_word += (*auxiliar).character;
                available_letters.erase(available_letters.find((*auxiliar).character));
            } else { //NO TENGO HIJOS
                auxiliar = current_node;
                bool found=false;
                while (!found && (*auxiliar.parent()).character!=0) {
                    if (!auxiliar.right_sibling().is_null()) {
                        auxiliar = auxiliar.right_sibling();
                        while (!validNode(auxiliar) && !(auxiliar.right_sibling().is_null()))
                            auxiliar = auxiliar.right_sibling();
                        if (validNode(auxiliar)) {
                            current_word.pop_back();
                            available_letters.insert((*current_node).character);

                            current_word += (*auxiliar).character;
                            available_letters.erase(available_letters.find((*auxiliar).character));
                            found = true; //PARO
                        } else {
                            current_word.pop_back();
                            available_letters.insert((*current_node).character);

                            current_node=auxiliar.parent();
                            auxiliar = current_node;
                        }
                    } else { //Hermano a la dcha nulo
                        current_word.pop_back();
                        available_letters.insert((*auxiliar).character);
                        auxiliar = auxiliar.parent();
                        while (auxiliar.right_sibling().is_null() && (*auxiliar.parent()).character!=0) {
                            current_word.pop_back();
                            available_letters.insert((*auxiliar).character);
                            auxiliar = auxiliar.parent();
                        }
                    }
                }
                if((*auxiliar.parent()).character==0 && auxiliar.right_sibling().is_null()) {
                    auxiliar=node();
                    current_word="";
                    available_letters.clear();
                }
                else if ((*auxiliar.parent()).character==0 && !auxiliar.right_sibling().is_null()){
                    current_word.pop_back();
                    available_letters.insert((*auxiliar).character);
                    auxiliar=auxiliar.right_sibling();
                    while (!validNode(auxiliar) && !(auxiliar.right_sibling().is_null()))
                        auxiliar = auxiliar.right_sibling();
                    if(validNode(auxiliar)){
                        current_word += (*auxiliar).character;
                        available_letters.erase(available_letters.find((*auxiliar).character));
                    }
                    else {
                        auxiliar=node();
                        current_word="";
                        available_letters.clear();
                    }
                }
                else if(!auxiliar.right_sibling().is_null() && !found){
                    auxiliar=auxiliar.right_sibling();
                    while (!validNode(auxiliar) && !(auxiliar.right_sibling().is_null()))
                        auxiliar = auxiliar.right_sibling();
                    current_word += (*auxiliar).character;
                    available_letters.erase(available_letters.find((*auxiliar).character));
                }
            }  //SUBIR
        }
        else {
            auxiliar=current_node.left_child();
            current_word+=(*auxiliar).character;
            available_letters.erase(available_letters.find((*auxiliar).character));
        }//Hijo izdo valido
    }

    current_node=auxiliar;
}

Dictionary::possible_words_iterator &Dictionary::possible_words_iterator::operator++() {

    do{
        nextNode();
    } while (!(current_node.is_null()) && !(*current_node).valid_word);

    return (*this);
}

std::string Dictionary::possible_words_iterator::operator*() const {return this->current_word;}


