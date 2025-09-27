## Problem Description

https://leetcode.com/problems/remove-nth-node-from-end-of-list/

```
Given the head of a linked list, remove the nth node from the end of the list and return its head.

Example 1:

Input: head = [1,2,3,4,5], n = 2
Output: [1,2,3,5]

Example 2:

Input: head = [1], n = 1
Output: []

Example 3:

Input: head = [1,2], n = 1
Output: [1]

Constraints:

The number of nodes in the list is sz.
1 <= sz <= 30
0 <= Node.val <= 100
1 <= n <= sz
```

## Solutions

### Approach 1: Count Nodes First (Two-pass solution)

**Idea**:

First, traverse the whole list to count how many nodes it has (say ```count```).

The node we need to remove is at position ```count - n``` from the start (```0-based``` index).

Traverse again to that position and adjust the pointers to "skip" the node.

**Steps**:

Count ```length = 5```

```n = 2``` → remove the ```5 - 2 = 3rd``` node (1-based)

Skip the ```4```.

**Pros** ✅:

Easy to understand for beginners.

Straightforward.

**Cons** ❌:

Requires two passes over the linked list.

Not optimal for large lists.

### Approach 2: Reverse the List Twice

**Idea**:

Reverse the linked list.

Now, the "nth from end" becomes "nth from start".

Remove the ```n-th``` node.

Reverse the list back to original order.

**Steps**:

```
Original: 1 → 2 → 3 → 4 → 5

Reverse: 5 → 4 → 3 → 2 → 1

Remove n=2 → 5 → 3 → 2 → 1

Reverse back → 1 → 2 → 3 → 5.
```

**Pros** ✅:

Clever trick, easier if you already know reversing a list.

**Cons** ❌:

Requires two reversals → extra operations.

More complex to implement.

Less efficient.

### Approach 3: Two Pointers (One-pass solution)

**Idea**:

Use fast and slow pointers.

Move fast pointer ```n``` steps ahead first.

Then move both fast and slow together until fast reaches the end.

Now, slow is at the node just before the one we need to remove.

Adjust pointers to skip the target node.

**Steps**:

For example, ```n = 2```

Start: fast and slow at head.

Move fast ```2``` steps → points at ```3```.

Move both until fast reaches last node (```5```).

Now slow points to ```3```.

Remove next node (```4```).

```Result: 1 → 2 → 3 → 5```

**Pros** ✅:

Only one pass needed.

Efficient.

No need to reverse.

**Cons** ❌:

Slightly tricky to understand at first.

## Tags

linked list