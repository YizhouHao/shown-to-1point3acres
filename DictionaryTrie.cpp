/**
 *  CSE 100 PA2 C++ Autocomplete
 *  Authors:  Yizhou Hao 
 */


#include "util.h"
#include "DictionaryTrie.h"
#include<map>

/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie(){
  root = NULL; //initialize root 

}

/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) */
bool DictionaryTrie::insert(std::string word, unsigned int freq)
{
  // word empty
  if(word.length() == 0){
    return false;
  }

  unsigned int i =0;
  std::string pass = word;
  TrieNode** curr = &root;
  return inserthelp(curr,freq,i,pass);  
}

/* helper method for insert*/
bool DictionaryTrie::inserthelp(TrieNode** curr,unsigned int freq,
     unsigned int i, std::string word){
  bool check = false; 

  if((*curr) == NULL){
    *curr = new TrieNode(word[i]);
      }
  
  if(word[i] > (*curr)->data){// larger
    check = inserthelp(&((*curr)->right),freq,i,word);
   }
    
  else if(word[i] < (*curr)->data){//smaller
    check = inserthelp(&((*curr)->left),freq,i,word);
  }

  else if(word[i] == (*curr)->data){
    if((i+1) != word.length()){ // NOT LAST
      check = inserthelp(&((*curr)->middle),freq,i+1,word);
    }

    else{ //last word
      if((*curr)->checkword != true){//not exist before
        (*curr)->checkword = true;
        (*curr)->freq = freq;
        check = true;
      }
      else if((*curr)->checkword == true){//already exist
        if(freq > (*curr)->freq){
          (*curr)->freq = freq;
        }
        check = false; 
      }
    }
  }
  return check; 
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{
  if(word.length() == 0){
    return false;
  }
  if(root == NULL){//no word
    return false;
  }
  
  TrieNode* curr = root; 
  for(unsigned int i =0;i<word.length();i++){
    label:
    if(word[i]>curr->data){//larger
      if(curr->right != NULL){
        curr = curr->right;
        goto label;//back to loop with same index but different node
      }
      else{
        return false;
      }
    }
    else if(word[i] < curr->data){//smaller
      if(curr->left != NULL){
        curr = curr->left;
        goto label;//back to loop with same index but different node
      }
      else{
        return false;
      }
    }

    else if(word[i] == curr->data){
      // already the last char
      if(i == word.length()-1){
        if(curr->checkword == true)
          return true;
        else{
          return false;
        }
      }
      // not the last char, travel down 
      else{
        if(curr->middle != NULL){
          curr = curr->middle; 
          
        }
        else
          return false;
      } 
    }
  }
  return false;
}

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
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix, unsigned int num_completions)
{
  std::vector<std::string> words;
  // situations to return empty words
  // root is null or num_completions <=0
  if(root == NULL && num_completions <= 0){
    return words;
  }
  // not find anything 
  if(!findpre(prefix)){
    return {};
  }
  // string is empty
  if(prefix.length() == 0){
    std::cout << "Invalid Input. Please retry with correct input" << std::endl; 
    return {}; 

  }
  //invalid char
  for(unsigned int i =0;i<prefix.length();i++){
    if((prefix[i]< 'a') || (prefix[i] > 'z') && (prefix[i] != ' ')){
      std::cout << "Invalid Input. Please retry with correct input" << std::endl; 
      return {}; 
    }
  }

  
  //traverse to last char of prefix
  TrieNode* curr= root;
  unsigned int j =0;
  while(j < prefix.length()){
    label:
    if(prefix[j] < curr->data){
      curr = curr->left;
      goto label;
    }
    else if(prefix[j] > curr->data){
      curr = curr->right;
      goto label;
    }
    else if(prefix[j] == curr->data){
      if(j != prefix.length()-1){
        curr = curr->middle;
        j++;
      }
      else{
        break; 
      }
    }
  }

  //get all words of this prefix
  std::multimap<int,std::string,std::greater<int>> allwords; 
  if(curr->checkword == true){
    allwords.insert(std::pair<int,std::string>(curr->freq,prefix)); 
  }

  getallwords(curr->middle,prefix,allwords);

  // pop top num_completions to words
  unsigned int k =0;
  auto it = allwords.begin();//iterator
  for(;it != allwords.end() && k<num_completions;it++){
    k++;
    words.push_back(it->second);
  }

  return words;
}

/*helper method to insert all words which contain prefix to the map*/
void DictionaryTrie::getallwords(TrieNode* curr, std::string prefix,
  std::multimap<int,std::string,std::greater<int>> &allwords){
  if(curr == NULL){
    return;
  }

  getallwords(curr->left,prefix,allwords);
  getallwords(curr->right,prefix,allwords);

  //insert to map if it's a word label
  if(curr->checkword == true){
    allwords.insert(std::pair<int,std::string>(curr->freq,prefix+curr->data));
  }

  //recursion
  getallwords(curr->middle,prefix+curr->data,allwords);

}


/* Return true if pre is in the dictionary, and false otherwise
 * last char dont need to be word label 
 * helper for prefix
 * */
bool DictionaryTrie::findpre(std::string word) const
{
  if(word.length() == 0){
    return false;
  }
  if(root == NULL){//no word
    return false;
  }
  
  TrieNode* curr = root; 
  for(unsigned int i =0;i<word.length();i++){
    label:
    if(word[i]>curr->data){//larger
      if(curr->right != NULL){
        curr = curr->right;
        goto label;//back to loop with same index but different node
      }
      else{
        return false;
      }
    }
    else if(word[i] < curr->data){//smaller
      if(curr->left != NULL){
        curr = curr->left;
        goto label;//back to loop with same index but different node
      }
      else{
        return false;
      }
    }

    else if(word[i] == curr->data){
      // already the last char
      if(i == word.length()-1){
        return true;
      }
      // not the last char, travel down 
      else{
        if(curr->middle != NULL){
          curr = curr->middle; 
          
        }
        else
          return false;
      } 
    }
  }
  return false;
}


/* Destructor */
DictionaryTrie::~DictionaryTrie(){
  deleteAll(root);
}

/* ctor for node*/
TrieNode::TrieNode(char input){
  checkword = false;
  freq =0;
  left = NULL;
  right = NULL;
  middle = NULL; 
  data = input; 
}

/* helper method to destructor 
 */
void DictionaryTrie::deleteAll(TrieNode* root){
  if(root == NULL){
    return;   
  }
  deleteAll(root->left);
  deleteAll(root->right);
  deleteAll(root->middle);
  delete root;
}

/* getter for root*/
TrieNode* DictionaryTrie::rootgetter(){
  return root; 
}

