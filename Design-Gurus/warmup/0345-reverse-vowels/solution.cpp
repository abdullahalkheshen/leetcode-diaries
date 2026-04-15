/**
 * Problem: 345. Reverse Vowels of a String
 * Link: https://leetcode.com/problems/reverse-vowels-of-a-string/
 * Platform: Design-Gurus
 * Difficulty: Easy
 * Tags: String, Two Pointers
 *
 * Date Solved: YYYY-MM-DD
 * Time Taken: XX min
 */

/*
    Problem Statement:
    Given a string s, reverse only all the vowels in the string and return it.
    The vowels are 'a', 'e', 'i', 'o', and 'u', and they can appear in both
    lower and upper cases, more than once.

    Example 1:
    Input: s = "hello"
    Output: "holle"

    Example 2:
    Input: s = "AEIOU"
    Output: "UOIEA"

    Example 3:
    Input: s = "DesignGUrus"
    Output: "DussgnGires"

    Constraints:
    - 1 <= s.length <= 3 * 10^5
    - s consist of printable ASCII characters
*/

#include <iostream>
#include <string>
#include <unordered_set>
#include <algorithm>

// ---------------------------------------------------------------------------

// Approach #1: Two Pointers with HashSet

/*
    Intuition:
    We can use the two-pointer technique to traverse the string from both ends
    simultaneously. Whenever a vowel is encountered at both ends, we will swap
    them. The process will continue until the two pointers meet in the middle.

    Algorithm:
    1. Create a set containing all lowercase and uppercase vowels.
    2. Initialize i and j pointers at the start and end of the string.
    3. Enter a while loop that continues while i < j.
    4. Keep iterating until we find a vowel at both edges (i and j).
    5. Once we've found a vowel at both pointers, swap these vowels.
    6. After the swap, increment i and decrement j.
    7. Return the modified string.

    Complexity Analysis:
    - Time: O(n), each element is iterated only once either by left or right pointer
    - Space: O(1), only need an extra temporary variable to perform the swap
*/

class Solution {
public:
    std::string reverse_vowels(std::string s) {
        int i = 0, j = s.length() - 1;
        std::unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};

        while (i < j) {
            if (vowels.count(s[i]) == 0)
                i++;
            else if (vowels.count(s[j]) == 0)
                j--;
            else
                std::swap(s[i++], s[j--]);
        }
        return s;
    }
};

// ---------------------------------------------------------------------------

// Approach #2: Two Pointers with Helper Function

/*
    Intuition:
    Same as Approach #1, but using a helper function to check if a character
    is a vowel instead of a HashSet.

    Algorithm:
    1. Create a helper function isVowel that checks if a character is a vowel.
    2. Use two pointers from both ends.
    3. Swap vowels when found at both positions.

    Complexity Analysis:
    - Time: O(n)
    - Space: O(1)
*/

class SolutionHelper {
private:
    bool is_vowel(char c) {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
               c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
    }

public:
    std::string reverse_vowels(std::string s) {
        int i = 0, j = s.length() - 1;

        while (i < j) {
            if (!is_vowel(s[i]))
                i++;
            else if (!is_vowel(s[j]))
                j--;
            else
                std::swap(s[i++], s[j--]);
        }
        return s;
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;

    // Test 1
    std::string result1 = sol.reverse_vowels("hello");
    std::cout << "Test 1: " << (result1 == "holle" ? "PASS" : "FAIL") << std::endl;

    // Test 2
    std::string result2 = sol.reverse_vowels("AEIOU");
    std::cout << "Test 2: " << (result2 == "UOIEA" ? "PASS" : "FAIL") << std::endl;

    // Test 3
    std::string result3 = sol.reverse_vowels("leetcode");
    std::cout << "Test 3: " << (result3 == "leotcede" ? "PASS" : "FAIL") << std::endl;

    // Test 4: No vowels
    std::string result4 = sol.reverse_vowels("bcdfg");
    std::cout << "Test 4: " << (result4 == "bcdfg" ? "PASS" : "FAIL") << std::endl;

    return 0;
}
