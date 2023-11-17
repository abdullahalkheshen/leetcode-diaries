/*
    Leetcode name: 141. Linked List Cycle

    LinkedList Cycle
    Problem Statement
    Given the head of a Singly LinkedList, write a function to determine if the LinkedList has a cycle in it or not.
*/

// ----------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #1: HashSet

/*
    Intuition:
        Traverse the list and keep a record of the visited nodes.
        If at any point we encounter a node that we've already visited, we can conclude that there is a cycle in the list.

    Algorithm:
        1. Create an empty set, visited_nodes, to keep track of the nodes that have been visited.
        2. Traverse the list starting from the head node.
        3. At each node, check whether it already exists in visited_nodes.
            3.1. If it does, return True as a cycle is detected.
            3.2. Otherwise, insert/add the node to visited_nodes.

    Complexity Analysis
        Time Complexity: O(n)
            -> Each node is visited once.

        Space Complexity: O(n)
            -> Set to store visited nodes.
*/

using namespace std;
#include <iostream>
#include <unordered_set>
#include <algorithm>

class Solution
{
public:
    struct ListNode
    {
        int value;
        ListNode *next;
        ListNode(int x) : value(x), next(nullptr) {}
    };

    bool hasCycle(ListNode *head)
    {
        unordered_set<ListNode *> visited_nodes;
        ListNode *current_node = head;
        while (current_node != nullptr)
        {
            if (visited_nodes.count(current_node) > 0) return true;
            visited_nodes.insert(current_node);
            current_node = current_node->next;
        }
        return false;
    }
};

// ----------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #2: Two Pointers (Fast and Slow)

/*
    Intuition:
        Also known as the "hare and tortoise" algorithm, this method uses two pointers that traverse the list at different speeds. 
        The slow pointer moves one step at a time, while the fast pointer moves two steps. 
        If there is a cycle, the fast pointer will eventually catch up to the slow pointer.

    Algorithm:
        1. Initialization:
            Initialize two pointers, slow_pointer and fast_pointer, both pointing to the head node initially.
        2. Cycle Detection:
            2.1. Traverse the list until the fast_pointer or its next becomes None.
            2.2. Update slow_pointer and fast_pointer as follows:
                slow_pointer = slow_pointer.next
                fast_pointer = fast_pointer.next.next
            2.3. If slow_pointer and fast_pointer meet at some point, return True.
    
    Complexity Analysis
        Time Complexity: O(n)
            —> In the worst-case scenario, each node is visited once.
        Space Complexity: O(1)
            —> Constant space is used.
*/

class Solution {
public:
    struct ListNode
    {
        int value;
        ListNode *next;
        ListNode(int x) : value(x), next(nullptr) {}
    };

    bool hasCycle(ListNode *head) {
        std::unordered_set<ListNode*> visited_nodes;
        ListNode *current_node = head;
        while (current_node != nullptr) 
        {
            if (visited_nodes.find(current_node) != visited_nodes.end()) return true;
            visited_nodes.insert(current_node);
            current_node = current_node->next;
        }
        return false;
    }
};