#include <string>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <stdlib.h>

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

int insertion_sort(int arr[], int n)	{
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

int merge_sort(int arr[], int n)	{
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

int main()	{
	int n = rand() % 200 + 50;
	int arr[n];
	for(int i = 0; i < n; ++i)	{
		arr[i] = rand() % 10;
		std::cout << arr[i] << " ,";
	}

	int a = insertion_sort(arr, n);
	std::cout << "Insertion sort barometer: " << a << std::endl;

	for(int i = 0; i < n; ++i)	{
		arr[i] = rand() % 10;
		std::cout << arr[i] << " , ";
	}

	int d = merge_sort(arr, n);
	std::cout << "Merge sort barometer: " << d << std::endl;

}