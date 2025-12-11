## Problem

https://leetcode.com/problems/next-greater-node-in-linked-list/description/

```
You are given the head of a linked list with n nodes.

For each node in the list, find the value of the next greater node. That is, for each node, 
find the value of the first node that is next to it and has a strictly larger value than it.

Return an integer array answer where answer[i] is the value of the next greater node of the 
ith node (1-indexed). If the ith node does not have a next greater node, set answer[i] = 0.

Example 1:
Input: head = [2,1,5]
Output: [5,5,0]
Explanation:
- Node 0 (value 2): next greater is 5
- Node 1 (value 1): next greater is 5
- Node 2 (value 5): no next greater, so 0

Example 2:
Input: head = [2,7,4,3,5]
Output: [7,0,5,5,0]
Explanation:
- Node 0 (value 2): next greater is 7
- Node 1 (value 7): no next greater (largest), so 0
- Node 2 (value 4): next greater is 5
- Node 3 (value 3): next greater is 5
- Node 4 (value 5): no next greater, so 0

Constraints:
- 1 <= n <= 10^4
- 1 <= Node.val <= 10^9
```

## Observations

1. **Next Greater Element Pattern**: This is a classic "next greater element" problem, typically solved using a monotonic stack.

2. **Linked List Traversal**: Unlike arrays, we can only traverse a linked list forward once. We cannot randomly access elements by index.

3. **Result Array Size**: We need to know the size of the result array upfront, which requires either:
   - Counting nodes first
   - Building the result as we go

4. **Stack Approach**: As we traverse the list, we can use a stack to keep track of nodes that haven't found their next greater element yet.

5. **Monotonic Decreasing Stack**: The stack should maintain elements in decreasing order. When we find a larger element, it's the "next greater" for all smaller elements in the stack.

6. **Key Insight**: Elements waiting for a next greater value can be stored in a stack with their indices. When we encounter a larger value, we can update all applicable indices in the result array.

## Solution

### Approach: Monotonic Stack

**Algorithm:**
1. **First Pass**: Traverse the linked list to initialize the result array with zeros (default when no next greater exists)
2. **Second Pass**: Use a stack to track pending nodes (value, index) that haven't found their next greater element
3. **For each node**:
   - While the stack is not empty and the current value is greater than the top of stack:
     - Pop from stack and update result[index] with current value
   - Push current (value, index) onto stack
4. Remaining elements in stack have no next greater element (already set to 0)

**Why this works:**
- The stack maintains nodes in decreasing order
- When we find a larger value, it's guaranteed to be the "next greater" for all smaller values in the stack
- We process each node exactly once, achieving O(n) time complexity

**Time Complexity**: O(n)
- First pass: O(n) to initialize result array
- Second pass: O(n) - each element is pushed and popped at most once

**Space Complexity**: O(n)
- Result array: O(n)
- Stack: O(n) in worst case (strictly decreasing list)

**Step-by-step execution for [2,7,4,3,5]:**

| Step | Current Node | Stack Before | Action | Stack After | Result Array |
|------|--------------|--------------|--------|-------------|--------------|
| Init | - | [] | Initialize | [] | [0,0,0,0,0] |
| 1 | 2 (i=0) | [] | Push (2,0) | [(2,0)] | [0,0,0,0,0] |
| 2 | 7 (i=1) | [(2,0)] | Pop (2,0), set res[0]=7, Push (7,1) | [(7,1)] | [7,0,0,0,0] |
| 3 | 4 (i=2) | [(7,1)] | Push (4,2) | [(7,1),(4,2)] | [7,0,0,0,0] |
| 4 | 3 (i=3) | [(7,1),(4,2)] | Push (3,3) | [(7,1),(4,2),(3,3)] | [7,0,0,0,0] |
| 5 | 5 (i=4) | [(7,1),(4,2),(3,3)] | Pop (3,3), set res[3]=5<br>Pop (4,2), set res[2]=5<br>Push (5,4) | [(7,1),(5,4)] | [7,0,5,5,0] |
| End | - | [(7,1),(5,4)] | Remaining have no next greater | - | [7,0,5,5,0] |

**Key Points:**
- Elements in stack represent nodes still waiting for their next greater element
- When a larger value is found, it resolves all pending smaller values
- Stack maintains decreasing order (bottom to top: larger to smaller)

# Tags
`Linked List` `Stack` `Monotonic Stack` `Array` `Next Greater Element`

