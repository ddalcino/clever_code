// This program shows off 3 different ways of calculating a palindrome
// in C++
// By: Nick from CoffeeBeforeArch

#include <algorithm>
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::equal;
using std::reverse;
using std::string;

// Compares letters at the front to those at the back
// A little ugly! Not easily apparent what the purpose of the loop and
// conditional check is doing
bool isPalindromeBad(const string &s) {
  // Get the size of the string
  std::size_t size = s.size();

  // Get the stopping point for comparison
  auto stop = size / 2;

  // Check the first half of the string to the second half
  for (std::size_t i = 0; i < stop; i++) {
    // Compare both sides of the string and see if they are the same
    if (s[i] != s[size - i - 1]) {
      // If !=, it's not a palindrome
      return false;
    }
  }

  // Otherwise, it is!
  return true;
}

// Let's just reverse the string and compare against it!
// Slightly more expensive. Reverse has to do (last - first) / 2 swaps
// We also have to create a temporary (input is const)
bool isPalindromeBetter1(const string &s) {
  string r(s);
  reverse(begin(r), end(r));
  return s == r;
}

// Similar to the previous solution, but we can just use reverse
// iterators
bool isPalindromeBetter2(const string &s) {
  string r(rbegin(s), rend(s));
  return s == r;
}

// As (almost) always, there's an STL function to the rescue
// Will be better performance that reversal then comparison
// No messy code like the first example
bool isPalindromeBest(const string &s) {
  // Use the equal function!
  // Size of the comparison is determined from the first two iterators,
  // so we don't have to pass rend(s) to the function.
  // We also don't need to create a temp variable
  return equal(begin(s), end(s), rbegin(s));
}

bool isPalindromeBestTimes2(const string &s) {
  const auto num_necessary_compares = s.size() / 2;
  return equal(begin(s), begin(s) + num_necessary_compares, rbegin(s));
}

int main() {
  // Our input palindrome
  string s1("rotor");

  // Test each of our functions
  bool sol1 = isPalindromeBad(s1);
  bool sol2 = isPalindromeBetter1(s1);
  bool sol3 = isPalindromeBetter2(s1);
  bool sol4 = isPalindromeBest(s1);
  bool sol5 = isPalindromeBestTimes2(s1);

  // Print the solution
  cout << sol1 << endl;
  cout << sol2 << endl;
  cout << sol3 << endl;
  cout << sol4 << endl;
  cout << sol5 << endl;

  return 0;
}
