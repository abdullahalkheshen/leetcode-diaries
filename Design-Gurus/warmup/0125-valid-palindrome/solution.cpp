/**
 * Problem: 125. Valid Palindrome
 * Link: https://leetcode.com/problems/valid-palindrome/
 * Platform: Design-Gurus
 * Difficulty: Easy
 * Tags: String, Two Pointers
 *
 * Date Solved: YYYY-MM-DD
 * Time Taken: XX min
 */

/*
    Problem Statement:
    A phrase is a palindrome if, after converting all uppercase letters into
    lowercase letters and removing all non-alphanumeric characters, it reads
    the same forward and backward. Alphanumeric characters include letters
    and numbers.

    Given a string s, return true if it is a palindrome, or false otherwise.

    Example 1:
    Input: sentence = "A man, a plan, a canal, Panama!"
    Output: true
    Explanation: "amanaplanacanalpanama" is a palindrome.

    Example 2:
    Input: sentence = "Was it a car or a cat I saw?"
    Output: true
    Explanation: "wasitacaroracatisaw" is a palindrome.

    Example 3:
    Input: s = "race a car"
    Output: false
    Explanation: "raceacar" is not a palindrome.

    Constraints:
    - 1 <= s.length <= 2 * 10^5
    - s consists only of printable ASCII characters
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

// ---------------------------------------------------------------------------

// Approach #1: Reverse then Compare

/*
    Intuition:
    A palindrome is a sequence that reads the same backwards as forwards.
    A palindrome, and its reverse, are identical to each other.

    Algorithm:
    1. Create filtered and reversed strings.
    2. Fill alphanumeric chars in the filtered string (converted to lowercase).
    3. Reverse the filtered string.
    4. Compare reversed string with original filtered string.

    Complexity Analysis:
    - Time: O(n), in length n of the string
    - Space: O(n), additional space to store the filtered and reversed strings
*/

class SolutionReverse {
public:
    bool is_palindrome(std::string s) {
        std::string filtered_string, reversed_string;

        for (char ch : s) {
            if (std::isalnum(ch)) {
                filtered_string += std::tolower(ch);
            }
        }

        reversed_string.resize(filtered_string.size());
        std::reverse_copy(filtered_string.begin(), filtered_string.end(),
                          reversed_string.begin());

        return filtered_string == reversed_string;
    }
};

// ---------------------------------------------------------------------------

// Approach #2: Two Pointers

/*
    Intuition:
    Our algorithm can leverage the two-pointer technique where one pointer
    starts at the beginning of the string, and the other one starts at the end.
    The two pointers move towards each other, checking if the characters they
    point to are the same.

    Algorithm:
    1. Set two pointers: 'left' at the start and 'right' at the end.
    2. Enter a while loop which continues until the two pointers cross.
    3. Skip non-alphanumeric characters.
    4. Compare characters at both pointers (case-insensitive).
    5. Return false if mismatch, true if all characters match.

    Complexity Analysis:
    - Time: O(n), we traverse over each character at most once
    - Space: O(1), no extra space required
*/

class Solution {
public:
    bool is_palindrome(std::string s) {
        int left = 0;
        int right = s.size() - 1;

        while (left < right) {
            while (left < right && !std::isalnum(s[left])) {
                left++;
            }
            while (left < right && !std::isalnum(s[right])) {
                right--;
            }

            if (std::tolower(s[left]) != std::tolower(s[right])) {
                return false;
            }

            left++;
            right--;
        }

        return true;
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;

    // Test 1
    bool result1 = sol.is_palindrome("A man, a plan, a canal: Panama");
    std::cout << "Test 1: " << (result1 == true ? "PASS" : "FAIL") << std::endl;

    // Test 2
    bool result2 = sol.is_palindrome("race a car");
    std::cout << "Test 2: " << (result2 == false ? "PASS" : "FAIL") << std::endl;

    // Test 3: Empty string (after filtering)
    bool result3 = sol.is_palindrome(" ");
    std::cout << "Test 3: " << (result3 == true ? "PASS" : "FAIL") << std::endl;

    // Test 4
    bool result4 = sol.is_palindrome("Was it a car or a cat I saw?");
    std::cout << "Test 4: " << (result4 == true ? "PASS" : "FAIL") << std::endl;

    // Test 5
    bool result5 = sol.is_palindrome("hello");
    std::cout << "Test 5: " << (result5 == false ? "PASS" : "FAIL") << std::endl;

    return 0;
}
