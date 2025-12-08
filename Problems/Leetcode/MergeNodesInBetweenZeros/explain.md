## Problem

https://leetcode.com/problems/merge-nodes-in-between-zeros/

You are given the head of a linked list, which contains a series of integers separated by 0's. The beginning and end of the linked list will have `Node.val == 0`.

For every two consecutive 0's, merge all the nodes lying in between them into a single node whose value is the sum of all the merged nodes. The modified list should not contain any 0's.

Return the head of the modified linked list.

### Example 1:
```
Input: head = [0,3,1,0,4,5,2,0]
Output: [4,11]
Explanation: 
The above figure represents the given linked list. The modified list contains
- The sum of the nodes marked in green: 3 + 1 = 4.
- The sum of the nodes marked in red: 4 + 5 + 2 = 11.
```

### Example 2:
```
Input: head = [0,1,0,3,0,2,2,0]
Output: [1,3,4]
Explanation: 
The above figure represents the given linked list. The modified list contains
- The sum of the nodes marked in green: 1 = 1.
- The sum of the nodes marked in red: 3 = 3.
- The sum of the nodes marked in yellow: 2 + 2 = 4.
```

### Constraints:
- The number of nodes in the list is in the range `[3, 2 * 10^5]`.
- `0 <= Node.val <= 1000`
- There are no two consecutive nodes with `Node.val == 0`.
- The beginning and end of the linked list have `Node.val == 0`.

## Observations

1. **Pattern Recognition**: The list always starts and ends with 0, creating clear boundaries for segments.

2. **Segment Structure**: Between any two consecutive 0's, we have a segment of non-zero values that need to be summed.

3. **No Consecutive Zeros**: The constraint that there are no two consecutive 0's means every 0 (except the first) marks the end of a segment that needs to be merged.

4. **Linear Traversal**: We only need to traverse the list once, making this a single-pass problem.

5. **Accumulation Strategy**: We can use a running sum that accumulates values between zeros and creates a new node when we encounter a zero.

6. **Result List Building**: We need to build a new linked list with the merged values, which can be done efficiently with a dummy head approach.

## Solution

### Approach: Single Pass with Running Sum

The solution uses a straightforward single-pass traversal with the following strategy:

**Algorithm Steps:**

1. **Initialize Variables**:
   - `s = 0`: Running sum to accumulate values between zeros
   - `new_head = ListNode(0)`: Dummy head for the result list
   - `p_head = new_head`: Pointer to build the result list

2. **Traverse the Original List**:
   - For each node, check if its value is 0
   - If it's 0 and we have accumulated a sum (`s > 0`):
     - Create a new node with the accumulated sum
     - Append it to the result list
     - Reset the sum to 0
   - If it's not 0:
     - Add the value to the running sum

3. **Return Result**:
   - Return `new_head.next` to skip the dummy head

### Why This Works:

- **First Zero**: When we encounter the first zero, `s = 0`, so we don't create a node (this is correct since the first zero is just a boundary marker).

- **Subsequent Zeros**: Each subsequent zero marks the end of a segment, triggering the creation of a new node with the sum.

- **Last Zero**: The last zero also triggers node creation if there's a sum accumulated, completing the last segment.

### Complexity Analysis:

**Time Complexity: O(n)**
- We traverse the entire linked list exactly once
- Each node is visited once
- Creating new nodes is O(1) per segment

**Space Complexity: O(1) for algorithm, O(k) for output**
- `s` and pointers use constant extra space
- The output list has k nodes where k is the number of segments (zero pairs)
- Not counting the output, the algorithm uses O(1) extra space

### Visual Example:

```
Input:  0 -> 3 -> 1 -> 0 -> 4 -> 5 -> 2 -> 0
        ^         ^    ^              ^    ^
      start    s=0+3  s=4         s=0+4   s=11
                  +1              +5+2
                  =4              =11
                create           create
                node(4)          node(11)

Output: 4 -> 11
```

### Key Insights:

1. **Dummy Head Pattern**: Using a dummy head simplifies list construction by eliminating special cases for the first node.

2. **State Machine**: The algorithm essentially implements a state machine:
   - State 1: Accumulating (when traversing non-zero nodes)
   - State 2: Finalizing (when encountering a zero with accumulated sum)

3. **Boundary Handling**: The `if s > 0` check elegantly handles both the first zero (skip) and subsequent zeros (create node).

4. **No Need for Modification**: We don't modify the original list; we create a new one, which is cleaner and avoids side effects.

# Tags
`Linked List` `Two Pointers` `Simulation`

