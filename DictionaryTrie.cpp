#include "util.h"
#include "DictionaryTrie.h"

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
  return inserthelp(root,freq,i,word);  
}

/* helper method for insert*/
bool DictionaryTrie::inserthelp(TrieNode* curr,unsigned int freq,
     unsigned int i, std::string word){
  if(word[i] == ' ')
     inserthelp(curr,freq,i+1,word);  

  if(curr == NULL){
    curr = new TrieNode(word[i]);
  }
  
  if(word[i] > (curr)->data){// larger
    //root = (root)->right;
    inserthelp(curr->right,freq,i,word);
   }
    
  else if(word[i] < (curr)->data){//smaller
    //root = (root)->left;
    inserthelp(curr->left,freq,i,word);
  }

  else if(word[i] == (curr)->data){
    if((i+1) != word.length()){ // NOT LAST
      //root = (root)->middle;
      inserthelp(curr->middle,freq,i+1,word);
    }

    else{ //last word
      if((curr)->checkword != true){//not exist before
        (curr)->checkword = true;
        (curr)->freq = freq;
        return true;
      }
      else{//already exist
        if(freq > (curr)->freq){
          (curr)->freq = freq;
        }
        return false; 
      }
    }
  }
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

    if(word[i]>curr->data){//larger
      if(curr->right != NULL){
        curr = curr->right;
      }
      else{
        return false;
      }
    }
    else if(word[i] < curr->data){//smaller
      if(curr->left != NULL){
        curr = curr->left;
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
  return words;
}

/* Destructor */
DictionaryTrie::~DictionaryTrie(){
  deleteAll(root);
}

/* ctor for node*/
TrieNode::TrieNode(char data){
  checkword = false;
  freq =0;
  left = NULL;
  right = NULL;
  middle = NULL; 
  this->data = data; 
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


