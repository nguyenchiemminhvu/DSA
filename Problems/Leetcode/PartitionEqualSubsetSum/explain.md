## Problem

https://leetcode.com/problems/partition-equal-subset-sum/description

Given an integer array `nums`, return `true` if you can partition the array into two subsets such that the sum of elements in both subsets is equal, or `false` otherwise.

**Example 1:**
- Input: `nums = [1,5,11,5]`
- Output: `true`
- Explanation: The array can be partitioned as `[1, 5, 5]` and `[11]`.

**Example 2:**
- Input: `nums = [1,2,3,5]`
- Output: `false`
- Explanation: The array cannot be partitioned into equal sum subsets.

**Constraints:**
- 1 ≤ nums.length ≤ 200
- 1 ≤ nums[i] ≤ 100

## Observations

### Key Insight: Reduce to Subset Sum Problem
This problem reduces to the classic **0/1 Knapsack** variant. If we can partition the array into two equal-sum subsets, then each subset sums to `total_sum / 2`. So the problem becomes: **"Can we find a subset that sums to exactly `total_sum / 2`?"**

### Mathematical Requirement
- If the total sum is **odd**, it's impossible to partition into two equal subsets → return `False` immediately.
- If the total sum is **even**, we need to find if there exists a subset with sum = `total_sum / 2`.

### Problem Structure
- **Choice**: For each number, we have two options:
  1. Include it in the subset (subtract from target sum)
  2. Exclude it from the subset (keep target sum same)
- **State**: At index `i` with current target amount `amount`:
  - Can we achieve exactly `amount` using elements from index `i` onwards?
- **Base Case**: 
  - If `amount == 0`, we found our subset → return `True`
  - If `i >= n` and `amount != 0` → impossible → return `False`

### Optimization Opportunities
1. **Early Pruning**: If `nums[i] > amount`, we can't use this element, so skip the inclusion choice
2. **Memoization**: Many subproblems repeat (same index, same remaining amount)
3. **Space Optimization**: We can reduce 2D DP to 1D by processing in reverse order

## Solution

### Approach 1: Memoization (Top-Down DP)

```python
def canPartition(self, nums: List[int]) -> bool:
    s = sum(nums)
    if s & 1:  # If sum is odd, impossible to partition
        return False
    
    half = s // 2
    mem = {}
    
    def F(i: int, amount: int) -> bool:
        """
        Can we achieve exactly 'amount' using elements from index i onwards?
        """
        if i >= n:
            return amount == 0
        
        if (i, amount) in mem:
            return mem[(i, amount)]
        
        res = False
        if nums[i] > amount:
            # Current element is too large, skip it
            res = F(i + 1, amount)
        else:
            # Try including or excluding current element
            res = F(i + 1, amount) or F(i + 1, amount - nums[i])
        
        mem[(i, amount)] = res
        return res
    
    return F(0, half)
```

**How it works:**
1. Check if total sum is odd → impossible
2. Target is `half = total_sum / 2`
3. Recursively try to form a subset with sum = `half`
4. For each number, try both options: include or exclude
5. Memoize results to avoid recomputation

---

### Approach 2: Dynamic Programming (Bottom-Up) - **Recommended**

```python
def canPartition(self, nums: List[int]) -> bool:
    n = len(nums)
    s = sum(nums)
    if s & 1:  # If sum is odd
        return False
    
    half = s // 2
    
    # dp[i][amount] = Can we achieve 'amount' using nums[0:i]?
    dp = [[False for _ in range(half + 1)] for _ in range(n + 1)]
    dp[n][0] = True  # Base case: empty subset sums to 0
    
    # Fill table from bottom to top
    for i in range(n - 1, -1, -1):
        for amount in range(half + 1):
            if nums[i] > amount:
                # Current element too large, can't include it
                dp[i][amount] = dp[i + 1][amount]
            else:
                # Either exclude current element OR include it
                dp[i][amount] = dp[i + 1][amount] or dp[i + 1][amount - nums[i]]
    
    return dp[0][half]
```

**How it works:**
1. `dp[i][amount]` represents: "Can we achieve sum `amount` using elements `nums[0:i]`?"
2. Build the table from the end (index `n`) backwards to index 0
3. At each cell, we have two choices:
   - **Exclude**: `dp[i+1][amount]` — skip current element
   - **Include**: `dp[i+1][amount - nums[i]]` — use current element (if it fits)
4. Return `dp[0][half]` — can we achieve `half` using all elements?

**Key Observation:** We iterate `amount` in both directions, but going forward (0 to half) is safer to avoid using updated values in the same iteration.

---

### Complexity Analysis

| Approach | Time | Space |
|----------|------|-------|
| Memoization | O(n × target) | O(n × target) |
| DP 2D | O(n × target) | O(n × target) |
| DP 1D | O(n × target) | O(target) |

Where `target = sum(nums) / 2`

---

### Example Walkthrough: `nums = [1, 5, 11, 5]`

**Setup:**
- Total sum = 22
- Target = 11
- Table size: (5 rows × 12 columns)

**DP Table Evolution:**
```
     amount: 0  1  2  3  4  5  6  7  8  9  10 11
i=4 (n):     T  F  F  F  F  F  F  F  F  F  F  F
i=3 (5):     T  F  F  F  F  T  F  F  F  F  F  T   ← dp[3][5]=T, dp[3][11]=T
i=2 (11):    T  F  F  F  F  T  F  F  F  F  F  T   ← dp[2][11]=T (can use 11 alone)
i=1 (5):     T  F  F  F  F  T  F  F  F  F  T  T   ← dp[1][10]=T (1+5+5=11? no... 5+5=10)
i=0 (1):     T  T  F  F  F  T  F  F  F  F  T  T   ← dp[0][11]=T
```

**Result:** `dp[0][11] = True` → Can partition as `[1,5,5]` and `[11]`

# Tags

