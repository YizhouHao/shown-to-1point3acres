/**
 *  CSE 100 PA2 C++ Autocomplete
 *  Authors:  Yizhou Hao 
 */


#include "util.h"
#include "DictionaryBST.h"

/* Create a new Dictionary that uses a BST back end */
DictionaryBST::DictionaryBST(){}

/* Insert a word into the dictionary. */
bool DictionaryBST::insert(std::string word)
{
  //when the word is already in the bst
  if(find(word)){
    return false; 
  }
  else{
    // the second is the bool 
    return diction.insert(word).second;
  }
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryBST::find(std::string word) const
{
  // find in c return a iterator 
  // when is not end(), it's found 
  return diction.find(word) != diction.end(); 
}

/* Destructor */
DictionaryBST::~DictionaryBST(){}
