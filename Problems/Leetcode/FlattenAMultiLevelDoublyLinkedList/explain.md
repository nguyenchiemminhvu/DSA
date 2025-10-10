## Problem Description

https://leetcode.com/problems/flatten-a-multilevel-doubly-linked-list/description/

```
You are given a doubly linked list, which contains nodes that have a next pointer, a previous pointer, and an additional child pointer. This child pointer may or may not point to a separate doubly linked list, also containing these special nodes. These child lists may have one or more children of their own, and so on, to produce a multilevel data structure as shown in the example below.

Given the head of the first level of the list, flatten the list so that all the nodes appear in a single-level, doubly linked list. Let curr be a node with a child list. The nodes in the child list should appear after curr and before curr.next in the flattened list.

Return the head of the flattened list. The nodes in the list must have all of their child pointers set to null.

Example 1:

Input: head = [1,2,3,4,5,6,null,null,null,7,8,9,10,null,null,11,12]
Output: [1,2,3,7,8,11,12,9,10,4,5,6]
Explanation: The multilevel linked list in the input is shown.
After flattening the multilevel linked list it becomes:

Example 2:


Input: head = [1,2,null,3]
Output: [1,3,2]
Explanation: The multilevel linked list in the input is shown.
After flattening the multilevel linked list it becomes:

Example 3:

Input: head = []
Output: []
Explanation: There could be empty list in the input.

Constraints:

The number of Nodes will not exceed 1000.
1 <= Node.val <= 105

How the multilevel linked list is represented in test cases:

We use the multilevel linked list from Example 1 above:

 1---2---3---4---5---6--NULL
         |
         7---8---9---10--NULL
             |
             11--12--NULL
The serialization of each level is as follows:

[1,2,3,4,5,6,null]
[7,8,9,10,null]
[11,12,null]
To serialize all levels together, we will add nulls in each level to signify no node connects to the upper node of the previous level. The serialization becomes:

[1,    2,    3, 4, 5, 6, null]
             |
[null, null, 7,    8, 9, 10, null]
                   |
[            null, 11, 12, null]
Merging the serialization of each level and removing trailing nulls we obtain:

[1,2,3,4,5,6,null,null,null,7,8,9,10,null,null,11,12]
```

## Observations

We are given a multilevel doubly linked list where each node has:
- next pointer (points to the next node in the same level)
- prev pointer (points to the previous node in the same level)
- child pointer (points to the head of another doubly linked list, which can have its own children)

The goal is to flatten the list so that:
- All nodes appear in a single-level doubly linked list.
- The order is: current node → all nodes in its child list → next node in the original list.
- All child pointers must be set to None after flattening.

This is essentially a depth-first traversal problem:
- When we encounter a node with a child, we need to process that child list before moving to the next node.
- The problem size is small (≤ 1000 nodes), so recursion is safe and easy to implement.

## Solutions

**Idea**: We can use recursion to flatten the list:

(1) If the current node has no child, simply move to the next node.
(2) If the current node has a child:
- Recursively flatten the child list.
- Insert the flattened child list between the current node and its next node.
- Update all prev and next pointers correctly.
- Set the child pointer to None to meet the requirement.

## Example walkthrough:

```head = [1,2,3,4,5,6,null,null,null,7,8,9,10,null,null,11,12]```

Start at ```1 → 2 → 3 → 4 → ...```

At node ```3```, find child list ```7 → 8 → 9 → 10```.

At node ```8```, find child list ```11 → 12```.

Flatten ```11 → 12``` first, attach to ```8```, then attach ```7 → 8 → 9 → 10``` to ```3```.

Continue until all levels are merged.

## Tags

doubly linked list, recursion