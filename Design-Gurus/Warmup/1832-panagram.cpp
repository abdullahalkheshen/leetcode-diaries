/* Panagram (Easy)
Problem Statement:
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

// Approach #1 Brute Force (Find Letters One By One)
/*
Intuition:
The straightforward way is to check the presence of each letter one by one.
We first iterate over sentence to find "a", then we iterate again to find "b", and so on.
If we manage to find all 26 letters, then sentence is a pangram, otherwise, it is not.

Algorithm:
For each lowercase letter current_character from a to z, iterate over sentence to check if it contains the letter current_character.
If we cannot find one of the letters, return False. Otherwise, return True after we finish all the iterations.

Big-O:
Time Complexity: O(n), Iterate over "n" chars in sentence for 26 times, with each iteration taking at most O(n).
Space Complexity: O(1), Just need to find letters one by one. */

#include <iostream>
#include <unordered_set>
#include <ctype.h>
using namespace std;

class Solution
{
public:
    bool isPanagram(string sentence)
    {
        for (int i = 0; i < 26; i++)
        {
            char current_character = 'a' + i;
            if (sentence.find(current_character) == string::npos)
                return false;
        }
        return true;
    }
};

// ----------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #2 Set
/*
Intuition: We can use a HashSet to check if the given sentence is a pangram or not. The HashSet will be used to store all the unique characters in the sentence.

Algorithm:
1. Converts the sentence to lowercase.
2. Iterate over each character of the sentence using a loop.
3. Add each character to the HashSet.
4. After looping through all characters, compare the size of the HashSet with 26 (total number of alphabets). If the size of the HashSet is equal to 26, it means the sentence contains all the alphabets and is a pangram, so the function will return true. Otherwise, it will return false.

Big-O:
Time complexity: O(n) where n is the number of characters in the sentence because it iterates over each character once
Space complexty: O(1) because the HashSet can store at most 26 characters.
*/

#include <string>
class Solution
{
public:
    // Function to check if given sentence is pangram
    bool isPanagram(string sentence)
    {
        unordered_set<char> unique_set;

        for (char current_character : sentence)
            if (isalpha(current_character))
                unique_set.insert(tolower(current_character));
        return unique_set.size() == 26;
    }

    // Or equivalent one-liner (without for loop):
    /* unordered_set<char> unique_set(sentence.begin(), sentence.end());
    return unique_set.size() == 26; */
};

// ----------------------------------------------------------------------------------------------------------------------------------------------------

// Approach 3 Vector/Array as Counter

/*
Intuition:
Note that each letter of alphabets has its own ASCII code, we map their ASCII codes to a unique number.

Algorithm:
1. Initialize an empty vector/array of size 26.
2. Iterate over sentence, for each character current_character, we let the value at the mapped index equal true.
3. Once we finish the iteration, check if every value of seen equal true.

Big-O:
Time complexity: O(n), we calculate the ASCII of current letter and update the value at the mapped index.
Space complexity: O(1), We use an array of size 26. Thus the space complexity is O(1).
*/

#include <array>
#include <vector>
class Solution
{
public:
    bool isPanagram(string sentence)
    {
        array<bool, 26> alphabets{};

        for (auto current_character : sentence)
            alphabets[current_character - 'a'] = true;

        for (auto status : alphabets)
            if (!status)
                return false;
        return true;
    }
};

            // ----------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #4 Map

/*
Intuition:
To determine if a sentence is a pangram (contains all letters of the alphabet), we can count the occurrences of each letter using a hashmap.
If all letters from 'a' to 'z' have at least one occurrence in the sentence, it's a pangram.

Algorithm:
1. Create an unordered_map to count occurrences of each letter.
2. Iterate through the given sentence and update the counts in the hashmap.
3. Check if all letters from 'a' to 'z' have at least one occurrence in the hashmap.
4. If any letter is missing, return false (not a pangram). Otherwise, return true.

Big-O:
Time complexity: O(n) to iterate through the sentence and mark each letter as seen in the hashmap.
Space complexity: O(26) to store the hashmap.

*/
#include <unordered_map>

class Solution
{
public:
    bool isPanagram(string sentence)
    {
        unordered_map<char, int> unordered_map;

        for (auto &&character : sentence)
            unordered_map[character]++;

        for (char character = 'a'; character < 'z'; character++)
        {
            if (unordered_map[character] == 0)
                return false;
        }
        return true;
    }
};

// OR

class Solution
{
public:
    bool isPanagram(string sentence)
    {
        unordered_map<char, bool> unordered_map;
        for (auto &&character : sentence)
        {
            if (isalpha(character))
                unordered_map[character] = true;

            for (char character = 'a'; character < 'z'; character++)
                if (!unordered_map[character])
                    return false;
            return true;
        }
    }
};
