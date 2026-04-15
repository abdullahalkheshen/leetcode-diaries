/**
 * Problem: 438. Find All Anagrams in a String
 * Link: https://leetcode.com/problems/find-all-anagrams-in-a-string/
 * Platform: Design-Gurus
 * Difficulty: Hard
 * Tags: Sliding Window, Hash Table, String
 *
 * Date Solved: YYYY-MM-DD
 * Time Taken: XX min
 */

/*
    Problem Statement:
    Given a string and a pattern, find all anagrams of the pattern in the given string.
    Every anagram is a permutation of a string. When we are not allowed to repeat 
    characters while finding permutations of a string, we get N! permutations (or anagrams) 
    of a string having N characters.

    For example, here are the six anagrams of the string "abc":
    abc, acb, bac, bca, cab, cba

    Write a function to return a list of starting indices of the anagrams of the 
    pattern in the given string.

    Example 1:
    Input: String="ppqp", Pattern="pq"  
    Output: [1, 2]  
    Explanation: The two anagrams of the pattern in the given string are "pq" and "qp".

    Example 2:
    Input: String="abbcabc", Pattern="abc"  
    Output: [2, 3, 4]  
    Explanation: The three anagrams of the pattern in the given string are "bca", "cab", and "abc".

    Constraints:
    - 1 <= s.length, p.length <= 3 * 10^4
    - s and p consist of lowercase English letters
*/

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

// ---------------------------------------------------------------------------

// Approach #1: Sliding Window with Character Matching

/*
    Intuition:
    Use a sliding window of size equal to the pattern length. Track how many 
    distinct characters have their required frequency fully matched. When all 
    characters are matched, we found an anagram starting at window_start.

    Algorithm:
    1. Create a frequency map of the pattern
    2. Slide a window of pattern length over the string
    3. When adding a character, decrement its count in map
    4. When count reaches 0, increment matched (character fully matched)
    5. When matched equals map size, record window_start as anagram position
    6. When removing a character, if its count was 0, decrement matched
    7. Increment the count back in the map

    Complexity Analysis:
    - Time: O(n + m) where n is string length, m is pattern length
    - Space: O(m) for the frequency map
*/

class Solution {
public:
    std::vector<int> find_anagrams(std::string s, std::string p) {
        int matched = 0;
        int window_start = 0;
        
        std::unordered_map<char, int> char_map;
        for (auto chr : p) {
            char_map[chr]++;
        }

        std::vector<int> result;

        for (int window_end = 0; window_end < (int)s.size(); window_end++) {
            if (char_map.find(s[window_end]) != char_map.end()) {
                char_map[s[window_end]]--;
                if (char_map[s[window_end]] == 0) {
                    matched++;
                }
            }

            if (matched == (int)char_map.size()) {
                result.push_back(window_start);
            }

            if (window_end >= (int)p.length() - 1) {
                if (char_map.find(s[window_start]) != char_map.end()) {
                    if (char_map[s[window_start]] == 0) {
                        matched--;
                    }
                    char_map[s[window_start]]++;
                }
                window_start++;
            }
        }
        return result;
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;
    
    // Test 1
    std::vector<int> result1 = sol.find_anagrams("ppqp", "pq");
    std::vector<int> expected1 = {1, 2};
    bool pass1 = (result1 == expected1);
    std::cout << "Test 1: " << (pass1 ? "PASS" : "FAIL");
    std::cout << " (got: [";
    for (size_t i = 0; i < result1.size(); i++) {
        std::cout << result1[i] << (i < result1.size() - 1 ? ", " : "");
    }
    std::cout << "])" << std::endl;
    
    // Test 2
    std::vector<int> result2 = sol.find_anagrams("abbcabc", "abc");
    std::vector<int> expected2 = {2, 3, 4};
    bool pass2 = (result2 == expected2);
    std::cout << "Test 2: " << (pass2 ? "PASS" : "FAIL");
    std::cout << " (got: [";
    for (size_t i = 0; i < result2.size(); i++) {
        std::cout << result2[i] << (i < result2.size() - 1 ? ", " : "");
    }
    std::cout << "])" << std::endl;
    
    // Test 3
    std::vector<int> result3 = sol.find_anagrams("cbaebabacd", "abc");
    std::vector<int> expected3 = {0, 6};
    bool pass3 = (result3 == expected3);
    std::cout << "Test 3: " << (pass3 ? "PASS" : "FAIL");
    std::cout << " (got: [";
    for (size_t i = 0; i < result3.size(); i++) {
        std::cout << result3[i] << (i < result3.size() - 1 ? ", " : "");
    }
    std::cout << "])" << std::endl;
    
    // Test 4 - No anagrams
    std::vector<int> result4 = sol.find_anagrams("abcd", "xyz");
    bool pass4 = result4.empty();
    std::cout << "Test 4: " << (pass4 ? "PASS" : "FAIL") << " (expected empty)" << std::endl;
    
    // Test 5 - Pattern equals string
    std::vector<int> result5 = sol.find_anagrams("abc", "abc");
    std::vector<int> expected5 = {0};
    bool pass5 = (result5 == expected5);
    std::cout << "Test 5: " << (pass5 ? "PASS" : "FAIL") << std::endl;
    
    return 0;
}
