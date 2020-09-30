#include <algorithm>  // only for demo of this test_script, remove later
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <random>

#include "heapsort.cpp"

using namespace std::chrono;
using std::cout;
using std::endl;
using std::random_device;
using std::sort;  // only for demo of this test_script, remove later
using std::uniform_int_distribution;

/**
 * How to use this script:
 * Write your algorithm
 *    must take in two pointers, start, end + 1
 * #include your algorithm above
 * replace sort in the next line with your sorting algorithm
 * Run this file...
 *
 * What does it do? Tests your algorithm, both with all numbers in sequence, as
 * well as randomly generated numbers Also with an odd and even number of
 * elements.
 */

void (*sorting_algorithm)(uint64_t*, uint64_t*) = heapsort;

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
// void sorting_algorithm(uint64_t* a, uint64_t* b) { sort(a, b); }
// This is our original test-code (imo more comprehensive than yours)
void swap(uint64_t arr[], uint64_t i, uint64_t j) {
  // if (i == 0 || i == 999) cout << i << " paired with: " << j << "\n";
  if (i == j) {
    // cout << "RANDOM BROKEN" << "\n";
    return;
  }
  uint64_t temp = arr[i];
  arr[i] = arr[j];
  arr[j] = temp;
}

bool is_in_order(uint64_t* arr, uint64_t num_elements) {
  for (int i = 0; i < num_elements - 1; i++) {
    if (arr[i] > arr[i + 1]) return false;
  }
  return true;
}

bool all_numbers_present(uint64_t* arr, uint64_t num_elements) {
  bool* nums = new bool[num_elements];
  memset(nums, 0, num_elements * sizeof(bool));  // set everything to false
  for (int i = 0; i < num_elements; i++) {
    uint64_t val_in_arr = arr[i];
    if (val_in_arr >= num_elements) {
      cout << "Item out of range. Could Crash, i: " << i
           << " val: " << val_in_arr << "\n";
    }
    nums[arr[i]] = true;
  }
  for (int i = 0; i < num_elements; i++) {
    if (!nums[i]) {
      cout << "Failed_all_numbers_present: " << i << "\n";
      return false;
    }
  }
  return true;
}

bool test_all_numbers(void (*algo_to_be_tested)(uint64_t*, uint64_t*),
                      uint64_t num_elements) {
  // Create a test array that's sorted.
  uint64_t* test_array = new uint64_t[num_elements];
  for (uint64_t i = 0; i < num_elements; i++) {
    test_array[i] = i;
  }
  random_device rd;
  uniform_int_distribution<int> distribution(0, num_elements - 1);
  for (uint64_t i = 0; i < num_elements; i++) {
    uint64_t rand_index = distribution(rd);
    // uint64_t(double(rand()) / (RAND_MAX) * (num_elements - i - 1)) + i;
    if (rand_index >= num_elements || rand_index < 0)
      cout << "WARNING: " << rand_index << " rand index is out of bounds."
           << "\n";
    swap(test_array, i, rand_index);
  }
  // print_array(test_array, test_array + num_elements);
  algo_to_be_tested(test_array, test_array + num_elements);
  // print_array(test_array, test_array + num_elements);
  bool answer = is_in_order(test_array, num_elements) &&
                all_numbers_present(test_array, num_elements);
  delete[] test_array;
  return answer;
}

bool test_random_numbers(void (*algo_to_be_tested)(uint64_t*, uint64_t*),
                         uint64_t num_elements, uint64_t max_val,
                         string message) {
  uint64_t* test_array = new uint64_t[num_elements];
  random_device rd;
  uniform_int_distribution<int> distribution(0, max_val);
  for (uint64_t i = 0; i < num_elements; i++) {
    test_array[i] = distribution(rd);
  }
  print_array(test_array, test_array + num_elements);
  cout << message << "\n";
  // auto start = high_resolution_clock::now();
  algo_to_be_tested(test_array, test_array + num_elements);
  // auto stop = high_resolution_clock::now();
  // auto duration = duration_cast<microseconds>(stop - start);
  // cout << "TOOK: " << (double)duration.count() / 1e6 << " seconds" << endl;
  bool answer = is_in_order(test_array, num_elements);
  print_array(test_array, test_array + num_elements);
  delete[] test_array;
  return answer;
}

bool test_random_numbers(void (*algo_to_be_tested)(uint64_t*, uint64_t*),
                         uint64_t num_elements) {
  return test_random_numbers(algo_to_be_tested, num_elements, 2147483647,
                             "");  // 2147483647 is INT_MAX
}

bool test_ordered_ascending(void (*algo_to_be_tested)(uint64_t*, uint64_t*),
                            uint64_t num_elements) {
  uint64_t* test_array = new uint64_t[num_elements];
  for (uint64_t i = 0; i < num_elements; i++) {
    test_array[i] = i;
  }
  algo_to_be_tested(test_array, test_array + num_elements);
  bool answer = is_in_order(test_array, num_elements) &&
                all_numbers_present(test_array, num_elements);
  delete[] test_array;
  return answer;
}

bool test_ordered_descending(void (*algo_to_be_tested)(uint64_t*, uint64_t*),
                             uint64_t num_elements) {
  uint64_t* test_array = new uint64_t[num_elements];
  for (uint64_t i = 0; i < num_elements; i++) {
    test_array[i] = num_elements - i - 1;
  }
  algo_to_be_tested(test_array, test_array + num_elements);
  bool answer = is_in_order(test_array, num_elements) &&
                all_numbers_present(test_array, num_elements);
  delete[] test_array;
  return answer;
}

bool run_trials(uint64_t num_elements, uint64_t num_tests) {
  for (uint64_t i = 0; i < num_tests; i++) {
    if (!test_all_numbers(sorting_algorithm, num_elements)) {
      cout << "Failed test_all_numbers"
           << "\n";
      return false;
    }
    if (!test_random_numbers(sorting_algorithm, num_elements)) {
      cout << "Failed test_random_numbers"
           << "\n";
      return false;
    }
    if (!test_ordered_ascending(sorting_algorithm, num_elements)) {
      cout << "Failed test_ordered_asc"
           << "\n";
      return false;
    }
    if (!test_ordered_descending(sorting_algorithm, num_elements)) {
      cout << "Failed test_ordered_des"
           << "\n";
      return false;
    }
  }
  return true;
}

// int main(int argc, char** argv) {
//   if (argc != 3) {
//     cout << "Expected number of elements followed by number of tests to run."
//          << "\n";
//   } else {
//     uint64_t num_elements = atoi(argv[1]);
//     uint64_t num_tests = atoi(argv[2]);
//     bool algorithm_successful = run_trials(num_elements, num_tests) &&
//                                 run_trials(num_elements + 1, num_tests);
//     if (algorithm_successful) {
//       cout << "All tests passed successfully!" << "\n";
//     } else {
//       cout << "Tests failed..." << "\n";
//     }
//   }
// }

void run_random_tests(uint64_t len_and_maxval, uint64_t num_arrays) {
  for (int i = 0; i < num_arrays; i++) {
    test_random_numbers(quicksort, len_and_maxval, len_and_maxval, "Quicksort");
    cout << "\n";
    test_random_numbers(heapsort, len_and_maxval, len_and_maxval, "Heapsort");
    cout << "\n";
    test_random_numbers(mergesort, len_and_maxval, len_and_maxval, "Mergesort");
    cout << "\n";
  }
}

void run_specific_case_algo(void (*algo_to_be_tested)(uint64_t*, uint64_t*),
                            uint64_t* start, uint64_t* end, string name) {
  uint64_t* arrcopy = new uint64_t[end - start];
  memcpy(arrcopy, start, (end - start) * sizeof(uint64_t));
  print_array(start, end);
  cout << name << "\n";
  algo_to_be_tested(start, end);
  print_array(start, end);
  delete[] arrcopy;
}

void run_specific_case(uint64_t* start, uint64_t* end) {
  run_specific_case_algo(quicksort, start, end, "Quicksort");
  cout << "\n";
  run_specific_case_algo(heapsort, start, end, "Heapsort");
  cout << "\n";
  run_specific_case_algo(mergesort, start, end, "Mergesort");
  cout << "\n";
}

void run_tests(uint64_t len_and_maxval, uint64_t num_arrays, uint64_t* start,
               uint64_t* end) {
  run_random_tests(len_and_maxval, num_arrays);
  run_specific_case(start, end);
}

int main(int argc, char** argv) {
  uint64_t len_and_maxval;
  cin >> len_and_maxval;
  uint64_t num_arrays;
  cin >> num_arrays;
  uint64_t num_elements;
  cin >> num_elements;
  uint64_t* numbers = new uint64_t[num_elements];
  for (uint64_t i = 0; i < num_elements; i++) {
    cin >> *(numbers + i);
  }
  run_tests(len_and_maxval, num_arrays, numbers, numbers + num_elements);
  cout << "DONE"
       << "\n";
  // test_random_numbers(mergesort, 1e8, 1e6, "Mergesort");  // BADWOLF
}

// Heap Sort does not work yet.

// Quicksort: 0.087323 seconds on 1e6
// Quicksort: 0.889496 seconds on 1e7
// Quicksort:  14.2216 seconds on 1e8

// Mergesort: 0.407459 seconds on 1e6
// Mergesort: 4.347280 seconds on 1e6
// Mergesort: 46.37960 seconds on 1e8

// People should not have issues with 1e8 elements as that would be 1 GB in
// memory...