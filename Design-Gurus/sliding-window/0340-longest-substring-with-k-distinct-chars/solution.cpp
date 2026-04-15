/**
 * Problem: 340. Longest Substring with At Most K Distinct Characters
 * Link: https://leetcode.com/problems/longest-substring-with-at-most-k-distinct-characters/
 * Platform: Design-Gurus
 * Difficulty: Medium
 * Tags: Sliding Window, Hash Table, String
 *
 * Date Solved: YYYY-MM-DD
 * Time Taken: XX min
 */

/*
    Problem Statement:
    Given a string, find the length of the longest substring in it with no more 
    than K distinct characters. You can assume that K is less than or equal to 
    the length of the given string.

    Example 1:
    Input: String="araaci", K=2  
    Output: 4  
    Explanation: The longest substring with no more than '2' distinct characters is "araa".

    Example 2:
    Input: String="araaci", K=1  
    Output: 2  
    Explanation: The longest substring with no more than '1' distinct characters is "aa".

    Example 3:
    Input: String="cbbebi", K=3  
    Output: 5  
    Explanation: The longest substrings with no more than '3' distinct characters are "cbbeb" & "bbebi".

    Constraints:
    - 1 <= s.length <= 5 * 10^4
    - 0 <= k <= 50
*/

#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

// ---------------------------------------------------------------------------

// Approach #1: Fixed Sliding Window + Binary Search

/*
    Intuition:
    Set up a target length and check if a valid substring with this length exists.
    Use binary search to find the maximum valid window length efficiently.
    For each candidate length, slide a fixed-size window to check validity.

    Algorithm:
    1. If k >= n, return n (entire string is valid)
    2. Binary search on window length in range [k, n]
    3. For each mid value, check if valid window of size mid exists
    4. If valid, search in right half; otherwise search in left half
    5. Return the maximum valid length found

    Complexity Analysis:
    - Time: O(n * log(n)) - log(n) binary search steps, O(n) per step
    - Space: O(n) - hash map could contain O(n) distinct characters
*/

class Solution1 {
public:
    int length_of_longest_substring_k_distinct(std::string& s, int k) {
        if ((int)s.length() <= k) return s.length();
        
        int left_bound = k;
        int right_bound = s.length();
        
        while (left_bound < right_bound) {
            int mid = (left_bound + right_bound + 1) / 2;
            if (is_valid_window(s, mid, k)) {
                left_bound = mid;
            } else {
                right_bound = mid - 1;
            }
        }
        return left_bound;
    }

private:
    bool is_valid_window(std::string& s, int window_size, int k) {
        std::unordered_map<char, int> char_map;

        for (int window_index = 0; window_index < window_size; window_index++) {
            char_map[s[window_index]]++;
        }
        if ((int)char_map.size() <= k) return true;

        for (int window_index = window_size; window_index < (int)s.length(); window_index++) {
            char_map[s[window_index]]++;
            char_map[s[window_index - window_size]]--;
            if (char_map[s[window_index - window_size]] == 0) {
                char_map.erase(s[window_index - window_size]);
            }
            
            if ((int)char_map.size() <= k) return true;
        }

        return false;
    }
};

// ---------------------------------------------------------------------------

// Approach #2: Dynamic Sliding Window

/*
    Intuition:
    Use a dynamic sliding window that expands when valid (distinct chars <= k) 
    and shrinks when invalid (distinct chars > k). Track the maximum valid 
    window size seen.

    Algorithm:
    1. Insert characters until we have K distinct characters in the HashMap
    2. Remember the length of this window as the longest so far
    3. Keep adding characters (slide window ahead)
    4. If distinct count > K, shrink from left until valid again
    5. Decrement frequency when removing; delete from map if frequency becomes 0
    6. Update maximum length at each step

    Complexity Analysis:
    - Time: O(n) - each character is processed at most twice
    - Space: O(k) - storing at most K+1 characters in the HashMap
*/

class Solution2 {
public:
    int length_of_longest_substring_k_distinct(const std::string& str, int k) {
        int max_size = 0;
        int window_start = 0;
        int window_end = 0;
        std::unordered_map<char, int> char_map;

        while (window_end < (int)str.length()) {
            char_map[str[window_end]]++;
            
            while ((int)char_map.size() > k) {
                char_map[str[window_start]]--;
                if (char_map[str[window_start]] == 0) {
                    char_map.erase(str[window_start]);
                }
                window_start++;
            }
            
            max_size = std::max(max_size, (window_end - window_start + 1));
            window_end++;
        }
        return max_size;
    }
};

// ---------------------------------------------------------------------------

// Approach #3: Fixed Sliding Window (Optimized)

/*
    Intuition:
    Once we find a valid window of size max_size, we don't need to decrease 
    the window size. We only look for larger valid windows. If the current 
    window is invalid, we maintain the same size and slide forward.

    Key insight: If we found a valid window of length L, there's no need to 
    check smaller windows. We either find a larger valid window or keep the 
    current maximum.

    Algorithm:
    1. Use hash map to track character frequencies in current window
    2. When adding a character, increment its count
    3. If distinct count <= k, we found a larger valid window (increment max_size)
    4. If distinct count > k, remove leftmost character to maintain window size
    5. Return max_size (which equals window_start at the end)

    Complexity Analysis:
    - Time: O(n) - single pass through the string
    - Space: O(n) - map might contain O(n) unique characters
*/

class Solution3 {
public:
    int length_of_longest_substring_k_distinct(std::string s, int k) {
        int window_start = 0;
        std::unordered_map<char, int> char_map;

        for (int window_end = 0; window_end < (int)s.length(); window_end++) {
            char_map[s[window_end]]++;

            if ((int)char_map.size() <= k) {
                window_start++;
            } else {
                char_map[s[window_end - window_start]]--;
                if (char_map[s[window_end - window_start]] == 0) {
                    char_map.erase(s[window_end - window_start]);
                }
            }
        }

        return window_start;
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution2 sol;
    
    // Test 1
    std::string s1 = "araaci";
    int result1 = sol.length_of_longest_substring_k_distinct(s1, 2);
    std::cout << "Test 1: " << (result1 == 4 ? "PASS" : "FAIL") 
              << " (got: " << result1 << ")" << std::endl;
    
    // Test 2
    std::string s2 = "araaci";
    int result2 = sol.length_of_longest_substring_k_distinct(s2, 1);
    std::cout << "Test 2: " << (result2 == 2 ? "PASS" : "FAIL") 
              << " (got: " << result2 << ")" << std::endl;
    
    // Test 3
    std::string s3 = "cbbebi";
    int result3 = sol.length_of_longest_substring_k_distinct(s3, 3);
    std::cout << "Test 3: " << (result3 == 5 ? "PASS" : "FAIL") 
              << " (got: " << result3 << ")" << std::endl;
    
    // Test 4 - k equals string length
    std::string s4 = "abc";
    int result4 = sol.length_of_longest_substring_k_distinct(s4, 3);
    std::cout << "Test 4: " << (result4 == 3 ? "PASS" : "FAIL") 
              << " (got: " << result4 << ")" << std::endl;
    
    // Test 5 - k = 0
    std::string s5 = "abc";
    int result5 = sol.length_of_longest_substring_k_distinct(s5, 0);
    std::cout << "Test 5: " << (result5 == 0 ? "PASS" : "FAIL") 
              << " (got: " << result5 << ")" << std::endl;
    
    return 0;
}
