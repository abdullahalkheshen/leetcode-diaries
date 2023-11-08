/*
    Leetcode name: 234. Palindrome Linked List

    Problem Statement
    Given the head of a Singly LinkedList, write a method to check if the LinkedList is a palindrome or not.

    Your algorithm should use constant space and the input LinkedList should be in the original form once the algorithm is finished. The algorithm should have O(N) time complexity where ‘N’ is the number of nodes in the LinkedList.

    Example 1:
    Input: 2 -> 4 -> 6 -> 4 -> 2 -> null
    Output: true

    Example 2:
    Input: 2 -> 4 -> 6 -> 4 -> 2 -> 2 -> null
    Output: false
*/

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #1 Iterative with Fast and Slow Pointers

/*
    Intuition:
        The problem asks us to determine if a given singly-linked list is a palindrome. We can solve this problem by reversing the second half of the linked list and comparing it with the first half.
        If both halves are identical, the linked list is a palindrome.

    Algorithm:
        1. Check if the given linked list is empty or contains only one element. If so, return `true` since a single node is always a palindrome.
        2. Initialize two pointers, `slow_pointer` and `fast_pointer`, both starting at the head of the linked list.
            The `slow_pointer` moves one step at a time, and the `fast_pointer` moves two steps at a time. This is done to find the middle of the linked list.
        3. Once the `fast_pointer` reaches the end of the list (or null), the `slow_pointer` will be pointing to the middle node.
        4. Reverse the second half of the linked list starting from the `slow_pointer`.
        5. Reset the `fast_pointer` back to the head of the linked list.
        6. Compare the values of each node in the first half (from the head to the middle) with the corresponding nodes in the reversed second half (from the middle to the end).
        7. If all comparisons are equal, return `true` as the linked list is a palindrome. Otherwise, return `false`.

    Complexity Analysis
    • Time complexity : O(n), where n is the number of nodes in the Linked List.
        Finding the middle is O(n), reversing a list in place is O(n), and then comparing the 2 resulting Linked Lists is also O(n).
    
    • Space complexity : 0(1).
        -> We are changing the next pointers for half of the nodes. This was all memory that had already been allocated, so we are not using any extra memory and therefore it is 0(1).
        -> It may look to be O(n) because we're creating a new list. It's incorrect, because we are changing each of the pointers one-by-one, in-place. 
        -> We are not needing to allocate more than 0(1) extra memory to do this work, and there is 0(1) stack frames going on the stack. It is the same as reversing the values in an Array in place (using the two-pointer technique).
        -> The downside of this approach is that in a concurrent environment (multiple threads and processes accessing the same data).
            Access to the Linked List by other threads or processes would have to be locked while this function is running, because the Linked List is temporarily broken.
            This is a limitation of many in-place algorithms though. 
*/

using namespace std;

class Solution
{
public:
    struct ListNode
    {
        int val;
        ListNode *next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode *next) : val(x), next(next) {}
    };

    ListNode *reverse_linkedlist(ListNode *head)
    {

        ListNode *previous = nullptr;
        ListNode *current = nullptr;
        ListNode *next = head;
        while (current)
        {
            // slide the three pointers
            previous = current;
            current = next;
            next = next->next;
            current->next = previous;
        }
        head = current;
        return head;
    }
    // OR
    /* ListNode* reverse_linkedlist(ListNode* head) {
    ListNode* previous = nullptr;
    ListNode* current = head;
    while (current)
    {
        ListNode* next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    return previous;
    } */

    bool isPalindrome(ListNode *head)
    {
        if (!head || !head->next) return true;

        ListNode *slow_pointer = head;
        ListNode *fast_pointer = head;

        while (fast_pointer && fast_pointer->next)
        {
            slow_pointer = slow_pointer->next;
            fast_pointer = fast_pointer->next->next;
        }

        if (fast_pointer) slow_pointer = slow_pointer->next;

        ListNode *middle_pointer = slow_pointer;
        middle_pointer = reverse_linkedlist(middle_pointer);

        fast_pointer = head; // THIS IS CRUCIAL AND CRITICAL AS IS RESTORE HEAD ON FAST POINTER

        while (middle_pointer)
        {
            if (middle_pointer->val != fast_pointer->val) return false;
            else
            {
                middle_pointer = middle_pointer->next;
                fast_pointer = fast_pointer->next;
            }
        }
        return true;
    }
};


// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #2: Recursive with One Pointer

/* 
    Intuition:

    The recursive approach utilizes the divide-and-conquer strategy to efficiently check whether a linked list is a palindrome. 
    It divides the list into two halves and recursively checks each half for palindromicity. 
    This approach is similar to the merge sort algorithm, where the list is recursively divided until it reaches base cases of single elements or empty lists, which are trivially palindromes.

    Algorithm:
        1. `checkPalindrome(head, target, isEven)`: This recursive function takes three arguments:
                - `head`: The current node of the linked list to be checked.
                - `target`: A pointer that traverses the second half of the list in reverse order.
                - `isEven`: A boolean flag indicating whether the linked list has an even or odd number of nodes.
            
            The function performs the following steps:
            a. Base case: If `head` has reached the `target` node, it indicates the end of the second half. If `isEven` is false, it means the middle node has been skipped, and the function returns `true`. Otherwise, it returns `true` if the current node's value matches the target node's value, indicating a palindrome.
            b. Recursive call: If the `target` node still exists, the function recursively checks the palindrome property for the remaining nodes in the first half of the list.
            c. Value comparison: If the current node's value matches the target node's value, it indicates a palindrome, and the function continues checking the next pair of nodes.
            d. Failure case: If any value mismatch occurs or the `target` node becomes `nullptr`, the function returns `false`, indicating that the linked list is not a palindrome.

        2. `isPalindrome(head)`: This function initiates the recursive check for the entire linked list.
            a. It finds the middle node of the linked list using the two-pointer approach.
            b. It determines whether the linked list has an even or odd number of nodes based on the position of the middle node.
            c. It calls the `checkPalindrome` function to recursively check the palindrome property for the first half of the list, passing the middle node as the starting point of the second half.
            d. It returns the result of the recursive call, indicating whether the entire linked list is a palindrome.

    Complexity Analysis:
        Time Complexity: O(n)
            → The recursive function traverses the entire linked list once, and each recursive call involves constant time operations. 
            → Therefore, the overall time complexity is linear to the number of nodes (n).
        Space Complexity: O(n)
            → In the worst case, the recursion stack can grow up to the size of the linked list, especially for unbalanced lists. 
            → Therefore, the space complexity is also linear to the number of nodes (n).
*/

class Solution
{
public:
    struct ListNode
    {
        int val;
        ListNode *next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode *next) : val(x), next(next) {}
    };

    bool checkPalindrome(ListNode *head, ListNode *&target, bool isEven)
    {

        if (head == target)
        {
            if (isEven == false)
                target = target->next;
            return true;
        }

        if (checkPalindrome(head->next, target, isEven) == false)
            return false;

        if (head && !target) return false;

        if (head->val == target->val)
        {
            target = target->next;
            return true;
        }

        return false;
    }

    bool isPalindrome(ListNode *head)
    {
        ListNode *slow_pointer = head;
        ListNode *fast_pointer = head;

        while (fast_pointer && fast_pointer->next)
        {
            slow_pointer = slow_pointer->next;
            fast_pointer = fast_pointer->next->next;
        }

        if (fast_pointer) slow_pointer = slow_pointer->next;
        
        ListNode *middle = slow_pointer;

        bool isEven = (fast_pointer) ? true : false;

        return checkPalindrome(head, middle, isEven);

        return true;
    }
};