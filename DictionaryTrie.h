/**
 *  CSE 100 PA3 C++ Autocomplete
 *  Authors: Jor-el Briones, Christine Alvarado
 */

#ifndef DICTIONARY_TRIE_H
#define DICTIONARY_TRIE_H

#include <vector>
#include <string>
#include<map>


/**
 * the class for the node in trie
 */
class TrieNode{

public:
  // ctor for node
  TrieNode(char data);
  
  // destructor for node  
  //~TrieNode();


  // check if it's the last char to mark a word 
  bool checkword; 
  char data; // the character in this node
  // use TST. 3 child 
  TrieNode* left;
  TrieNode* right;
  TrieNode* middle;  
  unsigned int freq; // the frequency of this node 
};


/**
 *  The class for a dictionary ADT, implemented as a trie
 *  You may implement this class as either a mulit-way trie
 *  or a ternary search trie, but you must use one or the other.
 *
 */
class DictionaryTrie
{
public:

  /* Create a new Dictionary that uses a Trie back end */
  DictionaryTrie();

  /* Insert a word with its frequency into the dictionary.
   * Return true if the word was inserted, and false if it
   * was not (i.e. it was already in the dictionary or it was
   * invalid (empty string) */
  bool insert(std::string word, unsigned int freq);

  /* Return true if word is in the dictionary, and false otherwise */
  bool find(std::string word) const;

  /* Return up to num_completions of the most frequent completions
   * of the prefix, such that the completions are words in the dictionary.
   * These completions should be listed from most frequent to least.
   * If there are fewer than num_completions legal completions, this
   * function returns a vector with as many completions as possible.
   * If no completions exist, then the function returns a vector of size 0.
   * The prefix itself might be included in the returned words if the prefix
   * is a word (and is among the num_completions most frequent completions
   * of the prefix)
   */
  std::vector<std::string>
  predictCompletions(std::string prefix, unsigned int num_completions);

  /* Destructor */
  ~DictionaryTrie();
 
  /*getter for root*/
  TrieNode* rootgetter();

private:
  /* helper method for dtor*/
  void deleteAll(TrieNode* root);
  /*helper for insert*/ 
  bool inserthelp(TrieNode** curr,unsigned int freq,
       unsigned int i, std::string word);

  /*helper for prefix*/
  bool findpre(std::string word) const;

  /*helper method to insert all words*/
  void getallwords(TrieNode* curr, std::string prefix,
  std::multimap<int,std::string,std::greater<int>> &allwords);
  

  TrieNode* root;
  
};


#endif // DICTIONARY_TRIE_H
