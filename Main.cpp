#include <string>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <stdlib.h>

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

template <class T>
int insertionsort(T arr[], int n)	{
	std::cout << "Insertion Sort" << std::endl 
	<< "-------------" << std::endl << std::endl;

	int barometer = 0;
	for(int i = 1; i < n; ++i)	{
		barometer = number_swap(arr, i, barometer); 
	}

	for(int i = 0; i < n; ++i)	{
		std::cout << arr[i] << std::endl;
	}

	return barometer;
}
template <class T>
int merge(T arr[], T temp[], int low, int mid, int high, int counter)	{
	int lower = low;
	int index = low;
	int pivot = mid+1;

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

template <class T>
int merge_builder(T arr[], T temp[], int low, int high, int counter)	{
	int mid;
	if(low < high)	{
		mid = (low+high)/2;
		counter = merge_builder(arr, temp, low, mid, counter);
		counter = merge_builder(arr, temp, mid+1, high, counter);
		counter = merge(arr, temp, low, mid, high, counter);
	}
	return counter;
}

template <class T>
int mergesort(T arr[], int n)	{
	std::cout << "Merge sort" << std::endl 
	<< "-------------" << std::endl << std::endl;

	T temp[n];
	int barometer = 0;
	barometer = merge_builder(arr, temp, 0, n-1, barometer);

	for(int i = 0; i < n; ++i)	{
		std::cout << arr[i] << std::endl;
	}

	return barometer;
}

template <class T>
int quick_sorter(T arr[], int low, int high, int counter)	{
	int pivot = high;
	int right = high-1;
	int left = low;
	T temp;
/*
	std::cout << "Pivot: " << arr[pivot] << std::endl << "left index: " <<
	left << std::endl << "right index: " << right << std::endl;
*/
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
	if(low < right -1)	{
		counter = quick_sorter(arr, low, right-1, counter);
	}
	if(right+1 < high)	{
		counter = quick_sorter(arr, right+1, high, counter);
	}

	return counter;
}

template <class T>
int quicksort(T arr[], int n)	{
	std::cout << "Quick Sort" << std::endl
	<< "-------------" << std::endl << std::endl;

	int barometer = 0;

	barometer = quick_sorter(arr, 0, n-1, barometer);

	std::cout << "SORTED ARRAY IS" << std::endl <<
	"-----------" << std::endl;
	for(int i = 0; i < n; ++i)	{
		std::cout << arr[i] << std::endl;
	}

	return barometer;

}

template <class T>
int shellsort(T arr[], int n)	{
	std::cout << "Shell Sort" << std::endl
	<< "-------------" << std::endl << std::endl;	
	int barometer = 0;
	int gap = n;
	T temp;
	bool swap = false;
	int back;
	while(gap > 1)	{
		gap = gap/2;
		std::cout << "Gap Size: " << gap << std::endl;
		for(int i = 0; (i+gap)<n; i++)	{
			back = i;
			barometer++;
			if(arr[i] > arr[i+gap] && (i+gap) < n)	{
				temp = arr[i];
				arr[i] = arr[i+gap];
				arr[i+gap] = temp;
				swap = true;
			}
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
	
		for(int i = 0; i < n; ++i)	{
			std::cout << arr[i] << ", ";
		}
		std::cout << std::endl << std::endl <<"repeating shell loop" << std::endl;
	
	}
	return barometer;
}

int main()	{
/*
	int num = 100;
	int n = rand() % 200 + 200;
	int arr[n];
	for(int i = 0; i < n; ++i)	{
		arr[i] = rand() % num;
		std::cout << arr[i] << ",";
	}

	int a = insertionsort(arr, n);
	std::cout << "Insertion sort barometer: " << a << std::endl;


	for(int i = 0; i < n; ++i)	{
		arr[i] = rand() % num;
		std::cout << arr[i] << ", ";
	}

	int b = mergesort(arr, n);
	std::cout << "Merge sort barometer: " << b << std::endl;


	for(int i = 0; i < n; ++i)	{
		arr[i] = rand() % num;
		std::cout << arr[i] << ", ";
	}	


	int c = quicksort(arr,n);
	std::cout << "Quick sort barometer: " << c << std::endl;

	for(int i = 0; i < n; ++i)	{
		arr[i] = rand() % num;
		std::cout << arr[i] << ", ";
	}
*/

	std::string arr[] = {"apple", "dog", "cat", "fish", "whale", "horse", "cow", "parrot", "shark", "dolphin", "crow"};
	int n = 11;

	int d = shellsort(arr,n);
	std::cout << "Shell sort barometer: " << d << std::endl;

	return 0;
}