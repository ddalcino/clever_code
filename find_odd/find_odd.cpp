// This program shows a clever way to find which number appears an odd
// number of times in a vector (assumes there is only 1 that fits this
// criteria).
// By: Nick from CoffeeBeforeArch

#include <functional>
#include <iostream>
#include <numeric>
#include <vector>
#include <execution>
#include <benchmark/benchmark.h>
#include <memory>

using std::accumulate;
using std::bit_xor;
using std::cout;
using std::endl;
using std::vector;

// Bad implementation of findOdd
// Compares every element against every other element
// Earliest it can exit is after one full scan of the vector
int findOddBad(const vector<int> &v) {
  // For each element in the vector
  for (auto i : v) {
    // Compare against all other vector elements
    int tmp = 0;
    for (auto j : v) {
      // Increment if we found an instance of "i"
      if (j == i) {
        tmp++;
      }
    }
    // If it appeared an odd number of times, we found the answer
    if (tmp % 2) {
      return i;
    }
  }

  // Returns 0 otherwise
  return 0;
}

// Always completes 1 full scan of the array
// Perform bit-wise XOR all elements together
// Background:
//  1.) XOR is an associative and commutative operation
//  2.) n XOR n = 0 (any number XOR itself is 0)
//  3.) n XOR 0 = n (any number XOR 0 is itself)
// Explanation:
//  The XOR of all even-count elements together is 0 because of (2).
//  The XOR of all odd-count elements together is "n" because of (2)
//  and (3).
//  Performing this operations can occur in any order because of (1),
//  so we can just intuitively XOR from the beginning to the end.
// Much better than the previous, but still a little "old-fashioned"
int findOddBetter(const vector<int> &v) {
  // Accumulate partial results in tmp
  int tmp = 0;

  // Bit-wise XOR of all elements
  for (auto i : v) {
    tmp ^= i;
  }

  return tmp;
}

// How about 1 line of code!
// Performs the same operation as the above, but we're making use of
// the STL!
int findOddBest(const vector<int> &v) {
  // Bit-wise XOR of all elements
  return accumulate(begin(v), end(v), 0, bit_xor<>());
}

int findOddBest17(const vector<int> &v) {
  // Bit-wise XOR of all elements
  return reduce(std::execution::par, begin(v), end(v), 0, bit_xor<>());
}

// Create a vector
static const vector<int> makeTestVec() {
  vector<int> v = vector<int>(static_cast<size_t>(1'000'000ull), 5);
  v.emplace_back(1);
  return v;
}
static const vector<int> &testVector() {
  static const vector<int> v{makeTestVec()};
  return v;
}

// Helper function that prevents elision of the whole test during a release build
void dont_elide_me(bool b) {
  if (!b)
    exit(1);
}

static void BM_findOddBad(benchmark::State &state) {
  for (auto _ : state)
    dont_elide_me(findOddBad(testVector()));
}
// Register the function as a benchmark
BENCHMARK(BM_findOddBad);

static void BM_findOddBetter(benchmark::State &state) {
  for (auto _ : state)
    dont_elide_me(findOddBetter(testVector()));
}
// Register the function as a benchmark
BENCHMARK(BM_findOddBetter);

static void BM_findOddBest(benchmark::State &state) {
  for (auto _ : state)
    dont_elide_me(findOddBest(testVector()));
}
// Register the function as a benchmark
BENCHMARK(BM_findOddBest);

static void BM_findOddBest17(benchmark::State &state) {
  for (auto _ : state)
    dont_elide_me(findOddBest17(testVector()));
}
// Register the function as a benchmark
BENCHMARK(BM_findOddBest17);

BENCHMARK_MAIN();

