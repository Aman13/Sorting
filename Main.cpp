#include <string>
#include <stdexcept>
#include <iostream>
#include <fstream>
 
using namespace std;

const int INSERTION = 0;
const int QUICK = 1;
const int MERGE = 2;
const int SHELL = 3;


template <class T>
T* readFile(string infile, int & n);
template <class T>
bool sorted(T arr[], int n);
template <class T>
bool contains(T arr1[], T arr2[], int n);
template <class T>
bool search(T arr[], int n, T target);
template <class T>
void sortTestResult(T arr[], int n, int sort);

//Checks and Swaps array values for insertion sort
//Param: arr[] = array to be sorted. i = the array value to be swapped
//      counter = barometer operation counter.
//Post: Returns the barometer operation counter and array with swapped values
template <class T>
int number_swap(T arr[], int i, int counter)	{
	int j = i;
	T temp;
	while(j > 0 && arr[j] < arr[j-1])	{
		temp = arr[j];
		arr[j] = arr[j-1];
		arr[j-1] = temp;
		++counter;
		j--;
	}
	return counter;
}

//Insertion Sort function
//Param: arr[] = array to be sorted
//		 n = size of array
//Post: Array is sorted, returns barometer operation value (how many comparisons were made).
template <class T>
int insertionsort(T arr[], int n)	{
	int barometer = 0;
	for(int i = 1; i < n; ++i)	{
		barometer = number_swap(arr, i, barometer); 
	}
	return barometer;

}
//Re-arranges value using merge sort algorithm putting values in a temporary array
//before inserting back into original array.
//Param: arr[] = array to be sorted. temp[] = temporary array to hold values.
//		low = lower bound of the array. mid = mid index of the array. high = upper bound of the array.
//		counter = barometer operation counter.
//Post:Array portion given is sorted. Returns barometer operation count.
template <class T>
int merge(T arr[], T temp[], int low, int mid, int high, int counter)	{
	int lower = low;
	int index = low;
	int pivot = mid+1;
	//Compares the value of above and below the pivot
	//swapping values when necessary.
	while((lower <= mid)&&(pivot <= high))	{
		if(arr[lower] <= arr[pivot])	{
			temp[index] = arr[lower];
			lower++;
		}
		else	{
			temp[index] = arr[pivot];
			pivot++;
		}
		index++;
		counter++;
	}
	if(lower > mid)	{
		for(int i = pivot; i <= high; ++i)	{
			temp[index] = arr[i];
			index++;
			counter++;
		}
	}
	else	{
		for(int i = lower; i <= mid; ++i)	{
			temp[index] = arr[i];
			index++;
			counter++;
		}
	}

	for(int i = low; i <= high; ++i)	{
		arr[i] = temp[i];
	}
	return counter;

}

//Breaks array into upper and lowerbound until it is as small as possible
//Sends the partitions to be sorted by merge function.
//Param: arr[] = array to be sorted. temp[] = temperorary array to help with sorting
//		low = lowerbound index of the array. high = upperbound index of the array.
//		counter = barometer operation value holder.
//Post: arr[] is sorted, returns counter which holds value for barometer operation.
template <class T>
int merge_builder(T arr[], T temp[], int low, int high, int counter)	{
	int mid;
	//Partitions array into smaller pieces until partioners are already sorted.
	//Recursivly merges partitions until entire array has called merge and is sorted.
	if(low < high)	{
		mid = (low+high)/2;
		counter = merge_builder(arr, temp, low, mid, counter);
		counter = merge_builder(arr, temp, mid+1, high, counter);
		counter = merge(arr, temp, low, mid, high, counter);
	}
	return counter;
}

//Intiates merge sort process on an array.
//Param: arr[] = array to be sorted. n = size of array.
//Post: arr[] is sorted and returns barometer operation value (number of comparisons made).
template <class T>
int mergesort(T arr[], int n)	{
	
	T temp[n];
	int barometer = 0;
	barometer = merge_builder(arr, temp, 0, n-1, barometer);

	return barometer;
}

//Runs quick sort algorithm, and sorts the array given.
//Param: arr[] = array to be sorted. low = lower bound index for the array
//		high = upper bound index for the array. counter = counts number of barometer operation.
//Post: arr[] is sorted and returns barometer operation value.
template <class T>
int quick_sorter(T arr[], int low, int high, int counter)	{
	int pivot = high;
	int right = high-1;
	int left = low;
	T temp;
	//Using the last value in the array as the pivot, the array is organized by swapping values larger than the pivot
	//with values smaller than the pivot
	while(left < right)	{
		if(arr[left] < arr[pivot])	{
			left++;
			counter++;
		}
		if(arr[left] >= arr[pivot])	{
			if(arr[left] > arr[right])	{
				temp = arr[left];
				arr[left] = arr[right];
				arr[right] = temp;				
			}
			counter++;
			--right;
		}
	}
	//Once the lower and upper bound have reached eachother that means the entire array has been checked
	//Once checked must find a position for the pivot
	//This part of the function searches for a value larger than the pivot and swaps it with the pivot
	bool swap = false;
	while(swap == false)	{
		if(arr[right] >= arr[pivot])	{
			temp = arr[right];
			arr[right] = arr[pivot];
			arr[pivot] = temp;
			swap = true;
			--right;
		}
		if(right == pivot)	{
			swap = true;
			--right;
		}
		++right;
		counter++;
	}
	//The function recursivly calls itself until it is partioned to a size that would be sorted from previous
	//instances of the function.
	if(low < right -1)	{
		counter = quick_sorter(arr, low, right-1, counter);
	}
	if(right+1 < high)	{
		counter = quick_sorter(arr, right+1, high, counter);
	}

	return counter;
}

//Intiates quick sort on an array
//Param: arr[] = array to be sorted. n = size of array.
//Post: arr[] is sorted and returns barometer operation value (number of comparisons made).
template <class T>
int quicksort(T arr[], int n)	{
	
	int barometer = 0;
	barometer = quick_sorter(arr, 0, n-1, barometer);

	return barometer;
}

//Intiates shell sort on an array, and sorts the array using shell sort algorithm.
//Param:arr[] = array to be sorted. n = size of array.
//Post: arr[] is sorted and returns barometer operation value (number of comparisons made).
template <class T>
int shellsort(T arr[], int n)	{
	
	int barometer = 0;
	int gap = n;
	T temp;
	bool swap = false;
	int back;
	//While the gap between array indexes is larger than one, comparisons are made.
	while(gap > 1)	{
		gap = gap/2;
		//The gap is reduced by half every loop, and every index is compared to the value that is
		//the gap indexes away.
		for(int i = 0; (i+gap)<n; i++)	{
			back = i;
			barometer++;
			//If the value is smaller, they are swapped so the array is being organized in ascending order.
			if(arr[i] > arr[i+gap] && (i+gap) < n)	{
				temp = arr[i];
				arr[i] = arr[i+gap];
				arr[i+gap] = temp;
				swap = true;
			}
			//Once a swap is made, we must check if another swap can be made the same distance behind the current index.
			//Swaps will continued to be made backwards until no swaps have been made or it is comparing values past the 
			//array index.
			while(swap == true)	{
				swap = false;
				barometer++;
				if(back-gap >= 0)	{
					back -= gap;

					if(arr[back] > arr[back+gap] && back >= 0)	{
					temp = arr[back];
					arr[back] = arr[back+gap];
					arr[back+gap] = temp;
					swap = true;
					}
				}
			}

		}
	}
	return barometer;
}


/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
void isTest()
{
  try{
         cout << "INSERTION SORT" << endl << "--------------" << endl;
         int n = 0;
         int* arr1 = readFile<int>("test1.txt", n);
         sortTestResult(arr1, n, INSERTION);
         float* arr2 = readFile<float>("test2.txt", n);
         sortTestResult(arr2, n, INSERTION);
         string* arr3 = readFile<string>("test4.txt", n);
         sortTestResult(arr3, n, INSERTION);
         int* arr4 = readFile<int>("test5.txt", n);
         sortTestResult(arr4, n, INSERTION);
         cout << endl;
  }catch(exception e){
         cout << e.what() << endl;
  }
}
 
// Tests the quicksort function
void qsTest()
{
  try{
         cout << "QUICKSORT" << endl << "---------" << endl;
         int n = 0;
         int* arr1 = readFile<int>("test1.txt", n);
         sortTestResult(arr1, n, QUICK);
         float* arr2 = readFile<float>("test2.txt", n);
         sortTestResult(arr2, n, QUICK);
         string* arr3 = readFile<string>("test3.txt", n);
         sortTestResult(arr3, n, QUICK);
         int* arr4 = readFile<int>("test5.txt", n);
         sortTestResult(arr4, n, QUICK);
         cout << endl;
  }catch(exception e){
         cout << e.what() << endl;
  }
}
 
// Tests the mergesort function
void msTest()
{
  try{
         cout << "MERGESORT" << endl << "---------" << endl;
         int n = 0;
         int* arr1 = readFile<int>("test1.txt", n);
         sortTestResult(arr1, n, MERGE);
         float* arr2 = readFile<float>("test2.txt", n);
         sortTestResult(arr2, n, MERGE);
         string* arr3 = readFile<string>("test3.txt", n);
         sortTestResult(arr3, n, MERGE);
         int* arr4 = readFile<int>("test5.txt", n);
         sortTestResult(arr4, n, MERGE);
         cout << endl;
  }catch(exception e){
         cout << e.what() << endl;
  }
}
 
// Tests the shellsort function
void shsTest()
{
  try{
         cout << "SHELL SORT" << endl << "---------" << endl;
         int n = 0;
         int* arr1 = readFile<int>("test1.txt", n);
         sortTestResult(arr1, n, SHELL);
         float* arr2 = readFile<float>("test2.txt", n);
         sortTestResult(arr2, n, SHELL);
         string* arr3 = readFile<string>("test3.txt", n);
         sortTestResult(arr3, n, SHELL);
         int* arr4 = readFile<int>("test5.txt", n);
         sortTestResult(arr4, n, SHELL);
         cout << endl;
  }catch(exception e){
         cout << e.what() << endl;
  }
}
 
// Tests that array is correctly sorted
template <class T>
void sortTestResult(T arr[], int n, int sort)
{
  T* arrcopy = new T[n];
  for(int i=0; i < n; i++){
         arrcopy[i] = arr[i];
  }
 
  cout << "n = " << n;
  if(sort == INSERTION){
         cout << ", comparisons = " << insertionsort(arr, n);
  }else if (sort == QUICK){
         cout << ", comparisons = " << quicksort(arr, n);
  }else if (sort == MERGE){
         cout << ", comparisons = " << mergesort(arr, n);
  }else if (sort == SHELL){
         cout << ", comparisons = " << shellsort(arr, n);
  }
  cout <<", values = " << contains(arr, arrcopy, n);
  cout <<", sorted = " << sorted(arr, n) << endl;
 
  delete[] arr;
  delete[] arrcopy;
}
 
// Opens a file and reads the contents into an array
// PARAM: infile = name of the file to be opened
//        n = the size of the result array
// PRE: the file contains values separated by white space
// POST: returns an array containing the contents of infile
template <class T>
T* readFile(string infile, int & n)
{
  T* result;
  T next;
  n = 0;
 
  ifstream ist(infile.c_str()); // open file
  // Check if file opened correctly
  if(ist.fail())
         throw runtime_error(infile + " not found");
    
  // Find file size
  while(ist >> next){
         n++;
  }
 
  // Read file into array
  ist.close();
  ist.open(infile.c_str());
  result = new T[n];
  for(int i=0; i < n; ++i){
         ist >> result[i];
  }
 
  ist.close();
 
  return result;
}
 
// Checks to see if the input array is in ascending order
// PARAM: arr = name of the array
//        n = size of arr
// PRE:
// POST: returns true iff arr is in ascending order
template <class T>
bool sorted(T arr[], int n)
{
  // Check to see each element i <= element i+1
  for(int i=0; i < n-1; ++i){
         if(arr[i] > arr[i+1]){
                 return false;
         }
  }
  return true;
}
 
// Checks to see if the two arrays contain the same values
// PARAM: arr1, arr2 = name of the arrays
//        n = size of both arrays
// PRE: arr1 and arr2 are the same size, arr1 is sorted
// POST: returns true iff arr1 contains all values in arr2
template <class T>
bool contains(T arr1[], T arr2[], int n)
{
  // Check to see each element of arr2 is in arr1
  for(int i=0; i < n; ++i){
         if(!search(arr1, n, arr2[i])){
                 return false;
         }
  }
  return true;
}
 
// Checks to see if target value is in array
// PARAM: arr = array to be searched
//        n = size of array
//        target =  value to be searched for
// PRE: arr is sorted
// POST: returns true iff target is in arr
template <class T>
bool search(T arr[], int n, T target)
{
  int low = 0;
  int high = n-1;
  int mid = 0;
 
  while(low <= high){
         mid = (low + high) / 2;
         if(arr[mid] == target){
                 return true;
         }else if(target < arr[mid]){
                 high = mid - 1;
         }else{
                 low = mid + 1;
         }
  }
  return false;
}


//////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
//////////////////////////////////////////////////////


int main()	{

		isTest();
		qsTest();
		msTest();
		shsTest();
}
