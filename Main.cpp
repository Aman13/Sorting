#include <string>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <stdlib.h>

int number_swap(int arr[], int i, int counter)	{
	int j = i;
	int temp;
	while(j > 0 && arr[j] < arr[j-1])	{
		temp = arr[j];
		arr[j] = arr[j-1];
		arr[j-1] = temp;
		++counter;
		j--;
	}
	return counter;
}

int insertionsort(int arr[], int n)	{
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

int merge(int arr[], int temp[], int low, int mid, int high, int counter)	{
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

int merge_builder(int arr[], int temp[], int low, int high, int counter)	{
	int mid;
	if(low < high)	{
		mid = (low+high)/2;
		counter = merge_builder(arr, temp, low, mid, counter);
		counter = merge_builder(arr, temp, mid+1, high, counter);
		counter = merge(arr, temp, low, mid, high, counter);
	}
	return counter;
}

int mergesort(int arr[], int n)	{
	std::cout << "Merge sort" << std::endl 
	<< "-------------" << std::endl << std::endl;

	int temp[n];
	int barometer = 0;
	barometer = merge_builder(arr, temp, 0, n-1, barometer);

	for(int i = 0; i < n; ++i)	{
		std::cout << arr[i] << std::endl;
	}
	return barometer;
}

int quick_sorter(int arr[], int low, int high, int counter)	{
	std::cout << "Entering quick_sorter" << std::endl;
	int left = low;
	int right = high-1;
	int pivot = high;
	int temp;

	while(left < right)	{
		while(arr[left] > arr[pivot] && right > left)	{
			if(right < pivot)	{
				temp = arr[left];
				arr[left] = arr[right];
				arr[right] = temp;
			}
			right--;
			counter++;
		}
		left++;
		counter++;
	}
	while(left < pivot)	{
		if(arr[left] > arr[pivot])	{
			temp = arr[pivot];
			arr[pivot] = arr[left];
			arr[left] = temp;
		}
		left++;
	}
	for(int i = low; i <= high; ++i)	{
		std::cout << arr[i] << std::endl;
	}

	return counter;
}

int quick_partioner(int arr[], int low, int high, int counter)	{
	int mid;
	if(low < high)	{
		counter = quick_sorter(arr, low, high, counter);
		int mid = (low+high)/2;
		counter = quick_partioner(arr, low, mid, counter);
		counter = quick_partioner(arr, mid+1, high, counter);
	}

	return counter;
}

int quicksort(int arr[], int n)	{
	std::cout << "Quick Sort" << std::endl
	<< "-------------" << std::endl << std::endl;

	int barometer = 0;

	barometer = quick_partioner(arr, 0, n-1, barometer);

	std::cout << "SORTED ARRAY IS" << std::endl <<
	"-----------" << std::endl;
	for(int i = 0; i < n; ++i)	{
		std::cout << arr[i] << std::endl;
	}

	return barometer;

}


int main()	{
	int n = rand() % 10 + 10;
	int arr[n];
	for(int i = 0; i < n; ++i)	{
		arr[i] = rand() % 100;
		std::cout << arr[i] << ",";
	}
/*
	int a = insertionsort(arr, n);
	std::cout << "Insertion sort barometer: " << a << std::endl;

	for(int i = 0; i < n; ++i)	{
		arr[i] = rand() % 100;
		std::cout << arr[i] << ", ";
	}

	int b = mergesort(arr, n);
	std::cout << "Merge sort barometer: " << b << std::endl;
*/
	int c = quicksort(arr,n);
	std::cout << "Quick sort barometer: " << c << std::endl;

}