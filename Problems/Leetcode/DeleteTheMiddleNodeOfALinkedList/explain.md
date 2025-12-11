## Problem

https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/description/

```
You are given the head of a linked list. Delete the middle node, and return the head of the modified linked list.

The middle node of a linked list of size n is the ⌊n / 2⌋th node from the start using 0-based indexing, where ⌊x⌋ denotes the largest integer less than or equal to x.

For n = 1, 2, 3, 4, and 5, the middle nodes are 0, 1, 1, 2, and 2, respectively.

Example 1:
Input: head = [1,3,4,7,1,2,6]
Output: [1,3,4,1,2,6]
Explanation: Since n = 7, node 3 with value 7 is the middle node. We return the new list after removing this node.

Example 2:
Input: head = [1,2,3,4]
Output: [1,2,4]
Explanation: For n = 4, node 2 with value 3 is the middle node.

Example 3:
Input: head = [2,1]
Output: [2]
Explanation: For n = 2, node 1 with value 1 is the middle node. Node 0 with value 2 is the only node remaining.

Constraints:
- The number of nodes in the list is in the range [1, 10^5].
- 1 <= Node.val <= 10^5
```

## Observations

1. **Middle Node Definition**: The middle node is at index ⌊n/2⌋ using 0-based indexing:
   - n=1: middle at index 0 (only node)
   - n=2: middle at index 1 (second node)
   - n=3: middle at index 1 (second node)
   - n=4: middle at index 2 (third node)
   - n=5: middle at index 2 (third node)

2. **Edge Cases**:
   - Single node list (n=1): After removing the middle, return `None`
   - Two node list (n=2): Remove the second node, return only the first

3. **Key Challenge**: We need to find the middle node efficiently without knowing the list length beforehand

4. **Two-Pointer Technique**: Using slow and fast pointers is optimal:
   - Fast pointer moves 2 steps at a time
   - Slow pointer moves 1 step at a time
   - When fast reaches the end, slow is at the middle

5. **Deletion Requirement**: To delete a node, we need a reference to the node **before** it, so we track a `prev` pointer

## Solution

### Approach: Two-Pointer (Slow-Fast) Technique

**Time Complexity**: O(n) where n is the number of nodes  
**Space Complexity**: O(1) - only using a few pointers

### Algorithm

1. **Handle Edge Cases**: If the list is empty or has only one node, return `None`

2. **Initialize Pointers**:
   - `prev = None`: tracks the node before the middle
   - `slow = head`: will eventually point to the middle node
   - `fast = head`: moves twice as fast to find the end

3. **Traverse the List**:
   - Move `fast` two steps and `slow` one step at a time
   - Update `prev` to track the node before `slow`
   - When `fast` reaches the end, `slow` is at the middle

4. **Delete the Middle Node**: 
   - Set `prev.next = slow.next` to skip over the middle node

5. **Return** the modified list head

### Code Walkthrough

```python
def deleteMiddle(self, head: Optional[ListNode]) -> Optional[ListNode]:
    # Edge case: empty list or single node
    if not head or not head.next:
        return None
    
    prev = None
    slow = fast = head
    
    # Move fast 2x speed of slow
    while fast and fast.next:
        prev = slow          # Track node before middle
        slow = slow.next     # Move slow one step
        fast = fast.next.next  # Move fast two steps
    
    # Delete middle node
    prev.next = slow.next
    return head
```

### Example Trace

For `head = [1,3,4,7,1,2,6]` (n=7):

```
Initial: prev=None, slow=1, fast=1

Iteration 1:
  prev=1, slow=3, fast=4
  
Iteration 2:
  prev=3, slow=4, fast=1
  
Iteration 3:
  prev=4, slow=7, fast=6
  
Iteration 4:
  prev=7, slow=1, fast=None (fast.next is None, loop ends)

Now: slow points to middle node (7)
     prev points to node before middle (4)
     
Delete: prev.next = slow.next
        (4).next = (1)
        
Result: [1,3,4,1,2,6]
```

### Why This Works

- When `fast` moves 2 steps for every 1 step of `slow`, by the time `fast` reaches the end (or goes past it), `slow` will be at exactly the middle position
- The `prev` pointer stays one step behind `slow`, giving us the reference we need to perform the deletion
- For odd-length lists: `fast` lands on the last node, `slow` is at ⌊n/2⌋
- For even-length lists: `fast` goes past the end, `slow` is at ⌊n/2⌋

# Tags

`Linked List` `Two Pointers` `Fast-Slow Pointers`

