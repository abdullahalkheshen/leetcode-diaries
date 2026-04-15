/**
 * Problem: 242. Valid Anagram
 * Link: https://leetcode.com/problems/valid-anagram/
 * Platform: Design-Gurus
 * Difficulty: Easy
 * Tags: Hash Table, String, Sorting
 *
 * Date Solved: YYYY-MM-DD
 * Time Taken: XX min
 */

/*
    Problem Statement:
    Given two strings s and t, return true if t is an anagram of s, and false
    otherwise.

    An Anagram is a word or phrase formed by rearranging the letters of a
    different word or phrase, typically using all the original letters exactly
    once.

    Example 1:
    Input: s = "listen", t = "silent"
    Output: true

    Example 2:
    Input: s = "rat", t = "car"
    Output: false

    Example 3:
    Input: s = "hello", t = "world"
    Output: false

    Constraints:
    - 1 <= s.length, t.length <= 5 * 10^4
    - s and t consist of lowercase English letters
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

// ---------------------------------------------------------------------------

// Approach #1: Sorting

/*
    Intuition:
    An anagram is produced by rearranging the letters of s into t. Therefore,
    if t is an anagram of s, sorting both strings will result in two identical
    strings. Furthermore, if s and t have different lengths, t must not be an
    anagram of s and we can return early.

    Algorithm:
    1. If the size of both strings aren't equal, directly return false.
    2. Sort both strings.
    3. Return the boolean of the comparison.

    Complexity Analysis:
    - Time: O(n log n), sorting costs O(n log n) and comparing costs O(n)
    - Space: O(1), if heapsort is used (depends on sorting implementation)
*/

class SolutionSorting {
public:
    bool is_anagram(std::string s, std::string t) {
        if (s.size() != t.size()) return false;

        std::sort(s.begin(), s.end());
        std::sort(t.begin(), t.end());

        return s == t;
    }
};

// ---------------------------------------------------------------------------

// Approach #2: Frequency Counter (Vector)

/*
    Intuition:
    To solve the anagram problem, we can count the frequency of each letter in
    both strings and compare them. If the frequencies of all letters are the
    same in both strings, then the two strings are anagrams of each other.

    Algorithm:
    1. Create an integer array freq of length 26 to track the frequency of each
       letter in the two strings.
    2. Loop through each character in both strings and increment the frequency
       of the corresponding letter in s and decrement for t.
    3. Finally, loop through the freq array and check if all frequencies are zero.

    Complexity Analysis:
    - Time: O(n), where n is the length of the strings
    - Space: O(1), size of freq array is constant (26)
*/

class Solution {
public:
    bool is_anagram(std::string s, std::string t) {
        if (s.length() != t.length()) return false;

        std::vector<int> freq(26, 0);

        for (size_t i = 0; i < s.length(); i++) {
            freq[s[i] - 'a']++;
            freq[t[i] - 'a']--;
        }

        for (int count : freq) {
            if (count != 0) return false;
        }

        return true;
    }
};

// ---------------------------------------------------------------------------

// Approach #3: Frequency Counter (HashMap)

/*
    Intuition:
    Same as Approach #2, but using a HashMap instead of a fixed-size array.
    This approach is more flexible and can handle Unicode characters.

    Algorithm:
    1. Declare a map to store character frequencies.
    2. Iterate through both strings, incrementing for s and decrementing for t.
    3. Check if all frequencies are zero.

    Complexity Analysis:
    - Time: O(n), where n is the length of the strings
    - Space: O(1), at most 26 characters in the map
*/

class SolutionHashMap {
public:
    bool is_anagram(std::string s, std::string t) {
        if (s.size() != t.size()) return false;

        std::unordered_map<char, int> counter;

        for (size_t i = 0; i < s.length(); i++) {
            counter[s[i]]++;
            counter[t[i]]--;
        }

        for (auto& pair : counter) {
            if (pair.second != 0) return false;
        }

        return true;
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;

    // Test 1
    bool result1 = sol.is_anagram("listen", "silent");
    std::cout << "Test 1: " << (result1 == true ? "PASS" : "FAIL") << std::endl;

    // Test 2
    bool result2 = sol.is_anagram("rat", "car");
    std::cout << "Test 2: " << (result2 == false ? "PASS" : "FAIL") << std::endl;

    // Test 3
    bool result3 = sol.is_anagram("hello", "world");
    std::cout << "Test 3: " << (result3 == false ? "PASS" : "FAIL") << std::endl;

    // Test 4
    bool result4 = sol.is_anagram("anagram", "nagaram");
    std::cout << "Test 4: " << (result4 == true ? "PASS" : "FAIL") << std::endl;

    // Test 5: Different lengths
    bool result5 = sol.is_anagram("ab", "abc");
    std::cout << "Test 5: " << (result5 == false ? "PASS" : "FAIL") << std::endl;

    return 0;
}
