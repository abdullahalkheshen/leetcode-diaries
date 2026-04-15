/**
 * Problem: 567. Permutation in String
 * Link: https://leetcode.com/problems/permutation-in-string/
 * Platform: Design-Gurus
 * Difficulty: Hard
 * Tags: Sliding Window, Hash Table, String, Two Pointers
 *
 * Date Solved: YYYY-MM-DD
 * Time Taken: XX min
 */

/*
    Problem Statement:
    Given a string and a pattern, find out if the string contains any permutation 
    of the pattern. Permutation is defined as the re-arranging of characters.
    For example, "abc" has 6 permutations: abc, acb, bac, bca, cab, cba.
    If a string has 'n' distinct characters, it will have n! permutations.

    Example 1:
    Input: String="oidbcaf", Pattern="abc"   
    Output: true   
    Explanation: The string contains "bca" which is a permutation of the pattern.
    
    Example 2:
    Input: String="odicf", Pattern="dc"   
    Output: false  
    Explanation: No permutation of the pattern is present in the given string.
    
    Example 3:
    Input: String="bcdxabcdy", Pattern="bcdyabcdx"  
    Output: true  
    Explanation: Both the string and the pattern are a permutation of each other.
    
    Example 4:
    Input: String="aaacb", Pattern="abc"  
    Output: true  
    Explanation: The string contains "acb" which is a permutation of the pattern.

    Constraints:
    - 1 <= s1.length, s2.length <= 10^4
    - s1 and s2 consist of lowercase English letters
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <vector>

// ---------------------------------------------------------------------------

// Approach #1: Brute Force (Generate All Permutations)

/*
    Intuition:
    Generate all permutations of the pattern and check if any is a substring 
    of the longer string. Use recursion with swapping to generate permutations.

    Algorithm:
    1. Use permute() to generate all permutations by swapping characters
    2. For each permutation, check if it exists as substring in s2
    3. Return true if any permutation is found

    Complexity Analysis:
    - Time: O(n!) - generating all permutations
    - Space: O(n^2) - recursion depth n, each node contains string of length n
*/

class Solution1 {
public:
    bool flag = false;
    
    bool find_permutation(std::string s1, std::string s2) {
        permute(s1, s2, 0);
        return flag;
    }

private:
    void permute(std::string s1, std::string s2, int current_index) {
        if (current_index == (int)s1.length()) {
            if (s2.find(s1) != std::string::npos) {
                flag = true;
            }
        } else {
            for (int next_index = current_index; next_index < (int)s1.length(); next_index++) {
                s1 = swap_chars(s1, current_index, next_index);
                permute(s1, s2, current_index + 1);
                s1 = swap_chars(s1, current_index, next_index);
            }
        }
    }

    std::string swap_chars(std::string s, int i0, int i1) {
        if (i0 == i1) return s;
        std::string s1 = s.substr(0, i0);
        std::string s2 = s.substr(i0 + 1, i1 - i0 - 1);
        std::string s3 = s.substr(i1 + 1);
        return s1 + s[i1] + s2 + s[i0] + s3;
    }
};

// ---------------------------------------------------------------------------

// Approach #2: Using Sorting

/*
    Intuition:
    One string is a permutation of another only if both contain the same 
    characters the same number of times. sorted(x) == sorted(y) for permutations.

    Algorithm:
    1. Sort the pattern string s1
    2. For every substring of s2 with length equal to s1, sort it
    3. If sorted strings match, return true
    4. Return false if no match found

    Complexity Analysis:
    - Time: O(l1*log(l1) + (l2-l1)*l1*log(l1)) where l1, l2 are string lengths
    - Space: O(l1) for the sorted string
*/

class Solution2 {
public:
    bool find_permutation(std::string s1, std::string s2) {
        s1 = sort_string(s1);
        for (int i = 0; i <= (int)s2.length() - (int)s1.length(); ++i) {
            if (s1 == sort_string(s2.substr(i, s1.length()))) {
                return true;
            }
        }
        return false;
    }

private:
    std::string sort_string(std::string str) {
        std::sort(str.begin(), str.end());
        return str;
    }
};

// ---------------------------------------------------------------------------

// Approach #3: Using Hashmap

/*
    Intuition:
    One string is a permutation of another only if both contain the same 
    characters with the same frequency. Compare frequency maps instead of sorting.

    Algorithm:
    1. Create frequency map of pattern s1
    2. For each window of size s1.length() in s2, create frequency map
    3. If maps match, return true
    4. Return false if no match found

    Complexity Analysis:
    - Time: O(l1 + 26*l1*(l2-l1)) - hashmap has at most 26 keys
    - Space: O(1) - hashmap has at most 26 key-value pairs
*/

class Solution3 {
public:
    bool find_permutation(std::string s1, std::string s2) {
        if (s1.length() > s2.length()) return false;

        std::unordered_map<char, int> s1_map;
        for (int i = 0; i < (int)s1.length(); i++) {
            s1_map[s1[i]]++;
        }

        for (int i = 0; i <= (int)s2.length() - (int)s1.length(); i++) {
            std::unordered_map<char, int> s2_map;
            for (int j = 0; j < (int)s1.length(); j++) {
                s2_map[s2[i + j]]++;
            }
            if (matches(s1_map, s2_map)) return true;
        }
        return false;
    }

private:
    bool matches(std::unordered_map<char, int>& s1_map, std::unordered_map<char, int>& s2_map) {
        for (auto& pair : s1_map) {
            char key = pair.first;
            if (s1_map[key] != s2_map[key]) return false;
        }
        return true;
    }
};

// ---------------------------------------------------------------------------

// Approach #4: Using Array

/*
    Intuition:
    Since strings contain only lowercase letters ('a' to 'z'), use an array 
    of size 26 instead of hashmap for frequency counting.

    Algorithm:
    1. Create frequency array for pattern s1
    2. For each window, create frequency array and compare
    3. Return true if arrays match

    Complexity Analysis:
    - Time: O(l1 + 26*l1*(l2-l1))
    - Space: O(1) - arrays of fixed size 26
*/

class Solution4 {
public:
    bool find_permutation(std::string s1, std::string s2) {
        if (s1.length() > s2.length()) return false;

        std::vector<int> s1map(26, 0);
        std::vector<int> s2map(26, 0);

        for (char c : s1) {
            s1map[c - 'a']++;
        }

        for (int i = 0; i <= (int)s2.length() - (int)s1.length(); i++) {
            for (int j = 0; j < (int)s1.length(); j++) {
                s2map[s2[i + j] - 'a']++;
            }

            if (matches(s1map, s2map)) return true;

            for (int j = 0; j < (int)s1.length(); j++) {
                s2map[s2[i + j] - 'a']--;
            }
        }

        return false;
    }

private:
    bool matches(std::vector<int>& s1map, std::vector<int>& s2map) {
        for (int i = 0; i < 26; i++) {
            if (s1map[i] != s2map[i]) return false;
        }
        return true;
    }
};

// ---------------------------------------------------------------------------

// Approach #5: Sliding Window

/*
    Intuition:
    Instead of recalculating frequency for each window, slide the window by 
    adding the new character and removing the old one.

    Algorithm:
    1. Create frequency arrays for both strings (first window)
    2. Slide window: increment new char, decrement old char
    3. Compare arrays at each position
    4. Return true if match found

    Complexity Analysis:
    - Time: O(l1 + 26*(l2-l1))
    - Space: O(1) - fixed size arrays
*/

class Solution5 {
public:
    bool find_permutation(const std::string& s1, const std::string& s2) {
        if (s1.length() > s2.length()) return false;

        std::vector<int> s1_vector(26, 0);
        std::vector<int> s2_vector(26, 0);

        for (int i = 0; i < (int)s1.length(); ++i) {
            s1_vector[s1[i] - 'a']++;
            s2_vector[s2[i] - 'a']++;
        }

        for (int i = 0; i + s1.length() - 1 < s2.length(); ++i) {
            if (matches(s1_vector, s2_vector)) return true;

            s2_vector[s2[i + s1.length()] - 'a']++;
            s2_vector[s2[i] - 'a']--;
        }

        return matches(s1_vector, s2_vector);
    }

private:
    bool matches(const std::vector<int>& s1_vector, const std::vector<int>& s2_vector) {
        for (int i = 0; i < 26; ++i) {
            if (s1_vector[i] != s2_vector[i]) return false;
        }
        return true;
    }
};

// ---------------------------------------------------------------------------

// Approach #6: Optimized Sliding Window

/*
    Intuition:
    Instead of comparing all 26 elements each time, track how many characters 
    have matching frequencies. Only update the count when frequencies change.

    Algorithm:
    1. Initialize frequency arrays and count matching characters
    2. Slide window: update frequencies and count
    3. If count reaches 26, all characters match - return true
    4. Return count == 26 at the end

    Complexity Analysis:
    - Time: O(l1 + (l2-l1)) = O(l2)
    - Space: O(1) - fixed size arrays
*/

class Solution6 {
public:
    bool find_permutation(std::string s1, std::string s2) {
        if (s1.length() > s2.length()) return false;
            
        std::vector<int> s1_vector(26, 0);
        std::vector<int> s2_vector(26, 0);

        for (size_t i = 0; i < s1.length(); i++) {
            s1_vector[s1[i] - 'a']++;
            s2_vector[s2[i] - 'a']++;
        }

        int count = 0;
        for (int i = 0; i < 26; ++i) {
            if (s1_vector[i] == s2_vector[i]) count++;
        }

        for (size_t i = 0; i < s2.length() - s1.length(); ++i) {
            int l = s2[i] - 'a';
            int r = s2[i + s1.length()] - 'a';

            if (count == 26) return true;

            s2_vector[r]++;
            if (s2_vector[r] == s1_vector[r]) count++;
            else if (s2_vector[r] == s1_vector[r] + 1) count--;

            s2_vector[l]--;
            if (s2_vector[l] == s1_vector[l]) count++;
            else if (s2_vector[l] == s1_vector[l] - 1) count--;
        }

        return count == 26;
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution6 sol;
    
    // Test 1
    bool result1 = sol.find_permutation("abc", "oidbcaf");
    std::cout << "Test 1: " << (result1 == true ? "PASS" : "FAIL") << std::endl;
    
    // Test 2
    bool result2 = sol.find_permutation("dc", "odicf");
    std::cout << "Test 2: " << (result2 == false ? "PASS" : "FAIL") << std::endl;
    
    // Test 3
    bool result3 = sol.find_permutation("bcdyabcdx", "bcdxabcdy");
    std::cout << "Test 3: " << (result3 == true ? "PASS" : "FAIL") << std::endl;
    
    // Test 4
    bool result4 = sol.find_permutation("abc", "aaacb");
    std::cout << "Test 4: " << (result4 == true ? "PASS" : "FAIL") << std::endl;
    
    // Test 5
    bool result5 = sol.find_permutation("ab", "eidbaooo");
    std::cout << "Test 5: " << (result5 == true ? "PASS" : "FAIL") << std::endl;
    
    return 0;
}
