## Problem

https://leetcode.com/problems/maximum-points-in-an-archery-competition/description/

```
Alice and Bob are opponents in an archery competition. The competition has set the following rules:

1. Alice first shoots numArrows arrows and then Bob shoots numArrows arrows.
2. The points are then calculated as follows:
   - The target has integer scoring sections ranging from 0 to 11 inclusive.
   - For each section of the target with score k (in between 0 to 11), say Alice and Bob have shot ak and bk arrows on that section respectively.
   - If ak >= bk, then Alice takes k points. If ak < bk, then Bob takes k points.
   - However, if ak == bk == 0, then nobody takes k points.

You are given the integer numArrows and an integer array aliceArrows of size 12, which represents the number of arrows Alice shot on each scoring section from 0 to 11. Now, Bob wants to maximize the total number of points he can obtain.

Return the array bobArrows which represents the number of arrows Bob shot on each scoring section from 0 to 11. The sum of the values in bobArrows should equal numArrows.

Example 1:
Input: numArrows = 9, aliceArrows = [1,1,0,1,0,0,2,1,0,1,2,0]
Output: [0,0,0,0,1,1,0,0,1,2,3,1]
Explanation: Bob earns a total point of 4 + 5 + 8 + 9 + 10 + 11 = 47.

Example 2:
Input: numArrows = 3, aliceArrows = [0,0,1,0,0,0,0,0,0,0,0,2]
Output: [0,0,0,0,0,0,0,0,1,1,1,0]
Explanation: Bob earns a total point of 8 + 9 + 10 = 27.

Constraints:
- 1 <= numArrows <= 10^5
- aliceArrows.length == bobArrows.length == 12
- 0 <= aliceArrows[i], bobArrows[i] <= numArrows
- sum(aliceArrows[i]) == numArrows
```

## Observations

1. **Binary Decision Problem**: For each scoring section (0-11), Bob has two choices:
   - **Don't compete**: Let Alice take the points for that section (shoot 0 arrows)
   - **Compete to win**: Shoot exactly `alice_arrows[i] + 1` arrows to beat Alice and claim the points

2. **Key Insights**:
   - Bob doesn't need to shoot more than `alice_arrows[i] + 1` arrows on any section - just enough to beat Alice
   - If Alice shot 0 arrows on a section, Bob only needs 1 arrow to win that section
   - The problem has a small search space: only 12 sections, so we can explore all possibilities
   - Any leftover arrows can be placed in any section (typically section 0 to avoid waste)

3. **State Space**:
   - For each section, we make a binary choice: compete or skip
   - Total possible combinations: 2^12 = 4096 (manageable with DFS/backtracking)

4. **Optimization Strategy**:
   - Higher scoring sections (11, 10, 9...) are more valuable
   - But we must consider the cost (arrows needed) vs reward (points gained)
   - We need to find the optimal subset of sections to compete in

## Solution

### Approach: DFS with Backtracking

The solution uses **Depth-First Search (DFS)** to explore all possible combinations of sections Bob can win, tracking the maximum score achievable.

### Algorithm:

1. **Base Case** (i == 0):
   - When we've considered all sections from 11 down to 1
   - Place all remaining arrows in section 0 (doesn't affect score, but uses up arrows)
   - Update the global maximum if current score is better

2. **Recursive Cases**:
   For each section `i` from 11 down to 1:
   
   **Option 1: Skip this section**
   - Don't shoot any arrows here, let Alice take the points
   - Recurse with same remaining arrows and score
   
   **Option 2: Win this section** (if we have enough arrows)
   - Check if `remain > alice_arrows[i]` (we need at least `alice_arrows[i] + 1` arrows)
   - Shoot `alice_arrows[i] + 1` arrows on section `i`
   - Recurse with reduced arrows and increased score by `i` points
   - Backtrack: reset `tmp[i] = 0` to try other combinations

3. **State Tracking**:
   - `tmp[]`: Current arrow distribution being explored
   - `bob_arrows[]`: Best arrow distribution found so far
   - `bob_max_score`: Maximum score achieved

### Code Explanation:

```python
class Solution:
    def maximumBobPoints(self, num_arrows: int, alice_arrows: List[int]) -> List[int]:
        bob_max_score = -1
        bob_arrows = [0] * 12
        tmp = [0] * 12

        def dfs(i: int, remain: int, score: int) -> None:
            nonlocal bob_max_score, bob_arrows
            
            # Base case: reached section 0
            if i == 0:
                tmp[0] = remain  # Put all remaining arrows in section 0
                if score > bob_max_score:
                    bob_max_score = score
                    bob_arrows = tmp[:]  # Save the best configuration
                tmp[0] = 0  # Backtrack
                return
            
            # Option 1: Don't compete for section i
            dfs(i - 1, remain, score)

            # Option 2: Compete and win section i (if we have enough arrows)
            if remain > alice_arrows[i]:
                tmp[i] = alice_arrows[i] + 1  # Shoot just enough to beat Alice
                dfs(i - 1, remain - alice_arrows[i] - 1, score + i)
                tmp[i] = 0  # Backtrack
        
        dfs(11, num_arrows, 0)  # Start from section 11 (highest value)
        return bob_arrows
```

### Complexity Analysis:

- **Time Complexity**: O(2^12) = O(4096) ≈ O(1)
  - We explore at most 2^12 combinations (binary choice for 12 sections)
  - Each recursive call does constant work
  
- **Space Complexity**: O(12) = O(1)
  - Recursion depth is at most 12
  - We use fixed-size arrays of length 12

### Why This Works:

1. **Exhaustive Search**: We explore every possible combination of sections Bob can win
2. **Greedy Element**: By processing from section 11 down to 1, we naturally consider higher-value sections first
3. **Optimal Substructure**: The best score for sections 0..i depends on the best scores for sections 0..i-1
4. **No Overlapping Subproblems**: Each path through the decision tree is unique

### Example Walkthrough:

For `numArrows = 9, aliceArrows = [1,1,0,1,0,0,2,1,0,1,2,0]`:

- Section 11: Alice has 0, Bob shoots 1 arrow → wins 11 points (cost: 1 arrow)
- Section 10: Alice has 2, Bob shoots 3 arrows → wins 10 points (cost: 3 arrows)
- Section 9: Alice has 1, Bob shoots 2 arrows → wins 9 points (cost: 2 arrows)
- Section 8: Alice has 0, Bob shoots 1 arrow → wins 8 points (cost: 1 arrow)
- Section 5: Alice has 0, Bob shoots 1 arrow → wins 5 points (cost: 1 arrow)
- Section 4: Alice has 0, Bob shoots 1 arrow → wins 4 points (cost: 1 arrow)
- **Total**: 47 points using 9 arrows

# Tags
`Dynamic Programming`, `Backtracking`, `DFS`, `Bitmask`, `Exhaustive Search`, `Optimization`

