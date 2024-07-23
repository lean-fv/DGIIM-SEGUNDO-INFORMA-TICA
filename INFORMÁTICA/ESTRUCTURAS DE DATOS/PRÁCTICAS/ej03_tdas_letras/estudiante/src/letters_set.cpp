/**
 * @file letters_set.cpp
 * @brief Fichero con definiciones para los métodos primitivos de la clase LettersSet
 * @authors Antonio Cantillo Molina & Leandro Jorge Fernández Vega
 * @date November, 2022
 */

#include <letters_set.h>
#include <string>
#include <iostream>


using namespace std;

//********************************************************************************************************************//
//                                          Métodos de la Clase LettersSet                                            //
//********************************************************************************************************************//


// CONSTRUCTORES

LettersSet::LettersSet(){}


LettersSet::LettersSet(const LettersSet & other){letters=other.letters;}


// MÉTODOS

bool LettersSet::insert(const pair<char, LetterInfo> & val){return letters.insert(val).second;}


bool LettersSet::erase(const char& key){return letters.erase(key);}


void LettersSet::clear(){letters.clear();}


bool LettersSet::empty() const{return letters.empty();}


int LettersSet::size() const{return letters.size();}


int LettersSet::getScore(string word){

    int l= word.length();
    int score=0;

    for (int i=0; i<l; i++)
        score+=letters[toupper(word.at(i))].score;
    return score;
}

const LettersSet::LS_iterator LettersSet::begin() {LettersSet::LS_iterator i; i=letters.begin(); return i;}

const LettersSet::LS_iterator LettersSet::end() {LS_iterator i; i=letters.end(); return i;}

const LettersSet::LS_const_iterator LettersSet::cbegin() const {LettersSet::LS_const_iterator i; i=letters.begin(); return i;}

const LettersSet::LS_const_iterator LettersSet::cend() const {LS_const_iterator i; i=letters.end(); return i;}

// OPERADORES

LettersSet& LettersSet::operator= (const LettersSet& cl){letters=cl.letters;}


LetterInfo& LettersSet::operator[](const char & val){return letters[val];}


ostream& operator<< (ostream& os, LettersSet& cl){

    LettersSet::LS_const_iterator i;

    os << "FORMATO: <Letra> <Repeticiones> <Puntuación>" << endl;

    for (i=cl.cbegin(); i!=cl.cend(); ++i) os << (*i).first << " " << (*i).second.repetitions << " " <<(*i).second.score << endl;

    return os;
}


istream& operator>> (istream& is, LettersSet& cl){

    string w;
    char letter;
    int quantity;
    int score;

    is >> w;
    is >> w;
    is >> w;

    while (is) {
        is >> letter;
        is >> quantity;
        is >> score;

        pair<char, LetterInfo> val;
        val.first=letter;
        val.second.score=score;
        val.second.repetitions=quantity;

        cl.insert(val);
    }

    return is;
}


//********************************************************************************************************************//
//                                          Métodos de la Clase LS_iterator                                           //
//********************************************************************************************************************//

//CONSTRUCTORES

LettersSet::LS_iterator::LS_iterator()=default;

LettersSet::LS_iterator::LS_iterator(const map<char, LetterInfo>::iterator &other) {it=other;}


// OPERADORES

const LettersSet::LS_iterator& LettersSet::LS_iterator::operator=(const LS_iterator& other) {

    it=other.it;
    return *this;
}

const LettersSet::LS_iterator& LettersSet::LS_iterator::operator=(const map<char,LetterInfo>::iterator& other) {

    it=other;
    return *this;
}

pair<char,LetterInfo> LettersSet::LS_iterator::operator*() const {return *it;}


LettersSet::LS_iterator& LettersSet::LS_iterator::operator++() {
    ++it;
    return *this;
}


LettersSet::LS_iterator& LettersSet::LS_iterator::operator--() {
    --it;
    return *this;
}

bool LettersSet::LS_iterator::operator!=(const LS_iterator& other) const {return it!=other.it;}

bool LettersSet::LS_iterator::operator==(const LS_iterator& other) const {return it==other.it;}



//********************************************************************************************************************//
//                                    Métodos de la Clase LS_const_iterator                                           //
//********************************************************************************************************************//


//CONSTRUCTORES

LettersSet::LS_const_iterator::LS_const_iterator()=default;

LettersSet::LS_const_iterator::LS_const_iterator(const map<char, LetterInfo>::const_iterator &other) {it=other;}


// OPERADORES

const LettersSet::LS_const_iterator& LettersSet::LS_const_iterator::operator=(const LS_const_iterator& other) {

    it=other.it;
    return *this;
}

const LettersSet::LS_const_iterator& LettersSet::LS_const_iterator::operator=(const map<char,LetterInfo>::const_iterator& other) {

    it=other;
    return *this;
}

const pair<char,LetterInfo> LettersSet::LS_const_iterator::operator*()const {return *it;}


LettersSet::LS_const_iterator& LettersSet::LS_const_iterator::operator++() {
    ++it;
    return *this;
}


LettersSet::LS_const_iterator& LettersSet::LS_const_iterator::operator--() {
    --it;
    return *this;
}

bool LettersSet::LS_const_iterator::operator!=(const LS_const_iterator& other) const {return it!=other.it;}

bool LettersSet::LS_const_iterator::operator==(const LS_const_iterator& other) const {return it==other.it;}

LettersSet::LS_const_iterator::~LS_const_iterator(){}