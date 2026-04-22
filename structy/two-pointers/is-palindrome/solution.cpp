/**
 * Problem: Is Palindrome
 * Link: https://structy.net/problems/premium/is-palindrome
 * Platform: Structy
 * Difficulty: Easy
 * Tags: Two Pointers, String
 *
 * Date Solved: 2026-04-22
 * Time Taken: 
 */

/*
    Problem Statement:
    Write a function that takes in a string and returns a boolean indicating
    whether or not it is a palindrome. A palindrome is a string that reads the
    same forwards and backwards.

    Example 1:
    Input: s = "abcba"
    Output: true
    Explanation: "abcba" reads the same forwards and backwards

    Example 2:
    Input: s = "amanaplanacanalpanama"
    Output: true
    Explanation: Classic palindrome phrase (without spaces)

    Example 3:
    Input: s = "abcdef"
    Output: false
    Explanation: "abcdef" reversed is "fedcba", not the same

    Example 4:
    Input: s = ""
    Output: true
    Explanation: An empty string is considered a palindrome

    Example 5:
    Input: s = "a"
    Output: true
    Explanation: A single character is always a palindrome

    Constraints:
    - The input is a string of characters
    - Comparison is case-sensitive and includes all characters
*/

#include <iostream>
#include <string>

// ---------------------------------------------------------------------------

// Approach #1: Two Pointers

/*
    Intuition:
    

    Algorithm:
    

    Complexity Analysis:
    - Time: O(n) where n is the length of the string
    - Space: O(1) constant extra space
*/

class Solution {
public:
    bool isPalindrome(std::string s) {
        int l=0;
        int r=s.size()-1;
        while (l<r) {
            while(l<r && !isalnum(s[l])) l++;
            while(l<r && !isalnum(s[r])) r--;

            if(tolower(s[l]) != tolower(s[r])) return false;
            l++;
            r--;
        }
        return true;
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;

    // Test 1: Odd-length palindrome
    std::string s1 = "abcba";
    bool result1 = sol.isPalindrome(s1);
    std::cout << "Test 1: " << (result1 == true ? "PASS" : "FAIL")
              << " (expected true, got " << (result1 ? "true" : "false") << ")" << std::endl;

    // Test 2: Long palindrome
    std::string s2 = "amanaplanacanalpanama";
    bool result2 = sol.isPalindrome(s2);
    std::cout << "Test 2: " << (result2 == true ? "PASS" : "FAIL")
              << " (expected true, got " << (result2 ? "true" : "false") << ")" << std::endl;

    // Test 3: Not a palindrome
    std::string s3 = "abcdef";
    bool result3 = sol.isPalindrome(s3);
    std::cout << "Test 3: " << (result3 == false ? "PASS" : "FAIL")
              << " (expected false, got " << (result3 ? "true" : "false") << ")" << std::endl;

    // Test 4: Empty string
    std::string s4 = "";
    bool result4 = sol.isPalindrome(s4);
    std::cout << "Test 4: " << (result4 == true ? "PASS" : "FAIL")
              << " (expected true, got " << (result4 ? "true" : "false") << ")" << std::endl;

    // Test 5: Single character
    std::string s5 = "a";
    bool result5 = sol.isPalindrome(s5);
    std::cout << "Test 5: " << (result5 == true ? "PASS" : "FAIL")
              << " (expected true, got " << (result5 ? "true" : "false") << ")" << std::endl;

    // Test 6: Even-length palindrome
    std::string s6 = "abba";
    bool result6 = sol.isPalindrome(s6);
    std::cout << "Test 6: " << (result6 == true ? "PASS" : "FAIL")
              << " (expected true, got " << (result6 ? "true" : "false") << ")" << std::endl;

    return 0;
}
