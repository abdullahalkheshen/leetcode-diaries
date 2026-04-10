/*
    Leetcode name: 18. 4Sum

    Problem Statement
    Given an array of unsorted numbers and a target number, find all unique quadruplets in it, whose sum is equal to the target number.

    Example 1:
    Input: [4, 1, 2, -1, 1, -3], target=1
    triplets: [-3, -1, 1, 4], [-3, 1, 1, 2]
    Explanation: Both the quadruplets add up to the target.

    Example 2:
    Input: [2, 0, -1, 1, -2, 2], target=2
    triplets: [-2, 0, 2, 2], [-1, 0, 1, 2]
    Explanation: Both the quadruplets add up to the target.
*/

// --------------------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #1 Brute Force
/* 
    Intuition:
    We find unique quadruplets of numbers in the input array that sum up to a specified target. 
    To achieve this, we iterate through four nested loops to generate "combinations" of four numbers and checks if their sum equals the target.

    Algorithm:
        1. Sort the input array, nums, in O(n * log(n)) time.
        2. Use four nested loops to generate all combinations of quadruplets, checking if their sum equals the target.
        3. Store unique quadruplets in a set and return them in O(m) time, where m is the number of unique quadruplets. The overall time complexity is O(n^4). The space complexity is O(max(n^4, m)).

    Complexity Analysis:
        Time Complexity: O(n^4),
            -> where n is the number of elements in the input array, as it involves four nested loops over the array elements. 
        Space Complexity: can be up to O(n^4)
            -> in the worst case due to the `set` used to store unique vector of quadruplets.
 */
using namespace std;
#include <iostream>
#include <set>
#include <algorithm>
#include <vector>

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        set<vector<int>> set;
        vector<vector<int>> triplets;
        for(int i=0; i<n-3; i++)
        {
            for(int j=i+1; j<n-2; j++)
            {
                for(int k=j+1; k<n-1; k++)
                {
                    for(int l=k+1; l<n; l++)
                    {
                        if((long long)nums[i] + (long long)nums[j] + (long long)nums[k] + (long long)nums[l] == target)
                        {
                            set.insert({nums[i], nums[j], nums[k], nums[l]});
                        }
                    }
                }
            }
        }

        for(auto it : set){
            triplets.push_back(it);
        }

        return triplets;
    }
};

// --------------------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #2 Sort + Two Pointers

/* 
    Intuition:
        The algorithm aims to find unique quadruplets in the sorted input array `nums` that sum up to a specified target. It uses two-pointer approach within nested loops to efficiently search for such quadruplets without using a set to ensure uniqueness.

    Algorithm:
        1. Sort the input array `nums` to simplify the search process in O(n * log(n)) time.
        2. Initialize an empty vector `triplets` to store the unique quadruplets.
        3. Begin two nested loops, with the outer loop iterating from `i = 0` to `n - 3`, and the inner loop from `j = i + 1` to `n - 2`. These loops select the first two elements of the quadruplet.
        4. Calculate the `complement` as the target minus `nums[i]` and `nums[j`.
        5. Initialize two pointers, `l` and `r`, to search for the other two elements of the quadruplet. Start `l` at `j + 1` and `r` at `n - 1`.
        6. Within a while loop, compare the sum of `nums[l]` and `nums[r]` with `complement`.
        7. If the sum is less than `complement`, increment `l`. If the sum is greater, decrement `r`.
        8. If the sum equals `complement`, add the quadruplet `{nums[i], nums[j], nums[l], nums[r]}` to the `triplets`.
        9. Move `l` and `r` past any duplicate elements in the array by using a do-while loop. This ensures unique quadruplets are considered.
        10. After the inner loop, handle duplicate elements in the `nums` array by incrementing `j` past duplicates.
        11. Similarly, after the outer loop, increment `i` past duplicates in the array.
        12. Return the `triplets` vector containing unique quadruplets that sum up to the target.

        Complexity Analysis:
            Time Complexity: O(n^3)
                ->  due to the nested loops and two-pointer approach. The sorting step takes O(n * log(n)) time, but it is dominated by the nested loops.

            Space Complexity:  O(1) 
                -> as the algorithm doesn't use additional data structures that scale with the input size. The `triplets` vector stores the resulting quadruplets but is not counted towards space complexity.
*/

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        int n = nums.size();
        if (n < 4) return {}; // Return empty vector if nums has less than 4 elements

        sort(nums.begin(), nums.end());
        vector<vector<int>> triplets;
        for(int i=0; i<n-3; i++){
            for(int j=i+1; j<n-2; j++){
                
                long long complement = (long long)target - (long long)nums[i] - (long long)nums[j];
                int l = j+1, r = n-1;
                
                while(l < r)
                {
                    if(nums[l] + nums[r] < complement) l++;                        
                    else if(nums[l] + nums[r] > complement) r--;
                    else
                    {
                        triplets.push_back({nums[i], nums[j], nums[l], nums[r]});
                        // In general, the third while loop is the best choice, as it has the fastest time complexity. 
                        // 1st method - Worst time complexity of O(n) as it iterates through the whole array
                            // int tempIndex1 = l, tempIndex2 = r;
                            // while(l < r && nums[l]==nums[tempIndex1]) l++;
                            // while(l < r && nums[r]==nums[tempIndex2]) r--;
                        
                        // 2nd one - with time complexity if O(n*logn)
                            // while(l<r && nums[l]==nums[l-1]) l++;
                            // while(l<r && nums[r]==nums[r+1]) r--;
                        
                        // 3rd one - with time complexity of O(1).
                            do{l++;} while(l<r && nums[l]==nums[l-1]);
                            do{r--;} while(l<r && nums[r]==nums[r+1]);                    }
                }
                while(j+1 < n && nums[j]==nums[j+1]) j++;
            }
            while(i+1 < n && nums[i]==nums[i+1]) i++;
        }
        return triplets;
    }
};

// --------------------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #3 Sort + Set + Two Pointers

/* 
    Intuition:
    Algorithm:
    Complexity Analysis:

*/

class Solution
{
public:
    static vector<vector<int>> searchQuadruplets(vector<int> &nums, int target)
    {
        int n = int(nums.size());
        sort(nums.begin(), nums.end());
        vector<vector<int>> quadruplets;
        set<vector<int>> set;

        for (int i = 0; i < int(nums.size()) - 3; i++)
        {
            // Their goal is to skip some unnecessary iterations at edge cases
            if(i>0 && nums[i]==nums[i-1]) continue;
            if(static_cast<long long>(nums[i]) + nums[i+1] + nums[i+2] + nums[i+3] > target) break;
            if(static_cast<long long>(nums[i]) + nums[n-3] + nums[n-2] + nums[n-1] < target) continue;
            
            // These two lines of code are wrong because they're not statically casted.
            // if(nums[i]+nums[i+1]+nums[i+2]+nums[i+3] > target) break;
            // if(nums[i]+nums[n-3]+nums[n-2]+nums[n-1] < target) continue;

            for (int j = i + 1; j < int(nums.size()) - 2; j++)
            {
                if(static_cast<long long>(nums[i]) + nums[j] + nums[j+1] + nums[j+2] > target) break;
                if(static_cast<long long>(nums[i]) + nums[j] + nums[n-2] + nums[n-1] < target) continue;
                
                // These two lines of code are wrong because they're not statically casted.
                // if(nums[i]+nums[j]+nums[j+1]+nums[j+2]>target) break;
                // if(nums[i]+nums[j]+nums[n-2]+nums[n-1]<target) continue;

                long long complement = static_cast<long long>(target) - static_cast<long long>(nums[i] + nums[j]);

                int l = j + 1, r = int(nums.size()) - 1;
                while (l < r)
                {
                    if (nums[l] + nums[r] < complement) l++;
                    else if (nums[l] + nums[r] > complement) r--;
                    else set.insert({nums[i], nums[j], nums[l++], nums[r--]});
                }
            }
        }
        for (auto &&it : set) quadruplets.push_back(it);        
        return quadruplets;
    }
};

// --------------------------------------------------------------------------------------------------------------------------------------------------------------

