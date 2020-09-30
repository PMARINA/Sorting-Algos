#pragma once
#include "QuickSort.cpp"
using namespace std;
/*
void makesubheap(uint64_t a[], int i, int n) {
  uint64_t temp;

  if ((i >= n) || ((2 * i) >= n)) {
    return;
  }
  if (((2 * i) + 1) >= n) {
    if (a[2 * i] > a[i]) {
      temp = a[2 * i];
      a[2 * i] = a[i];
      a[i] = temp;
    }
  } else {
    if (a[2 * i] > a[(2 * i) + 1]) {
      if (a[2 * i] > a[2]) {
        temp = a[2 * i];
        a[2 * i] = a[i];
        a[i] = temp;
      }
    } else {
      if (a[(2 * i) + 1] > a[i]) {
        temp = a[(2 * i) + 1];
        a[(2 * i) + 1] = a[i];
        a[i] = temp;
      }
    }
  }
};
*/

void heapify(uint64_t a[], int n, int i) {
  uint64_t temp;
  int largest;
  int le = (2*i) + 1;
  int ri = (2*i) + 2;
  if ((le <= n) && (a[le] > a[i])) {
    largest = le;
  } else {
    largest = i;
  }
  if ((ri <= n) && (a[ri] > a[largest])) {
    largest = ri;
  }
  if (largest != i) {
    temp = a[largest];
    a[largest] = a[i];
    a[i] = temp;
    heapify(a, n, largest);
  }
}

/*
void makeheap(uint64_t a[], int n) {
  for (int i = 1; i <= (n / 2); i++) {
    makesubheap(a, i, n);
  }
};
*/

void buildheap(uint64_t a[], int n) {
  for (int i = 1; i <= (n / 2); i++) {
    heapify(a, n, i);
  }
}
/*
void rebuildheap(uint64_t a[], int n) {
  uint64_t temp;
  for (int i = 2; i <= (n - 1); i++) {
    temp = a[i];
    a[i] = a[0];
    a[0] = temp;
  }
};
*/

void heapsort(uint64_t a[], int n) {
  uint64_t temp;
  buildheap(a, n);
  for (int i = 2; i <= n; i++) {
    temp = a[1];
    a[1] = a[i];
    a[i] = temp;
    n = n - 1;
    heapify(a, n, 1);
  }
}

void heapsort(uint64_t* a, uint64_t* b) {
  print_array(a, b);
  heapsort(a, b - a);
  print_array(a, b);
}