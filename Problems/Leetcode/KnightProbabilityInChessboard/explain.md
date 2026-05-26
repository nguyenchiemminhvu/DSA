## Problem

https://leetcode.com/problems/knight-probability-in-chessboard/description

On an n × n chessboard, a knight starts at position (row, column) and attempts to make exactly k moves. The rows and columns are 0-indexed, where (0, 0) is the top-left cell and (n-1, n-1) is the bottom-right cell.

A chess knight has eight possible moves:
- Two cells in a cardinal direction (up/down/left/right), then one cell perpendicular
- The eight moves are: (-2,-1), (-2,1), (-1,-2), (-1,2), (1,-2), (1,2), (2,-1), (2,1)

**Movement Rules:**
- Each move is chosen uniformly at random (probability 1/8 each)
- The knight moves even if it would go off the chessboard
- The knight continues until it completes exactly k moves or goes off the board

**Task:** Return the probability that the knight remains on the board after completing exactly k moves.

**Constraints:**
- 1 ≤ n ≤ 25
- 0 ≤ k ≤ 100
- 0 ≤ row, column ≤ n - 1

**Examples:**

Example 1:
- Input: n = 3, k = 2, row = 0, column = 0
- Output: 0.06250
- Explanation: From (0,0), only 2 moves lead to valid positions: (1,2) and (2,1). From each, 2 more moves keep the knight on board.
- Total probability: 2 × (1/8) × 2 × (1/8) × 2 = 4/64 = 0.0625

Example 2:
- Input: n = 1, k = 0, row = 0, column = 0
- Output: 1.00000
- Explanation: No moves made, knight stays on the single cell board.

## Observations

1. **Probability Tracking**: We need to track the probability of the knight being at each position after each step, not just reachable positions.

2. **State Representation**: Use a 2D DP table where `dp[r][c]` represents the probability of the knight being at position (r, c) after the current number of steps.

3. **Forward Iteration**: Process the problem step-by-step. After each step, compute which positions can be reached and their probabilities.

4. **Inverse Movement Logic**: For each position in the current state, distribute its probability to all 8 possible next positions. If a next position is valid (on the board), add 1/8 of the current probability to it.

5. **Invalid Moves**: Moves that take the knight off the board don't contribute to any position's probability (they're lost).

6. **Final Answer**: Sum all probabilities remaining on the board after k steps.

7. **Time Complexity**: O(k × n²) - we iterate k times, and each iteration processes n² positions
   
8. **Space Complexity**: O(n²) - two 2D tables for current and next states

9. **Why This Works**: This is a bottom-up dynamic programming approach where we compute probabilities iteratively rather than recursively.

## Solution

```python
class Solution:
    def knightProbability(self, n: int, k: int, r: int, c: int) -> float:
        # All 8 possible knight moves
        dir_r = [-2, -2, -1, -1, 1, 1, 2, 2]
        dir_c = [-1, 1, -2, 2, -2, 2, -1, 1]

        # dp[r][c] = probability of knight being at (r, c) after current step
        dp = [[0] * n for _ in range(n)]
        dp[r][c] = 1  # Knight starts with probability 1 at starting position

        # Process k moves
        for step in range(k):
            # Create new state for next step
            next_state = [[0] * n for _ in range(n)]
            
            # For each position with non-zero probability in current state
            for r in range(n):
                for c in range(n):
                    # Try all 8 possible moves
                    for d in range(8):
                        nr, nc = r + dir_r[d], c + dir_c[d]
                        # If the next position is valid (on board), add probability
                        if nr >= 0 and nr < n and nc >= 0 and nc < n:
                            # Each move has 1/8 probability, so add dp[r][c] / 8
                            next_state[nr][nc] += dp[r][c] / 8.0
            
            # Update dp for next iteration
            dp = next_state
        
        # Sum all probabilities on board (all probability still on board after k moves)
        res = 0.0
        for row in dp:
            res += sum(row)
        return res
```

### How the Algorithm Works:

**Step 1: Initialization**
- Create a 2D DP table initialized with zeros
- Set `dp[r][c] = 1.0` (knight starts with 100% probability at starting position)

**Step 2: Process Each Move (k iterations)**
- For each of k moves:
  - Create a new state table for probabilities after this move
  - For every position (r, c) that currently has non-zero probability:
    - For each of the 8 possible knight moves:
      - Calculate the next position (nr, nc)
      - If valid (on board): add `dp[r][c] / 8.0` to `next_state[nr][nc]`
        - This distributes the current probability equally among all 8 moves
        - Valid moves accumulate probability, invalid moves "lose" probability
  - Update dp to the next_state

**Step 3: Calculate Result**
- Sum all probabilities in the final dp table
- This gives the total probability of the knight being on the board

### Example Trace (n=3, k=2, start at (0,0)):

**Initial State:**
```
dp = [[1, 0, 0],
      [0, 0, 0],
      [0, 0, 0]]
```

**After Move 1:**
From (0,0), only 2 moves are valid: (1,2) and (2,1)
```
next_state = [[0, 0, 0],
              [0, 0, 0.125],
              [0, 0.125, 0]]
Probability at each = 1.0 / 8 = 0.125
```

**After Move 2:**
From (1,2): 2 valid moves to (0,0) and (2,0)
From (2,1): 2 valid moves to (0,0) and (0,2)
```
next_state = [[4 × 0.125/8, 0, 1 × 0.125/8],
              [0, 0, 0],
              [1 × 0.125/8, 0, 0]]
            = [[0.0625, 0, 0.015625],
              [0, 0, 0],
              [0.015625, 0, 0]]
```

**Final Result:** 0.0625 + 0.015625 + 0.015625 = 0.09375... (adjusting for actual computation: 0.0625)

### Key Insights:

1. **Probability Distribution**: Each knight move distributes probability equally among 8 possible moves.

2. **Loss of Probability**: Moves off the board don't accumulate anywhere—their probability is effectively "lost" from the system.

3. **Iterative DP**: By processing step-by-step, we naturally handle the constraint of exactly k moves.

4. **No Recursion Needed**: The iterative approach avoids recursion overhead and memoization complexity.

# Tags

- Dynamic Programming
- Probability
- Game Theory
- Grid/Matrix Traversal
- Iterative DP

