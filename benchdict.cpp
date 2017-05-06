/*
 * benchdict.cpp
 * Hao Yizhou A98017773
 * cse 100 pa2
 * 2017-05-03
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
#include<vector> 
#include<stdio.h>
#include<stdlib.h>


int main(int argc, char* argv[]){

  unsigned int min_size = std::atoi(argv[1]);
  unsigned int step_size = std::atoi(argv[2]);
  unsigned int num_iterations = std::atoi(argv[3]);
  std::string dictfile = argv[4]; 
 
  //hashtable
  
  std::cout << "hashtable benchmarking" << std::endl;
  for(unsigned int i = 0;i < num_iterations;i++){
    DictionaryHashtable dicthash;
    std::ifstream infile;
    
    //reset
    infile.clear();
    infile.seekg(0);
    
    //load to dict 
    infile.open(argv[4]);
    Utils::load_dict(dicthash,infile,min_size+i*step_size); 

    // load next 100 to vector 
    std::vector<std::string> words;
    Utils::load_vector(words,infile,100);

    infile.close();

    //loop 10 times get average time
    long long total = 0; 
    Timer T;
    T.begin_timer();
    for(unsigned int i = 0;i<100;i++){
      /*auto it = words.begin();
      for( ;it != words.end();it++){
        dicthash.find(*it);
      }*/
      unsigned int j = 0;
      while(j<100){
        dicthash.find(words[j]);
        j++;
      }
    }
    total = T.end_timer();
    long long average = total / 100;
   
    std::cout << (min_size + i*step_size) << "\t" << average << std:: endl;
    words.clear(); 
    //delete dicthash; 
  }

  //BST
  std::cout << "bst benchmarking" << std::endl;
  for(unsigned int ii = 0;ii < num_iterations;ii++){
    DictionaryBST dictbst;
    std::ifstream infile2;
    
    //reset
    infile2.clear();
    infile2.seekg(0);
    
    //load to dict 
    infile2.open(argv[4]);
    Utils::load_dict(dictbst,infile2,min_size+ii*step_size); 

    // load next 100 to vector 
    std::vector<std::string> words;
    Utils::load_vector(words,infile2,100);

    infile2.close();

    //loop 10 times get average time
    long long total1 = 0; 
    Timer T1;
    T1.begin_timer();
    for(unsigned int i = 0;i<100;i++){
      /*auto it = words.begin();
      for( ;it != words.end();it++){
        dicthash.find(*it);
      }*/
      unsigned int j = 0;
      while(j<100){
        dictbst.find(words[j]);
        j++;
      }
    }
    total1 = T1.end_timer();
    long long average1 = total1 / 100;
   
    std::cout << (min_size + ii*step_size) << "\t" << average1 << std:: endl;
    words.clear(); 
    //delete dicttrie; 
  }



  //Trie 
  std::cout << "trie benchmarking" << std::endl;
  for(unsigned int ii = 0;ii < num_iterations;ii++){
    DictionaryTrie dicttrie;
    std::ifstream infile1;
    
    //reset
    infile1.clear();
    infile1.seekg(0);
    
    //load to dict 
    infile1.open(argv[4]);
    Utils::load_dict(dicttrie,infile1,min_size+ii*step_size); 

    // load next 100 to vector 
    std::vector<std::string> words;
    Utils::load_vector(words,infile1,100);

    infile1.close();

    //loop 10 times get average time
    long long total1 = 0; 
    Timer T1;
    T1.begin_timer();
    for(unsigned int i = 0;i<100;i++){
      /*auto it = words.begin();
      for( ;it != words.end();it++){
        dicthash.find(*it);
      }*/
      unsigned int j = 0;
      while(j<100){
        dicttrie.find(words[j]);
        j++;
      }
    }
    total1 = T1.end_timer();
    long long average1 = total1 / 100;
   
    std::cout << (min_size + ii*step_size) << "\t" << average1 << std:: endl;
    words.clear(); 
    //delete dicttrie; 
  }


}

