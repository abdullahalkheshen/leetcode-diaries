/* Problem Statement 
Given an array of strings words and two different strings that already exist in the array word1 and word2, return the shortest distance between these two words in the list.

Example 1:
Input: words = ["the", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog"], word1 = "fox", word2 = "dog"
Output: 5
Explanation: The distance between "fox" and "dog" is 5 words.

Example 2:
Input: words = ["a", "c", "d", "b", "a"], word1 = "a", word2 = "b"
Output: 1
Explanation: The shortest distance between "a" and "b" is 1 word. Please note that "a" appeared twice.

Example 3:
Input: words = ["a", "b", "c", "d", "e"], word1 = "a", word2 = "e"
Output: 4
Explanation: The distance between "a" and "e" is 4 words. */


// ----------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #1 Brute Force (Two Pass)
/* 
Intuition:
A naive solution to this problem is to go through the entire array looking for the first word. Every time we find an occurrence of the first word, we search the entire array for the closest occurrence of the second word.

Algorithm/Pseudocode:
1. Initialize shortest_distance to be returned.
2. Nested for loop:
    -> Iterate through all outer for loop to find first word1.
    -> Iterate through all inner for loop to find first word2.
    -> In inner loop, return the shortest_distance;

Big-O:
Time complexity: O(n^2), since for every occurrence of word1, we traverse the entire array in search for the closest occurrence of word2.
Space complexity: is O(1), since no additional space is allocated. */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

class Solution {
public:
  int shortest_distance(vector<string>& words, string word1, string word2)
   {
    int shortest_distance = words.size();
    for (size_t i = 0; i < words.size(); i++)
    {
        if (words[i] == word1)
        {
            for (size_t j = 0; j < words.size(); j++)
            {
                if (words[j] == word2)
                {
                    shortest_distance = std::min(shortest_distance, static_cast<int>(std::abs(static_cast<int>(i)-static_cast<int>(j))));
                }
            }
        }
        
    }
    return shortest_distance;
  }
};



// ----------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #2 Two Pointers (One Pass)
/* 
Intuition:

Algorithm:
1. Initialize two pointers pointer1 and pointer2 to store the positions of word1 and word2 in the words list, respectively. 
    -> Initialize these variables to -1 which means that the words haven't been found yet.

2. Initialize a variable shortest_distance with the length of the words list.

3. Loop through the words list and for each word check if it is word1 or word2.
    -> If it is word1, update pointer1 with the current index.
    -> If it is word2, update pointer2 with the current index.

4. If both pointer1 and pointer2 have been updated, that means both word1 and word2 have been found in the words list.
    -> In this case, update the shortest_distance with the absolute difference of the positions of word1 and word2.

5. Repeat steps 3 and 4 until the end of the words list is reached.
6. Return the final value of shortest_distance as the result.



Big-O:
Time complexity: O(N⋅M) where N is the number of words in, and M is the total length of two input words.
Space complexity: O(1), since no additional space is allocated.*/


class Solution
{
public:
    int shortestDistance(vector<string>& words, string word1, string word2) {
        int pointer1=-1; int pointer2=-1; int shortest_distance=words.size();
        for(int i=0; i<words.size(); i++)
        {
            if(words[i]==word1){pointer1=i;}
            if(words[i]==word2){pointer2=i;}
            if(pointer1!=-1 && pointer2!=-1)
                shortest_distance = min(shortest_distance, abs(pointer2-pointer1));
        }
        return shortest_distance;
    }
};