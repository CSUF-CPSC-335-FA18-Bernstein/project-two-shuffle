///////////////////////////////////////////////////////////////////////////////
// project2.hh
//
// The three algorithms specified in the project 1 requirements
// document, plus helper functions.
//
///////////////////////////////////////////////////////////////////////////////

#include "project2.hh"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


void swapStrings(string_vector & strings, int i1, int i2) {
  string temp = strings[i1];
  strings[i1] = strings[i2];
  strings[i2] = temp;
  return;
}

//-----------------------------------------------------------------------------
// Randomize the order of all items in the list
//-----------------------------------------------------------------------------
void randomize_list(string_vector & strings) {
  string temp;
  int randNum, i;
  int maxSize = strings.size();
  srand(time(NULL)); //seeds the RNG with the current unix time

  for (i = 0; i < maxSize; i++) {
    randNum = rand() % maxSize;
    swapStrings(strings, i, randNum);
  }
	
  return;
}

//-----------------------------------------------------------------------------
void merge(string_vector & strings, size_t start, size_t mid, size_t end) {
  int i;
  int size = end-start+1;
  int readFromLeft = start;
  int readFromRight = mid;
  string stage[size];
  
  for (i = 0; i < size; i++){
    if(strings[readFromLeft] < strings[readFromRight]) {
      stage[i] = strings[readFromLeft++];
    }
    else {
      stage[i] = strings[readFromRight++];
    }

    //Check if we've exhausted all the elements from the left or the right
    //if so, copy the rest from the other side and exit the loop
    if(readFromLeft >= mid){
      for(++i; i < size; i++){
	stage[i] = strings[readFromRight++];
      }
      break;
    }
    else if(readFromRight > end) {
      for(++i; i < size; i++){
	stage[i] = strings[readFromLeft++];
      }
      break;
    }
  }

  //now copy back the strings from stage to the original vector
  for(i = 0; i<size; i++){
    strings[start+i] = stage[i];
  }
  
  return;
}

//-----------------------------------------------------------------------------
// Sort the given list using the merge sort algorithm.
// This is a recursive method which splits the list into two
// parts, recursively calls itself on the two parts and then merges 
// the two parts together using the merge() method.
//-----------------------------------------------------------------------------
void mergesort(string_vector & strings, size_t start, size_t end) {
  //handle the base case
  if (start == end) {
    return;
  }
  
  int mid = (start+end)/2 + 1;
  mergesort(strings, start, mid-1);
  mergesort(strings, mid, end);
  merge(strings, start, mid, end);
  
  return;
}

//-----------------------------------------------------------------------------
// Implementation of the Hoare Partition.
// This partition uses the first element of the list as a partition
// and divides the list into less than and greater than the pivot value
// It returns the index of the final position of the pivot value.
//-----------------------------------------------------------------------------
int hoare_partition(string_vector & strings, int start, int end) {
  //can't partition an array of size 1
  if(start == end){
    return 0;
  }

  string pivot = strings[start];
  int i = start+1;
  int j = end;

  while(i<j){
    while((i<end) && (strings[i] < pivot)){
      i++;
    }

    while((j>start+1) && (strings[j] > pivot)){    
      j--;
    }

    swapStrings(strings, i, j);
  }

  swapStrings(strings, i, j);
  swapStrings(strings, j, start);
  return j;
}

//-----------------------------------------------------------------------------
// Sort the given list using the quicksort algorithm.
// This is a recursive method which splits the list into two
// parts, recursively calls itself on the two parts and then merges 
// the two parts together using the merge() method.
//-----------------------------------------------------------------------------
void quicksort(string_vector & strings, int start, int end) {
  // TODO: implement this function, then delete this comment
  return;
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// ALREADY IMPLEMENTED 
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Load words from the file at the given path. The words vector is
// cleared, and then each word from the file is added to the
// vector. Returns true on success or fale on I/O error.
//-----------------------------------------------------------------------------
bool load_words(string_vector& words, const std::string& path) 
{
  //std::cout << "Loading words from [" << path << "]" << std::endl;
  words.clear();
  std::ifstream ifs(path.c_str());
  if (!ifs.is_open() || !ifs.good()) {
    //cout << "Failed to open [" << path << "]" << std::endl;
    return false;
  }
  int countWordsLoaded = 0;
  while (!ifs.eof()) {
    std::string lineBuffer;
    std::getline(ifs, lineBuffer);
    if (ifs.eof()) {
      break;
    }
    words.push_back(lineBuffer);
    countWordsLoaded++;
  }
  //std::cout << "Loaded " << countWordsLoaded << " words from [" << path << "]" << std::endl;;
  return true;
}

//-----------------------------------------------------------------------------
// Sort the given list using the merge sort algorithm.
// This method is simply a helper to make the initial 
// call the recursive mergesort() method below that requires
// first and last indexes for sorting range
//-----------------------------------------------------------------------------
void mergesort(string_vector & strings) {
  if (strings.size() == 0) {
    return;
  }
  mergesort(strings, 0, strings.size() - 1);
  return;
}

//-----------------------------------------------------------------------------
// Sort the given list using the quicksort algorithm.
// This method is simply a helper to make the initial 
// call the recursive mergesort() method below that requires
// first and last indexes for sorting range
//-----------------------------------------------------------------------------
void quicksort(string_vector & strings) {
  if (strings.size() == 0) {
    return;
  }
  quicksort(strings, 0, strings.size() - 1);
  return;
}

