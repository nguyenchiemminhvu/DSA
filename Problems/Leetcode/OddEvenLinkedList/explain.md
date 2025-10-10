## Problem Description

https://leetcode.com/problems/odd-even-linked-list/

```
Given the head of a singly linked list, group all the nodes with odd indices together followed by the nodes with even indices, and return the reordered list.

The first node is considered odd, and the second node is even, and so on.

Note that the relative order inside both the even and odd groups should remain as it was in the input.

You must solve the problem in O(1) extra space complexity and O(n) time complexity.

Example 1:

Input: head = [1,2,3,4,5]
Output: [1,3,5,2,4]

Example 2:

Input: head = [2,1,3,5,6,4,7]
Output: [2,3,6,7,1,5,4]

Constraints:

The number of nodes in the linked list is in the range [0, 104].
-106 <= Node.val <= 106
```

## Observations

Odd/even refers to indices, not values

Example: In ```[2,1,3,5,6,4,7]```, ```2``` is odd (index ```1```), ```1``` is even (index ```2```), ```3``` is odd (index ```3```), etc.

We are rearranging by position, not by value.

Relative order must be preserved.

Within odd indices: ```1 → 3 → 5``` must keep the order they appeared in the original list.

Similarly for evens: ```2 → 4```.

Constraints suggest an ```in-place algorithm```

We cannot use an extra array or list (```O(n)``` extra space is disallowed).

Instead, we must relink existing nodes directly.

## Solutions

### Naive Approach (Extra Space, O(n))

Traverse the linked list, collect odd-indexed nodes and even-indexed nodes separately.

Concatenate odd list + even list.

Return the new head.

**Drawbacks:**

Requires O(n) extra memory for storing two lists.

Not acceptable per problem constraints.

### Optimal Approach (In-place, O(1) Space, O(n) Time)

**Idea:**

We use two pointers to rearrange nodes as we traverse:

```back``` → keeps track of the last node in the odd list.

```front``` → keeps track of the current node in the even list.

```even_head``` → stores the first even node so that after finishing odds, we can connect them to the start of the even list.

**Algorithm:**

```
Handle edge cases: if head is None or only one node, return as-is.

(1) Initialize:

    back = head (first node, odd start),
    front = head.next (second node, even start),
    even_head = front (to reconnect later).

(2) Rearrange links:

    At each step, back.next skips one node and points to the next odd.

    Move back forward to that odd node.

    Swap roles of back and front to continue alternating.

    After finishing, connect the last odd node (cur) to even_head.
```

## Tags

linked list