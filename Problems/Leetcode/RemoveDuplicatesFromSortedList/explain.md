## Problem

https://leetcode.com/problems/remove-duplicates-from-sorted-list/description/

```
Given the head of a sorted linked list, delete all duplicates such that each element appears only once. Return the linked list sorted as well.

Example 1:

Input: head = [1,1,2]
Output: [1,2]

Example 2:

Input: head = [1,1,2,3,3]
Output: [1,2,3]

Constraints:

The number of nodes in the list is in the range [0, 300].
-100 <= Node.val <= 100
The list is guaranteed to be sorted in ascending order.
```

## Observations

1. **Input Characteristics**:
   - The linked list is already sorted in ascending order
   - Node values are in range [-100, 100]
   - List can have 0 to 300 nodes
   - We need to remove duplicates while keeping only one occurrence of each value

2. **Key Insights**:
   - Since the list is sorted, all duplicate values will be adjacent to each other
   - We only need to compare each node with its immediate next node
   - We can solve this in-place without extra space
   - Time complexity: O(n) - single pass through the list
   - Space complexity: O(1) - only using pointers

3. **Edge Cases**:
   - Empty list (head is None)
   - Single node list (head.next is None)
   - All nodes have the same value
   - No duplicates in the list

## Solution

1. **Base Case Handling**: If the list is empty or has only one node, return it as-is since no duplicates are possible.

2. **Main Logic**: 
   - Start with `cur` pointing to the head
   - While there's a next node to compare:
     - If the next node has the same value as current node, skip it by updating `cur.next = cur.next.next`
     - If values are different, move `cur` to the next node
   - This ensures we keep the first occurrence and remove subsequent duplicates

3. **Why This Works**:
   - Since the list is sorted, duplicates are always adjacent
   - By comparing `cur.val` with `cur.next.val`, we catch all duplicates
   - When we find a duplicate, we "skip" it by redirecting the pointer
   - We only advance `cur` when no duplicate is found, ensuring we don't skip checking the new `cur.next`

**Example Walkthrough** for [1,1,2,3,3]:
- Start: cur=[1] -> [1] -> [2] -> [3] -> [3]
- cur.val=1, cur.next.val=1 → Skip: cur=[1] -> [2] -> [3] -> [3]  
- cur.val=1, cur.next.val=2 → Move: cur=[2] -> [3] -> [3]
- cur.val=2, cur.next.val=3 → Move: cur=[3] -> [3]
- cur.val=3, cur.next.val=3 → Skip: cur=[3] -> null
- Result: [1] -> [2] -> [3]

**Time Complexity**: O(n) - visit each node at most once
**Space Complexity**: O(1) - only using constant extra space

## Tags

linked list