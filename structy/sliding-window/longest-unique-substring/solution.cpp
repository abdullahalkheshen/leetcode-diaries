/**
 * Problem: Longest Unique Substring
 * Link: https://structy.net/
 * Platform: Structy
 * Difficulty: Medium
 * Tags: Sliding Window, String, Hash Set, Variable-Size Window
 *
 * Date Solved: 2026-04-30
 * Time Taken:
 */

/*
    Problem Statement:
    Write a function that takes in a string as an argument. The function should
    return the length of the longest substring that consists of only unique
    characters.

    Example 1:
    Input: s = "abccba"
    Output: 3
    Explanation: Longest substring with all unique chars is "abc" (length 3).

    Example 2:
    Input: s = "aabcdea"
    Output: 5
    Explanation: Longest substring with all unique chars is "bcdea" (length 5).

    Example 3:
    Input: s = "aaaaa"
    Output: 1
    Explanation: Longest substring with all unique chars is "a" (length 1).

    Example 4:
    Input: s = ""
    Output: 0

    Constraints:
    - 0 <= s.length <= 10^5
    - s consists of printable ASCII characters
*/

#include <iostream>
#include <string>
#include <unordered_set>
#include <algorithm>

// ---------------------------------------------------------------------------

// Approach #1: Variable-Size Sliding Window with Hash Set

/*
    Intuition:
    Maintain a window [i..j] where all characters are unique. Use a hash set
    to track which characters are currently in the window. When we encounter
    a duplicate at s[j], shrink the window from the left (removing s[i] from
    the set and advancing i) until the duplicate is gone. At every valid
    window, check if its length is the longest seen so far.

    Algorithm:
    1. Initialize two pointers i = 0, j = 0, a hash set, and longest = 0.
    2. While s[j] is already in the set, remove s[i] and increment i (shrink).
    3. Insert s[j] into the set (expand window).
    4. Update longest = max(longest, j - i + 1).
    5. Increment j and repeat.
    6. Return longest.

    Complexity Analysis:
    - Time: O(n) — each character is added and removed from the set at most once
    - Space: O(min(n, m)) — where m is the size of the character set (e.g. 128 for ASCII)
*/

class Solution {
public:
    int longestUniqueSubstring(std::string s) {
        int i = 0, j = 0;
        int longest = 0;
        std::unordered_set<char> unique_chars;

        while (j < s.size()) {
            while (!unique_chars.insert(s[j]).second) {
                unique_chars.erase(s[i++]);
            }
            longest = std::max(longest, j - i + 1);
            j++;
        }

        return longest;
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;

    // Test 1: Basic case with duplicate in middle
    int result1 = sol.longestUniqueSubstring("abccba");
    std::cout << "Test 1: " << (result1 == 3 ? "PASS" : "FAIL")
              << " (expected 3, got " << result1 << ")" << std::endl;

    // Test 2: Duplicate at boundaries
    int result2 = sol.longestUniqueSubstring("aabcdea");
    std::cout << "Test 2: " << (result2 == 5 ? "PASS" : "FAIL")
              << " (expected 5, got " << result2 << ")" << std::endl;

    // Test 3: All same characters
    int result3 = sol.longestUniqueSubstring("aaaaa");
    std::cout << "Test 3: " << (result3 == 1 ? "PASS" : "FAIL")
              << " (expected 1, got " << result3 << ")" << std::endl;

    // Test 4: Empty string
    int result4 = sol.longestUniqueSubstring("");
    std::cout << "Test 4: " << (result4 == 0 ? "PASS" : "FAIL")
              << " (expected 0, got " << result4 << ")" << std::endl;

    // Test 5: All unique characters
    int result5 = sol.longestUniqueSubstring("abcdef");
    std::cout << "Test 5: " << (result5 == 6 ? "PASS" : "FAIL")
              << " (expected 6, got " << result5 << ")" << std::endl;

    // Test 6: Single character
    int result6 = sol.longestUniqueSubstring("a");
    std::cout << "Test 6: " << (result6 == 1 ? "PASS" : "FAIL")
              << " (expected 1, got " << result6 << ")" << std::endl;

    // Test 7: Longest at the end
    int result7 = sol.longestUniqueSubstring("aabcdefgh");
    std::cout << "Test 7: " << (result7 == 8 ? "PASS" : "FAIL")
              << " (expected 8, got " << result7 << ")" << std::endl;

    return 0;
}
