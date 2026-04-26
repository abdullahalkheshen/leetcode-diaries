/**
 * Problem: Count Substring Anagrams
 * Link: https://structy.net/
 * Platform: Structy
 * Difficulty: Easy
 * Tags: Sliding Window, String, Hash Map
 *
 * Date Solved:
 * Time Taken:
 */

/*
    Problem Statement:
    Write a function that takes in a string and an anagram. The function
    should return the number of substrings of the string that are anagrams
    of the given anagram.

    You can assume that the anagram is not longer than the string.

    Example 1:
    Input: s = "greyhounds", anagram = "hoy"
    Output: 1
    Explanation: The substring "yho" (index 3-5) is the only anagram of "hoy".

    Example 2:
    Input: s = "abcbacba", anagram = "abc"
    Output: 4
    Explanation: "abc" (0-2), "bcb" — no, "cba" (2-4), "bac" (3-5), "acb" — no,
                 substrings that are anagrams: "abc", "cba", "bac", "cba" → 4.

    Example 3:
    Input: s = "breakdowns", anagram = "snow"
    Output: 1

    Example 4:
    Input: s = "southernly", anagram = "thorny"
    Output: 0

    Example 5:
    Input: s = "aaaaaa", anagram = "aa"
    Output: 5

    Example 6:
    Input: s = "abab", anagram = "ab"
    Output: 3
    Explanation: "ab" (0-1), "ba" (1-2), "ab" (2-3) → 3.

    Constraints:
    - anagram.length <= s.length
*/

#include <iostream>
#include <string>
#include <unordered_map>

// ---------------------------------------------------------------------------

// Approach #1: Fixed Sliding Window with Frequency Maps

/*
    Intuition:
    This is the counting variant of has-substring-anagram. Every anagram of a
    string has the same character frequencies, so two strings are anagrams iff
    their frequency maps match. Since all candidate substrings share the same
    length k (the anagram length), we slide a fixed-size window across s and
    compare frequency maps at each position.

    We only need to check the anagram's keys against the window map (not the
    other way around) because both represent strings of equal length k — if
    every anagram character has the correct count, there's no room for extras.

    Algorithm:
    1. Build anagram_map from the anagram string.
    2. Initialize two pointers left = 0, right = 0, a window_map, and count = 0.
    3. Expand the window by adding s[right] to window_map.
    4. Once the window reaches anagram size (right - left + 1 == k):
       a. Compare window_map against anagram_map — if equal, increment count.
       b. Shrink from the left: decrement window_map[s[left]], then left++.
    5. Increment right to continue sliding.
    6. Return count.

    Complexity Analysis:
    - Time: O(n * k) — n is s.length(), k is anagram.length(); map comparison is O(k)
    - Space: O(k) — both maps hold at most k entries
*/

class Solution {
public:
    bool maps_equal(std::unordered_map<char, int>& window_map, std::unordered_map<char, int>& anagram_map) {
        for (auto& [key, val] : anagram_map) {
            if (window_map[key] != val) return false;
        }
        return true;
    }

    int countSubstringAnagrams(std::string s, std::string anagram) {
        int left = 0;
        int right = 0;
        int count = 0;

        std::unordered_map<char, int> anagram_map;
        std::unordered_map<char, int> window_map;

        for (char c : anagram) anagram_map[c]++;

        while (right < (int)s.size()) {
            window_map[s[right]]++;

            if (right - left + 1 == (int)anagram.size()) {
                if (maps_equal(window_map, anagram_map)) count++;

                window_map[s[left]]--;
                left++;
            }

            right++;
        }

        return count;
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;

    // Test 1
    int result1 = sol.countSubstringAnagrams("greyhounds", "hoy");
    std::cout << "Test 1: " << (result1 == 1 ? "PASS" : "FAIL")
              << " (expected 1, got " << result1 << ")" << std::endl;

    // Test 2
    int result2 = sol.countSubstringAnagrams("abcbacba", "abc");
    std::cout << "Test 2: " << (result2 == 4 ? "PASS" : "FAIL")
              << " (expected 4, got " << result2 << ")" << std::endl;

    // Test 3
    int result3 = sol.countSubstringAnagrams("breakdowns", "snow");
    std::cout << "Test 3: " << (result3 == 1 ? "PASS" : "FAIL")
              << " (expected 1, got " << result3 << ")" << std::endl;

    // Test 4
    int result4 = sol.countSubstringAnagrams("southernly", "thorny");
    std::cout << "Test 4: " << (result4 == 0 ? "PASS" : "FAIL")
              << " (expected 0, got " << result4 << ")" << std::endl;

    // Test 5
    int result5 = sol.countSubstringAnagrams("aaaaaa", "aa");
    std::cout << "Test 5: " << (result5 == 5 ? "PASS" : "FAIL")
              << " (expected 5, got " << result5 << ")" << std::endl;

    // Test 6
    int result6 = sol.countSubstringAnagrams("abab", "ab");
    std::cout << "Test 6: " << (result6 == 3 ? "PASS" : "FAIL")
              << " (expected 3, got " << result6 << ")" << std::endl;

    return 0;
}
