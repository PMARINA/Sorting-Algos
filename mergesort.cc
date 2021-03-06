#include <iostream>
using namespace std;

void merge(uint64_t* start, int l, int m, int r) {
  // size of left and right arrays
  int s1 = m - l + 1;
  int s2 = r - m;

  // temp arrays to size of left and right
  int* la = new int[s1];
  int* ra = new int[s2];

  for (int i = 0; i < s1; i++)  // move data to temp array Left
    la[i] = start[l + i];

  for (int j = 0; j < s2; j++)  // move data to temp array Right
    ra[j] = start[m + j + 1];

  // compare elements and insert into array A until left or right array is empty
  int i = 0, j = 0;  // reset iteration values
  int k = l;         // set k for merged list
  while (i < s1 && j < s2) {
    if (la[i] <= ra[j]) {
      start[k] = la[i];
      i++;
    } else {
      start[k] = ra[j];
      j++;
    }
    k++;
  }

  // put remaining, ordered, numbers into the array a which are remaining in
  // left or right arrays
  while (i < s1) {
    start[k] = la[i];
    i++;
    k++;
  }

  while (j < s2) {
    start[k] = ra[j];
    j++;
    k++;
  }
  delete[] la;
  delete[] ra;
}

void TDmergesort(uint64_t* start, int l, int r) {
  if (l < r) {
    int m = l + (r - l) / 2;  // midpoint

    TDmergesort(start, l, m);      // left side
    TDmergesort(start, m + 1, r);  // right side

    merge(start, l, m, r);
  }
}

void mergesort(uint64_t* start, uint32_t n) { TDmergesort(start, 0, n - 1); }

void mergesort(uint64_t* start, uint64_t* end) {
  mergesort(start, end - start);
}

void printArray(uint64_t* start, uint32_t size) {
  for (int i = 0; i < size; i++) cout << (start[i]) << " ";
  cout << endl;
}