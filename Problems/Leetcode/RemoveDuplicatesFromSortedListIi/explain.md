## Problem

https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/

```
Given the head of a sorted linked list, delete all nodes that have duplicate numbers, 
leaving only distinct numbers from the original list. Return the linked list sorted as well.

Example 1:
Input: head = [1,2,3,3,4,4,5]
Output: [1,2,5]

Example 2:
Input: head = [1,1,1,2,3]
Output: [2,3]

Constraints:
- The number of nodes in the list is in the range [0, 300].
- -100 <= Node.val <= 100
- The list is guaranteed to be sorted in ascending order.
```

## Observations

1. **Key Difference from Remove Duplicates I**: In this problem, we must remove ALL occurrences of duplicate values, not just keep one copy. For example, if we have `[1,1,2]`, the result should be `[2]`, not `[1,2]`.

2. **Sorted List Property**: Since the list is sorted, all duplicate values are adjacent to each other. This means we can detect duplicates by comparing consecutive nodes.

3. **Edge Cases to Consider**:
   - Empty list: return `None`
   - Single node: return the node (no duplicates possible)
   - All nodes have duplicates: return `None`
   - Duplicates at the head: the new head will be different

4. **Recursive vs Iterative**: This problem can be solved both recursively and iteratively. The recursive approach is elegant but uses stack space proportional to the list length.

5. **Dummy Node Technique**: For iterative solutions, a dummy node before the head simplifies handling cases where the head itself needs to be removed.

## Solution

### Approach: Recursive Solution

The provided solution uses recursion to elegantly handle the removal of duplicate nodes.

**Algorithm**:

1. **Base Case**: If the list is empty or has only one node, return it as-is (no duplicates possible).

2. **Detect Duplicates at Current Position**:
   - While the current node and its next node have the same value, skip the next node
   - Mark that we found duplicates with a flag

3. **Recursive Decision**:
   - If duplicates were found at this position, skip the current node entirely by returning `deleteDuplicates(head.next)`
   - If no duplicates, keep the current node and recursively process the rest: `head.next = deleteDuplicates(head.next)`

**Example Walkthrough**: `head = [1,2,3,3,4,4,5]`

```
deleteDuplicates([1,2,3,3,4,4,5])
  → head.val = 1, no duplicates at position
  → head.next = deleteDuplicates([2,3,3,4,4,5])
       → head.val = 2, no duplicates at position
       → head.next = deleteDuplicates([3,3,4,4,5])
            → head.val = 3, found duplicate (3,3)
            → skip current node, return deleteDuplicates([4,4,5])
                 → head.val = 4, found duplicate (4,4)
                 → skip current node, return deleteDuplicates([5])
                      → head.val = 5, no duplicates
                      → return [5]
                 → return [5]
            → return [5]
       → head.next = [5]
       → return [2,5]
  → head.next = [2,5]
  → return [1,2,5]
```

**Complexity Analysis**:
- **Time Complexity**: $O(n)$ where n is the number of nodes. Each node is visited once.
- **Space Complexity**: $O(n)$ due to recursion stack. In the worst case (all unique values), the recursion depth equals the list length.

**Code**:
```python
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next

class Solution:
    def deleteDuplicates(self, head: Optional[ListNode]) -> Optional[ListNode]:
        # Base case: empty list or single node
        if not head or not head.next:
            return head
        
        # Check if current node has duplicates
        dup = False
        while head and head.next and head.next.val == head.val:
            head.next = head.next.next  # Skip duplicate
            dup = True
        
        # If duplicates found, skip current node entirely
        if dup:
            return self.deleteDuplicates(head.next)
        else:
            # Keep current node, process rest
            head.next = self.deleteDuplicates(head.next)
            return head
```

### Alternative: Iterative Solution with Dummy Node

```python
class Solution:
    def deleteDuplicates(self, head: Optional[ListNode]) -> Optional[ListNode]:
        # Dummy node simplifies edge cases
        dummy = ListNode(0, head)
        prev = dummy
        
        while head:
            # If current node is start of duplicates
            if head.next and head.val == head.next.val:
                # Skip all nodes with this value
                while head.next and head.val == head.next.val:
                    head = head.next
                # Connect prev to node after duplicates
                prev.next = head.next
            else:
                # No duplicate, move prev forward
                prev = prev.next
            
            head = head.next
        
        return dummy.next
```

**Iterative Complexity**:
- **Time Complexity**: $O(n)$
- **Space Complexity**: $O(1)$ - only uses constant extra space

# Tags
#linked-list #two-pointers #recursion #sorted-list #medium

