# Spiral Matrix IV

## Problem

https://leetcode.com/problems/spiral-matrix-iv/description/

You are given two integers `m` and `n`, which represent the dimensions of a matrix.

You are also given the `head` of a linked list of integers.

Generate an `m x n` matrix that contains the integers in the linked list presented in **spiral order** (clockwise), starting from the top-left of the matrix. If there are remaining empty spaces, fill them with `-1`.

Return the generated matrix.

### Example 1:
```
Input: m = 3, n = 5, head = [3,0,2,6,8,1,7,9,4,2,5,5,0]
Output: [[3,0,2,6,8],[5,0,-1,-1,1],[5,2,4,9,7]]
Explanation: The diagram shows how values are printed in spiral order.
Remaining spaces are filled with -1.
```

### Example 2:
```
Input: m = 1, n = 4, head = [0,1,2]
Output: [[0,1,2,-1]]
Explanation: Values are printed from left to right.
The last space is set to -1.
```

### Constraints:
- `1 <= m, n <= 10^5`
- `1 <= m * n <= 10^5`
- The number of nodes in the list is in the range `[1, m * n]`
- `0 <= Node.val <= 1000`

---

## Observations

1. **Spiral Order Pattern**: We need to fill the matrix in a clockwise spiral pattern:
   - Start at top-left (0, 0)
   - Move right → down → left → up → right (and repeat)
   
2. **Direction Management**: Four directions need to be cycled:
   - Right: (0, 1)
   - Down: (1, 0)
   - Left: (0, -1)
   - Up: (-1, 0)

3. **Boundary Conditions**: Change direction when:
   - We hit the matrix boundary (out of bounds)
   - We encounter an already visited cell

4. **Linked List Traversal**: Process nodes sequentially while traversing the matrix in spiral order

5. **Default Fill Value**: All cells are initialized to `-1`, so unvisited cells automatically have the correct value

6. **Visited Tracking**: Need to track visited cells to avoid overwriting values when the spiral path turns

---

## Solution

### Approach: Spiral Traversal with Direction Rotation

**Key Idea**: Simulate the spiral movement by maintaining current position and direction, rotating clockwise when we can't proceed.

### Algorithm Steps:

1. **Initialize Matrix**: Create `m x n` matrix filled with `-1`

2. **Setup Traversal State**:
   - Start position: `(0, -1)` (before first cell, will move right immediately)
   - Directions array: `[(0,1), (1,0), (0,-1), (-1,0)]` for right, down, left, up
   - Direction index: `0` (starting with right movement)
   - Visited set: Track filled positions

3. **Spiral Traversal**:
   - While there are nodes in the linked list:
     - Calculate next position using current direction
     - **If next position is valid** (in bounds AND not visited):
       - Mark as visited
       - Fill cell with node value
       - Move to next node
       - Update current position
     - **Else** (hit boundary or visited cell):
       - Rotate direction clockwise: `idir = (idir + 1) % 4`
       - Don't advance node or position (try new direction next iteration)

4. **Return Result**: The filled matrix

### Time Complexity: O(m × n)
- We visit each cell at most once
- Linked list traversal is O(number of nodes) ≤ O(m × n)
- Overall: O(m × n)

### Space Complexity: O(m × n)
- Matrix storage: O(m × n)
- Visited set: O(m × n) in worst case
- Overall: O(m × n)

---

### Code Implementation

```python
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next

class Solution:
    def spiralMatrix(self, m: int, n: int, head: Optional[ListNode]) -> List[List[int]]:
        # Initialize matrix with -1
        grid = [[-1] * n for _ in range(m)]
        
        # Starting position (will move to 0,0 on first iteration)
        r, c = 0, -1
        
        # Direction vectors: right, down, left, up (clockwise)
        directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
        idir = 0  # Start moving right
        
        # Track visited positions
        visited = set()
        
        # Process each node in the linked list
        while head:
            val = head.val
            
            # Calculate next position based on current direction
            next_r, next_c = r + directions[idir][0], c + directions[idir][1]
            
            # Check if next position is valid (in bounds and not visited)
            if next_r >= 0 and next_r < m and next_c >= 0 and next_c < n and (next_r, next_c) not in visited:
                # Valid position: fill it and advance
                visited.add((next_r, next_c))
                grid[next_r][next_c] = val
                head = head.next
                r, c = next_r, next_c
            else:
                # Invalid position: rotate direction clockwise
                idir = (idir + 1) % 4
        
        return grid
```

---

### Walkthrough Example

**Input**: `m = 3, n = 5, head = [3,0,2,6,8,1,7,9,4,2,5,5,0]`

**Spiral Path**:
```
Step  | Pos    | Dir   | Value | Grid State
------|--------|-------|-------|------------------
1     | (0,0)  | Right | 3     | [3, _, _, _, _]
2     | (0,1)  | Right | 0     | [3, 0, _, _, _]
3     | (0,2)  | Right | 2     | [3, 0, 2, _, _]
4     | (0,3)  | Right | 6     | [3, 0, 2, 6, _]
5     | (0,4)  | Right | 8     | [3, 0, 2, 6, 8]
-     | -      | Down  | -     | Turn (boundary)
6     | (1,4)  | Down  | 1     | [_, _, _, _, 1]
7     | (2,4)  | Down  | 7     | [_, _, _, _, 7]
-     | -      | Left  | -     | Turn (boundary)
8     | (2,3)  | Left  | 9     | [_, _, _, 9, 7]
9     | (2,2)  | Left  | 4     | [_, _, 4, 9, 7]
10    | (2,1)  | Left  | 2     | [_, 2, 4, 9, 7]
11    | (2,0)  | Left  | 5     | [5, 2, 4, 9, 7]
-     | -      | Up    | -     | Turn (boundary)
12    | (1,0)  | Up    | 5     | [5, _, _, _, 1]
-     | -      | Right | -     | Turn (visited)
13    | (1,1)  | Right | 0     | [5, 0, _, _, 1]
```

**Final Matrix**:
```
[3, 0, 2, 6, 8]
[5, 0,-1,-1, 1]
[5, 2, 4, 9, 7]
```

---

### Key Insights

1. **Starting Position Trick**: Starting at `(0, -1)` simplifies the code - first move goes to `(0, 0)` naturally

2. **Direction Rotation**: Using modulo `% 4` cycles through directions elegantly

3. **Boundary Detection**: Combined check for bounds AND visited cells handles both edge hits and spiral turns

4. **No Backtracking Needed**: Since we only advance when valid, we never need to undo moves

5. **Automatic -1 Fill**: Pre-initializing with `-1` means we don't need special handling for remaining cells

# Tags

`Matrix` `Linked List` `Simulation` `Spiral Traversal`

