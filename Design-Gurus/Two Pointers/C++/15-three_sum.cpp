/*
    Leetcode: 15. 3Sum

    Problem Statement
    Given an array of unsorted numbers, find all unique triplets in it that add up to zero.

    Example 1:

    Input: [-3, 0, 1, 2, -1, 1, -2]
    Output: [[-3, 1, 2], [-2, 0, 2], [-2, 1, 1], [-1, 0, 1]]
    Explanation: There are four unique triplets whose sum is equal to zero. smallest sum.'
    Example 2:

    Input: [-5, 2, -1, -2, 3]
    Output: [[-5, 2, 3], [-2, -1, 3]]
    Explanation: There are two unique triplets whose sum is equal to zero.

*/

// ----------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #1 Brute force (Three Pass)
    // Triple for loop of O(n^3) this probably will exceed time limit.

// ----------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #2 Sort + Two Pointers
/*
    Intuition:
        first, we will sort the array and then iterate through it taking one number at a time. Let’s say during our iteration we are at number ‘X’, so we need to find ‘Y’ and ‘Z’ such that X+Y+Z=0.
        At this stage, our problem translates into finding a pair whose sum is equal to “-X” (as from the above equation ).

    Algorithm:
        1. Sort the input array.
        2. Iterate over the array. For each element, it calls the method twoSumⅠⅠ to find pairs in the rest of the array that add up to the negative value of the current element.
        3. The twoSumⅠⅠ method uses the two-pointer technique to find pairs that add up to a given target.
            3.1. It starts with one pointer at the index after the current number, and another pointer at the end of the array.
            3.2. It calculates the sum of the numbers at those pointers, and if the sum is equal to the target, it adds a triplet consisting of the negative target
                (which is the number we're currently processing in the searchTriplets method) and the two numbers that make up the sum to the result list.
        4. If/else if/else:
            4.1. If the sum is less than the target, it means we need to increase the sum, so we increment left pointer one step to the right.
            4.2. If the sum is greater than the target, it means we need to decrease the sum, so we move the right pointer one step to the left.
        To avoid adding duplicate triplets to the list, the algorithm skips elements that are the same as the previous element both in the searchTriplets method and in the twoSumⅠⅠ method.
        5. In the end, the searchTriplets method returns a list of all unique triplets in the array that add up to zero.

    Complexity Analysis:
        Time Complexity: O(n^2)
            -> Sorting the array will take O(n*logn). The twoSumⅠⅠ() function will take O(n).
                As we are calling twoSumⅠⅠ() for every number in the input array, this means that overall searchTriplets() will take O(n*logn + n^2) which is asymptotically equivalent to O(n^2).

        Space Complexity: O(n)
            ->  Which is required for sorting. Ignoring the space required for the output array.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{

public:
    vector<vector<int>> searchTriplets(vector<int> &arr)
    {

        vector<vector<int>> triplets(arr.size());
        sort(arr.begin(), arr.end());

        /*
            // We can proceed with one of the if/else statements
            // So either we say continue to twoSum if elements are unique or || 
            for (int i = 0; i < nums.size() && nums[i] <= 0; ++i)
            {
                
                // Skip duplicates
                // only continue to twoSum with unique elements ..
                // This else if can also be removed and just write twoSumII(nums, i, res);
                
                if (i>0 && nums[i] == nums[i - 1]) continue;
                else if (i == 0 || nums[i - 1] != nums[i])
                {
                    twoSumII(nums, i, res);
                }
            }
        */

        for (size_t i = 0; i < arr.size() && arr[i] <= 0; i++)
        {
            if (i == 0 || arr[i] != arr[i - 1])
            {
                twoSumⅠⅠ(arr, i, triplets); // call the non-static member function on the instance
            }
        }
        return triplets;
    }
    void twoSumⅠⅠ(const vector<int> &arr, int i, vector<vector<int>> &triplets)
    {
        // left pointer start next to "i" pointer directly.
        int l = i + 1, r = arr.size() - 1;
        while (l < r)
        {
            int sum = arr[i] + arr[l] + arr[r];
            if (sum < 0) l++;
            else if (sum > 0) r--;
            else
            {
                triplets.push_back({arr[i], arr[l], arr[r]});
                // l<r or || l+1<arr.size()
                while (l<r && arr[l] == arr[l - 1])
                    l++;
                while (l<r && arr[r] == arr[r - 1])
                    r--;
            }
        }
    }
};


// Same approach using One function:
vector<vector<int>> threeSum(vector<int>& nums)
{
    sort(nums.begin(),nums.end());
    int n=nums.size();
    vector<vector<int>> triplets;
    for(int i=0;i<n-2;i++)
    {
        if(i>0 && (nums[i]==nums[i-1]))continue;
        int l=i+1, r= n-1;
        while(l<r)
        {
            int sum =nums[i]+nums[l]+nums[r];
            // sum (which's 0 for this problem) = arr[i] + arr[l] + arr[r];
            // So check for -nums[i] i.e. arr[l] + arr[r] == -arr[i]
            // So it'd be: if(arr[l]+arr[r] < -arr[i])
            if(sum<0) l++;
            else if(sum>0)r--;
            else {
                triplets.push_back({nums[i],nums[l],nums[r]});
                while(l+1<r && nums[l] == nums[l+1]) l++; // skip duplicate low_pointer side.
                while(l<r-1 && nums[r] == nums[r-1]) r--; // skip duplicate high_pointer side.
            }
            l++;r--; // update pointers for the next iteration to pass across new nums / Loop continuation condition.
        }
    }
    return triplets;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #2 Sort + Set

/* 
    Intuition:
        Like in the approach above, we will also sort the array so we can skip repeated values.
        We move our pivot element nums[i] and analyze elements to its right. We find all pairs whose sum is equal -nums[i] using the Two Sum:
         One-pass Hash Table approach, so that the sum of the pivot element (nums[i]) and the pair (-nums[i]) is equal to zero.
        To do that, we process each element nums[j] to the right of the pivot, and check whether a complement -nums[i] - nums[j] is exists in the hashset.
         If it is, we found a triplet. Then, we add nums[j] to the hashset, so it can be used as a complement from that point on.

    Algorithm:
        1. For the main function:
            1.1. Sort the input array nums.
            1.2. Iterate through the array:
            1.3. Conditional statement:
                1.3.1 If the current value is greater than zero, break from the loop. Remaining values cannot sum to zero.
                1.3.2 If the current value is the same as the one before, skip it.
            1.4. Otherwise, call twoSum for the current position i.
        
        2. For twoSum function:
            2.1. For each index j > i in A:
            2.2. Compute complement value as -nums[i] - nums[j].
            2.3. If complement exists in hashset seen:
                2.3.1. We found a triplet - add it to the result res.
            2.4. Increment j while the next value is the same as before to avoid duplicates in the result.
            2.5. Add nums[j] to hashset seen
        
        3. Return the result res.

        Complexity Analysis:
            Time Complexity: O(n^2)
                -> twoSum is O(n*logn), and we call it "n" times.
                -> Sorting the array takes O(n*log⁡n), so overall complexity is O(n*log⁡n + n^2).
                -> This is asymptotically equivalent to O(n^2).

            Space Complexity: O(n) for the hashset.
*/

# include<unordered_set>
class Solution
{
    public:
    vector<vector<int>> threeSum(vector<int>& nums)
    {
        vector<vector<int>> res;
        for (size_t i = 0; i < nums.size(); i++)
        {
            if (i>0 || nums[i] == nums[i-1]) continue;
            else if (i==0 || nums[i] != nums[i])
            {
                twoSum(nums, i, res);
            }
        }
        return res;
    }
    vector<vector<int>> twoSum(vector<int> nums, int i, vector<vector<int>> res)
    {
        // Now, Instead of two pointers, ONE pointer "j" + set
        unordered_set<int> s;
        for (size_t j = i+1; j < nums.size(); j++)
        {
            int comp = - nums[i] - nums[j];

            if (s.count(comp))
            {
                res.push_back({nums[i], nums[j], comp});

                // "Optional" while loops for optimizing time efficiency by skipping dups.
                while(j+1 < nums.size() && nums[j] != nums[j-1]) ++j;
                while(i+1 < nums.size() && nums[i] != nums[i+1]) ++i;
            }
            
        }
    }
};

// ----------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #2 No Sorting (Set + Map)

/* 
    Intuition:
        What if you cannot modify the input array, and you want to avoid copying it due to memory constraints?
        We can adapt the hashset approach above to work for an unsorted array. We can put a combination of three values into a hashset to avoid duplicates. 
        Values in a combination should be ordered (e.g. ascending). Otherwise, we can have results with the same values in the different positions.
    
    Algorithm:
        0. The algorithm is similar to the hashset approach above. We just need to add few optimizations so that it works efficiently for repeated values.
           `
        1. Declare hashset dups to skip duplicates in the outer loop.
            *Without this optimization, the submission will time out for the test case with 3,000 zeroes.
            *This case is handled naturally when the array is sorted.
        
        2. Instead of re-populating a hashset every time in the inner loop, use a hashmap and populate it once.
            Values in the hashmap will indicate whether we have encountered that element in the current iteration.
            When we process nums[j] in the inner loop, we set its hashmap value to i.
            This indicates that we can now use nums[j] as a complement for nums[i].            
            This is more like a trick to compensate for container overheads. The effect varies by language, e.g. for C++ it cuts the runtime in half.
            *Without this trick the submission may time out.
        
        3. return the vector of vectors of the results.
    
    Complexity Analysis
        Time Complexity: O(n^2)
            We have outer and inner loops, each going through "n" elements.
            -> While the asymptotic complexity is the same, this algorithm is noticeably slower than the previous approach.
            -> Lookups in a hashset, though requiring a constant time, are expensive compared to the direct memory access.

        Space Complexity: O(n)
            -> O(n+n) = O(n) for the hashset/hashmap.
            -> For the purpose of complexity analysis, we ignore the memory required for the output.
                However, in this approach we also store output in the hashset for deduplication. 
                In the worst case, there could be O(n^2) triplets in the output, like for this example: [-k, -k + 1, ..., -1, 0, 1, ... k - 1, k].
            -> Adding a new number to this sequence will produce n / 3 new triplets.

 */

#include <set>
#include <unordered_map>

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        set<vector<int>> res;
        unordered_set<int> dups;
        unordered_map<int, int> seen;
        for (int i = 0; i < nums.size(); ++i)
            if (dups.insert(nums[i]).second)
            {
                for (int j = i + 1; j < nums.size(); ++j)
                {
                    // complement + nums[i] + nums[j] = 0;
                    // complement is an element calculated, and explored in previous iterations, then pushed into a map with the index of "i" found at it.
                    int complement = -nums[i] - nums[j]; 
                    auto it = seen.find(complement);
                    if (it != end(seen) && it->second == i) 
                    {
                        vector<int> triplet = {nums[i], nums[j], complement};

                        sort(begin(triplet), end(triplet));
                        res.insert(triplet);
                    }
                    seen[nums[j]] = i;  
                }
            }
        return vector<vector<int>>(begin(res), end(res));
    }
};


/* 
    Notes :
        *if (dups.insert(nums[i]).second):
        The .second member of the returned pair is a Boolean value that indicates whether the insertion succeeded.
        If the insertion succeeded, .second is true.
        If the insertion failed, .second is false.
*/

// Least and not last, leetcode's video editorial was crucial and critical for undersatnding this problem.