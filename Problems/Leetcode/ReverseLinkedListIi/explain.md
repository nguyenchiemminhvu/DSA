## Problem

https://leetcode.com/problems/reverse-linked-list-ii/description/

```
Given the head of a singly linked list and two integers left and right where left <= right, 
reverse the nodes of the list from position left to position right, and return the reversed list.

Example 1:
Input: head = [1,2,3,4,5], left = 2, right = 4
Output: [1,4,3,2,5]

Example 2:
Input: head = [5], left = 1, right = 1
Output: [5]

Constraints:
- The number of nodes in the list is n
- 1 <= n <= 500
- -500 <= Node.val <= 500
- 1 <= left <= right <= n

Follow-up: Could you do it in one pass?
```

## Observations

1. **Partial Reversal**: Unlike reversing an entire linked list, we only need to reverse a specific segment from position `left` to position `right`.

2. **Position-Based**: Positions are 1-indexed, not 0-indexed. This affects how we traverse to find the target nodes.

3. **Edge Cases**:
   - Single node list (left == right == 1)
   - Reversing from the head (left == 1)
   - Reversing the entire list (left == 1, right == n)
   - Adjacent positions (right == left + 1)

4. **Key Nodes to Track**:
   - Node before position `left` (to reconnect the reversed segment)
   - Node at position `left` (becomes the tail of reversed segment)
   - Node at position `right` (becomes the head of reversed segment)
   - Node after position `right` (to reconnect after reversal)

5. **Two Approaches**:
   - **Value swap** (using stack): Simpler but requires O(n) extra space
   - **Pointer manipulation** (in-place): More complex but O(1) space and truly "one pass"

## Solution

### Approach 1: Stack-Based Value Reversal (Current Implementation)

**Algorithm:**

1. **Create Dummy Node**: Use a dummy node pointing to head to simplify edge cases (especially when left == 1).

2. **Locate Key Positions**:
   - Use helper function `get_pair_node(head, idx)` to find the pair (prev, current) at any index
   - Find `prev_left` (node before left) and `p_left` (node at left)
   - Find `prev_right` (node before right) and `p_right` (node at right)

3. **Store Values in Stack**:
   - Traverse from `p_left` to `p_right` (inclusive)
   - Push each node's value onto a stack
   - Stack naturally provides LIFO order for reversal

4. **Reverse Values**:
   - Traverse the same segment again
   - Pop values from stack and assign to nodes
   - This effectively reverses the values in the segment

5. **Return Result**: Return the original head (unchanged structure, only values modified)

**Time Complexity**: O(n)
- Finding left position: O(left)
- Finding right position: O(right)  
- Storing values: O(right - left + 1)
- Reversing values: O(right - left + 1)
- Overall: O(n) where n is the number of nodes

**Space Complexity**: O(right - left + 1)
- Stack stores values from left to right position
- Not true O(1) space as required by follow-up

**Code:**
```python
def reverseBetween(self, head: Optional[ListNode], left: int, right: int) -> Optional[ListNode]:
    def get_pair_node(head: Optional[ListNode], idx: int) -> Tuple[ListNode]:
        prev = head
        cur = head.next
        while idx > 1:
            prev = cur
            cur = cur.next
            idx -= 1
        return (prev, cur)
    
    if not head or not head.next:
        return head
    
    dummy = ListNode(0, head)
    prev_left, p_left = get_pair_node(dummy, left)
    prev_right, p_right = get_pair_node(dummy, right)
    
    # Store values in stack
    st = []
    p = p_left
    while p != p_right.next:
        st.append(p.val)
        p = p.next
    
    # Reverse by popping from stack
    p = p_left
    while p != p_right.next:
        p.val = st.pop()
        p = p.next
    
    return head
```

### Approach 2: In-Place Pointer Reversal (One Pass, O(1) Space)

For the follow-up question, here's the optimal solution:

**Algorithm:**

1. Create dummy node and find the node before position `left`
2. Start reversing by repeatedly moving the next node to the front
3. This is done by pointer manipulation without changing values

**Visualization:**
```
Original: dummy -> 1 -> 2 -> 3 -> 4 -> 5, left=2, right=4

Step 1: dummy -> 1 -> 3 -> 2 -> 4 -> 5  (move 3 to front)
Step 2: dummy -> 1 -> 4 -> 3 -> 2 -> 5  (move 4 to front)
Result: [1, 4, 3, 2, 5]
```

**Code:**
```python
def reverseBetween(self, head: Optional[ListNode], left: int, right: int) -> Optional[ListNode]:
    if not head or left == right:
        return head
    
    dummy = ListNode(0, head)
    prev = dummy
    
    # Move to node before left position
    for _ in range(left - 1):
        prev = prev.next
    
    # Start reversing
    current = prev.next
    for _ in range(right - left):
        next_node = current.next
        current.next = next_node.next
        next_node.next = prev.next
        prev.next = next_node
    
    return dummy.next
```

**Time Complexity**: O(n) - truly one pass
**Space Complexity**: O(1) - only pointers used

**Key Insight**: Instead of reversing the entire segment at once, we repeatedly extract the next node and insert it at the beginning of the segment. After `right - left` iterations, the segment is reversed.

# Tags

`Linked List`, `Two Pointers`, `Stack`, `In-Place Algorithm`

