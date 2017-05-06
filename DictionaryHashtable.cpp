/**
 *  CSE 100 PA2 C++ Autocomplete
 *  Authors:  Yizhou Hao 
 */


#include "util.h"
#include "DictionaryHashtable.h"

/* Create a new Dictionary that uses a Hashset back end */
DictionaryHashtable::DictionaryHashtable(){}

/* Insert a word into the dictionary. */
bool DictionaryHashtable::insert(std::string word)
{
  // if already in hashtable
  if(find(word)){
    return false;
  } 
  else{
    // in pair second is bool 
    return diction.insert(word).second;
  }
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryHashtable::find(std::string word) const
{
  return diction.find(word) != diction.end(); 
}

/* Destructor */
DictionaryHashtable::~DictionaryHashtable(){}
