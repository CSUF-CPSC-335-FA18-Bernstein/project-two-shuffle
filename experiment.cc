///////////////////////////////////////////////////////////////////////////////
// experiment.cc
//
// Example code showing how to run an algorithm once and measure its elapsed
// time precisely. You should modify this program to gather all of your
// experimental data.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>

#include "project2.hh"
#include "timer.hh"

using namespace std;

//Helper function to get a subset of all the words
string_vector getSubset(string_vector words,int start,int size){
  //make sure we don't go off the edge of the words vector
  if((start + size) > words.size()-1){
    start -= (start + size - words.size() + 1);
  }

  return string_vector(words.begin() + start, words.begin() + start + size);
}


int main() {

  string_vector all_words;
  if ( ! load_words(all_words, "words.txt") ) {
    cerr << "error: cannot open \"words.txt\"" << endl;
    return 1;
  }

  srand(time(NULL));

  int i;
  int n = 50000;
  int iterations = 5000;
  int totalSize = all_words.size();
  int randStart;
  Timer timer;
  double elapsed[iterations][2] = {0.0};
  string_vector n_words;
    
  cout << "Words=" << n << ", "<< "iteration=" << iterations << endl;
  cout << "Iteration,\tMergeTime,\tQSTime" << endl;

  //Run the experiment and gather timing data
  for(i = 0; i < iterations; i++){
    cout << i << ",\t";
    
    //Get the merge sort time
    randStart = rand() % totalSize;
    n_words = getSubset(all_words, randStart, n);
    randomize_list(n_words);
    timer.reset();
    mergesort(n_words);
    elapsed[i][0] = timer.elapsed();
    cout << elapsed[i][0] << ",\t";

    //Get the quick sort time
    randStart = rand() % totalSize;
    n_words = getSubset(all_words, randStart, n);
    randomize_list(n_words);
    timer.reset();
    quicksort(n_words);
    elapsed[i][1] = timer.elapsed();
    cout << elapsed[i][1] << endl;
    }

  double sumMerge, sumQuick, meanMerge, meanQuick, stdMerge, stdQuick = 0.0;

  //From here on we are calculating population parameters for this experiment
  for(i = 0; i < iterations; i++){
    sumMerge += elapsed[i][0];
    sumQuick += elapsed[i][1];
  }

  meanMerge = sumMerge / iterations;
  meanQuick = sumQuick / iterations;

  sumMerge = sumQuick = 0;
  for(i = 0; i < iterations; i++){
    sumMerge += (elapsed[i][0] - meanMerge) * (elapsed[i][0] - meanMerge);
    sumQuick += (elapsed[i][1] - meanQuick) * (elapsed[i][1] - meanQuick);
  }

  stdMerge = sqrt(sumMerge/(iterations-1));
  stdQuick = sqrt(sumQuick/(iterations-1));

  cout << endl << "Mean MS Time= " << meanMerge << " Std of MS Time="
       << stdMerge << endl;
  cout << "Mean QS Time= " << meanQuick << " Std of QS Time="
       << stdQuick << endl;
  
  return 0;
}



