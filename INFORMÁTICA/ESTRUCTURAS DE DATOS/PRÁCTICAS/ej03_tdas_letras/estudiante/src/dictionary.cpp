/**
 * @file dictionary.cpp
 * @brief Fichero con definiciones para los métodos primitivos de la clase Dictionary.
 * @authors Antonio Cantillo Molina & Leandro Jorge Fernández Vega
 * @date November, 2022
 */


#include "dictionary.h"
#include <string>
#include <vector>

using namespace std;

//********************************************************************************************************************//
//                                    Métodos de la Clase Dictionary                                                  //
//********************************************************************************************************************//


Dictionary::Dictionary(){}

Dictionary::Dictionary(const Dictionary& other) {words=other.words;}

bool Dictionary::exists(const string& val) const {words.count(val);}

bool Dictionary::insert(const string& val){words.insert(val).second;}

bool Dictionary::erase(const string& val) {words.erase(val);}

void Dictionary::clear(){words.clear();}

bool Dictionary::empty() const{return words.empty();}

unsigned int Dictionary::size() const{return words.size();}

int Dictionary::getOccurrences(const char c) {
    int occurrences=0;

    for (set<string>::const_iterator i=words.cbegin(); i!=words.cend();++i)
        for (string::const_iterator j=i->cbegin(); j!=i->cend();++j)
            if (c==tolower((*j))) occurrences++;

    return occurrences;
}

int Dictionary::getTotalLetters() {
    int letters=0;

    for (set<string>::const_iterator i=words.cbegin(); i!=words.cend();++i)
        for (string::const_iterator j=i->cbegin(); j!=i->cend();++j)
            letters++;

    return letters;
}

vector<string> Dictionary::WordsOflength(int length) {
    vector<string> words_of_length;

    for (set<string>::const_iterator i=words.cbegin(); i!=words.cend();++i)
        if((*i).length() == length) words_of_length.push_back((*i));

    return words_of_length;
}

ostream& operator<<(ostream& os, const Dictionary& dic) {

    for (Dictionary::Dic_const_iterator i=dic.cbegin(); i!=dic.cend(); ++i) os << (*i);

    return os;
}

istream& operator>>(istream& is, Dictionary& dic) {

    string w;

    while(is) {
        is >> w;
        dic.insert(w);
    }

    return is;
}

const Dictionary::Dic_iterator Dictionary::begin() {Dictionary::Dic_iterator i; i=words.begin(); return i;}

const Dictionary::Dic_iterator Dictionary::end() {Dic_iterator i; i=words.end(); return i;}

const Dictionary::Dic_const_iterator Dictionary::cbegin() const {Dictionary::Dic_const_iterator i; i=words.begin(); return i;}

const Dictionary::Dic_const_iterator Dictionary::cend() const {Dic_const_iterator i; i=words.end(); return i;}

//********************************************************************************************************************//
//                                          Métodos de la Clase Dic_iterator                                           //
//********************************************************************************************************************//

//CONSTRUCTORES

Dictionary::Dic_iterator::Dic_iterator()=default;

Dictionary::Dic_iterator::Dic_iterator(const set<string>::iterator &other) {it=other;}


// OPERADORES

const Dictionary::Dic_iterator& Dictionary::Dic_iterator::operator=(const Dic_iterator& other) {

    it=other.it;
    return *this;
}

const Dictionary::Dic_iterator& Dictionary::Dic_iterator::operator=(const set<string>::iterator& other) {

    it=other;
    return *this;
}

string Dictionary::Dic_iterator::operator*() const {return *it;}


Dictionary::Dic_iterator& Dictionary::Dic_iterator::operator++() {
    ++it;
    return *this;
}


Dictionary::Dic_iterator& Dictionary::Dic_iterator::operator--() {
    --it;
    return *this;
}

bool Dictionary::Dic_iterator::operator!=(const Dic_iterator& other) const {return it!=other.it;}

bool Dictionary::Dic_iterator::operator==(const Dic_iterator& other) const {return it==other.it;}



//********************************************************************************************************************//
//                                    Métodos de la Clase LS_const_iterator                                           //
//********************************************************************************************************************//


//CONSTRUCTORES

Dictionary::Dic_const_iterator::Dic_const_iterator()=default;

Dictionary::Dic_const_iterator::Dic_const_iterator(const set<string>::const_iterator &other) {it=other;}


// OPERADORES

const Dictionary::Dic_const_iterator& Dictionary::Dic_const_iterator::operator=(const Dic_const_iterator& other) {

    it=other.it;
    return *this;
}

const Dictionary::Dic_const_iterator& Dictionary::Dic_const_iterator::operator=(const set<string>::const_iterator& other) {

    it=other;
    return *this;
}

const string Dictionary::Dic_const_iterator::operator*()const {return *it;}


Dictionary::Dic_const_iterator& Dictionary::Dic_const_iterator::operator++() {
    ++it;
    return *this;
}


Dictionary::Dic_const_iterator& Dictionary::Dic_const_iterator::operator--() {
    --it;
    return *this;
}

bool Dictionary::Dic_const_iterator::operator!=(const Dic_const_iterator& other) const {return it!=other.it;}

bool Dictionary::Dic_const_iterator::operator==(const Dic_const_iterator& other) const {return it==other.it;}

Dictionary::Dic_const_iterator::~Dic_const_iterator(){}
