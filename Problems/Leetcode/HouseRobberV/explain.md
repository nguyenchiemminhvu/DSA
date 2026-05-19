## Problem

https://leetcode.com/problems/house-robber-v/description/?q=robber

```
# House Robber V - Dynamic Programming with Color Constraint

## Problem

**Link:** https://leetcode.com/problems/house-robber-v/description/?q=robber

You are a professional robber planning to rob houses along a street. Each house has:
- `nums[i]`: amount of money in the ith house
- `colors[i]`: color code of that house

**Constraint:** You cannot rob two adjacent houses if they share the same color code.

**Goal:** Return the maximum amount of money you can rob.

### Examples

**Example 1:**
```
Input: nums = [1,4,3,5], colors = [1,1,2,2]
Output: 9

Explanation: Rob houses at indices 1 and 3 (non-adjacent)
- House 1: $4 (color 1)
- House 3: $5 (color 2)
- Total: $4 + $5 = $9
```

**Example 2:**
```
Input: nums = [3,1,2,4], colors = [2,3,2,2]
Output: 8

Explanation: Rob houses at indices 0, 1, and 3
- House 0: $3 (color 2)
- House 1: $1 (color 3) ✓ different color from house 0
- House 3: $4 (color 2) ✓ non-adjacent to house 1
- Total: $3 + $1 + $4 = $8
```

**Example 3:**
```
Input: nums = [10,1,3,9], colors = [1,1,1,2]
Output: 22

Explanation: Rob houses at indices 0, 2, and 3
- House 0: $10 (color 1)
- House 2: $3 (color 1) ✓ non-adjacent to house 0
- House 3: $9 (color 2) ✓ non-adjacent and different color from house 2
- Total: $10 + $3 + $9 = $22
```

### Constraints

- `1 <= n == nums.length == colors.length <= 10^5`
- `1 <= nums[i], colors[i] <= 10^5`

---

## Observations

### Key Insights

1. **Color Constraint Modifies Adjacency Rules**
   - Standard House Robber: Can't rob adjacent houses (constraint: positions must differ by ≥ 2)
   - This variant: Can rob adjacent houses IF they have different colors
   - Example: [House(i), House(i+1)] can both be robbed if `colors[i] != colors[i+1]`

2. **State Transitions are Conditional**
   - At each house `i`, we have options:
     - **If `colors[i] == colors[i-1]`**: Must skip house `i-1`
       - Rob house `i`: take `nums[i] + dp[i-2]`
       - Skip house `i`: take `dp[i-1]`
       - Choose maximum
     - **If `colors[i] != colors[i-1]`**: Can rob house `i-1` if beneficial
       - Rob house `i`: take `nums[i] + dp[i-1]` (since previous different color)
       - Skip house `i`: take `dp[i-1]`
       - The second option is always ≤ first, so rob it

3. **Overlapping Subproblems**
   - Decision at house `i` depends only on optimal solutions from houses `[0...i-1]`
   - Classic DP structure with optimal substructure

4. **Linear Dependency Chain**
   - Each house's best solution only depends on previous houses
   - Can be solved bottom-up iteratively without recursion overhead

---

## Solution

### Approach: Bottom-Up Dynamic Programming

**Time Complexity:** $O(n)$  
**Space Complexity:** $O(n)$ (can be optimized to $O(1)$)

#### Algorithm

1. **Initialize DP Array**
   - `dp[i]` = maximum money that can be robbed from houses `[0...i]`
   - Start with `dp = nums[:]` (copy of nums array)

2. **Iterate Through Houses**
   - For each house `i`:
     - **If colors match** (`colors[i] == colors[i-1]`):
       - We must skip the previous house
       - `dp[i] = max(dp[i-1], nums[i] + (dp[i-2] or 0))`
       - Option 1: Don't rob house `i`, keep `dp[i-1]`
       - Option 2: Rob house `i`, add to `dp[i-2]` (skip i-1 due to color match)
     - **If colors differ** (`colors[i] != colors[i-1]`):
       - We can rob both adjacent houses
       - `dp[i] = nums[i] + dp[i-1]`
       - Always beneficial to include previous house since we can have consecutive different colors

3. **Return Result**
   - `dp[n-1]` contains the maximum money from all houses

#### Implementation

```python
class Solution:
    def rob(self, nums: List[int], colors: List[int]) -> int:
        n = len(nums)
        dp = nums[:]
        
        for i in range(n):
            if i - 1 >= 0 and colors[i] != colors[i - 1]:
                # Different color: can include previous house
                dp[i] = nums[i] + dp[i - 1]
            else:
                # Same color or first house: choose between skip or rob with gap
                dp[i] = max(
                    dp[i - 1] if i - 1 >= 0 else 0,
                    nums[i] + (dp[i - 2] if i - 2 >= 0 else 0)
                )
        
        return dp[n - 1]
```

### Trace Through Example 2

```
nums = [3, 1, 2, 4]
colors = [2, 3, 2, 2]

i=0: colors[0]=2, no previous
    dp[0] = 3

i=1: colors[1]=3, colors[0]=2 (different!)
    dp[1] = nums[1] + dp[0] = 1 + 3 = 4

i=2: colors[2]=2, colors[1]=3 (different!)
    dp[2] = nums[2] + dp[1] = 2 + 4 = 6

i=3: colors[3]=2, colors[2]=2 (same!)
    dp[3] = max(dp[2], nums[3] + dp[1]) 
         = max(6, 4 + 4) 
         = max(6, 8) = 8

Result: 8 ✓
```

### Memoization Approach (Alternative)

The commented-out code in `solve.py` shows a top-down recursive approach with memoization:

```python
mem = {}
def F(i: int) -> int:
    if i < 0:
        return 0
    if i in mem:
        return mem[i]
    
    res = 0
    if i - 1 >= 0 and colors[i] != colors[i - 1]:
        # Different color: must include previous
        res = nums[i] + F(i - 1)
    else:
        # Same color or first house: choose max
        res = max(
            F(i - 1),
            nums[i] + F(i - 2)
        )
    mem[i] = res
    return res
return F(n - 1)
```

Both approaches have same complexity but iterative DP is more cache-efficient.

---

## Space Optimization

If space is critical, we can use only 2 variables instead of full DP array:

```python
def rob(self, nums: List[int], colors: List[int]) -> int:
    prev2 = 0  # dp[i-2]
    prev1 = 0  # dp[i-1]
    
    for i in range(len(nums)):
        if i > 0 and colors[i] != colors[i - 1]:
            curr = nums[i] + prev1
        else:
            curr = max(prev1, nums[i] + prev2)
        
        prev2 = prev1
        prev1 = curr
    
    return prev1
```

**Space Complexity:** $O(1)$

---

## Tags

`#dynamic-programming` `#house-robber` `#greedy-with-constraints` `#array` `#interval-dp`
```
