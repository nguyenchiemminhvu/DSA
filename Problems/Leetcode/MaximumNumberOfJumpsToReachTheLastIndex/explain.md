## Problem

https://leetcode.com/problems/maximum-number-of-jumps-to-reach-the-last-index/description

Given a 0-indexed array `nums` of n integers and an integer `target`, you start at index 0. In one step, you can jump from index i to any index j where:
- `0 <= i < j < n` (can only jump forward)
- `-target <= nums[j] - nums[i] <= target` (difference constraint)

**Return** the maximum number of jumps to reach index n-1, or -1 if unreachable.

**Examples:**
- `nums = [1,3,6,4,1,2], target = 2` → Output: 3 (path: 0→1→3→5)
- `nums = [1,3,6,4,1,2], target = 3` → Output: 5 (path: 0→1→2→3→4→5)
- `nums = [1,3,6,4,1,2], target = 0` → Output: -1 (no valid jumps)

## Observations

1. **Forward-only jumps**: We can only jump to indices greater than current, ensuring progress toward the end.

2. **Difference constraint**: Not all forward indices are reachable—only those where the value difference is within `[-target, target]`.

3. **Maximize jumps**: We want the longest path, not the shortest. This is different from classic shortest-path problems.

4. **Greedy fails**: A greedy approach won't work because jumping to the farthest reachable index might block access to more intermediate indices that lead to more jumps overall.

5. **Optimal substructure**: The maximum jumps to reach index j is:
   - 0 if j = 0
   - -1 if unreachable from any previous index
   - Otherwise: max(dp[i] + 1) for all i where i < j and `|nums[j] - nums[i]| <= target`

6. **DAG property**: Since we can only jump forward (i → j where i < j), the index ordering forms a DAG (directed acyclic graph), eliminating cycles and enabling DP.

## Solution

### Approach: Dynamic Programming (Iterative)

**Key idea**: Use `dp[i]` to store the maximum number of jumps needed to reach index i.

```python
class Solution:
    def maximumJumps(self, nums: List[int], target: int) -> int:
        n = len(nums)
        dp = [-1] * n          # Initialize all as unreachable
        dp[0] = 0              # Base case: 0 jumps to stay at start
        
        # Process indices in order (ensures we process dependencies first)
        for i in range(n - 1):
            if dp[i] == -1:    # If current index is unreachable, skip it
                continue
            
            # Try jumping to all forward indices
            for j in range(i + 1, n):
                # Check if j is within the difference constraint
                if abs(nums[j] - nums[i]) <= target:
                    # Update j with maximum jumps path
                    dp[j] = max(dp[j], dp[i] + 1)
        
        return dp[n - 1]
```

**Algorithm breakdown:**

1. **Initialize**: `dp[i] = -1` for all indices (unreachable), except `dp[0] = 0` (starting point).

2. **Forward iteration**: Process indices from 0 to n-2:
   - Skip unreachable indices (`dp[i] == -1`)
   - For each reachable index i, explore all forward indices j
   - If jump constraint is satisfied, update: `dp[j] = max(dp[j], dp[i] + 1)`

3. **Result**: Return `dp[n-1]` (maximum jumps to reach the last index, or -1 if unreachable).

**Time Complexity**: $O(n^2)$ — nested loops iterate through all pairs (i, j) where i < j.

**Space Complexity**: $O(n)$ — single dp array of size n.

**Why this works:**
- Forward processing ensures when we compute dp[j], all previous indices dp[i] (i < j) are already finalized.
- The max() operation captures the longest path among all reachable predecessors.
- Value of -1 naturally represents unreachability: if no valid predecessor exists, dp[j] stays -1.

### Alternative: Recursive with Memoization

The commented solution uses top-down DP:
```python
mem = {}
def F(i: int, jumps: int) -> int:
    if i == n - 1:
        return jumps
    if (i, jumps) in mem:
        return mem[(i, jumps)]
    
    max_jumps = -1
    for j in range(i + 1, n):
        if abs(nums[j] - nums[i]) <= target:
            max_jumps = max(max_jumps, F(j, jumps + 1))
    
    mem[(i, jumps)] = max_jumps
    return max_jumps
```

This explores all possible jump sequences from index 0, tracking the number of jumps. However, the memoization key includes `jumps`, which can take O(n) different values, making the complexity less efficient in practice.

**Why the iterative approach is better:**
- Cleaner state representation: only track position, not the jump count
- Natural DAG processing order ensures correctness
- Better space efficiency: O(n) vs O(n²) in worst case for memoization

# Tags
- Dynamic Programming
- DAG (Directed Acyclic Graph)
- Forward Iteration
- Array Problem

