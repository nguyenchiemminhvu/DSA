## Problem

https://leetcode.com/problems/combination-sum-iv/description/

Given an array of **distinct integers** `nums` and a **target integer** `target`, return the **number of possible combinations** that add up to `target`.

The test cases are generated so that the answer can fit in a 32-bit integer.

**Note:** Different sequences are counted as **different combinations**. For example, `[1,2]` and `[2,1]` are different combinations.

### Examples

**Example 1:**
```
Input: nums = [1,2,3], target = 4
Output: 7
Explanation:
The possible combination ways are:
(1, 1, 1, 1)
(1, 1, 2)
(1, 2, 1)
(1, 3)
(2, 1, 1)
(2, 2)
(3, 1)
```

**Example 2:**
```
Input: nums = [9], target = 3
Output: 0
```

### Constraints

- `1 <= nums.length <= 200`
- `1 <= nums[i] <= 1000`
- All elements of `nums` are unique
- `1 <= target <= 1000`

## Observations

1. **Ordered vs Unordered Combinations:** Unlike typical "Combination Sum" problems, this problem treats ordered sequences as different combinations. This is a **permutation counting** problem in disguise.

2. **Optimal Substructure:** To reach a target amount, we can use any number from the array, and the order matters. The total ways to reach `target` equals the sum of ways to reach `target - num` for all numbers in `nums`.

3. **Overlapping Subproblems:** Many subproblems will be computed multiple times. For example, reaching amount 2 might be needed from multiple starting points. This makes it ideal for dynamic programming.

4. **DP State Definition:** Let `dp[i]` = number of ways to form a sum of `i` using elements from `nums` (with repetition allowed, order matters).
   - Base case: `dp[0] = 1` (one way to form 0: use nothing)
   - Transition: `dp[i] = sum(dp[i - num] for num in nums if num <= i)`

5. **Time & Space Complexity:**
   - **Time:** $O(target \times |nums|)$ — we iterate through each amount and for each amount we check all numbers
   - **Space:** $O(target)$ — for the DP array

## Solution

### Approach 1: Top-Down DP (Memoization)

```python
class Solution:
    def combinationSum4(self, nums: List[int], target: int) -> int:
        mem = {}
        
        def F(amount: int) -> int:
            # Base cases
            if amount < 0:
                return 0
            if amount == 0:
                return 1  # Found a valid combination
            
            # Check memoization
            if amount in mem:
                return mem[amount]
            
            # Try using each number
            ways = 0
            for num in nums:
                ways += F(amount - num)
            
            # Store result and return
            mem[amount] = ways
            return ways
        
        return F(target)
```

**How it works:**
- Start from the target amount and work backwards
- For each amount, try subtracting each number in `nums`
- Recursively count combinations for the remaining amount
- Memoize results to avoid recomputation
- Base case: amount == 0 means we successfully formed the target (return 1)

### Approach 2: Bottom-Up DP (Iterative) — **Recommended**

```python
class Solution:
    def combinationSum4(self, nums: List[int], target: int) -> int:
        # Initialize DP array
        dp = [0] * (target + 1)
        dp[0] = 1  # One way to make 0: use nothing
        
        # Build up from amount 1 to target
        for amount in range(1, target + 1):
            for num in nums:
                if num <= amount:
                    dp[amount] += dp[amount - num]
        
        return dp[target]
```

**Why this is better:**
- No recursion overhead (avoids stack limits)
- Clearer iteration order: amounts increase from 0 to target
- More intuitive to understand the build-up process
- Slightly better cache locality

### Step-by-Step Trace (Example 1: nums = [1,2,3], target = 4)

```
Initial: dp = [1, 0, 0, 0, 0]

amount = 1:
  - num = 1: dp[1] += dp[0] = 1
  - num = 2: skip (2 > 1)
  - num = 3: skip (3 > 1)
  Result: dp = [1, 1, 0, 0, 0]

amount = 2:
  - num = 1: dp[2] += dp[1] = 1
  - num = 2: dp[2] += dp[0] = 1
  - num = 3: skip (3 > 2)
  Result: dp = [1, 1, 2, 0, 0]

amount = 3:
  - num = 1: dp[3] += dp[2] = 2
  - num = 2: dp[3] += dp[1] = 1
  - num = 3: dp[3] += dp[0] = 1
  Result: dp = [1, 1, 2, 4, 0]

amount = 4:
  - num = 1: dp[4] += dp[3] = 4
  - num = 2: dp[4] += dp[2] = 2
  - num = 3: dp[4] += dp[1] = 1
  Result: dp = [1, 1, 2, 4, 7]

Answer: dp[4] = 7 ✓
```

## Key Insights

### Why Order Matters

The problem statement says "different sequences are counted as different combinations." This is crucial:
- `[1, 2]` and `[2, 1]` are **different**
- This is why we iterate through amounts and for each amount try all numbers
- If we used a typical combination approach (iterate numbers first), we'd avoid duplicates, but that's not what we want here!

### The Counterintuitive Loop Order

Notice the loop structure:
```python
for amount in range(target + 1):        # Outer loop: amounts
    for num in nums:                    # Inner loop: numbers
        dp[amount] += dp[amount - num]
```

**NOT:**
```python
for num in nums:                # This would count unordered combinations
    for amount in range(num, target + 1):
        dp[amount] += dp[amount - num]
```

The order of loops is critical because we're counting **ordered** combinations (permutations with repetition).

## Follow-up: Negative Numbers Allowed

If negative numbers are allowed in the array:

1. **The problem becomes unbounded** — without a lower limit, we can use negative numbers infinitely, potentially creating infinite combinations.

2. **Necessary limitations:**
   - Limit the number of times each element can be used
   - Add a constraint on the length of combinations
   - Add a constraint that at least one positive number must be used
   - Or allow only non-negative numbers in the recursive path

3. **Example:** "Find combinations using at most K elements" would make it well-defined.

# Tags

- Dynamic Programming
- Memoization
- Bottom-Up DP
- Recursion
- Combinatorics
- LeetCode Medium

