## Problem Description

https://leetcode.com/problems/rotate-list/

```
Given the head of a linked list, rotate the list to the right by k places.

Example 1:

Input: head = [1,2,3,4,5], k = 2
Output: [4,5,1,2,3]

Example 2:

Input: head = [0,1,2], k = 4
Output: [2,0,1]

Constraints:

The number of nodes in the list is in the range [0, 500].
-100 <= Node.val <= 100
0 <= k <= 2 * 109
```

## Observations

Rotating the list by k positions means moving the last k nodes to the front.

If k is greater than the length of the list, we can reduce it using k % n, where n is the number of nodes.

**Corner cases:**

Empty list (```head = None```) → return ```None```.

Single node → rotation has no effect.

```k % n == 0``` → no change needed.

## Solutions

First, compute the length n of the list.

Normalize ```k``` as ```k % n```. If ```k == 0```, simply return head.

Use two pointers (```fast``` and ```slow```) to find the new "cut" point in the list:

Move fast ```k``` steps ahead.

Move slow and fast together until fast reaches the last node.

At this point, slow.next is the new head of the rotated list.

Break the list at slow and connect the old tail (```fast```) to the old head.

## Complexity Analysis

**Time Complexity**: ```O(n)``` → We traverse the list twice (once for length, once for finding the new head).

**Space Complexity**: ```O(1)``` → Only a few extra pointers used.

## Tags

linked list