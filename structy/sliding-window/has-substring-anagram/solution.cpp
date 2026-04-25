/**
 * Problem: Has Substring Anagram
 * Link: https://structy.net/
 * Platform: Structy
 * Difficulty: Easy
 * Tags: Sliding Window, String, Hash Map
 *
 * Date Solved: 2026-04-25
 * Time Taken:
 */

/*
    Problem Statement:
    Write a function that takes in a string and an anagram. The function
    should return a boolean indicating whether or not the string contains
    a substring with the same characters as the anagram.

    You can assume that the string contains no duplicate characters.
    You can assume that the anagram contains no duplicate characters.
    You can assume that the anagram is not longer than the string.

    Example 1:
    Input: s = "greyhounds", anagram = "hoy"
    Output: true
    Explanation: The substring "yho" is an anagram of "hoy".

    Example 2:
    Input: s = "gruyheonds", anagram = "hoy"
    Output: false

    Example 3:
    Input: s = "breakdowns", anagram = "snow"
    Output: true

    Example 4:
    Input: s = "dermatoglyphics", anagram = "red"
    Output: true

    Example 5:
    Input: s = "southernly", anagram = "thorny"
    Output: false

    Constraints:
    - anagram.length <= s.length
    - No duplicate characters in s or anagram
*/

#include <iostream>
#include <string>
#include <unordered_map>

// ---------------------------------------------------------------------------

// Approach #1: Fixed Sliding Window with Frequency Maps

/*
    Intuition:
    We can use a sliding window to check if the substring is an anagram of the anagram.
    We can use a hash map to store the frequency of the characters in the substring and the anagram.
    We can then slide the window across the string and check if the substring is an anagram of the anagram.
    If the substring is an anagram of the anagram, we return true.
    Otherwise, we return false.

    Algorithm:
    1. Build anagram_map from the anagram string.
    2. Initialize two pointers i = 0, j = 0 and a window_map.
    3. Expand the window by adding s[j] to window_map.
    4. Once the window reaches anagram size (j - i + 1 == k):
       a. Compare window_map against anagram_map — if equal, return true.
       b. Shrink from the left: decrement window_map[s[i]], erase if zero, increment i.
    5. Increment j to continue sliding.
    6. If no match found, return false.

    Complexity Analysis:
    - Time: O(n * k) — n is s.length(), k is anagram.length(); map comparison is O(k)
    - Space: O(k) — both maps hold at most k entries
*/

class Solution {
public:
    bool is_anagram(std::unordered_map<char, int>& window, std::unordered_map<char, int>& need) {
        for (auto& [c, count] : need) {
            if (window[c] != count) return false;
        }
        return true;
    }

    bool hasSubstringAnagram(std::string s, std::string anagram) {
        int i = 0;
        int j = 0;
        std::unordered_map<char, int> need;
        std::unordered_map<char, int> window;

        for (char c : anagram) need[c]++;

        while (j < (int)s.size()) {
            window[s[j]]++;
            if (j - i + 1 == (int)anagram.size()) {
                if (is_anagram(window, need)) return true;
                window[s[i]]--;
                i++;
            }
            j++;
        }
        return false;
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;
    // Test 1
    bool result1 = sol.hasSubstringAnagram("greyhounds", "hoy");
    std::cout << "Test 1: " << (result1 == true ? "PASS" : "FAIL")
              << " (expected true, got " << (result1 ? "true" : "false") << ")" << std::endl;

    // Test 2
    bool result2 = sol.hasSubstringAnagram("gruyheonds", "hoy");
    std::cout << "Test 2: " << (result2 == false ? "PASS" : "FAIL")
              << " (expected false, got " << (result2 ? "true" : "false") << ")" << std::endl;

    // Test 3
    bool result3 = sol.hasSubstringAnagram("breakdowns", "snow");
    std::cout << "Test 3: " << (result3 == true ? "PASS" : "FAIL")
              << " (expected true, got " << (result3 ? "true" : "false") << ")" << std::endl;

    // Test 4
    bool result4 = sol.hasSubstringAnagram("dermatoglyphics", "red");
    std::cout << "Test 4: " << (result4 == true ? "PASS" : "FAIL")
              << " (expected true, got " << (result4 ? "true" : "false") << ")" << std::endl;

    // Test 5
    bool result5 = sol.hasSubstringAnagram("southernly", "thorny");
    std::cout << "Test 5: " << (result5 == false ? "PASS" : "FAIL")
              << " (expected false, got " << (result5 ? "true" : "false") << ")" << std::endl;

    return 0;
}
