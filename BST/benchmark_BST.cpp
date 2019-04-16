/*
 * Program to run some benchmark tests comparing a binary search tree's
 * functions against a binary search array
 *
 * Name: Ajay Nair
 * Email: ajnair@ucsd.edu
 */
#include <iostream>
#include "BSA.hpp"
#include "BST.hpp"
#include "Timer.hpp"

using namespace std;

/** Returns a vector of random double values with range [min, max]
 *  Note that rand() returns bad random numbers, but for simplicity, we use it
 *  to serve our purpose here.
 */
vector<double> randNums(unsigned int size, int min, int max) {
  vector<double> result;
  for (unsigned int i = 0; i < size; i++) {
    result.push_back((max - min) * ((double)rand() / (double)RAND_MAX) + min);
  }
  return result;
}

int main () {
  const int MIN = 0; // min value of random data
  const int MAX = 100; // max value of random data
  const int NUM_INSERT = 30000; // number of random data to insert
  const int NUM_FIND = 30000; // number of random data to find
  const int NUM_RUN = 10;

  vector<double> insertData = randNums(NUM_INSERT, MIN, MAX);
  vector<double> findData = randNums(NUM_FIND, MIN, MAX);

  BSA<double> bsa;
  BST<double> bst;

  cout << "Insert benchmarking for BSA and BST: " << endl;
  cout << "Number of data to insert: " << NUM_INSERT << endl;

  Timer t;
  long long sumTime = 0;
  long long averageTime = 0;
  int run;
  vector<double>::iterator it;

  for(run = 0; run < NUM_RUN; run++) {
    bsa = BSA<double>();
    for(it = insertData.begin(); it != insertData.end(); ++it) {
      t.begin_timer();
      bsa.insert(*it);
      sumTime += t.end_timer();
    }
  }
  averageTime = sumTime / (insertData.size() * NUM_RUN);

  cout << "Average time taken to insert for BSA: " << averageTime
    << " milliseconds" << endl;

  sumTime = 0;
  averageTime = 0;
  for(run = 0; run < NUM_RUN; run++) {
    bst = BST<double>();
    for(it = insertData.begin(); it != insertData.end(); ++it) {
      t.begin_timer();
      bst.insert(*it);
      sumTime += t.end_timer();
    }
    if(run + 1 < NUM_RUN) {
      bst.~BST<double>();
    }
  }
  averageTime = sumTime / (insertData.size() * NUM_RUN);

  cout << "Average time taken to insert for BST: " << averageTime
    << " milliseconds" << endl;

  cout << endl; // new line

  cout << "Find benchmarking for BSA and BST: " << endl;
  cout << "Number of data in BSA/BST: " << NUM_INSERT << endl;
  cout << "Number of data to find: " << NUM_FIND << endl;

  sumTime = 0;
  averageTime = 0;

  for(run = 0; run < NUM_RUN; run++) {
    for(it = findData.begin(); it != findData.end(); ++it) {
      t.begin_timer();
      bsa.find(*it);
      sumTime += t.end_timer();
    }
  }
  averageTime = sumTime / (findData.size() * NUM_RUN);

  cout << "Average time taken to find for BSA: " << averageTime
    << " milliseconds" << endl;

  sumTime = 0;
  averageTime = 0;

  for(run = 0; run < NUM_RUN; run++) {
    for(it = findData.begin(); it != findData.end(); ++it) {
      t.begin_timer();
      bst.find(*it);
      sumTime += t.end_timer();
    }
  }
  averageTime = sumTime / (findData.size() * NUM_RUN);

  cout << "Average time taken to find for BST: " << averageTime
    << " milliseconds" << endl;    
}
