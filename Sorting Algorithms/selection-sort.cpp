//============================================================================
// Name        : selection-sort.cpp
// Author      : 
// Date        :
// Copyright   : 
// Description : Implementation of selection sort in C++
//============================================================================

#include "sort.h"
#include <iostream>

void
SelectionSort::sort(vector<int>& v)				// main entry point
{
  /* Complete this function with the implementation of selection sort algorithm 
  Record number of comparisons in variable num_cmps of class Sort
  */

 for (int i = 0; i < (v.size() - 1); i++){
    int min = i;
    for(int j = i+1; j < v.size(); j++){
      if (num_cmps++, v[j] < v[min]){
        min = j;
      }
    }
    if (min != i){
      int temp = v[i];
      v[i] = v[min];
      v[min] = temp;
    }
 }


}