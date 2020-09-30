#include <algorithm>  // only for demo of this test_script, remove later
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <random>

#include "QuickSort.cpp"
#include "heapsort.cpp"
#include "mergesort.cc"

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

// void sorting_algorithm(uint64_t* a, uint64_t* b) { sort(a, b); }
// This is our original test-code (imo more comprehensive than yours)
void swap(uint64_t arr[], uint64_t i, uint64_t j) {
  // if (i == 0 || i == 999) cout << i << " paired with: " << j << endl;
  if (i == j) {
    // cout << "RANDOM BROKEN" << endl;
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
           << " val: " << val_in_arr << endl;
    }
    nums[arr[i]] = true;
  }
  for (int i = 0; i < num_elements; i++) {
    if (!nums[i]) {
      cout << "Failed_all_numbers_present: " << i << endl;
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
           << endl;
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
                         uint64_t num_elements) {
  uint64_t* test_array = new uint64_t[num_elements];
  random_device rd;
  uniform_int_distribution<int> distribution(0, INT_MAX);
  for (uint64_t i = 0; i < num_elements; i++) {
    test_array[i] = distribution(rd);
  }
  algo_to_be_tested(test_array, test_array + num_elements);
  bool answer = is_in_order(test_array, num_elements);
  delete[] test_array;
  return answer;
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
      cout << "Failed test_all_numbers" << endl;
      return false;
    }
    if (!test_random_numbers(sorting_algorithm, num_elements)) {
      cout << "Failed test_random_numbers" << endl;
      return false;
    }
    if (!test_ordered_ascending(sorting_algorithm, num_elements)) {
      cout << "Failed test_ordered_asc" << endl;
      return false;
    }
    if (!test_ordered_descending(sorting_algorithm, num_elements)) {
      cout << "Failed test_ordered_des" << endl;
      return false;
    }
  }
  return true;
}

int main(int argc, char** argv) {
  if (argc != 3) {
    cout << "Expected number of elements followed by number of tests to run."
         << endl;
  } else {
    uint64_t num_elements = atoi(argv[1]);
    uint64_t num_tests = atoi(argv[2]);
    bool algorithm_successful = run_trials(num_elements, num_tests) &&
                                run_trials(num_elements + 1, num_tests);
    if (algorithm_successful) {
      cout << "All tests passed successfully!" << endl;
    } else {
      cout << "Tests failed..." << endl;
    }
  }
}

// bool run_tests(uint64_t len_and_maxval, uint64_t num_arrays) {}

// int main(int argc, char** argv) {
//   uint64_t len_and_maxval;
//   cin >> len_and_maxval;
//   uint64_t num_arrays;
//   cin >> num_arrays;
//   run_tests(len_and_maxval, num_arrays);
//   uint64_t num_elements;
//   cin >> num_elements;
//   uint64_t* numbers = new uint64_t[num_elements];
//   for (uint64_t i = 0; i < num_elements; i++) {
//     cin >> *(numbers + i);
//   }
//   for (int i = 0; i < num_elements; i++) {
//     cout << numbers[i] << "\t";
//   }
//   cout << endl;
// }