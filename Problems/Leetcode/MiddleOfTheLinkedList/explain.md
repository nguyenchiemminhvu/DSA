## Problem

https://leetcode.com/problems/middle-of-the-linked-list/

```
Given the head of a singly linked list, return the middle node of the linked list.

If there are two middle nodes, return the second middle node.

Example 1:

Input: head = [1,2,3,4,5]
Output: [3,4,5]
Explanation: The middle node of the list is node 3.

Example 2:

Input: head = [1,2,3,4,5,6]
Output: [4,5,6]
Explanation: Since the list has two middle nodes with values 3 and 4, we return the second one.

Constraints:

The number of nodes in the list is in the range [1, 100].
1 <= Node.val <= 100
```

## Observations

1. **Problem Understanding**: We need to find the middle node of a singly linked list. When there are two middle nodes (even number of nodes), we should return the second one.

2. **Two Pointer Technique**: This is a classic application of the "fast and slow pointer" (tortoise and hare) technique. The fast pointer moves 2 steps while the slow pointer moves 1 step.

3. **Edge Cases**:
   - Single node: Return the only node
   - Two nodes: Return the second node
   - Odd number of nodes: Return the exact middle
   - Even number of nodes: Return the second of the two middle nodes

4. **Time Complexity**: O(n) where n is the number of nodes
5. **Space Complexity**: O(1) - only using two pointers

## Solution

The solution uses the two-pointer technique with a slight modification to handle the "second middle node" requirement:

```python
def middleNode(self, head: Optional[ListNode]) -> Optional[ListNode]:
    slow = head
    fast = head.next  # Start fast pointer one step ahead
    while fast and fast.next:
        slow = slow.next
        fast = fast.next.next
    if not fast:  # Odd number of nodes
        return slow
    return slow.next  # Even number of nodes
```

**Key Insights**:

1. **Starting Position**: Fast pointer starts at `head.next` instead of `head`. This ensures that when there are even number of nodes, we get the second middle node.

2. **Loop Termination**: The loop continues while `fast` and `fast.next` are not None:
   - For odd number of nodes: `fast` becomes None, slow points to the middle
   - For even number of nodes: `fast.next` becomes None, slow points to the first middle

3. **Final Decision**:
   - If `fast` is None (odd nodes): return `slow` (exact middle)
   - If `fast` is not None (even nodes): return `slow.next` (second middle)

**Example Walkthrough**:

For `[1,2,3,4,5]` (odd):
- Initial: slow=1, fast=2
- Step 1: slow=2, fast=4
- Step 2: slow=3, fast=None
- Return slow (3)

For `[1,2,3,4,5,6]` (even):
- Initial: slow=1, fast=2
- Step 1: slow=2, fast=4
- Step 2: slow=3, fast=6
- fast.next is None, exit loop
- Return slow.next (4)

# Tags

- Linked List
- Two Pointers
- Fast and Slow Pointer
- Tortoise and Hare Algorithm

