/**
 * Problem: 243. Shortest Word Distance
 * Link: https://leetcode.com/problems/shortest-word-distance/
 * Platform: Design-Gurus
 * Difficulty: Easy
 * Tags: Array, String, Two Pointers
 *
 * Date Solved: YYYY-MM-DD
 * Time Taken: XX min
 */

/*
    Problem Statement:
    Given an array of strings words and two different strings that already exist
    in the array word1 and word2, return the shortest distance between these two
    words in the list.

    Example 1:
    Input: words = ["the", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog"],
           word1 = "fox", word2 = "dog"
    Output: 5
    Explanation: The distance between "fox" and "dog" is 5 words.

    Example 2:
    Input: words = ["a", "c", "d", "b", "a"], word1 = "a", word2 = "b"
    Output: 1
    Explanation: The shortest distance between "a" and "b" is 1 word.
    Please note that "a" appeared twice.

    Example 3:
    Input: words = ["a", "b", "c", "d", "e"], word1 = "a", word2 = "e"
    Output: 4
    Explanation: The distance between "a" and "e" is 4 words.

    Constraints:
    - 2 <= words.length <= 3 * 10^4
    - 1 <= words[i].length <= 10
    - words[i] consists of lowercase English letters
    - word1 and word2 are in words
    - word1 != word2
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>

// ---------------------------------------------------------------------------

// Approach #1: Brute Force (Two Pass)

/*
    Intuition:
    A naive solution to this problem is to go through the entire array looking
    for the first word. Every time we find an occurrence of the first word, we
    search the entire array for the closest occurrence of the second word.

    Algorithm:
    1. Initialize shortest_distance to be returned.
    2. Nested for loop:
        - Iterate through outer for loop to find first word1.
        - Iterate through inner for loop to find first word2.
        - In inner loop, update the shortest_distance.

    Complexity Analysis:
    - Time: O(n^2), since for every occurrence of word1, we traverse the entire
      array in search for the closest occurrence of word2.
    - Space: O(1), since no additional space is allocated.
*/

class SolutionBruteForce {
public:
    int shortest_distance(std::vector<std::string>& words,
                          std::string word1,
                          std::string word2) {
        int shortest_dist = words.size();

        for (size_t i = 0; i < words.size(); i++) {
            if (words[i] == word1) {
                for (size_t j = 0; j < words.size(); j++) {
                    if (words[j] == word2) {
                        shortest_dist = std::min(shortest_dist,
                            static_cast<int>(std::abs(static_cast<int>(i) - static_cast<int>(j))));
                    }
                }
            }
        }
        return shortest_dist;
    }
};

// ---------------------------------------------------------------------------

// Approach #2: Two Pointers (One Pass)

/*
    Intuition:
    We can solve this in one pass by keeping track of the most recent positions
    of word1 and word2 as we iterate through the array.

    Algorithm:
    1. Initialize two pointers pointer1 and pointer2 to store the positions of
       word1 and word2 in the words list, respectively. Initialize to -1.
    2. Initialize a variable shortest_distance with the length of the words list.
    3. Loop through the words list and for each word check if it is word1 or word2.
        - If it is word1, update pointer1 with the current index.
        - If it is word2, update pointer2 with the current index.
    4. If both pointer1 and pointer2 have been updated, update the shortest_distance
       with the absolute difference of the positions.
    5. Return the final value of shortest_distance.

    Complexity Analysis:
    - Time: O(n * m) where n is the number of words, and m is the total length
      of two input words.
    - Space: O(1), since no additional space is allocated.
*/

class Solution {
public:
    int shortest_distance(std::vector<std::string>& words,
                          std::string word1,
                          std::string word2) {
        int pointer1 = -1;
        int pointer2 = -1;
        int shortest_dist = words.size();

        for (int i = 0; i < static_cast<int>(words.size()); i++) {
            if (words[i] == word1) pointer1 = i;
            if (words[i] == word2) pointer2 = i;

            if (pointer1 != -1 && pointer2 != -1) {
                shortest_dist = std::min(shortest_dist, std::abs(pointer2 - pointer1));
            }
        }
        return shortest_dist;
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;

    // Test 1
    std::vector<std::string> words1 = {"the", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog"};
    int result1 = sol.shortest_distance(words1, "fox", "dog");
    std::cout << "Test 1: " << (result1 == 5 ? "PASS" : "FAIL") << std::endl;

    // Test 2
    std::vector<std::string> words2 = {"a", "c", "d", "b", "a"};
    int result2 = sol.shortest_distance(words2, "a", "b");
    std::cout << "Test 2: " << (result2 == 1 ? "PASS" : "FAIL") << std::endl;

    // Test 3
    std::vector<std::string> words3 = {"a", "b", "c", "d", "e"};
    int result3 = sol.shortest_distance(words3, "a", "e");
    std::cout << "Test 3: " << (result3 == 4 ? "PASS" : "FAIL") << std::endl;

    return 0;
}
