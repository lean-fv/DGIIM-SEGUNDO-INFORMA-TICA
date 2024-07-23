/**
 * @file letters_bag.cpp
 * @brief Fichero con definiciones para los métodos primitivos de la clase LettersBag
 * @authors Antonio Cantillo Molina & Leandro Jorge Fernández Vega
 * @date November, 2022
 */


#include <letters_bag.h>
#include "bag.h"
#include "letters_set.h"
using namespace std;


LettersBag::LettersBag(){}

LettersBag::LettersBag(const LettersSet & letterSet){

    for(LettersSet::LS_const_iterator i=letterSet.cbegin(); i!=letterSet.cend(); ++i){
        for(int j=0; j<(*i).second.repetitions; ++j){
            insertLetter((*i).first);
        }
    }
}

void LettersBag::insertLetter(const char & I){letters.add(I);}

char LettersBag::extractLetter() {return letters.get();}

vector<char> LettersBag::extractLetters(int num) {

    vector<char> aux;

    for(int i=0; i<num; i++) aux.push_back(letters.get());
    return aux;

}

void LettersBag::clear(){letters.clear();}

unsigned int LettersBag::size() const {return letters.size();}

LettersBag& LettersBag::operator=(const LettersBag& other){
    if (this!=&other) letters=other.letters;

    return *this;
}
