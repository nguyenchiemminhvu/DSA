## Problem

https://leetcode.com/problems/house-robber-ii/description

```
You are a professional robber planning to rob houses along a street. Each house has a 
certain amount of money stashed. All houses at this place are arranged in a CIRCLE. 
That means the first house is the neighbor of the last one. 

Adjacent houses have a security system connected, and it will automatically contact 
the police if two adjacent houses were broken into on the same night.

Given an integer array nums representing the amount of money of each house, return 
the maximum amount of money you can rob tonight without alerting the police.

Constraints:
- 1 <= nums.length <= 100
- 0 <= nums[i] <= 1000

Example 1:
Input: nums = [2,3,2]
Output: 3
Explanation: Cannot rob house 1 (money = 2) and house 3 (money = 2), 
because they are adjacent in the circle (first and last are neighbors).

Example 2:
Input: nums = [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and house 3 (money = 3). Total = 4.

Example 3:
Input: nums = [1,2,3]
Output: 3
```

## Observations

1. **Circular Constraint**: Unlike House Robber I (linear), here houses form a circle. 
   The first and last houses are neighbors, so we cannot rob both.

2. **Reduce to Linear Problem**: The circular constraint can be handled by solving two 
   separate linear sub-problems:
   - **Sub-problem 1**: Rob houses from index 0 to n-2 (exclude last house)
   - **Sub-problem 2**: Rob houses from index 1 to n-1 (exclude first house)
   - Return the maximum result from both sub-problems

3. **Dynamic Programming Structure**: For each house, we have two choices:
   - Rob this house: gain money from this house + max money from houses 2+ positions ahead
   - Skip this house: max money from the next house onwards

4. **Base Case**: When we reach or exceed the array boundary, no more houses can be robbed, 
   so return 0.

5. **Memoization**: Store results of F(i, n) to avoid recalculating the same subproblems.

6. **Why Two Scenarios Work**: 
   - If we rob the first house, we cannot rob the last house (sub-problem 1)
   - If we don't rob the first house, we can potentially rob the last house (sub-problem 2)
   - One of these two scenarios will always give the optimal answer

## Solution

### Algorithm Overview

**Approach**: Top-down Dynamic Programming (Memoization)

The key insight is to break the circular constraint by considering two mutually exclusive scenarios:
1. Rob houses excluding the last one (indices 0 to n-2)
2. Rob houses excluding the first one (indices 1 to n-1)

Return the maximum result from both scenarios.

### Code Explanation

```python
class Solution:
    def rob(self, nums: List[int]) -> int:
        n = len(nums)
        if n == 1:
            return nums[0]  # Only one house, must rob it

        # Helper function using top-down DP with memoization
        mem = {}
        def F(i: int, n: int) -> int:
            """
            Returns the maximum money that can be robbed from houses starting 
            at index i up to index n-1 (exclusive).
            
            Args:
                i: current house index
                n: exclusive upper bound (rob houses up to index n-1)
            
            Returns:
                Maximum money that can be robbed
            """
            if i >= n:
                return 0  # No more houses to rob
            if i in mem:
                return mem[i]  # Return memoized result
            
            # Two choices: rob or skip this house
            max_robbed = max(
                nums[i] + F(i + 2, n),  # Rob this house, skip next
                F(i + 1, n)              # Skip this house
            )
            mem[i] = max_robbed
            return max_robbed
        
        # Scenario 1: Rob houses from 0 to n-2 (exclude last house)
        op1 = F(0, n - 1)
        
        # Scenario 2: Rob houses from 1 to n-1 (exclude first house)
        mem = {}  # Reset memoization table
        op2 = F(1, n)
        
        # Return the maximum of both scenarios
        return max(op1, op2)
```

### Step-by-Step Walkthrough

**Example: nums = [1, 2, 3, 1]**

**Scenario 1: F(0, 3)** — Rob from index 0 to 2 (exclude last house)
```
F(0, 3):
  ├─ Rob house 0 (money=1) → 1 + F(2, 3)
  │   └─ F(2, 3):
  │       ├─ Rob house 2 (money=3) → 3 + F(4, 3) = 3 + 0 = 3
  │       └─ Skip house 2 → F(3, 3) = 0
  │       └─ max(3, 0) = 3
  │   → 1 + 3 = 4
  └─ Skip house 0 → F(1, 3)
      └─ F(1, 3):
          ├─ Rob house 1 (money=2) → 2 + F(3, 3) = 2 + 0 = 2
          └─ Skip house 1 → F(2, 3) = 3
          └─ max(2, 3) = 3
      → 3
  → max(4, 3) = 4
```

**Scenario 2: F(1, 4)** — Rob from index 1 to 3 (exclude first house)
```
F(1, 4):
  ├─ Rob house 1 (money=2) → 2 + F(3, 4)
  │   └─ F(3, 4):
  │       ├─ Rob house 3 (money=1) → 1 + F(5, 4) = 1 + 0 = 1
  │       └─ Skip house 3 → F(4, 4) = 0
  │       └─ max(1, 0) = 1
  │   → 2 + 1 = 3
  └─ Skip house 1 → F(2, 4)
      └─ F(2, 4):
          ├─ Rob house 2 (money=3) → 3 + F(4, 4) = 3 + 0 = 3
          └─ Skip house 2 → F(3, 4) = 1
          └─ max(3, 1) = 3
      → 3
  → max(3, 3) = 3
```

**Result**: max(4, 3) = **4** ✓

The optimal solution is to rob house 1 and house 3 (0-indexed), getting $1 + $3 = $4.

### Complexity Analysis

- **Time Complexity**: O(n)
  - We compute F(i, n) for at most n different values of i in each scenario
  - Each computation is O(1) with memoization
  - Two scenarios: 2 × O(n) = O(n)

- **Space Complexity**: O(n)
  - Memoization table stores up to n entries
  - Recursion call stack depth is at most O(n)
  - Total: O(n) for both memoization and stack

# Tags

