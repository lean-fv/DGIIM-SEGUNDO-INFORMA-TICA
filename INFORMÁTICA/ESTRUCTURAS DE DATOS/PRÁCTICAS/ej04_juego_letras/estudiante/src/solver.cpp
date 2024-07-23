/**
 * @file Solver.cpp
 * @brief  Fichero de implementación para la clase Solver.
 * @authors Antonio Cantillo Molina & Leandro Jorge Fernández Vega
 * @date December, 2022
 */

#include "dictionary.h"
#include "letters_set.h"
#include "letters_bag.h"
#include <string>
#include <vector>
#include "solver.h"

Solver::Solver(const Dictionary& dict, const LettersSet& letters_set) {
    this->dict=dict;
    this->letters_set=letters_set;
}

bool Solver::possibleWord(string word, vector<char> letters){

    vector<char> aux(letters);

    int wlength = word.length();
    bool possible=true;
    bool found=false;

    for (int i=0; i<wlength && possible; ++i) {
        for(vector<char>::iterator j=aux.begin(); j!=aux.end() && !found; ++j){
            if(word.at(i) == tolower((*j))) {
                aux.erase(j);
                found=true;
            }
        }
        if(!found) possible=false;
        found=false;
    }
    return possible;
}

pair<vector<string>,int> Solver::getSolutions(const vector <char>&available_letters, bool score_game) {

    string max_word;
    int MaxPuncOrLength = 0;

    vector<string> words;

    //Puntuación

    if (score_game) {
        for (Dictionary::iterator i = dict.begin(); i != dict.end(); ++i)
            if (possibleWord(*i,available_letters) &&  letters_set.getScore((*i)) > MaxPuncOrLength){
                MaxPuncOrLength = letters_set.getScore((*i));
            }
        for (Dictionary::iterator i = dict.begin(); i != dict.end(); ++i)
            if (possibleWord(*i,available_letters) && letters_set.getScore((*i)) == MaxPuncOrLength) words.push_back((*i));
    }

    //Longitud

    else {
        for (Dictionary::iterator i = dict.begin(); i != dict.end(); ++i)
            if (possibleWord(*i,available_letters) && (*i).length() > MaxPuncOrLength) MaxPuncOrLength = (*i).length();
        for (Dictionary::iterator i = dict.begin(); i != dict.end(); ++i)
            if (possibleWord(*i,available_letters) && (*i).length()== MaxPuncOrLength) words.push_back((*i));
    }

    pair<vector<string>, int> p(words, MaxPuncOrLength);

    return p;
}