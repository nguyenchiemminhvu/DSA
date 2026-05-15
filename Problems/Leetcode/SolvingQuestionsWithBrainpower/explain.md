## Problem

https://leetcode.com/problems/solving-questions-with-brainpower/description/

You are given a 0-indexed 2D integer array `questions` where `questions[i] = [pointsi, brainpoweri]`.

The array describes the questions of an exam, where you have to process the questions **in order** (starting from question 0) and make a decision whether to **solve** or **skip** each question:
- **Solve** question `i`: earn `points[i]` points, but you will be **unable to solve** each of the next `brainpower[i]` questions
- **Skip** question `i`: move to the next question

Return the **maximum points** you can earn for the exam.

### Example 1
**Input:** `questions = [[3,2],[4,3],[4,4],[2,5]]`  
**Output:** `5`

**Explanation:** Solve questions 0 and 3
- Solve question 0: Earn 3 points, skip next 2 questions
- Unable to solve questions 1 and 2
- Solve question 3: Earn 2 points
- Total: 3 + 2 = 5 points

### Example 2
**Input:** `questions = [[1,1],[2,2],[3,3],[4,4],[5,5]]`  
**Output:** `7`

**Explanation:** Solve questions 1 and 4
- Skip question 0
- Solve question 1: Earn 2 points, skip next 2 questions
- Unable to solve questions 2 and 3
- Solve question 4: Earn 5 points
- Total: 2 + 5 = 7 points

---

## Observations

1. **Sequential Processing**: Questions must be processed in order. At each question, we have exactly two choices: solve or skip.

2. **State Definition**: At each question `i`, the state is completely defined by the current position. The maximum points we can get from question `i` onwards depends only on our decision at question `i`.

3. **Skip Cost is Free**: Skipping a question has no cost—we simply move to the next question. Only solving has a consequence (skipping future questions).

4. **Non-trivial Skip Decision**: Even if we can solve a question with high points, we might prefer to skip it because the `brainpower` cost might prevent us from solving more valuable questions later.

5. **Backward Traversal Insight**: Working backwards from the last question simplifies the recurrence relation since we already know the maximum points we can earn from future questions.

6. **Overlapping Subproblems**: The same question index can be reached through different sequences of decisions, making memoization effective (though bottom-up DP is more elegant here).

---

## Solution

### Approach: Dynamic Programming (Bottom-Up)

**Intuition**: Use bottom-up DP where `dp[i]` represents the maximum points we can earn starting from question `i` onwards.

**Recurrence Relation**:
At each question `i`, we have two choices:
- **Skip**: Move to question `i+1`, earning `dp[i+1]` points
- **Solve**: Earn `questions[i][0]` points and jump to question `i + questions[i][1] + 1`, earning `dp[i + questions[i][1] + 1]` points

Therefore: $$dp[i] = \max(dp[i+1], \, questions[i][0] + dp[i + questions[i][1] + 1])$$

**Base Case**: `dp[n] = 0` (no more questions to solve)

**Direction**: Process from `n-1` down to `0` (backward)

### Code

```python
class Solution:
    def mostPoints(self, questions: List[List[int]]) -> int:
        n = len(questions)
        
        # dp[i] = maximum points we can earn from question i onwards
        dp = [0] * (n + 1)
        
        # Process questions from right to left
        for i in range(n - 1, -1, -1):
            # Option 1: Skip question i → earn dp[i+1]
            skip = dp[i + 1]
            
            # Option 2: Solve question i → earn points[i] + dp[next_available]
            next_available = i + questions[i][1] + 1
            solve = questions[i][0] + dp[next_available]
            
            # Take the maximum
            dp[i] = max(skip, solve)
        
        return dp[0]
```

### Complexity Analysis

- **Time Complexity**: $O(n)$ — We iterate through the questions array once, from right to left
- **Space Complexity**: $O(n)$ — We maintain a DP array of size $n+1$

### Alternative: Top-Down Memoization

```python
class Solution:
    def mostPoints(self, questions: List[List[int]]) -> int:
        n = len(questions)
        mem = {}
        
        def maxPoints(i: int) -> int:
            # Base case: no more questions
            if i >= n:
                return 0
            
            # Check memoization
            if i in mem:
                return mem[i]
            
            # Option 1: Skip question i
            skip = maxPoints(i + 1)
            
            # Option 2: Solve question i
            solve = questions[i][0] + maxPoints(i + questions[i][1] + 1)
            
            # Store and return the maximum
            mem[i] = max(skip, solve)
            return mem[i]
        
        return maxPoints(0)
```

**Why bottom-up is preferred here**:
- Avoids recursion overhead
- More intuitive state transitions
- Easier to reason about bounds checking

### Walkthrough: Example 1

`questions = [[3,2],[4,3],[4,4],[2,5]]`

Building DP table (bottom-up):

| i | question | skip (dp[i+1]) | solve (points + dp[next]) | dp[i] |
|---|----------|----------------|--------------------------|-------|
| 4 | - | 0 | - | 0 |
| 3 | [2,5] | 0 | 2 + dp[9]=2 | 2 |
| 2 | [4,4] | 2 | 4 + dp[7]=4 | 4 |
| 1 | [4,3] | 4 | 4 + dp[5]=4 | 4 |
| 0 | [3,2] | 4 | 3 + dp[3]=5 | 5 |

**Answer**: `dp[0] = 5`

### Key Insights

1. **When to Solve vs. Skip**:
   - Solve if: `questions[i][0] + dp[next] > dp[i+1]`
   - Skip otherwise

2. **Skip Cost Analysis**: The skip cost is 0, but the solve cost can be high. A question with high brainpower can "lock out" many future high-value questions.

3. **Greedy Doesn't Work**: Simply solving the highest-point questions first doesn't guarantee the optimal solution (see Example 2).

---

# Tags

- Dynamic Programming
- Array
- Backward Iteration
- Decision Making (Solve/Skip)
- Recurrence Relation

