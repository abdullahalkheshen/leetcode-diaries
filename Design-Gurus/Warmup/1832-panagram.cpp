/* Panagram (Easy)
Problem Statement
Given a string sentence containing English letters (lower- or upper-case), return true if sentence is a Pangram, or false otherwise.

A Pangram is a sentence where every letter of the English alphabet appears at least once.

Note: The given sentence might contain other characters like digits or spaces, your solution should handle these too.

Example 1:
Input: sentence = "TheQuickBrownFoxJumpsOverTheLazyDog"
Output: true
Explanation: The sentence contains at least one occurrence of every letter of the English alphabet either in lower or upper case.

Example 2:
Input: sentence = "This is not a pangram"
Output: false
Explanation: The sentence doesn't contain at least one occurrence of every letter of the English alphabet. */

// ----------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #1 Set
/* 
Intuition: We can use a HashSet to check if the given sentence is a pangram or not. The HashSet will be used to store all the unique characters in the sentence.

Algorithm:
1. Converts the sentence to lowercase.
2. Iterate over each character of the sentence using a loop.
3. Add each character to the HashSet.
4. After looping through all characters, compare the size of the HashSet with 26 (total number of alphabets). If the size of the HashSet is equal to 26, it means the sentence contains all the alphabets and is a pangram, so the function will return true. Otherwise, it will return false.

Big-O:
Time complexity: O(n) where  n is the number of characters in the sentence because it iterates over each character once
Space complexty: O(1) because the HashSet can store at most 26 characters.
*/

#include<iostream>
#include<unordered_set>
#include<ctype.h>
using namespace std;

class Solution
{
    public:
        // Function to check if given sentence is pangram
        bool checkPanagram(string sentence)
        {
            // 1. Create a set to store unique characters
            unordered_set<char> unique_set;

            // 2. Convert sentence to lowercase and iterate over each character
            for(char current_character:sentence)
                if (isalpha(current_character))
                    unique_set.insert(tolower(current_character));

            return unique_set.size()==26;
        }

        
        // Or equivalent one-liner (without for loop):
        /* unordered_set<char> unique_set(sentence.begin(), sentence.end());
        return unique_set.size() == 26; */
};

// ----------------------------------------------------------------------------------------------------------------------------------------------------