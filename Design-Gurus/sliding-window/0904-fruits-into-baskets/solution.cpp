/**
 * Problem: 904. Fruit Into Baskets
 * Link: https://leetcode.com/problems/fruit-into-baskets/
 * Platform: Design-Gurus
 * Difficulty: Medium
 * Tags: Sliding Window, Hash Table, Array
 *
 * Date Solved: YYYY-MM-DD
 * Time Taken: XX min
 */

/*
    Problem Statement:
    You are visiting a farm to collect fruits. The farm has a single row of fruit trees. 
    You will be given two baskets, and your goal is to pick as many fruits as possible.

    Rules:
    - Each basket can have only one type of fruit (no limit on quantity)
    - You can start with any tree, but you can't skip a tree once started
    - You will pick exactly one fruit from every tree until you cannot
    - You stop when you have to pick from a third fruit type

    This equals: Find the longest subarray with at most 2 unique elements.

    Example 1:
    Input: Fruit=['A', 'B', 'C', 'A', 'C']  
    Output: 3  
    Explanation: We can put 2 'C' in one basket and one 'A' in the other from ['C', 'A', 'C']
    
    Example 2:
    Input: Fruit=['A', 'B', 'C', 'B', 'B', 'C']  
    Output: 5  
    Explanation: We can put 3 'B' in one basket and two 'C' in the other from ['B', 'C', 'B', 'B', 'C']

    Constraints:
    - 1 <= fruits.length <= 10^5
    - 0 <= fruits[i] < fruits.length
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <set>

// ---------------------------------------------------------------------------

// Approach #1: Brute Force

/*
    Intuition:
    Check every subarray and find the longest valid one (containing at most 2 types).

    Algorithm:
    1. Initialize max_length = 0
    2. Iterate over all subarrays using left and right indices
    3. For each subarray, count the types of fruits using a set
    4. If the subarray has no more than 2 types, update max_length
    5. Return max_length

    Complexity Analysis:
    - Time: O(n^3) - three nested loops
    - Space: O(n) - set could contain O(n) different types in worst case
*/

class Solution1 {
public:
    int find_length(std::vector<char>& arr) {
        int max_length = 0;
        
        for (int left = 0; left < (int)arr.size(); left++) {
            for (int right = 0; right < (int)arr.size(); right++) {
                std::set<char> basket;
                for (int window_index = left; window_index <= right; window_index++) {
                    basket.insert(arr[window_index]);
                }

                if (basket.size() <= 2) {
                    max_length = std::max(max_length, (right - left + 1));
                }
            }
        }
        return max_length;
    }
};

// ---------------------------------------------------------------------------

// Approach #2: Optimized Brute Force

/*
    Intuition:
    For consecutive subarrays, the only difference is one added fruit. Instead of 
    recounting all fruits, just add the new fruit to the existing basket.
    Use early stopping: if current subarray is invalid, all longer subarrays 
    with same left index are also invalid.

    Algorithm:
    1. Initialize max_length = 0
    2. For each left index, iterate right while basket size <= 2
    3. If adding new fruit would exceed 2 types, break and move to next left
    4. Update max_length for each valid window
    5. Return max_length

    Complexity Analysis:
    - Time: O(n^2) - two nested loops
    - Space: O(1) - basket never exceeds 3 types due to early stopping
*/

class Solution2 {
public:
    int find_length(std::vector<char>& arr) {
        int max_length = 0;

        for (int left = 0; left < (int)arr.size(); left++) {
            std::set<char> basket;
            int right = left;
            while (right < (int)arr.size()) {
                if (basket.find(arr[right]) == basket.end() && basket.size() == 2) {
                    break;
                }
                basket.insert(arr[right++]);
            }
            max_length = std::max(max_length, (right - left));
        }
        return max_length;
    }
};

// ---------------------------------------------------------------------------

// Approach #3: Fixed Sliding Window

/*
    Intuition:
    Once we find a valid window of size k, we only need to look for windows 
    larger than k. We maintain the window size and only shrink by 1 when invalid.
    
    Key insight: If we found a valid window of size k, there's no need to 
    recalculate smaller windows. We just check if adding a new fruit expands 
    the valid window.

    Algorithm:
    1. Use a hash map to track fruit frequencies in current window
    2. Expand window by adding fruit at right
    3. If more than 2 types, shrink by removing fruit at left (only by 1)
    4. Window size at the end represents the maximum valid window

    Complexity Analysis:
    - Time: O(n) - single pass through the array
    - Space: O(1) - map never exceeds 3 entries
*/

class Solution3 {
public:
    int find_length(std::vector<char>& arr) {
        int left = 0;
        int right = 0;
        std::unordered_map<char, int> basket;

        for (right = 0; right < (int)arr.size(); right++) {
            basket[arr[right]]++;
            if (basket.size() > 2) {
                basket[arr[left]]--;
                if (basket[arr[left]] == 0) {
                    basket.erase(arr[left]);
                }
                left++;
            }
        }
        return right - left;
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution1 sol1;
    Solution2 sol2;
    Solution3 sol3;
    
    // Test 1
    std::vector<char> arr1 = {'A', 'B', 'C', 'A', 'C'};
    int result1 = sol3.find_length(arr1);
    std::cout << "Test 1 (Approach 3): " << (result1 == 3 ? "PASS" : "FAIL") 
              << " (got: " << result1 << ")" << std::endl;
    
    // Test 2
    std::vector<char> arr2 = {'A', 'B', 'C', 'B', 'B', 'C'};
    int result2 = sol3.find_length(arr2);
    std::cout << "Test 2 (Approach 3): " << (result2 == 5 ? "PASS" : "FAIL") 
              << " (got: " << result2 << ")" << std::endl;
    
    // Test 3 - Using Approach 2
    int result3 = sol2.find_length(arr1);
    std::cout << "Test 3 (Approach 2): " << (result3 == 3 ? "PASS" : "FAIL") 
              << " (got: " << result3 << ")" << std::endl;
    
    // Test 4 - Using Approach 1
    int result4 = sol1.find_length(arr2);
    std::cout << "Test 4 (Approach 1): " << (result4 == 5 ? "PASS" : "FAIL") 
              << " (got: " << result4 << ")" << std::endl;
    
    // Test 5 - Single type
    std::vector<char> arr3 = {'A', 'A', 'A', 'A'};
    int result5 = sol3.find_length(arr3);
    std::cout << "Test 5 (Single type): " << (result5 == 4 ? "PASS" : "FAIL") 
              << " (got: " << result5 << ")" << std::endl;
    
    return 0;
}
