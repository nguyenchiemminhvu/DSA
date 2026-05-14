## Problem

https://leetcode.com/problems/coin-change-ii/description/

Given an integer `amount` and a list of coins with different denominations, return the number of **different combinations** that make up the amount.

**Example:**
```
Input: amount = 5, coins = [1,2,5]
Output: 4
Explanation: 
  - 5
  - 2+2+1
  - 2+1+1+1
  - 1+1+1+1+1
```

Note: You can assume that you have an infinite number of each kind of coin.

## Observations

1. **Combination vs Permutation**: This problem asks for combinations (order doesn't matter), not permutations. `[2,1,2]` and `[1,2,2]` are the same combination.

2. **Unbounded Knapsack**: This is a variant of the unbounded knapsack problem where we can use each coin multiple times.

3. **State Definition**: We need to track:
   - Which coin we're currently considering (coin index)
   - The remaining amount to make up

4. **Recurrence Relation**:
   - For each coin, we have two choices: use it or skip it
   - `F(i, amount) = F(i+1, amount) + F(i, amount - coins[i])`
   - Base cases:
     - If `amount == 0`: return 1 (one way to make 0 - use no coins)
     - If `i >= n`: return 0 (no more coins to use)

5. **Order Matters for Combination Handling**: To avoid counting permutations, we must iterate through coins in a specific order and for each coin, consider all amounts. This ensures we process coin combinations in a fixed order.

6. **Space Optimization**: We can optimize the DP table from 2D to 1D by using a rolling array or by iterating amounts in a specific order.

## Solution

### Approach: Dynamic Programming (Bottom-Up)

```python
class Solution:
    def change(self, amount: int, coins: List[int]) -> int:
        n = len(coins)
        coins.sort(reverse=True)  # Optional sorting for potential pruning
        
        # dp[i][a] = number of ways to make amount 'a' using coins[0..i-1]
        dp = [[0 for _ in range(amount + 1)] for _ in range(n + 1)]
        
        # Base case: one way to make 0 (use no coins)
        for i in range(n + 1):
            dp[i][0] = 1
        
        # Fill the DP table from bottom-right to top-left
        for i in range(n - 1, -1, -1):
            for a in range(amount + 1):
                # Option 1: Don't use coins[i]
                dp[i][a] = dp[i + 1][a]
                
                # Option 2: Use coins[i] (if possible)
                if coins[i] <= a:
                    dp[i][a] += dp[i][a - coins[i]]
        
        return dp[0][amount]
```

### Explanation:

**DP Table Meaning:**
- `dp[i][a]` = number of ways to make amount `a` using coins from index `i` to `n-1`

**Iteration Order:**
- We iterate from `i = n-1` down to `0` (coins)
- For each coin, we iterate through all amounts from `0` to `amount`
- This ensures that when we consider coin `i`, we've already computed all subproblems for coins after it

**Recurrence:**
- For each `dp[i][a]`, we have two choices:
  1. Skip coin `i`: take value from `dp[i+1][a]`
  2. Use coin `i`: add value from `dp[i][a - coins[i]]`
     - Note: We use `dp[i][a - coins[i]]`, not `dp[i+1][...]` because we can use the same coin multiple times

**Why this handles combinations correctly:**
- By processing coins in order and allowing multiple uses of the same coin within the inner loop, we ensure that `[2,1,2]` is only counted once
- Permutations like `[2,1,2]`, `[1,2,2]`, `[2,2,1]` are counted as one combination

**Time Complexity:** $O(n \times \text{amount})$
**Space Complexity:** $O(n \times \text{amount})$ for the 2D DP table

### Alternative: Space-Optimized Solution (1D DP)

```python
class Solution:
    def change(self, amount: int, coins: List[int]) -> int:
        dp = [0] * (amount + 1)
        dp[0] = 1  # One way to make 0
        
        # For each coin
        for coin in coins:
            # Update all amounts that can be made with this coin
            for a in range(coin, amount + 1):
                dp[a] += dp[a - coin]
        
        return dp[amount]
```

**Why this works:**
- We maintain a 1D array where `dp[a]` = number of ways to make amount `a`
- By processing coins one by one and iterating amounts from left to right, we naturally avoid counting permutations
- When processing coin `c`, `dp[a - c]` contains combinations using coins up to `c` (including `c` itself), so we add it

**Time Complexity:** $O(n \times \text{amount})$
**Space Complexity:** $O(\text{amount})$

### Memoization Approach (Top-Down)

```python
class Solution:
    def change(self, amount: int, coins: List[int]) -> int:
        n = len(coins)
        mem = {}
        
        def F(i: int, amount: int) -> int:
            # Base cases
            if amount == 0:
                return 1  # Found a valid combination
            if amount < 0 or i >= n:
                return 0  # Invalid or no more coins
            
            # Check memo
            if (i, amount) in mem:
                return mem[(i, amount)]
            
            # Recurrence: skip coin i or use coin i
            ways = F(i + 1, amount)  # Skip coin i
            ways += F(i, amount - coins[i])  # Use coin i
            
            mem[(i, amount)] = ways
            return ways
        
        return F(0, amount)
```

# Tags

`Dynamic Programming` `Unbounded Knapsack` `Combination` `DP Optimization`

