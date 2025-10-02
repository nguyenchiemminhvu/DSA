## Problem Description

https://leetcode.com/problems/swap-nodes-in-pairs/

```
Given a linked list, swap every two adjacent nodes and return its head. You must solve the problem without modifying the values in the list's nodes (i.e., only nodes themselves may be changed.)

Example 1:

Input: head = [1,2,3,4]

Output: [2,1,4,3]

Explanation:

Example 2:

Input: head = []

Output: []

Example 3:

Input: head = [1]

Output: [1]

Example 4:

Input: head = [1,2,3]

Output: [2,1,3]

Constraints:

The number of nodes in the list is in the range [0, 100].
0 <= Node.val <= 100
```

## Observations

The problem requires swapping every two adjacent nodes in a singly linked list, without changing node values.

If the list is empty or has only one node, no swaps are needed.

The swap must be performed by changing the node connections, not the values.

Recursion is a natural fit, as the problem can be broken down into swapping the first two nodes and then recursively swapping the rest.

The base case is when the list is empty or has only one node left.

## Solution

We use recursion to swap pairs of nodes:

1. **Base Case:**
- If the list is empty (`head == None`) or has only one node (`head.next == None`), return `head`.

2. **Recursive Case:**
- Recursively swap the rest of the list starting from `head.next.next`.
- Swap the first two nodes by updating their `next` pointers.

## Tags

linked list, recursion