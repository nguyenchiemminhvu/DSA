## Problem

https://leetcode.com/problems/remove-nodes-from-linked-list/description/

You are given the head of a linked list.

Remove every node which has a node with a **greater value** anywhere to the right side of it.

Return the head of the modified linked list.

### Example 1:
```
Input: head = [5,2,13,3,8]
Output: [13,8]
```
**Explanation:** The nodes that should be removed are 5, 2 and 3.
- Node 13 is to the right of node 5.
- Node 13 is to the right of node 2.
- Node 8 is to the right of node 3.

### Example 2:
```
Input: head = [1,1,1,1]
Output: [1,1,1,1]
```
**Explanation:** Every node has value 1, so no nodes are removed.

### Constraints:
- The number of the nodes in the given list is in the range `[1, 10^5]`.
- `1 <= Node.val <= 10^5`

## Observations

1. **Right-to-Left Property**: A node should be removed if there exists ANY node to its right with a greater value. This means we need to compare each node with all nodes that come after it.

2. **Monotonic Decreasing Sequence**: The resulting list will be in non-increasing order (monotonic decreasing or equal). Why? Because if we keep a node, it means there's no greater value to its right, so all remaining nodes to the right must be ≤ current node's value.

3. **Reverse Traversal Insight**: If we traverse from right to left, we can keep track of the maximum value seen so far. Any node less than this maximum should be removed.

4. **Stack-Based Approach**: We can use a stack to maintain nodes in decreasing order. As we process nodes from left to right, we can pop smaller values from the stack.

5. **List Reversal Approach**: Another approach is to:
   - Reverse the linked list
   - Traverse and keep only nodes that are >= maximum seen so far
   - Reverse again to restore order

## Solution

### Approach 1: Reverse List (Two-Pass) - O(1) Space

**Algorithm:**
1. Reverse the entire linked list
2. Traverse the reversed list from head (which is the original tail)
3. Keep track of the maximum value seen so far
4. Only keep nodes whose value >= current maximum
5. Reverse the list again to restore original order

**Visualization for [5,2,13,3,8]:**
```
Original:     5 -> 2 -> 13 -> 3 -> 8
Step 1:       8 -> 3 -> 13 -> 2 -> 5  (reversed)
Step 2:       8 -> 13                 (keep nodes >= max seen)
              max=8, keep 8
              max=8, skip 3 (3 < 8)
              max=13, keep 13
              max=13, skip 2 and 5
Step 3:       13 -> 8                 (reversed back)
```

**Time Complexity:** O(n) - Three passes through the list  
**Space Complexity:** O(1) - Only pointers, no extra data structures

---

### Approach 2: Recursion (Elegant)

**Algorithm:**
1. Recursively process the list from right to left
2. Return the maximum value seen in the right subtree
3. If current node's value < max from right, skip this node
4. If current node's value >= max from right, keep it and update max

**Visualization for [5,2,13,3,8]:**
```
Call stack (unwinding from right to left):
- Node(8): max_right = 0, keep 8, return max=8
- Node(3): max_right = 8, 3 < 8, skip, return max=8
- Node(13): max_right = 8, 13 >= 8, keep 13, return max=13
- Node(2): max_right = 13, 2 < 13, skip, return max=13
- Node(5): max_right = 13, 5 < 13, skip, return max=13
Result: 13 -> 8
```

**Implementation:**
```cpp
ListNode* removeNodes(ListNode* head) {
    if (!head || !head->next) return head;
    
    // Process the rest of the list first
    ListNode* nextNode = removeNodes(head->next);
    
    // If current node's value is less than next node, skip current
    if (head->val < nextNode->val) {
        return nextNode;
    }
    
    // Otherwise, keep current node and link to processed rest
    head->next = nextNode;
    return head;
}
```

**Time Complexity:** O(n)  
**Space Complexity:** O(n) - Recursion stack

---

### Approach 3: Stack (Single Pass)

**Algorithm:**
1. Use a stack (or vector) to store nodes
2. For each node, pop all smaller nodes from stack
3. The top of stack (if exists) becomes the previous node to link to current
4. Push current node to stack
5. The stack maintains nodes in decreasing order

**Visualization for [5,2,13,3,8]:**
```
Process 5:  stack = [5]
Process 2:  stack = [5, 2]  (2 < 5, just push)
Process 13: stack = [13]    (pop 2 and 5, push 13)
Process 3:  stack = [13, 3] (3 < 13, just push)
Process 8:  stack = [13, 8] (pop 3, push 8)
            Link: 13 -> 8

Final result: 13 -> 8
```

**Implementation:**
```cpp
ListNode* removeNodes(ListNode* head) {
    vector<ListNode*> stack;
    ListNode* curr = head;
    
    while (curr) {
        // Remove all nodes smaller than current from stack
        while (!stack.empty() && stack.back()->val < curr->val) {
            stack.pop_back();
        }
        
        // Link previous node to current (if exists)
        if (!stack.empty()) {
            stack.back()->next = curr;
        }
        
        stack.push_back(curr);
        curr = curr->next;
    }
    
    // Return the first node in stack (new head)
    return stack.empty() ? nullptr : stack[0];
}
```

**Time Complexity:** O(n) - Each node pushed and popped at most once  
**Space Complexity:** O(n) - Stack storage

---

### Why These Solutions Work:

**Reversal Approach**: When we reverse the list, the rightmost node becomes the first node. This is important because the rightmost node can never be removed (there's nothing to its right). As we traverse the reversed list, we're effectively looking at the original list from right to left. The maximum value we've seen represents the largest value to the "right" of the current node in the original list.

**Recursive Approach**: After processing the right part of the list, we know the first remaining node. If the current node is smaller than that, we skip it; otherwise, we keep it. This naturally processes from right to left due to the call stack.

**Stack Approach**: The stack maintains a monotonic decreasing sequence of nodes. When we encounter a larger value, all smaller values to its left must be removed (since this larger value is to their right).

---

### Key Takeaways

1. **Think Backwards**: Many linked list problems become easier when you think about processing from the end.

2. **Monotonic Property**: The result has a special property (non-increasing sequence) that can guide the solution.

3. **Multiple Approaches**: This problem can be solved with reversal, recursion, or stack - each with different trade-offs.

4. **Trade-offs**: 
   - Reversal: O(1) space, three passes
   - Recursion: O(n) space, elegant code, single conceptual pass
   - Stack: O(n) space, single pass, explicit structure

# Tags

Linked List, Stack, Recursion, Monotonic Stack, Two Pointers

