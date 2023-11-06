/* 
    Leetcode name: 876. Middle of the Linked List
    
    Middle of the LinkedList
    Problem Statement
    Given the head of a Singly LinkedList, write a method to return the middle node of the LinkedList.
    If the total number of nodes in the LinkedList is even, return the second middle node.

    Example 1:
    Input: 1 -> 2 -> 3 -> 4 -> 5 -> null
    Output: 3
    
    Example 2:
    Input: 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> null
    Output: 4
    
    Example 3:
    Input: 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> null
    Output: 4
*/

// ----------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #1 Brute Force / Most Intuitive

/* 
    Intuition:
        Imagine a detective investigating a crime scene, carefully counting each footprint left behind. The detective counts the total number of footprints and then walks through the crime scene, stopping at the halfway point to identify the middle footprint.

    Algorithm:
        1. Initialize a pointer `p` to the head of the linked list and a counter `count` to 0.
        2. Traverse the linked list using the pointer `p`, incrementing the counter `count` for each node visited.
        3. Once the entire list has been traversed, calculate the middle index `mid = count // 2`.
        4. Reinitialize the pointer `p` to the head of the linked list.
        5. Traverse the linked list again using `p`, advancing `p` until it reaches the node at index `mid`, which represents the middle node of the linked list.
        6. Return the pointer `p` pointing to the middle node.

    Complexity Analysis:
        Time Complexity: O(n)
            - We traverse the linked list twice, once to count the nodes and once to find the middle node.
            - Each iteration takes constant time, so the overall time complexity is linear to the number of nodes (n).

        Space Complexity: O(1)
            - We only use constant memory for the pointers `p` and `q`, and the counter `count`.
            - The memory usage does not depend on the size of the input linked list.

        Comparison with the Two-Pointer Approach:
        While both approaches have the same time complexity of O(n), the two-pointer approach is generally considered more efficient and elegant. This is because it avoids the redundant traversal of the linked list to count the nodes. Additionally, the two-pointer approach is more adaptable to handling edge cases, such as empty or single-node lists, without additional checks.
*/

class Solution {
public:
    struct ListNode {
        int val;
        ListNode *next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode *next) : val(x), next(next) {}
    };

    ListNode* middleNode(ListNode* head) {
        ListNode * p = head;
        int count = 0;

        while(p)
        {
            count++;
            p=p->next;
        }

        ListNode *q= head;
        for(int i=0; i<count/2; i++) q=q->next;
        return q;
    }
};


// ----------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #2: Two pointers (Fast & Slow)

/* 
    Intuition:
        Imagine two runners racing along a linked list track. One runner, the "slow pointer," takes one step at a time, while the other runner, the "fast pointer," takes two steps at a time. When the fast pointer reaches the end of the track, the slow pointer will be at the middle node of the linked list.

    Algorithm:
        1. Initialize two pointers, `slow_pointer` and `fast_pointer`, both pointing to the head of the linked list.
        2. While `fast_pointer` and its next node (`fast_pointer->next`) both exist:
            a. Advance `slow_pointer` by one node (`slow_pointer = slow_pointer->next`).
            b. Advance `fast_pointer` by two nodes (`fast_pointer = fast_pointer->next->next`).
        3. `slow_pointer` will be pointing to the middle node of the linked list.

    Complexity Analysis:
        Time Complexity: O(n)
            - We traverse the linked list once, advancing both pointers simultaneously.
            - Each iteration takes constant time, so the overall time complexity is linear to the number of nodes (n).

        Space Complexity: O(1)
            - We only use constant memory for the two pointers, `slow_pointer` and `fast_pointer`.
            - The memory usage does not depend on the size of the input linked list.
*/

class Solution
{
    struct ListNode
    {
        int value;
        ListNode* next = nullptr;
        ListNode() : value(0), next(nullptr) {}
        ListNode(int x, ListNode *next) : value(x), next(nullptr) {}
    };

    ListNode* middle_node(ListNode* head)
    {
        ListNode* slow_pointer = head;
        ListNode* fast_pointer = head;
        while (fast_pointer && fast_pointer->next)
        {
            slow_pointer = slow_pointer->next;
            fast_pointer = fast_pointer->next->next;
        }
        return slow_pointer;
    }

};

// ----------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #3 Output to Array/vector

/* 
    Intuition:
        Imagine a train conductor dividing a long train into two equal halves. 
        The conductor first attaches all the train cars to a long rope and then pulls the rope from the middle, effectively dividing the train into two halves.

    Algorithm:
        1. Create an empty vector `v`.
        2. Add the head node of the linked list to the vector `v`.
        3. While the last element of the vector `v` has a next node:
        a. Append the next node of the last element to the vector `v`.
        4. The middle node is located at index `v.size() // 2` of the vector `v`.
        5. Return the node at index `v.size() // 2` of the vector `v`.

    Complexity Analysis:
        * Time Complexity: O(n)
            - We traverse the linked list once to populate the vector `v`.
            - Accessing elements in a vector takes constant time, so the overall time complexity is linear to the number of nodes (n).

        * Space Complexity: O(n)
            - We create and store a vector `v` that holds the entire linked list, requiring O(n) space.
            - The memory usage depends on the size of the input linked list.

    Comparison with the Two-Pointer Approach and the Counting Approach:
        While all three approaches have the same time complexity of O(n), the two-pointer approach is generally considered more efficient and space-efficient. 
        This is because it avoids the overhead of creating and storing a vector, which can be significant for large linked lists.
        The two-pointer approach also has the advantage of being more adaptable to handling edge cases, such as empty or single-node lists, without additional checks. 
        The counting approach, while straightforward, requires an additional pass through the linked list to find the middle node after counting the nodes.
*/

using namespace std;
#include <vector>

class Solution
{
    public:
        struct ListNode
        {
            int value;
            ListNode * next = nullptr;
            ListNode() : value(0), next(nullptr) {}
            // ListNode(int x, ListNode *next) : value(x), next(next) {}
        };
        
        ListNode* middle_node(ListNode* head)
        {
            vector<ListNode*> v = {head};
            while(v.back()->next) v.push_back(v.back()->next);
            return v[v.size()/2];
        }
};
