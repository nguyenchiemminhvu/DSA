## Problem

https://leetcode.com/problems/beautiful-arrangement/description/

```
Suppose you have n integers labeled 1 through n. A permutation of those n integers perm 
(1-indexed) is considered a beautiful arrangement if for every i (1 <= i <= n), either 
of the following is true:

- perm[i] is divisible by i.
- i is divisible by perm[i].

Given an integer n, return the number of the beautiful arrangements that you can construct.

Example 1:
Input: n = 2
Output: 2
Explanation: 
The first beautiful arrangement is [1,2]:
    - perm[1] = 1 is divisible by i = 1
    - perm[2] = 2 is divisible by i = 2
The second beautiful arrangement is [2,1]:
    - perm[1] = 2 is divisible by i = 1
    - i = 2 is divisible by perm[2] = 1

Example 2:
Input: n = 1
Output: 1

Constraints:
- 1 <= n <= 15
```

## Observations

1. **Beautiful Arrangement Constraint**: For position `i` (1-indexed), we can place value `val` if:
   - `i % val == 0` (position divisible by value), OR
   - `val % i == 0` (value divisible by position)

2. **Small Input Size**: Since `n <= 15`, we can use backtracking/DFS to explore all possible permutations without worrying about timeout.

3. **State Space**: At each position, we need to:
   - Track which numbers have been used (to ensure permutation property)
   - Try all unused numbers that satisfy the divisibility constraint
   - Backtrack when we've explored all possibilities

4. **Optimization Opportunity**: We only try values that satisfy the divisibility constraint rather than trying all unused values and then checking.

## Solution

### Approach: Backtracking with Pruning

**Algorithm**:
1. Use a recursive DFS function that builds the permutation position by position (0-indexed internally, representing 1-indexed positions)
2. Maintain a `used` set to track which values have been placed in the permutation
3. At each position `i`:
   - Try each value from 1 to n that:
     - Hasn't been used yet
     - Satisfies the divisibility constraint with position `i+1` (converting to 1-indexed)
   - Recursively build the rest of the permutation
   - Backtrack by removing the value from the used set
4. Base case: When we've filled all n positions, increment the count

**Time Complexity**: O(k) where k is the number of valid beautiful arrangements. In the worst case, this approaches O(n!), but pruning significantly reduces the actual number of states explored.

**Space Complexity**: O(n) for the recursion stack and the used set.

**Code**:
```python
class Solution:
    def countArrangement(self, n: int) -> int:
        count = 0
        used = set()
        
        def dfs(i: int) -> None:
            nonlocal count
            # Base case: filled all positions
            if i >= n:
                count += 1
                return
            
            # Try each value from 1 to n
            for val in range(1, n+1):
                # Check divisibility constraint (i is 0-indexed, so position is i+1)
                if (i + 1) % val == 0 or val % (i + 1) == 0:
                    if val not in used:
                        # Choose
                        used.add(val)
                        # Explore
                        dfs(i + 1)
                        # Unchoose (backtrack)
                        used.remove(val)
        
        dfs(0)
        return count
```

**Key Points**:
- **Position vs Index**: The code uses 0-indexed positions internally (`i`), but the problem uses 1-indexed positions, so we use `i+1` in the divisibility checks
- **Pruning**: We only explore values that satisfy the divisibility constraint, which significantly reduces the search space
- **Backtracking Pattern**: Classic choose-explore-unchoose pattern with the used set

**Example Trace (n=2)**:
```
dfs(0):  # position 1
  try val=1: (1%1==0) ✓, not used ✓
    used={1}, dfs(1):  # position 2
      try val=1: used ✗
      try val=2: (2%2==0) ✓, not used ✓
        used={1,2}, dfs(2): count=1 ✓
  try val=2: (1%2==0) ✓, not used ✓
    used={2}, dfs(1):  # position 2
      try val=1: (2%1==0) ✓, not used ✓
        used={2,1}, dfs(2): count=2 ✓
      try val=2: used ✗

Result: 2 beautiful arrangements
```

# Tags
- Backtracking
- Recursion
- Permutation
- DFS

