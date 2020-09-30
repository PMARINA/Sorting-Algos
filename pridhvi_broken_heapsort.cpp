#pragma once
//#include "QuickSort.cpp"
using namespace std;

void print_array(uint64_t*, uint64_t*);

void heapify(uint64_t a[], int n, int i) {
  uint64_t temp;
  int smallest;
  int le = (2 * i);
  int ri = (2 * i) + 1;
  if ((le <= n) && (a[le] < a[i])) {
    smallest = le;
  } else {
    smallest = i;
  }
  if ((ri <= n) && (a[ri] < a[smallest])) {
    smallest = ri;
  }
  if (smallest != i) {
    temp = a[smallest];
    a[smallest] = a[i];
    a[i] = temp;
    heapify(a, n, smallest);
  }
}

void buildheap(uint64_t a[], int n) {
  for (int i = 1; i <= ((n / 2)); i++) {
    heapify(a, n, i);
  }
}

void heapsort(uint64_t a[], int n) {
  uint64_t temp;
  buildheap(a, n);
  print_array(a + 1, a + n + 2);
  uint64_t* atemp = a;
  for (int i = 1; i <= (n); i++) {
    // temp = a[1];
    // a[0] = a[0];
    // a[0] = temp;
    // n = n - 1;
    heapify(atemp++, n, 1);
  }
}

void heapsort(uint64_t* abs, uint64_t* babs) {
// uint64_t* a = new uint64_t[6];
// a[0] = 1;
// a[1] = 5;
// a[2] = 9;
// a[3] = 12;
// a[4] = 6;
// a[5] = 10;
// uint64_t* b = a + 6;
#define a abs
#define b babs
  print_array(a, b);
  uint64_t* start = new uint64_t[b - a + 1];
  memcpy(start + 1, a, (b - a) * sizeof(uint64_t));
  heapsort(start, b - a - 1);
  memcpy(a, start + 1, (b - a) * sizeof(uint64_t));
  print_array(a, b);
}