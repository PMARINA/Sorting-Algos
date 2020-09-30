#pragma once
#include <cstdint>
#include <iostream>

using std::cout;
using std::endl;
int i = 0;
void print_array(uint64_t* start, uint64_t* end) {
  // uint64_t* start = s;
  // uint64_t* end = e;
  // cout << i++ << endl;
  while (start < end) cout << *(start++) << "\t";
  cout << "\n";
}
void run_sort(uint64_t* start, uint64_t* end) {
  // If recursion done, return
  if ((end - start) <= 1) return;
  // print_array(start, end);
  // Pivot is always the last element (Lomuto)
  uint64_t pivot_value = *(end - 1);
  // Do Lomuto Partition-based sorting
  uint64_t temp;
  uint64_t* pivot = end;
  for (uint64_t *read_head = start, *write_head = start; read_head < end;
       read_head++) {
    if (*read_head <= pivot_value) {
      // Swap read and write head values...
      temp = *read_head;
      *read_head = *write_head;
      *write_head = temp;
      // increment the write head
      pivot = write_head++;
    }
  }
  // print_array(start, end);
  // cin >> temp;
  // Partition and recurse...
  uint64_t* mid_addr = pivot;
  run_sort(start, mid_addr);
  run_sort(mid_addr, end);
}
void quicksort(uint64_t* start, uint64_t* end) {
  // print_array(start, end);
  run_sort(start, end);
  // print_array(start, end);
}