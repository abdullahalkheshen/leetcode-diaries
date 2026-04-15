/**
 * Problem: 1832. Check if the Sentence Is Pangram
 * Link: https://leetcode.com/problems/check-if-the-sentence-is-pangram/
 * Platform: Design-Gurus
 * Difficulty: Easy
 * Tags: Hash Table, String
 *
 * Date Solved: YYYY-MM-DD
 * Time Taken: XX min
 */

/*
    Problem Statement:
    Given a string sentence containing English letters (lower- or upper-case),
    return true if sentence is a Pangram, or false otherwise.

    A Pangram is a sentence where every letter of the English alphabet appears
    at least once.

    Note: The given sentence might contain other characters like digits or
    spaces, your solution should handle these too.

    Example 1:
    Input: sentence = "TheQuickBrownFoxJumpsOverTheLazyDog"
    Output: true
    Explanation: The sentence contains at least one occurrence of every letter
    of the English alphabet either in lower or upper case.

    Example 2:
    Input: sentence = "This is not a pangram"
    Output: false
    Explanation: The sentence doesn't contain at least one occurrence of every
    letter of the English alphabet.

    Constraints:
    - 1 <= sentence.length <= 1000
    - sentence consists of lowercase and/or uppercase English letters
*/

#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <array>
#include <cctype>

// ---------------------------------------------------------------------------

// Approach #1: Brute Force (Find Letters One By One)

/*
    Intuition:
    The straightforward way is to check the presence of each letter one by one.
    We first iterate over sentence to find "a", then we iterate again to find
    "b", and so on.

    Algorithm:
    1. For each lowercase letter from 'a' to 'z', iterate over sentence to check
       if it contains the letter.
    2. If we cannot find one of the letters, return false.
    3. Otherwise, return true after we finish all the iterations.

    Complexity Analysis:
    - Time: O(26 * n) = O(n), iterate over n chars in sentence for 26 times
    - Space: O(1), just need to find letters one by one
*/

class SolutionBruteForce {
public:
    bool is_pangram(std::string sentence) {
        for (int i = 0; i < 26; i++) {
            char current_character = 'a' + i;
            if (sentence.find(current_character) == std::string::npos &&
                sentence.find(std::toupper(current_character)) == std::string::npos) {
                return false;
            }
        }
        return true;
    }
};

// ---------------------------------------------------------------------------

// Approach #2: HashSet

/*
    Intuition:
    We can use a HashSet to store all the unique characters in the sentence.
    If the set contains all 26 letters, it's a pangram.

    Algorithm:
    1. Convert the sentence to lowercase.
    2. Iterate over each character of the sentence.
    3. Add each alphabetic character to the HashSet.
    4. Compare the size of the HashSet with 26.

    Complexity Analysis:
    - Time: O(n), where n is the number of characters in the sentence
    - Space: O(1), because the HashSet can store at most 26 characters
*/

class Solution {
public:
    bool is_pangram(std::string sentence) {
        std::unordered_set<char> unique_set;

        for (char current_character : sentence) {
            if (std::isalpha(current_character)) {
                unique_set.insert(std::tolower(current_character));
            }
        }

        return unique_set.size() == 26;
    }
};

// ---------------------------------------------------------------------------

// Approach #3: Frequency Counter (Array)

/*
    Intuition:
    Each letter of the alphabet has its own ASCII code. We can map their ASCII
    codes to a unique index in an array.

    Algorithm:
    1. Initialize an empty array of size 26.
    2. Iterate over sentence, for each character, mark the corresponding index
       as true.
    3. Check if every value in the array is true.

    Complexity Analysis:
    - Time: O(n), we iterate through the sentence once
    - Space: O(1), we use an array of size 26
*/

class SolutionArray {
public:
    bool is_pangram(std::string sentence) {
        std::array<bool, 26> alphabets{};

        for (char current_character : sentence) {
            if (std::isalpha(current_character)) {
                alphabets[std::tolower(current_character) - 'a'] = true;
            }
        }

        for (bool status : alphabets) {
            if (!status) return false;
        }

        return true;
    }
};

// ---------------------------------------------------------------------------

// Approach #4: HashMap

/*
    Intuition:
    To determine if a sentence is a pangram, we can count the occurrences of
    each letter using a hashmap. If all letters from 'a' to 'z' have at least
    one occurrence, it's a pangram.

    Algorithm:
    1. Create an unordered_map to count occurrences of each letter.
    2. Iterate through the sentence and update the counts.
    3. Check if all letters from 'a' to 'z' have at least one occurrence.

    Complexity Analysis:
    - Time: O(n), to iterate through the sentence
    - Space: O(1), at most 26 entries in the hashmap
*/

class SolutionHashMap {
public:
    bool is_pangram(std::string sentence) {
        std::unordered_map<char, int> char_count;

        for (char character : sentence) {
            if (std::isalpha(character)) {
                char_count[std::tolower(character)]++;
            }
        }

        for (char c = 'a'; c <= 'z'; c++) {
            if (char_count[c] == 0) return false;
        }

        return true;
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;

    // Test 1
    bool result1 = sol.is_pangram("TheQuickBrownFoxJumpsOverTheLazyDog");
    std::cout << "Test 1: " << (result1 == true ? "PASS" : "FAIL") << std::endl;

    // Test 2
    bool result2 = sol.is_pangram("This is not a pangram");
    std::cout << "Test 2: " << (result2 == false ? "PASS" : "FAIL") << std::endl;

    // Test 3
    bool result3 = sol.is_pangram("abcdefghijklmnopqrstuvwxyz");
    std::cout << "Test 3: " << (result3 == true ? "PASS" : "FAIL") << std::endl;

    // Test 4
    bool result4 = sol.is_pangram("abcdefghijklmnopqrstuvwxy");
    std::cout << "Test 4: " << (result4 == false ? "PASS" : "FAIL") << std::endl;

    return 0;
}
