//============================================================================
// Name        : bubble-sort.cpp
// Author      : 
// Date        :
// Copyright   : 
// Description : Implementation of bubble sort in C++
//============================================================================

#include "sort.h"

void 
BubbleSort::sort(vector<int>& v)			// main entry point
{
  /* Complete this function with the implementation of bubble sort algorithm 
     Record number of comparisons in variable num_cmps of class Sort
  */
 
    bool value = true;
    while(value){
      value = false;
      for (int i = 0; i < v.size()-1; i++) {
          if (num_cmps++, v[i]>v[i+1] ){
              swap(v[i],v[i+1]);
              value = true;
          }
      }
    }
    //cout << "NUMBER of COMPARISONS : " << num_cmps;
}