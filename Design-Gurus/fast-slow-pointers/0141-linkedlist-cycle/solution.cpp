/**
 * Problem: 141. Linked List Cycle
 * Link: https://leetcode.com/problems/linked-list-cycle/
 * Platform: Design-Gurus
 * Difficulty: Easy
 * Tags: Linked List, Two Pointers, Hash Table, Fast-Slow Pointers
 *
 * Date Solved: YYYY-MM-DD
 * Time Taken: XX min
 */

/*
    Problem Statement:
    Given the head of a Singly LinkedList, write a function to determine if the 
    LinkedList has a cycle in it or not.

    Example 1:
    Input: head = [3,2,0,-4], pos = 1
    Output: true
    Explanation: There is a cycle in the linked list, where the tail connects to 
    the 1st node (0-indexed).

    Example 2:
    Input: head = [1,2], pos = 0
    Output: true

    Example 3:
    Input: head = [1], pos = -1
    Output: false

    Constraints:
    - The number of nodes in the list is in the range [0, 10^4].
    - -10^5 <= Node.val <= 10^5
    - pos is -1 or a valid index in the linked-list.
*/

#include <iostream>
#include <unordered_set>

// ---------------------------------------------------------------------------

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// ---------------------------------------------------------------------------

// Approach #1: HashSet

/*
    Intuition:
    Traverse the list and keep a record of the visited nodes.
    If at any point we encounter a node that we've already visited, we can 
    conclude that there is a cycle in the list.

    Algorithm:
    1. Create an empty set, visited_nodes, to keep track of the nodes that have been visited.
    2. Traverse the list starting from the head node.
    3. At each node, check whether it already exists in visited_nodes.
        3.1. If it does, return true as a cycle is detected.
        3.2. Otherwise, insert/add the node to visited_nodes.

    Complexity Analysis:
    - Time: O(n) - Each node is visited once.
    - Space: O(n) - Set to store visited nodes.
*/

class Solution_HashSet {
public:
    bool has_cycle(ListNode* head) {
        std::unordered_set<ListNode*> visited_nodes;
        ListNode* current_node = head;
        
        while (current_node != nullptr) {
            if (visited_nodes.count(current_node) > 0) {
                return true;
            }
            visited_nodes.insert(current_node);
            current_node = current_node->next;
        }
        return false;
    }
};

// ---------------------------------------------------------------------------

// Approach #2: Two Pointers (Fast and Slow)

/*
    Intuition:
    Also known as the "hare and tortoise" algorithm, this method uses two pointers 
    that traverse the list at different speeds. The slow pointer moves one step at 
    a time, while the fast pointer moves two steps. If there is a cycle, the fast 
    pointer will eventually catch up to the slow pointer.

    Algorithm:
    1. Initialization:
        Initialize two pointers, slow_pointer and fast_pointer, both pointing to 
        the head node initially.
    2. Cycle Detection:
        2.1. Traverse the list until the fast_pointer or its next becomes nullptr.
        2.2. Update slow_pointer and fast_pointer as follows:
            slow_pointer = slow_pointer->next
            fast_pointer = fast_pointer->next->next
        2.3. If slow_pointer and fast_pointer meet at some point, return true.

    Complexity Analysis:
    - Time: O(n) - In the worst-case scenario, each node is visited once.
    - Space: O(1) - Constant space is used.
*/

class Solution {
public:
    bool has_cycle(ListNode* head) {
        ListNode* slow_pointer = head;
        ListNode* fast_pointer = head;
        
        while (fast_pointer != nullptr && fast_pointer->next != nullptr) {
            slow_pointer = slow_pointer->next;
            fast_pointer = fast_pointer->next->next;
            
            if (slow_pointer == fast_pointer) {
                return true;
            }
        }
        return false;
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;
    
    // Test 1: List with cycle
    ListNode* head1 = new ListNode(3);
    head1->next = new ListNode(2);
    head1->next->next = new ListNode(0);
    head1->next->next->next = new ListNode(-4);
    head1->next->next->next->next = head1->next; // Create cycle
    
    bool result1 = sol.has_cycle(head1);
    std::cout << "Test 1: " << (result1 == true ? "PASS" : "FAIL") << std::endl;
    
    // Test 2: List without cycle
    ListNode* head2 = new ListNode(1);
    head2->next = new ListNode(2);
    head2->next->next = new ListNode(3);
    
    bool result2 = sol.has_cycle(head2);
    std::cout << "Test 2: " << (result2 == false ? "PASS" : "FAIL") << std::endl;
    
    // Test 3: Single node without cycle
    ListNode* head3 = new ListNode(1);
    
    bool result3 = sol.has_cycle(head3);
    std::cout << "Test 3: " << (result3 == false ? "PASS" : "FAIL") << std::endl;
    
    // Test 4: Empty list
    bool result4 = sol.has_cycle(nullptr);
    std::cout << "Test 4: " << (result4 == false ? "PASS" : "FAIL") << std::endl;
    
    return 0;
}
