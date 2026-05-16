## Problem

https://leetcode.com/problems/partition-array-for-maximum-sum/description/

Given an integer array `arr`, partition the array into (contiguous) subarrays of length **at most** `k`. After partitioning, each subarray has their values changed to become the **maximum value** of that subarray.

Return the **largest sum** of the given array after partitioning. Test cases are generated so that the answer fits in a 32-bit integer.

### Examples

**Example 1:**
```
Input: arr = [1,15,7,9,2,5,10], k = 3
Output: 84
Explanation: arr becomes [15,15,15,9,10,10,10]
```
- Partition: [1,15,7] | [9] | [2,5,10]
- Max values: 15, 15, 15 | 9 | 10, 10, 10
- Sum: 15×3 + 9×1 + 10×3 = 45 + 9 + 30 = 84

**Example 2:**
```
Input: arr = [1,4,1,5,7,3,6,1,9,9,3], k = 4
Output: 83
```

**Example 3:**
```
Input: arr = [1], k = 1
Output: 1
```

### Constraints
- `1 <= arr.length <= 500`
- `0 <= arr[i] <= 10^9`
- `1 <= k <= arr.length`

## Observations

1. **Optimal Substructure**: This is a dynamic programming problem because the maximum sum from position `i` depends on choosing the best partition endpoint (from `i-k` to `i`), and the rest is solved optimally by previous positions.

2. **Greedy Doesn't Work**: You can't greedily pick the largest element at each step. For example, `[1,15,7]` with `k=3`: even though 15 is largest, partitioning `[1,15]|[7]` gives `15*2 + 7 = 37`, while `[1,15,7]` gives `15*3 = 45`.

3. **State Definition**: Let `dp[i]` = maximum sum when partitioning `arr[0...i]`. For each position `i`, we try all possible partition sizes from 1 to `k`, pick the maximum element in that range, multiply by the partition size, and add it to the best sum from the previous position.

4. **Recurrence Relation**:
   ```
   dp[i] = max(
       max_val * (i - j + 1) + dp[j - 1]
   ) for j from i down to max(i - k, -1)
   ```
   - `j` is the start of the current partition
   - `i - j + 1` is the partition size
   - `max_val` is the maximum in `arr[j...i]`

5. **Optimization**: Instead of recalculating `max(arr[j...i])` for each `j`, we can iterate backwards from `i` and incrementally update `max_val`, reducing complexity from O(n·k²) to O(n·k).

## Solution

```python
class Solution:
    def maxSumAfterPartitioning(self, arr: List[int], k: int) -> int:
        n = len(arr)
        dp = [0] * n
        
        for i in range(n):
            max_val = arr[i]
            # Try partitions of length 1 to k ending at position i
            for j in range(i, max(i - k, -1), -1):
                # Incrementally update max value from arr[j] to arr[i]
                max_val = max(max_val, arr[j])
                # Current partition: arr[j...i]
                # Partition length: i - j + 1
                # Contribution: max_val * partition_length
                # Plus best sum from arr[0...j-1]
                dp[i] = max(
                    dp[i],
                    max_val * (i - j + 1) + (dp[j - 1] if j - 1 >= 0 else 0)
                )
        
        return dp[n - 1]
```

### Step-by-Step Walkthrough (Example 1: `arr = [1,15,7,9,2,5,10]`, `k = 3`)

| i | j range | partitions tried | max_val | contribution | dp[i] |
|---|---------|------------------|---------|--------------|-------|
| 0 | [0,0] | [1] | 1 | 1×1 + 0 = 1 | 1 |
| 1 | [1,0] | [15], [1,15] | 15, 15 | 15×1+1=16, 15×2+0=30 | 30 |
| 2 | [2,0] | [7], [15,7], [1,15,7] | 7, 15, 15 | 7×1+30=37, 15×2+1=31, 15×3+0=45 | **45** |
| 3 | [3,1] | [9], [7,9], [15,7,9] | 9, 9, 15 | 9×1+45=54, 9×2+30=48, 15×3+1=46 | **54** |
| 4 | [4,2] | [2], [5,2], [9,5,2] | 2, 5, 9 | 2×1+54=56, 5×2+45=55, 9×3+30=57 | **57** |
| 5 | [5,3] | [5], [2,5], [9,2,5] | 5, 5, 9 | 5×1+57=62, 5×2+54=64, 9×3+45=72 | **72** |
| 6 | [6,4] | [10], [5,10], [2,5,10] | 10, 10, 10 | 10×1+72=82, 10×2+57=77, 10×3+54=84 | **84** |

### Complexity Analysis

- **Time Complexity**: O(n·k) where we iterate through each position once and try up to k partition sizes
- **Space Complexity**: O(n) for the DP array

### Alternative Approach (Top-Down Memoization)

The commented recursive solution at the beginning uses memoization:
```python
def F(i: int) -> int:
    # Base case: if we've processed all elements
    if i < 0:
        return 0
    # Try all partition sizes from 1 to k
    for j in range(i, max(i - k, -1), -1):
        max_val = max(arr[j:i + 1])
        res = max(res, (max_val * (i - j + 1)) + F(j - 1))
    return res
```

This is logically equivalent but bottom-up DP is generally more efficient as it avoids function call overhead and is easier to understand.

# Tags

Dynamic Programming, Array Partitioning, Optimal Substructure

