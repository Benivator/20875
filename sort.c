#include "sort.h"


#ifdef ASCENDING
bool ascending = true;
#else
bool ascending = false;
#endif


void ssort(int * arr, int size) {
	/* For step 3, fill this in to perform a selection sort
	   For step 4, add conditional compilation flags to perform an ascending selection sort instead */




		// var for storing the lowest number past arr[i]
		int current_min_num = arr[0];

		// var for storing the largest number past arr[i]
		int current_max_num = arr[0];



	// loop for checking and changing arr[i] to lowest or highest number
	for(int i = 0; i < size; i++)
	{
		
		// loop to find lowest or highest number in the array and store it in current_min_number
		for(int j = i; j < size; j++)
		{

		  // check if arr[j] is the smallest number and change current_min_num if true
		  if((arr[j] < current_min_num) && (ascending ==  true))
		  {
		  current_min_num = arr[j];
		  }

		  if((arr[j] > current_max_num) && (ascending == false))
		  {
		  current_max_num = arr[j];
		  }

		}  
		

		// rearrange the array with the new found min or max number
		if(ascending ==  true)
		{
			arr[i] = current_min_num;
		}

		else
		{
			arr[i] = current_max_num;
		}
	}
}
