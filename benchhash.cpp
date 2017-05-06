/*
 * benchhash.cpp
 * Hao Yizhou A98017773
 * cse 100 pa2
 * 2017-05-05
 */

#include<iostream>
#include<string>
#include<algorithm>
#include<set>
#include<cstdlib>
#define LETTERS 26
#include<fstream>
#include<vector> 
#include<stdio.h>
#include<stdlib.h>
#include "util.h"


//declare two hash methods
int hashone(std::string word, unsigned int tablesize);
int hashtwo(std::string word, unsigned int tablesize);

/*
 * the main method to run the program
 */
int main(int argc, char* argv[]){

  // read input
  std::string dictfile = argv[1];
  unsigned int num_words = std::atoi(argv[2]);
  
  // for compare
  unsigned int tablesize = num_words * 2;
  std::vector<unsigned int> hashtable1(tablesize,0);
  std::vector<unsigned int> hashtable2(tablesize,0); 

  // load next 100 to vector words
  std::ifstream infile;
  infile.clear();
  infile.seekg(0);
  infile.open(argv[1]);
  std::vector<std::string> words;
  Utils::load_vector(words,infile,num_words);
  infile.close();


  //call two hash 
  unsigned int i = 0;
  unsigned int j = 0;

  // see how many hits for each plot
  while(i < num_words){
    int temp = hashone(words[i],tablesize);
    hashtable1[temp] = hashtable1[temp] +1;
    i++;
  }

  unsigned int max1 = 0;
  unsigned int max2 = 0;

  //get max hit for hashone
  i=0; 
  while(i < tablesize){
    if(hashtable1[i] > max1){
      max1 = hashtable1[i];
    }
    i++;
  }

  // same for hashtwo
  while(j < num_words){
    int temp = hashtwo(words[j],tablesize);
    hashtable2[temp] = hashtable2[temp] +1;
    j++;
  }

  //same for hashtwo
  j=0; 
  while(j < tablesize){
    if(hashtable2[j] > max2){
      max2 = hashtable2[j];
    }
    j++;
  }

  //create histogram for hashone and hashtwo
  std::vector<int> histo1(max1+1,0);
  std::vector<int> histo2(max2+1,0); 
  i=0;j=0;
  unsigned int k =0;
  unsigned int l =0;

  while(i < tablesize){
    k = 0;
    while(k < max1 + 1){
      if(hashtable1[i] == k){
        histo1[k] = histo1[k] +1;
      }
      k++;
    }
    i++;
  }
  
  while(j < tablesize){
    l = 0;
    while(l < max2 + 1){
      if(hashtable2[j] == l){
        histo2[l] = histo2[l] +1;
      }
      l++;
    }
    j++;
  }

  //caculate average for hash one two
  unsigned int average1 =0;
  unsigned int average2 = 0; 
  unsigned int multiplier1 =0;
  unsigned int multiplier2 =0;
  i=max1;j=max2;
  
  while( i >0 ){
    multiplier1 = multiplier1 + histo1[i];
    average1 = average1 + i*multiplier1;
    i--;
  }

  double average11 = (double)average1 / (double)num_words;

  while( j >0 ){
    multiplier2 = multiplier2 + histo2[j];
    average2 = average2 + j*multiplier2;
    j--;
  }

  double average22 = (double)average2 / (double)num_words;

  // print stats
  i =0; j=0;
  std::cout << std::endl; 
  std::cout << "print stats for hashone " << std::endl;
  std::cout << "#hits    #slots recieve this " << std::endl;
  // histogram
  while(i < max1 + 1){
    std::cout << i << "       " << histo1[i] <<std::endl;
    i++;
  }

  // average and max hit
  std::cout << "The average number of steps for hashone is " <<average11 <<std::endl;
  std::cout << "The worst case steps needed for hashone is " << max1 <<std::endl; 

  std::cout << std::endl; 
  std::cout << "print stats for hashtwo " << std::endl;
  std::cout << "#hits    #slots recieve this " << std::endl;
  // histogram
  while(j < max2 + 1){
    std::cout << j << "       " << histo2[j] <<std::endl;
    j++;
  }
  // average and max hit
  std::cout << "The average number of steps for hashtwo is " <<average22 <<std::endl;
  std::cout << "The worst case steps needed for hashtwo is " << max2 <<std::endl; 

  
  

  // test cases for two hash funcs.
  std::cout << std::endl; 
  std::cout << "hashone with 'a' and size 100. The return is " 
    << hashone("a",100) << std::endl;
  std::cout << "hashtwo with 'a' and size 100. The return is " 
    << hashtwo("a",100) << std::endl;
  std::cout << "hashone with 'app' and size 100. The return is " 
    << hashone("app",100) << std::endl;
  std::cout << "hashtwo with 'app' and size 100. The return is " 
    << hashtwo("app",100) << std::endl;
  std::cout << "hashone with 'apple' and size 100. The return is " 
    << hashone("apple",100) << std::endl;
  std::cout << "hashtwo with 'apple' and size 100. The return is " 
    << hashtwo("apple",100) << std::endl;

  return 0; 
}

/*
 *the index hash to is returned
 *http://stackoverflow.com/questions/8317508/hash-function-for-a-string
 */
int hashone(std::string word, unsigned int tablesize)   
{       int sum = 0;
        unsigned int SIZE = tablesize;
        for (unsigned int k = 0; k < word.length(); k++)
            sum = sum + int(word[k]);
        return  sum % SIZE; 
}


/*
 * the index hash to is returned 
 *http://stackoverflow.com/questions/8317508/hash-function-for-a-string
 */
int hashtwo(std::string word, unsigned int tablesize)
{
   int seed = 131; 
   unsigned long hash = 0;
   unsigned int SIZE = tablesize;
   for(unsigned int i = 0; i < word.length(); i++)
   {
      hash = (hash * seed) + word[i];
   }
   return hash % SIZE;
}


