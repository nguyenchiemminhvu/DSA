## Problem

https://leetcode.com/problems/sort-list/

```
Given the head of a linked list, return the list after sorting it in ascending order.

Example 1:
Input: head = [4,2,1,3]
Output: [1,2,3,4]

Example 2:
Input: head = [-1,5,3,4,0]
Output: [-1,0,3,4,5]

Example 3:
Input: head = []
Output: []

Constraints:
- The number of nodes in the list is in the range [0, 5 * 10^4].
- -10^5 <= Node.val <= 10^5

Follow up: Can you sort the linked list in O(n log n) time and O(1) memory (i.e. constant space)?
```

## Observations

1. **Sorting Requirements**: We need to sort a linked list in ascending order with optimal time complexity.

2. **Time Complexity Constraint**: The follow-up asks for O(n log n) time complexity, which suggests algorithms like:
   - Merge Sort (most suitable for linked lists)
   - Quick Sort
   - Heap Sort

3. **Space Complexity Constraint**: O(1) constant space (excluding recursion stack) rules out converting to array.

4. **Linked List Properties**:
   - Cannot access elements by index (no random access)
   - Can only traverse sequentially
   - Easy to split and merge by changing pointers
   - Finding middle element requires two-pointer technique

5. **Why Merge Sort?**
   - Works well with linked lists (no need for random access)
   - Guaranteed O(n log n) time complexity
   - Can achieve O(1) auxiliary space (recursion stack is O(log n))
   - Splitting and merging are natural operations for linked lists

6. **Key Challenges**:
   - Finding the middle of the list to split it
   - Splitting the list into two halves
   - Merging two sorted lists back together

## Solution

### Approach: Merge Sort (Top-Down)

The solution uses **merge sort** algorithm adapted for linked lists:

#### Algorithm Steps:

1. **Base Case**: If the list is empty or has only one node, it's already sorted.

2. **Find Middle** (using slow-fast pointer technique):
   - `slow` pointer moves one step at a time
   - `fast` pointer moves two steps at a time
   - When `fast` reaches the end, `slow` is at the middle
   - Keep track of `prev` to split the list

3. **Split the List**:
   - Set `prev.next = None` to break the list into two halves
   - Left half: from `head` to `prev`
   - Right half: from `slow` to end

4. **Recursive Sort**:
   - Recursively sort the left half
   - Recursively sort the right half

5. **Merge**:
   - Use a dummy node to simplify merging
   - Compare values from both sorted halves
   - Append smaller value to result
   - Handle remaining nodes from either half

#### Complexity Analysis:

- **Time Complexity**: O(n log n)
  - The list is divided into halves recursively: O(log n) levels
  - At each level, we merge n nodes: O(n) work
  - Total: O(n log n)

- **Space Complexity**: O(log n)
  - Recursion stack depth: O(log n) for balanced splitting
  - Auxiliary space (excluding recursion): O(1)

#### Implementation Details:

**`merge()` function**:
```python
def merge(left: Optional[ListNode], right: Optional[ListNode]) -> Optional[ListNode]:
    dummy = ListNode(-1)  # Dummy node simplifies edge cases
    p = dummy
    
    # Merge two sorted lists
    while left and right:
        if left.val <= right.val:
            p.next = left
            left = left.next
        else:
            p.next = right
            right = right.next
        p = p.next
    
    # Attach remaining nodes
    if left:
        p.next = left
    if right:
        p.next = right
    
    return dummy.next  # Skip dummy node
```

**`merge_sort()` function**:
```python
def merge_sort(head: Optional[ListNode]) -> Optional[ListNode]:
    # Base case: empty or single node
    if not head or not head.next:
        return head
    
    # Find middle using slow-fast pointers
    slow = fast = head
    prev = None
    while fast and fast.next:
        prev = slow
        slow = slow.next
        fast = fast.next.next
    
    # Split the list
    prev.next = None
    
    # Recursively sort both halves
    left = merge_sort(head)
    right = merge_sort(slow)
    
    # Merge sorted halves
    new_head = merge(left, right)
    return new_head
```

#### Key Insights:

1. **Dummy Node Pattern**: Using a dummy node in merge function eliminates special cases for the first node.

2. **In-Place Sorting**: We reuse existing nodes by changing pointers, not creating new nodes.

3. **Two-Pointer Technique**: Finding the middle efficiently without counting nodes first.

4. **Splitting Strategy**: `prev.next = None` cleanly splits the list into two independent halves.

5. **Stability**: Merge sort is stable (maintains relative order of equal elements) due to `<=` comparison.

### Alternative: Bottom-Up Merge Sort (O(1) Space)

For true O(1) auxiliary space, a bottom-up iterative merge sort can be used, which avoids recursion stack overhead but is more complex to implement.

# Tags
`Linked List` `Two Pointers` `Divide and Conquer` `Sorting` `Merge Sort`

