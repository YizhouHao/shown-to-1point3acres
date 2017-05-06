/**
 *  CSE 100 PA2 C++ Autocomplete
 *  Authors:  Yizhou Hao 
 */


#include<iostream>
#include<string>
#include<algorithm>
#include<set>
#include<cstdlib>
#include "util.h"
#include "DictionaryTrie.h"
#include "DictionaryBST.h"
#include "DictionaryHashtable.h"
#define LETTERS 26
#include<fstream>
using namespace std;

/*
 * The main class to run the test 
 */
int main(int argc, char** argv)
{

  //Initialize words
  vector<std::string> words;
  vector<string>::iterator wit;
  vector<string>::iterator wen;
  //initialize nonwords
  set<string> nope;
  set<string>::iterator nit;
  set<string>::iterator nen;

  //Initialize data structures
  DictionaryBST d_bst;
  DictionaryHashtable d_ht;
  DictionaryTrie dt;
  int t_bst, t_ht, tt;

  words.push_back("harry");
  words.push_back("sriram");
  words.push_back("cse");
  words.push_back("crucio");
  words.push_back("autocomplete");
  
  //test insert
  cout << "Inserting into Dictionaries..." << endl;

  wit = words.begin();
  wen = words.end();
  for(; wit != wen; ++wit)
    {
      cout << "Inserting: \"" << *wit << "\"... ";
      t_bst = d_bst.insert(*wit);
      t_ht = d_ht.insert(*wit);
      tt = dt.insert(*wit, 1);
      if(!t_bst)
	{
	  cout << "failed for DictionaryBST... ";
	}
      if(!t_ht)
	{
	  cout << "failed for DictionaryHashset... ";
	}
      if(!tt)
	{
	  cout << "failed for DictionaryTrie... ";
	}
      if(t_bst && t_ht && tt)
	{
	  cout << "PASSED! :D ";
	}
      cout << endl;
    }

  //test for freq, should be 1 now
  TrieNode* root = dt.rootgetter();
  TrieNode* curry = root->middle->middle->middle->middle;
  TrieNode* currcse = root->left->middle->middle;
  TrieNode* curro = root->left->middle->left->middle->middle->middle->middle;
  TrieNode* currae = root-> left->left->middle->middle->middle->middle->middle->middle
             ->middle->middle->middle->middle->middle;
  TrieNode* currm = root->right->middle->middle->middle->middle->middle;
  if(curry->freq != 1){
    cout << "harry freq should be 1 \"";
  }
  if(currcse->freq != 1){
    cout << "cse freq should be 1 \"";
  }
  if(curro->freq != 1){
    cout << "crucio freq should be 1 \"";
  }
  if(currae->freq != 1){
    cout << "autocomplete freq should be 1 \"";
  }
  if(currm->freq != 1){
    cout << "sriram freq should be 1 \"";
  }
  cout << endl; 

  
  // test re-insert same thing
  cout << endl << "Re-inserting elements that were just inserted into Dictionaries..." << endl;

  wit = words.begin();
  wen = words.end();
  for(; wit != wen; ++wit)
    {
      cout << "Inserting: \"" << *wit << "\"... ";
      t_bst = d_bst.insert(*wit);
      t_ht = d_ht.insert(*wit);
      tt = dt.insert(*wit, 0);
      if(t_bst)
        {
          cout << "failed for DictionaryBST... ";
        }
      if(t_ht)
        {
          cout << "failed for DictionaryHashset... ";
        }
      if(tt)
        {
          cout << "failed for DictionaryTrie... ";
        }
      if(!t_bst && !t_ht && !tt)
        {
          cout << "PASSED! :D ";
        }
      cout << endl;
    }

  cout << endl;

  // freq should still 1 now 
  if(curry->freq != 1){
    cout << "harry freq should still be 1 \"";
  }
  if(currcse->freq != 1){
    cout << "cse freq should still be 1 \"";
  }
  if(curro->freq != 1){
    cout << "crucio freq should still be 1 \"";
  }
  if(currae->freq != 1){
    cout << "autocomplete freq should still be 1 \"";
  }
  if(currm->freq != 1){
    cout << "sriram freq should still be 1 \"";
  }
  cout << endl; 

  // change to high freq
  cout << endl << "Re-inserting elements that were just inserted into Dictionaries with high freq..." << endl;

  wit = words.begin();
  wen = words.end();
  for(; wit != wen; ++wit)
    {
      cout << "Inserting: \"" << *wit << "\"... ";
      t_bst = d_bst.insert(*wit);
      t_ht = d_ht.insert(*wit);
      tt = dt.insert(*wit, 10);
      if(t_bst)
        {
          cout << "failed for DictionaryBST... ";
        }
      if(t_ht)
        {
          cout << "failed for DictionaryHashset... ";
        }
      if(tt)
        {
          cout << "failed for DictionaryTrie... ";
        }
      if(!t_bst && !t_ht && !tt)
        {
          cout << "PASSED! :D ";
        }
      cout << endl;
    }

  cout << endl;

  // freq now should be 10
  if(curry->freq != 10){
    cout << "harry freq should be 10 \"";
  }
  if(currcse->freq != 10){
    cout << "cse freq should be 10 \"";
  }
  if(curro->freq != 10){
    cout << "crucio freq should be 10 \"";
  }
  if(currae->freq != 10){
    cout << "autocomplete freq should be 10 \"";
  }
  if(currm->freq != 10){
    cout << "sriram freq should be 10 \"";
  }
  cout << endl; 


  //test find
  wit = words.begin();
  wen = words.end();
  for(; wit != wen; ++wit)
  {
      cout << "Finding: \"" << *wit << "\"... ";
      t_bst = d_bst.find(*wit);
      t_ht = d_ht.find(*wit);
      tt = dt.find(*wit);
      if(!t_bst)
        {
          cout << "failed for DictionaryBST... ";
        }
      if(!t_ht)
        {
          cout << "failed for DictionaryHashset... ";
        }
      if(!tt)
        {
          cout << "failed for DictionaryTrie... ";
        }
      if(t_bst && t_ht && tt)
        {
          cout << "PASSED! :D ";
        }
      cout << endl;
    }

  cout << endl;

  // find not element
  cout << "Finding: \"" << "nishuosha" << "\"... ";
  std::string word1 = "nishuosha";
  t_bst = d_bst.find(word1);
  t_ht = d_ht.find(word1);
  tt = dt.find(word1);
  if(t_bst)
    {
      cout << "failed for DictionaryBST... ";
    }
  if(t_ht)
    {
      cout << "failed for DictionaryHashset... ";
    }
  if(tt)
    {
      cout << "failed for DictionaryTrie... ";
    }
  if(!t_bst && !t_ht && !tt)
    {
      cout << "PASSED! :D ";
    }
  cout << endl;

  //test for predictcompletions
  DictionaryTrie diction;
  ifstream file;
  file.open("shuffled_unique_freq_dict.txt");
  Utils::load_dict(diction,file);
  file.close();
  vector<std::string> words1 = diction.predictCompletions("eyesh",3);
  for (unsigned int i = 0;i<words1.size();i++){
    cout << words1[i] << endl; 
  }
  
  return 0;
}
