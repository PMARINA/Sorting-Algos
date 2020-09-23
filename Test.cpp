#include <algorithm>  // only for demo of this test_script, remove later
#include <cstdint>
#include <iostream>
using std::cout;
using std::endl;
using std::sort;  // only for demo of this test_script, remove later

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

void (*sorting_algorithm)(uint64_t*, uint64_t*) = sort;

// void sorting_algorithm(uint64_t* a, uint64_t* b) { sort(a, b); }

void swap(uint64_t arr[], uint64_t i, uint64_t j) {
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

bool test_all_numbers(void (*algo_to_be_tested)(uint64_t*, uint64_t*),
                      uint64_t num_elements) {
  // Create a test array that's sorted.
  uint64_t* test_array = new uint64_t[num_elements];
  for (uint64_t i = 0; i < num_elements; i++) {
    test_array[i] = i;
  }

  for (uint64_t i = 0; i < num_elements; i++) {
    swap(test_array, i,
         uint64_t(double(rand()) / (RAND_MAX) * (num_elements - i)) + i);
  }

  algo_to_be_tested(test_array, test_array + num_elements);
  return is_in_order(test_array, num_elements);
}
bool test_random_numbers(void (*algo_to_be_tested)(uint64_t*, uint64_t*),
                         uint64_t num_elements) {
  uint64_t* test_array = new uint64_t[num_elements];
  for (uint64_t i = 0; i < num_elements; i++) {
    test_array[i] = uint64_t(double(rand()) / RAND_MAX * UINT64_MAX);
  }
  algo_to_be_tested(test_array, test_array + num_elements);
  return is_in_order(test_array, num_elements);
}
bool run_trials(uint64_t num_elements, uint64_t num_tests) {
  for (uint64_t i = 0; i < num_tests; i++) {
    if (!test_all_numbers(sorting_algorithm, num_elements)) return false;
    if (!test_random_numbers(sorting_algorithm, num_elements)) return false;
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