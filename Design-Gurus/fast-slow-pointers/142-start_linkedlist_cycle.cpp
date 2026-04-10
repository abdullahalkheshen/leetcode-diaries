/* 
    Leetcode name: 142. Linked List Cycle II

    Problem Statement
    Given the head of a Singly LinkedList that contains a cycle, write a function to find the starting node of the cycle.
*/

// ----------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #1 HashSet

/* 
    Intuition:
        The provided code utilizes a hash table, specifically an unordered_set, to detect cycles in a linked list. 
        The hash table stores the memory addresses of the nodes visited during the traversal of the linked list. 
        If a node is encountered that has already been visited, it indicates the presence of a cycle, as the node is part of a repeating loop in the linked list.

    Algorithm:
        1. Initialize an unordered_set `s` to store visited nodes.
        2. Set a pointer `current_pointer` to the head of the linked list.
        3. Iterate while `current_pointer` is not null and `current_pointer->next` is not null:
        a. Check if the memory address of `current_pointer` is already present in the hash table `s`:
            i. If yes, it indicates the presence of a cycle, and the current node is the start of the cycle. Return `current_pointer`.
            ii. If no, insert the memory address of `current_pointer` into the hash table `s`.
        b. Advance `current_pointer` to `current_pointer->next`.
        4. If the loop terminates without detecting a cycle, return `nullptr`, indicating the absence of a cycle in the linked list.

    Complexity Analysis:
    Time Complexity: O(n), 
        → where n is the number of nodes in the linked list.
    Space Complexity: O(n), 
        → where n is the number of nodes in the linked list. 
        → This is due to the usage of the hash table to store visited nodes.    
        
*/

using namespace std;
#include <unordered_set>

class Solution
{
    public:
        struct ListNode
        {
            int value;
            ListNode* next;
            ListNode() : value(0), next(nullptr) {};
        };

        static ListNode* fincCycleStart(ListNode* head)
        {
            unordered_set<ListNode*> s;
            ListNode* current_pointer = 0;
            while (current_pointer && current_pointer->next)
            {
                if (s.count(current_pointer) > 0) return current_pointer;
                else s.insert(current_pointer);
                current_pointer = current_pointer -> next;
            }
            return nullptr;
        }
};

// ----------------------------------------------------------------------------------------------------------------------------------------------------

// Read this first: https://medium.com/@zephyr.ventum/floyds-tortoise-and-hare-cycle-finding-algorithm-my-over-explanation-5631c5ce71d7 
// Approach #2 Two Pointers (Fast & Slow)

/* 

    Intuition:  
        The algorithm employs the concept of two pointers, a slow pointer and a fast pointer, to detect the presence of a cycle in a linked list. The key idea is that in a cycle, if you have two runners (the slow pointer and fast pointer), they will eventually meet. This is because the fast pointer moves faster and will "lap" the slow pointer, and when they do, you'll have a loop. The algorithm doesn't modify the linked list and can determine the node where the cycle begins.

    Algorithm:  
        1. Start with two pointers, `slow_pointer` and `fast_pointer`, both initialized at the head of the linked list.
        2. Use a loop to iterate through the list, with the loop continuing as long as both `fast_pointer` and `fast_pointer->next` are not null.
        3. In each iteration of the loop, advance the `slow_pointer` by one step and the `fast_pointer` by two steps.
        4. If the two pointers meet at some point, it indicates the presence of a cycle. To find the node where the cycle begins, reset the `slow_pointer` to the head of the linked list and move both pointers one step at a time until they meet again. The meeting point will be the node where the cycle starts.
        5. Return the node where the `slow_pointer` and `fast_pointer` converge.

    Complexity Analysis:    
        • Time Complexity: O(n),
            "n" is the number of nodes in the linked list. 
            In the worst case, both pointers traverse the entire list before finding the cycle.
        • Space Complexity: O(1),
            as the algorithm uses only a constant amount of extra space for the two pointers, regardless of the size of the linked list.
*/

class Solution
{
    struct ListNode
    {
        int value;
        ListNode* next;
        ListNode() : value(0), next(nullptr) {};
    };

    static ListNode* findCycleStart(ListNode* head)
    {
        ListNode* slow_pointer=head;
        ListNode* fast_pointer=head;
        while (fast_pointer && fast_pointer->next) // fast_pointer && fast_pointer->next
        {
            slow_pointer = slow_pointer->next;
            fast_pointer = fast_pointer->next->next;
            if (slow_pointer == fast_pointer)
            {
                slow_pointer = head;
                while (slow_pointer != fast_pointer)
                {
                    slow_pointer = slow_pointer->next;
                    fast_pointer = fast_pointer->next;
                }
                return slow_pointer;
            }
        }
        return nullptr;
    }
};