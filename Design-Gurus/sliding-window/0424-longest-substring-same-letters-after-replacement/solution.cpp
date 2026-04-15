/**
 * Problem: 424. Longest Repeating Character Replacement
 * Link: https://leetcode.com/problems/longest-repeating-character-replacement/
 * Platform: Design-Gurus
 * Difficulty: Medium
 * Tags: Sliding Window, Hash Table, String
 *
 * Date Solved: YYYY-MM-DD
 * Time Taken: XX min
 */

/*
    Problem Statement:
    Given a string with lowercase letters only, if you are allowed to replace no 
    more than 'k' letters with any letter, find the length of the longest substring 
    having the same letters after replacement.

    Example 1:
    Input: String="aabccbb", k=2  
    Output: 5  
    Explanation: Replace the two 'c' with 'b' to have a longest repeating substring "bbbbb".

    Example 2:
    Input: String="abbcb", k=1  
    Output: 4  
    Explanation: Replace the 'c' with 'b' to have a longest repeating substring "bbbb".

    Example 3:
    Input: String="abccde", k=1  
    Output: 3  
    Explanation: Replace the 'b' or 'd' with 'c' to have the longest repeating substring "ccc".

    Constraints:
    - 1 <= s.length <= 10^5
    - s consists of only uppercase English letters
    - 0 <= k <= s.length
*/

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

// ---------------------------------------------------------------------------

// Approach #1: Fixed Sliding Window + Binary Search

/*
    Intuition:
    If a valid substring of length i exists, then all substrings of length i-1 
    are also valid (monotonic property). Use binary search on the length.
    For each candidate length, use a sliding window to check if any valid 
    substring exists.

    A window is valid if: window_size - max_frequency <= k
    (we can replace all non-majority characters with at most k operations)

    Algorithm:
    1. Binary search on window length in range [1, n+1]
    2. For each mid value, check if valid window of size mid exists
    3. Use sliding window with frequency tracking to validate
    4. If valid, search in right half; otherwise search in left half

    Complexity Analysis:
    - Time: O(n * log(n)) - log(n) binary search steps, O(n) per step
    - Space: O(m) where m is number of distinct characters (max 26)
*/

class Solution1 {
public:
    int character_replacement(std::string s, int k) {
        int low = 1;
        int high = s.length() + 1;

        while (low + 1 < high) {
            int mid = low + (high - low) / 2;
            if (is_valid_substring(s, mid, k)) {
                low = mid;
            } else {
                high = mid;
            }
        }
        return low;
    }

private:
    bool is_valid_substring(const std::string& s, int substring_length, int k) {
        std::vector<int> counter(26, 0);
        int max_frequency = 0;
        int window_start = 0;
        
        for (int window_end = 0; window_end < (int)s.length(); window_end++) {
            counter[s[window_end] - 'a'] += 1;
            if (window_end + 1 - window_start > substring_length) {
                counter[s[window_start++] - 'a']--;
            }
            max_frequency = std::max(max_frequency, counter[s[window_end] - 'a']);
            
            if (substring_length - max_frequency <= k) return true;
        }
        return false;
    }
};

// ---------------------------------------------------------------------------

// Approach #2: Dynamic Sliding Window (Per Character)

/*
    Intuition:
    For each unique character, find the longest substring where that character 
    is the majority (after at most k replacements). The answer is the maximum 
    across all characters.

    A window is valid for character 'c' if: window_size - count_of_c <= k

    Algorithm:
    1. Collect all unique characters in the string
    2. For each character, use sliding window to find longest valid substring
    3. Expand window while valid, shrink when invalid
    4. Track maximum length across all characters

    Complexity Analysis:
    - Time: O(n * m) where m is number of unique characters (max 26)
    - Space: O(m) for storing unique characters
*/

class Solution2 {
public:
    int character_replacement(std::string s, int k) {
        std::unordered_set<char> all_letters;
        for (int i = 0; i < (int)s.length(); i++) {
            all_letters.insert(s[i]);
        }

        int max_size = 0;
        for (char letter : all_letters) {
            int max_char_count = 0;
            int start = 0;
            
            for (int end = 0; end < (int)s.length(); end++) {
                if (s[end] == letter) {
                    max_char_count++;
                }
                while ((end - start + 1) - max_char_count > k) {
                    if (s[start++] == letter) {
                        max_char_count--;
                    }
                }
                max_size = std::max(max_size, (end - start + 1));
            }
        }
        return max_size;
    }
};

// ---------------------------------------------------------------------------

// Approach #3: Dynamic Sliding Window (Optimized)

/*
    Intuition:
    Instead of iterating per character, track the maximum frequency of any 
    character in the current window. The window is valid if:
    window_size - max_frequency <= k

    Key insight: We don't need to decrease max_frequency when shrinking because 
    we only care about finding larger valid windows. If max_frequency doesn't 
    increase, we won't find a larger window anyway.

    Algorithm:
    1. Use hash map to track character frequencies in current window
    2. Track max_frequency of any character seen so far
    3. If window becomes invalid (size - max_freq > k), shrink by 1
    4. Update max_size at each step

    Complexity Analysis:
    - Time: O(n) - each character is visited at most twice
    - Space: O(m) where m is number of distinct characters (max 26)
*/

class Solution3 {
public:
    int character_replacement(std::string s, int k) {
        int max_size = 0;
        int max_char_count = 0;
        int window_start = 0;
        int window_end = 0;
        std::unordered_map<char, int> char_map;
        
        while (window_end < (int)s.size()) {
            char_map[s[window_end]]++;
            max_char_count = std::max(max_char_count, char_map[s[window_end]]);
            
            if ((window_end - window_start + 1) - max_char_count > k) {
                char_map[s[window_start++]]--;
            }
            
            max_size = std::max(max_size, window_end - window_start + 1);
            window_end++;
        }
        return max_size;
    }
};

// ---------------------------------------------------------------------------

// Approach #4: Dynamic Sliding Window (Alternative with While Loop)

/*
    Intuition:
    Same as Approach #3, but using a while loop to shrink the window. This is 
    equivalent because we only shrink by 1 each time (the if and while behave 
    the same in this case).

    Algorithm:
    Same as Approach #3, but with while loop for shrinking.

    Complexity Analysis:
    - Time: O(n) - each character is visited at most twice
    - Space: O(m) where m is number of distinct characters (max 26)
*/

class Solution4 {
public:
    int character_replacement(std::string s, int k) {
        int max_size = 0;
        int max_char_count = 0;
        int window_start = 0;
        int window_end = 0;
        std::unordered_map<char, int> char_map;
        
        while (window_end < (int)s.size()) {
            char_map[s[window_end]]++;
            max_char_count = std::max(max_char_count, char_map[s[window_end]]);
            
            while ((window_end - window_start + 1) - max_char_count > k) {
                char_map[s[window_start++]]--;
            }
            
            max_size = std::max(max_size, window_end - window_start + 1);
            window_end++;
        }
        return max_size;
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution3 sol;
    
    // Test 1
    int result1 = sol.character_replacement("aabccbb", 2);
    std::cout << "Test 1: " << (result1 == 5 ? "PASS" : "FAIL") 
              << " (got: " << result1 << ")" << std::endl;
    
    // Test 2
    int result2 = sol.character_replacement("abbcb", 1);
    std::cout << "Test 2: " << (result2 == 4 ? "PASS" : "FAIL") 
              << " (got: " << result2 << ")" << std::endl;
    
    // Test 3
    int result3 = sol.character_replacement("abccde", 1);
    std::cout << "Test 3: " << (result3 == 3 ? "PASS" : "FAIL") 
              << " (got: " << result3 << ")" << std::endl;
    
    // Test 4 - All same characters
    int result4 = sol.character_replacement("AAAA", 2);
    std::cout << "Test 4: " << (result4 == 4 ? "PASS" : "FAIL") 
              << " (got: " << result4 << ")" << std::endl;
    
    // Test 5 - k = 0
    int result5 = sol.character_replacement("ABAB", 0);
    std::cout << "Test 5: " << (result5 == 1 ? "PASS" : "FAIL") 
              << " (got: " << result5 << ")" << std::endl;
    
    // Test 6 - Large k
    int result6 = sol.character_replacement("ABAB", 4);
    std::cout << "Test 6: " << (result6 == 4 ? "PASS" : "FAIL") 
              << " (got: " << result6 << ")" << std::endl;
    
    return 0;
}
