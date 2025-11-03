## Problem

https://leetcode.com/problems/delete-node-in-a-linked-list/description/

```
There is a singly-linked list head and we want to delete a node node in it.

You are given the node to be deleted node. You will not be given access to the first node of head.

All the values of the linked list are unique, and it is guaranteed that the given node node is not the last node in the linked list.

Delete the given node. Note that by deleting the node, we do not mean removing it from memory. We mean:

The value of the given node should not exist in the linked list.
The number of nodes in the linked list should decrease by one.
All the values before node should be in the same order.
All the values after node should be in the same order.
Custom testing:

For the input, you should provide the entire linked list head and the node to be given node. node should not be the last node of the list and should be an actual node in the list.
We will build the linked list and pass the node to your function.
The output will be the entire list after calling your function.

Example 1:

Input: head = [4,5,1,9], node = 5
Output: [4,1,9]
Explanation: You are given the second node with value 5, the linked list should become 4 -> 1 -> 9 after calling your function.

Example 2:

Input: head = [4,5,1,9], node = 1
Output: [4,5,9]
Explanation: You are given the third node with value 1, the linked list should become 4 -> 5 -> 9 after calling your function.

Constraints:

The number of the nodes in the given list is in the range [2, 1000].
-1000 <= Node.val <= 1000
The value of each node in the list is unique.
The node to be deleted is in the list and is not a tail node.
```

## Observations

1. **Unique constraint**: We only have access to the node to be deleted, not the head or previous nodes.
2. **Cannot truly delete**: Since we don't have access to the previous node, we can't modify its `next` pointer to skip the current node.
3. **Key insight**: Instead of deleting the node, we can "shift" all values from the next nodes to the left, effectively removing the target value.
4. **Guaranteed constraints**: The node to delete is never the last node, so we always have at least one next node.
5. **Memory consideration**: The actual last node will become unreachable and can be garbage collected.

## Solutions

### Approach: Value Shifting with Two Pointers

The solution uses a clever approach where instead of deleting the node, we shift all subsequent values one position to the left and remove the last node.

```python
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution:
    def deleteNode(self, node):
        """
        :type node: ListNode
        :rtype: void Do not return anything, modify node in-place instead.
        """
        slow = node
        fast = node.next
        while fast:
            slow.val = fast.val
            if fast.next == None:
                slow.next = fast.next  # This sets slow.next to None
                break
            slow = fast
            fast = fast.next
```

**Algorithm Explanation:**

1. **Initialize two pointers**: `slow` starts at the node to delete, `fast` starts at the next node
2. **Value shifting**: Copy the value from `fast` to `slow`, effectively "moving" the next value into the current position
3. **Advance pointers**: Move both pointers forward to continue the shifting process
4. **Handle last node**: When `fast.next` is None (fast is at the last node), copy its value to slow and set `slow.next = None` to remove the last node

**Example walkthrough** (head = [4,5,1,9], delete node with value 5):
```
Initial: 4 -> 5 -> 1 -> 9
         slow  fast

Step 1: Copy 1 to position of 5
        4 -> 1 -> 1 -> 9
         slow      fast

Step 2: Copy 9 to second position of 1  
        4 -> 1 -> 9 -> 9
              slow     fast

Step 3: fast.next is None, so set slow.next = None
        4 -> 1 -> 9
```

**Time Complexity**: O(n) where n is the number of nodes from the target node to the end
**Space Complexity**: O(1) - only using two pointers

### Alternative Simpler Approach

```python
def deleteNode(self, node):
    node.val = node.next.val
    node.next = node.next.next
```

This simpler approach works by:
1. Copying the next node's value to the current node
2. Skipping the next node by updating the pointer

Both approaches achieve the same result, but the two-pointer approach explicitly shows the shifting concept.

# Tags
- Linked List
- Two Pointers
- In-place Modification

