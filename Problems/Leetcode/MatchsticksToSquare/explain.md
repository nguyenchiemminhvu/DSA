## Problem

https://leetcode.com/problems/matchsticks-to-square/description/

You are given an integer array `matchsticks` where `matchsticks[i]` is the length of the ith matchstick. You want to use **all** the matchsticks to make one square. You should **not break** any stick, but you can link them up, and each matchstick must be used **exactly one time**.

Return `true` if you can make this square and `false` otherwise.

**Example 1:**
```
Input: matchsticks = [1,1,2,2,2]
Output: true
Explanation: You can form a square with length 2, one side of the square came from two sticks with length 1.
```

**Example 2:**
```
Input: matchsticks = [3,3,3,3,4]
Output: false
Explanation: You cannot find a way to form a square with all the matchsticks.
```

**Constraints:**
- `1 <= matchsticks.length <= 15`
- `1 <= matchsticks[i] <= 10^8`

## Observations

1. **Square Property**: A square has 4 equal sides. If we can use all matchsticks, then the sum of all matchsticks must be divisible by 4.

2. **Side Length**: If `sum(matchsticks) % 4 == 0`, then each side must have length `target = sum(matchsticks) / 4`.

3. **Impossible Cases**:
   - If the total sum is not divisible by 4, it's impossible to form a square.
   - If any single matchstick is longer than the target side length, it's impossible.

4. **Partition Problem**: This problem is essentially partitioning the array into 4 subsets where each subset sums to the target value.

5. **Search Space**: With up to 15 matchsticks, we have at most $2^{15}$ possible combinations, making backtracking feasible.

6. **Optimization - Sorting**: Sorting the matchsticks in descending order helps prune the search tree early. Larger matchsticks are more restrictive, so trying them first helps fail faster.

7. **Optimization - Early Termination**: Once we successfully fill 3 sides with the target sum, the remaining matchsticks must form the 4th side (since total sum is correct).

## Solution

### Approach: Backtracking with DFS

The solution uses depth-first search (DFS) with backtracking to try different combinations of matchsticks for each side of the square.

**Key Idea**: Try to build 4 sides of length `target` by assigning each matchstick to one of the sides. Use backtracking to explore all possibilities.

**Algorithm Steps**:

1. **Validation**:
   - Calculate total sum and check if divisible by 4
   - Calculate target side length
   - Sort matchsticks in descending order for early pruning
   - Check if largest matchstick exceeds target (impossible case)

2. **DFS with Backtracking**:
   - **State**: `(i, cur_sum, segments)`
     - `i`: current index to start searching from
     - `cur_sum`: current sum being built for the current side
     - `segments`: number of remaining sides to complete
   
   - **Base Cases**:
     - If only 1 segment remains: return `True` (the last segment will automatically be valid since sum is correct)
     - If current side is complete (`cur_sum == target`): start building next side from index 0
   
   - **Recursive Case**:
     - For each unused matchstick from index `i` to `n`:
       - Skip if already used or would exceed target
       - Mark as used, recursively try with this matchstick
       - If successful, return `True`
       - Otherwise, backtrack (mark as unused) and try next matchstick

**Time Complexity**: $O(4^n)$ in worst case, where $n$ is the number of matchsticks. Each matchstick can potentially go into any of the 4 sides. However, with pruning optimizations (sorting + early termination), the actual complexity is much better in practice.

**Space Complexity**: $O(n)$ for the recursion stack and the `used` array.

**Code Walkthrough**:

```python
class Solution:
    def makesquare(self, nums: List[int]) -> bool:
        s = sum(nums)
        k = 4  # number of sides in a square
        
        # Check if sum is divisible by 4
        if s % k != 0:
            return False
        
        n = len(nums)
        target = s // k
        
        # Sort in descending order for better pruning
        nums.sort(reverse=True)
        
        # If largest matchstick exceeds target, impossible
        if nums[0] > target:
            return False
        
        # Track which matchsticks have been used
        used = [False] * n
        
        def dfs(i: int, cur_sum: int, segments: int) -> bool:
            # Base case: only 1 segment left (must be valid)
            if segments == 1:
                return True
            
            # Current side complete, start building next side
            if cur_sum == target:
                return dfs(0, 0, segments - 1)
            
            # Try adding each unused matchstick to current side
            for j in range(i, n):
                # Skip if used or would exceed target
                if used[j] or cur_sum + nums[j] > target:
                    continue
                
                # Try using this matchstick
                used[j] = True
                if dfs(j + 1, cur_sum + nums[j], segments):
                    return True
                
                # Backtrack
                used[j] = False
            
            return False
        
        return dfs(0, 0, k)
```

**Why This Works**:
- We systematically try to build each of the 4 sides
- The `used` array ensures each matchstick is used exactly once
- Sorting helps fail fast when large matchsticks can't fit
- Once 3 sides are built correctly, the 4th must be valid (optimization)

# Tags
#backtracking #dfs #partition #array #recursion

