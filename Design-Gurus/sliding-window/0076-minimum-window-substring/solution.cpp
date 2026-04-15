/**
 * Problem: 76. Minimum Window Substring
 * Link: https://leetcode.com/problems/minimum-window-substring/
 * Platform: Design-Gurus
 * Difficulty: Hard
 * Tags: Sliding Window, Hash Table, String
 *
 * Date Solved: YYYY-MM-DD
 * Time Taken: XX min
 */

/*
    Problem Statement:
    Given a string and a pattern, find the smallest substring in the given string 
    which has all the characters of the given pattern.

    Example 1:
    Input: String="aabdec", Pattern="abc"
    Output: "abdec"
    Explanation: The smallest substring having all characters of the pattern is "abdec"

    Example 2:
    Input: String="aabdec", Pattern="abac"  
    Output: "aabdec"  
    Explanation: The smallest substring having all character occurrences of the pattern is "aabdec"
    
    Example 3:
    Input: String="abdbca", Pattern="abc"  
    Output: "bca"  
    Explanation: The smallest substring having all characters of the pattern is "bca".
    
    Example 4:
    Input: String="adcad", Pattern="abc"  
    Output: ""  
    Explanation: No substring in the given string has all characters of the pattern

    Constraints:
    - 1 <= s.length, t.length <= 10^5
    - s and t consist of uppercase and lowercase English letters
*/

#include <iostream>
#include <string>
#include <unordered_map>

// ---------------------------------------------------------------------------

// Approach #1: Sliding Window with Character Matching

/*
    Intuition:
    Use a sliding window approach where we expand the window until we have all 
    required characters, then shrink from the left to find the minimum window.
    We track how many characters are "matched" (have their required frequency met).

    Algorithm:
    1. Create a frequency map of the pattern
    2. Expand window by moving window_end, decrementing character counts
    3. When a character's count reaches 0, increment matched
    4. When matched equals pattern length, we have a valid window
    5. Try to shrink from left while maintaining validity
    6. Track minimum window size and starting position

    Complexity Analysis:
    - Time: O(n + m) where n is string length, m is pattern length
    - Space: O(m) for the frequency map
*/

class Solution1 {
public:
    std::string find_substring(std::string s, std::string p) {
        int matched = 0;
        int window_start = 0;
        int minimum_window_size = s.size() + 1;
        int min_window_start = 0;
        
        std::unordered_map<char, int> char_map;
        for (auto chr : p) {
            char_map[chr]++;
        }

        for (int window_end = 0; window_end < (int)s.size(); window_end++) {
            if (char_map.find(s[window_end]) != char_map.end()) {
                char_map[s[window_end]]--;
                if (char_map[s[window_end]] >= 0) {
                    matched++;
                }
            }

            while (matched == (int)p.size()) {
                if (minimum_window_size > window_end - window_start + 1) {
                    min_window_start = window_start;
                    minimum_window_size = window_end - window_start + 1;
                }

                if (char_map.find(s[window_start]) != char_map.end()) {
                    if (char_map[s[window_start]] == 0) {
                        matched--;
                    }
                    char_map[s[window_start]]++;
                }
                
                window_start++;
            }
        }
        return (minimum_window_size > (int)s.size()) ? "" : s.substr(min_window_start, minimum_window_size);
    }
};

// ---------------------------------------------------------------------------

// Approach #2: Sliding Window with Distinct Character Tracking

/*
    Intuition:
    Instead of tracking total matched characters, track how many distinct 
    characters have their required frequency fully met. This is useful when 
    pattern has repeated characters.

    Algorithm:
    1. Create frequency map of pattern, count required distinct characters
    2. Expand window, track window character counts
    3. When a character's window count equals required count, increment formed
    4. When formed equals required, we have a valid window
    5. Shrink from left while maintaining validity
    6. Track minimum window

    Complexity Analysis:
    - Time: O(n + m) where n is string length, m is pattern length
    - Space: O(n + m) for both frequency maps
*/

class Solution2 {
public:
    std::string min_window(std::string s, std::string t) {
        if (s.length() == 0 || t.length() == 0) {
            return "";
        }

        std::unordered_map<char, int> dict_t;
        for (char c : t) {
            dict_t[c]++;
        }

        int required = dict_t.size();
        int l = 0, r = 0;
        int formed = 0;
        int ans[3] = {-1, 0, 0};
        std::unordered_map<char, int> window_counts;

        while (r < (int)s.length()) {
            char c = s[r];
            window_counts[c]++;

            if (dict_t.find(c) != dict_t.end() && window_counts[c] == dict_t[c]) {
                formed++;
            }

            while (l <= r && formed == required) {
                c = s[l];
                if (ans[0] == -1 || r - l + 1 < ans[0]) {
                    ans[0] = r - l + 1;
                    ans[1] = l;
                    ans[2] = r;
                }

                window_counts[c]--;

                if (dict_t.find(c) != dict_t.end() && window_counts[c] < dict_t[c]) {
                    formed--;
                }

                l++;
            }

            r++;
        }

        return ans[0] == -1 ? "" : s.substr(ans[1], ans[2] - ans[1] + 1);
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution1 sol1;
    Solution2 sol2;
    
    // Test 1
    std::string result1 = sol1.find_substring("aabdec", "abc");
    std::cout << "Test 1 (Approach 1): " << (result1 == "abdec" ? "PASS" : "FAIL") 
              << " (got: " << result1 << ")" << std::endl;
    
    // Test 2
    std::string result2 = sol1.find_substring("abdbca", "abc");
    std::cout << "Test 2 (Approach 1): " << (result2 == "bca" ? "PASS" : "FAIL") 
              << " (got: " << result2 << ")" << std::endl;
    
    // Test 3
    std::string result3 = sol1.find_substring("adcad", "abc");
    std::cout << "Test 3 (Approach 1): " << (result3 == "" ? "PASS" : "FAIL") 
              << " (got: " << result3 << ")" << std::endl;
    
    // Test 4 - Using Approach 2
    std::string result4 = sol2.min_window("ADOBECODEBANC", "ABC");
    std::cout << "Test 4 (Approach 2): " << (result4 == "BANC" ? "PASS" : "FAIL") 
              << " (got: " << result4 << ")" << std::endl;
    
    // Test 5 - Using Approach 2
    std::string result5 = sol2.min_window("a", "a");
    std::cout << "Test 5 (Approach 2): " << (result5 == "a" ? "PASS" : "FAIL") 
              << " (got: " << result5 << ")" << std::endl;
    
    return 0;
}
