#include <iostream>
using namespace std;

// Merges two subarrays of a[1...m]+a[m+1...r]
void merge(int a[], int l, int m, int r) 
{ 
	int i = 0, j = 0, k = 0; //left,right,and merged array indexes
	int n1 = m - l + 1; //length for left
	int n2 = r - m; //length for right
	int L[n1], R[n2]; //temp arrays

	for (i = 0; i < n1; i++) //move data to temp arrays Left
		L[i] = a[l + i]; 
	for (j = 0; j < n2; j++) //move data to temp arrays Right
		R[j] = a[m + 1 + j]; 


	i = 0; j = 0; k = 0; //resetting indexes

	//compare elements and order them in
	while (i < n1 && j < n2) { 
		if (L[i] <= R[j]) { 
			a[k] = L[i]; 
			i++; 
		} 
		else { 
			a[k] = R[j]; 
			j++; 
		} 
		k++; 
	} 

	//move remaining elements into the array, left side
	while (i < n1) { 
		a[k] = L[i]; 
		i++; 
		k++; 
	} 

	//move remaining elements into the array, right side
	while (j < n2) { 
		a[k] = R[j]; 
		j++; 
		k++; 
	} 
} 


void topDownMergeSort(int a[], int l, int r)  //l is left index and r is right index
{ 
	if (l < r) { 
		int m = l + (r - l) / 2; //setting midpoint

		 
		topDownMergeSort(a, l, m); //sort left half
		topDownMergeSort(a, m + 1, r); //sort right half

		merge(a, l, m, r); //merge halves back together
	} 
} 


void mergesort (int a[],uint32_t n){
    topDownMergeSort(a, 0, n - 1); 
}


/*
//=============================================================
//Test code
void printArray(int A[], int size) 
{ 
	int i; 
	for (i = 0; i < size; i++) 
		cout << (A[i]) << " "; 
	cout << ("\n"); 
} 


int main() 
{ 
	int a[] = {9,8,7,6,5,4,3,2,1,0,-1,-2,5,4,8,-4,55}; 
	int n = sizeof(a) / sizeof(a[0]); 

	cout << "Given array is \n"; 
	printArray(a, n); 

	topDownMergeSort(a, 0, n - 1); 

	cout << "\nSorted array is \n"; 
	printArray(a, n); 
	return 0; 
} 
