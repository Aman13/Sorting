#include <string>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <stdlib.h>

int merge(int arr[], int temp[], int low, int mid, int high)	{
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
	}
	if(lower > mid)	{
		for(int i = pivot; i <= high; ++i)	{
			temp[index] = arr[i];
			index++;
		}
	}
	else	{
		for(int i = lower; i <= mid; ++i)	{
			temp[index] = arr[i];
			index++;
		}
	}

	for(int i = low; i <= high; ++i)	{
		std::cout << "final array builder" << std::endl;
		arr[i] = temp[i];
	}
	return 0;

}

int merge_builder(int arr[], int temp[], int low, int high)	{
	std::cout << "merge builder" << std::endl;
	int mid;
	if(low < high)	{
		mid = (low+high)/2;
		merge_builder(arr, temp, low, mid);
		merge_builder(arr, temp, mid+1, high);
		merge(arr, temp, low, mid, high);
	}
	return 0;
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

	merge_builder(arr, temp, 0, n-1);

	for(int i = 0; i < n; ++i)	{
		std::cout << arr[i] << std::endl;
	}
	return 13;
}

int main()	{
	int n = rand() % 10 + 5;
	int arr[n];
	for(int i = 0; i < n; ++i)	{
		arr[i] = rand() % 10;
		std::cout << arr[i] << std::endl;
	}

	//int a = insertion_sort(arr, n);
	//std::cout << "Insertion sort barometer: " << a << std::endl;

	int b = merge_sort(arr, n);
	std::cout << "Merge sort barometer: " << b << std::endl;

	int num = sizeof(arr)/sizeof(int);
	std::cout << "sizeof(arr) =" << sizeof(arr) << std::endl
	<< std::endl << "size = " << num << std::endl
	<< "n = " << n << std::endl;
}

/*
 
void merge(int *a, int *b, int low, int pivot, int high)
{
    int h,i,j,k;
    h=low;
    i=low;
    j=pivot+1;
 
    while((h<=pivot)&&(j<=high))
    {
        if(a[h]<=a[j])
        {
            b[i]=a[h];
            h++;
        }
        else
        {
            b[i]=a[j];
            j++;
        }
        i++;
    }
    if(h>pivot)
    {
        for(k=j; k<=high; k++)
        {
            b[i]=a[k];
            i++;
        }
    }
    else
    {
        for(k=h; k<=pivot; k++)
        {
            b[i]=a[k];
            i++;
        }
    }
    for(k=low; k<=high; k++) a[k]=b[k];
}




void mergesort(int *a, int *b, int low, int high)
{
    int pivot;
    if(low<high)
    {
        pivot=(low+high)/2;
        mergesort(a,b,low,pivot);
        mergesort(a,b,pivot+1,high);
        merge(a,b,low,pivot,high);
    }
}

int main()
{
    int a[] = {12,10,43,23,-78,45,123,56,98,41,90,24};
    int num;
 
    num = sizeof(a)/sizeof(int);
 
    int b[num];
 
    mergesort(a,b,0,num-1);
 
    for(int i=0; i<num; i++)	{
        std::cout<<a[i]<<" ";
    	std::cout<<std::endl;
    }
}
*/