#pragma once
// #include "QuickSort.cpp"
using namespace std;

void print_array(uint64_t*, uint64_t*);
void printHeap(uint64_t arr[], int n) {
  cout << "Array representation of Heap is:\n";

  cout << arr[1] << endl;
  cout << arr[2] << "\t" << arr[3] << endl;
  cout << arr[4] << "\t" << arr[5] << "\t" << arr[6] << "\t" << arr[7] << endl;
  cout << arr[8] << "\t" << arr[9] << "\t" << arr[n] << endl;

  for (int i = 1; i <= n; ++i) cout << arr[i] << " ";
  cout << "\n";
}

void heapify(uint64_t a[], int n, int i) {
  uint64_t temp;
  int largest = i;
  int le = (2 * i);
  int ri = (2 * i) + 1;
  if ((le <= n) && (a[le] > a[largest])) {
    largest = le;
  }
  if ((ri <= n) && (a[ri] > a[largest])) {
    largest = ri;
  }
  if (largest != i) {
    swap(a[largest], a[i]);
    heapify(a, n, largest);
  }
}

void buildheap(uint64_t a[], int n) {
  for (int i = (n / 2) + 1; i >= 1; i--) {
    heapify(a, n, i);
  }
  // printHeap(a, n);
}

void heapsort(uint64_t a[], int n) {
  uint64_t temp;
  buildheap(a, n);
  uint64_t temp_n = n;
  for (int i = n; i >= 2; i--) {
    swap(a[1], a[temp_n]);
    heapify(a, --temp_n, 1);
  }
}

void heapsort(uint64_t* a, uint64_t* b) {
  // print_array(a, b);
  heapsort(a - 1, b - a);
  // print_array(a, b);
}