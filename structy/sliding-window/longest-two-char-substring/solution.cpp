/**
 * Problem: Longest Two Character Substring
 * Link: https://structy.net/
 * Platform: Structy
 * Difficulty: Medium
 * Tags: Sliding Window, String, Hash Map, Variable-Size Window
 *
 * Date Solved: 2026-04-30
 * Time Taken:
 */

/*
    Problem Statement:
    Write a function that takes in a string as an argument. The function should
    return the length of the longest substring that contains at most two unique
    characters.

    Example 1:
    Input: s = "aabcbcba"
    Output: 5
    Explanation: Longest substring with at most 2 unique chars is "bcbcb" (length 5).

    Example 2:
    Input: s = "cccccc"
    Output: 6
    Explanation: Entire string uses only 1 unique char, which is <= 2.

    Example 3:
    Input: s = "abcabcabc"
    Output: 2
    Explanation: No substring longer than 2 has at most 2 unique chars.

    Example 4:
    Input: s = "aab"
    Output: 3
    Explanation: Entire string "aab" has 2 unique chars.

    Constraints:
    - 0 <= s.length <= 10^5
    - s consists of lowercase English letters
*/

#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

// ---------------------------------------------------------------------------

// Approach #1: Variable-Size Sliding Window with Hash Map (Frequency Count)

/*
    Intuition:
    Maintain a window [i..j] where the number of distinct characters is at most
    2. Use a hash map to track the frequency of each character in the current
    window. When adding s[j] causes the distinct count to exceed 2, shrink from
    the left by decrementing frequencies and removing characters whose count
    drops to 0.

    Algorithm:
    1. Initialize two pointers i = 0, j = 0, a frequency map, and longest = 0.
    2. Increment freq[s[j]] (expand window).
    3. While map.size() > 2, decrement freq[s[i]]; if it reaches 0, erase it; increment i.
    4. Update longest = max(longest, j - i + 1).
    5. Increment j and repeat.
    6. Return longest.

    Complexity Analysis:
    - Time: O(n) — each character is added and removed from the window at most once
    - Space: O(1) — the map holds at most 3 entries before shrinking
*/

class Solution {
public:
    int longestTwoCharSubstring(std::string s) {
        int i = 0, j = 0;
        int longest = 0;
        std::unordered_map<char, int> freq;

        while (j < s.size()) {
            freq[s[j]]++;

            while (freq.size() > 2) {
                freq[s[i]]--;
                if (freq[s[i]] == 0) freq.erase(s[i]);
                i++;
            }
            if (freq.size() == 2)
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

    // Test 1: Mixed characters, longest is in the middle
    int result1 = sol.longestTwoCharSubstring("aabcbcba");
    std::cout << "Test 1: " << (result1 == 5 ? "PASS" : "FAIL")
              << " (expected 5, got " << result1 << ")" << std::endl;

    // Test 2: All same characters
    int result2 = sol.longestTwoCharSubstring("cccccc");
    std::cout << "Test 2: " << (result2 == 6 ? "PASS" : "FAIL")
              << " (expected 6, got " << result2 << ")" << std::endl;

    // Test 3: Alternating 3 characters
    int result3 = sol.longestTwoCharSubstring("abcabcabc");
    std::cout << "Test 3: " << (result3 == 2 ? "PASS" : "FAIL")
              << " (expected 2, got " << result3 << ")" << std::endl;

    // Test 4: Entire string fits
    int result4 = sol.longestTwoCharSubstring("aab");
    std::cout << "Test 4: " << (result4 == 3 ? "PASS" : "FAIL")
              << " (expected 3, got " << result4 << ")" << std::endl;

    // Test 5: Empty string
    int result5 = sol.longestTwoCharSubstring("");
    std::cout << "Test 5: " << (result5 == 0 ? "PASS" : "FAIL")
              << " (expected 0, got " << result5 << ")" << std::endl;

    // Test 6: Two characters only
    int result6 = sol.longestTwoCharSubstring("ababababab");
    std::cout << "Test 6: " << (result6 == 10 ? "PASS" : "FAIL")
              << " (expected 10, got " << result6 << ")" << std::endl;

    // Test 7: Single character
    int result7 = sol.longestTwoCharSubstring("a");
    std::cout << "Test 7: " << (result7 == 1 ? "PASS" : "FAIL")
              << " (expected 1, got " << result7 << ")" << std::endl;

    // Test 8: Longest at the end
    int result8 = sol.longestTwoCharSubstring("abcbbbbbb");
    std::cout << "Test 8: " << (result8 == 7 ? "PASS" : "FAIL")
              << " (expected 7, got " << result8 << ")" << std::endl;

    return 0;
}
