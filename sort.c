#include "sort.h"


#ifdef ASCENDING
bool ascending = true;
#else
bool ascending = false;
#endif


void ssort(int * arr, int size) {
	/* For step 3, fill this in to perform a selection sort
	   For step 4, add conditional compilation flags to perform an ascending selection sort instead */



	// loop for checking and changing arr[i] to lowest or highest number
	for(int i = 0; i < size; i++)
	{

		// var for storing the lowest number past arr[i]
		int current_min_num = arr[i];

		// var for storing the largest number past arr[i]
		int current_max_num = arr[i];


		int min_index_location = i;


		int max_index_location = i;


		int storage; 

		
		// loop to find lowest or highest number in the array and store it in current_min_number
		for(int j = i; j < size; j++)
		{

		  // check if arr[j] is the smallest number and change current_min_num if true
		  if((arr[j] < current_min_num) && (ascending ==  true))
		  {
		  current_min_num = arr[j];
		  min_index_location = j;
		  }

		  if((arr[j] > current_max_num) && (ascending == false))
		  {
		  current_max_num = arr[j];
		  max_index_location = j;
		  }

		}  
		

		// rearrange the array with the new found min or max number
		if(ascending ==  true)
		{
			storage = arr[i];

			arr[i] = current_min_num;

			arr[min_index_location] = storage;

			current_min_num = arr[i+1];
		}

		else
		{
			storage = arr[i];

			arr[i] = current_max_num;

			arr[max_index_location] = storage;

			current_max_num = arr[i+1];
		}
	}
}
