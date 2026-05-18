## Problem

https://leetcode.com/problems/jump-game-v/description

Given an array of integers `arr` and an integer `d`, you can jump from index `i` to index `j` if:
1. **Distance constraint**: `|i - j| <= d` (you can jump at most `d` positions left or right)
2. **Height constraint**: `arr[i] > arr[j]` (the current element must be strictly greater than the destination)
3. **Path constraint**: `arr[i] > arr[k]` for all indices `k` between `i` and `j` (the current element must be strictly greater than all intermediate elements)

You can start from any index in the array. The goal is to find the maximum number of indices you can visit by making valid jumps.

### Examples:
- **Example 1**: `arr = [6,4,14,6,8,13,9,7,10,6,12]`, `d = 2` → Output: `4`
  - Starting at index 10: jump to 8 → 6 → 7 (visiting indices 10, 8, 6, 7)
  
- **Example 2**: `arr = [3,3,3,3,3]`, `d = 3` → Output: `1`
  - Cannot jump anywhere since all elements are equal
  
- **Example 3**: `arr = [7,6,5,4,3,2,1]`, `d = 1` → Output: `7`
  - Strictly decreasing array allows visiting all indices

## Observations

1. **Greedy approach fails**: We cannot greedily jump to the smallest adjacent element because a larger jump might lead to a longer path overall.

2. **Directed acyclic graph (DAG)**: The problem forms a DAG because we can only jump to strictly smaller values. This means no cycles are possible.

3. **Optimal substructure**: The maximum path starting from index `i` is:
   - `1 + max(maxJumps(j))` where `j` is any valid jump destination from `i`
   - Or just `1` if no valid jumps exist from `i`

4. **Processing order matters**: For DP to work correctly, we must compute the answer for smaller values before larger values. Processing indices in sorted order by their array values ensures dependencies are satisfied.

5. **Two-phase exploration**: From each index, we explore both left and right directions up to distance `d`, stopping early when we encounter a non-decreasing element.

## Solution

The solution uses **dynamic programming with sorting**:

### Approach:
1. **Sort by values**: Create a sorted list of indices, ordered by their corresponding array values (smallest to largest).
2. **Fill DP array**: Process indices in this sorted order. For each index `i`:
   - Initialize `dp[i] = 1` (we can at least visit index `i` itself)
   - Explore all valid destinations (left and right, within distance `d`)
   - For each valid destination `j`: update `dp[i] = max(dp[i], 1 + dp[j])`
3. **Why this works**: When processing index `i`, all potential jump destinations have already been processed (since they have smaller or equal values), so their DP values are already computed.

### Key optimizations:
- **Early termination**: When exploring left/right, stop immediately when encountering an element >= current value (no further jumps possible in that direction due to the path constraint)
- **O(n²) complexity**: At most we check `2d` elements from each index, and with `n` indices, the complexity is O(n log n + n·d)

### Code walkthrough:
```python
dp = [1] * n  # Each index can visit at least itself
sorted_idx = sorted(range(n), key=lambda x: arr[x])  # Sort indices by values

for i in range(len(sorted_idx)):
    idx = sorted_idx[i]
    cur_max = arr[idx]
    
    # Explore left direction
    for j in range(idx - 1, idx - d - 1, -1):
        if j < 0 or arr[j] >= cur_max:
            break
        dp[idx] = max(dp[idx], 1 + dp[j])
    
    # Explore right direction
    for j in range(idx + 1, idx + d + 1):
        if j >= n or arr[j] >= cur_max:
            break
        dp[idx] = max(dp[idx], 1 + dp[j])

return max(dp)  # Maximum jumps from any starting position
```

# Tags
- Dynamic Programming
- Depth-First Search (Alternative with memoization)
- Sorting
- Greedy (analysis of why naive greedy fails)
- Directed Acyclic Graph (DAG)

