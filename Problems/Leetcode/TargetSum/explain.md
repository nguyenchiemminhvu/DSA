## Problem

https://leetcode.com/problems/target-sum/

```
You are given an integer array nums and an integer target.

You want to build an expression out of nums by adding one of the symbols '+' and '-' 
before each integer in nums and then concatenate all the integers.

For example, if nums = [2, 1], you can add a '+' before 2 and a '-' before 1 and 
concatenate them to build the expression "+2-1".

Return the number of different expressions that you can build, which evaluates to target.

Example 1:
Input: nums = [1,1,1,1,1], target = 3
Output: 5
Explanation: There are 5 ways to assign symbols to make the sum of nums be target 3.
-1 + 1 + 1 + 1 + 1 = 3
+1 - 1 + 1 + 1 + 1 = 3
+1 + 1 - 1 + 1 + 1 = 3
+1 + 1 + 1 - 1 + 1 = 3
+1 + 1 + 1 + 1 - 1 = 3

Example 2:
Input: nums = [1], target = 1
Output: 1

Constraints:
- 1 <= nums.length <= 20
- 0 <= nums[i] <= 1000
- 0 <= sum(nums[i]) <= 1000
- -1000 <= target <= 1000
```

## Observations

1. **Decision Tree**: At each position, we have 2 choices: add `+` or `-` before the number
   - This creates a binary decision tree with depth = len(nums)
   - Total possible expressions = 2^n

2. **Overlapping Subproblems**: The same state (index, current_sum) can be reached through different paths
   - Example: `+1-2+3` and `-2+1+3` both reach sum=2 at some point
   - This makes it suitable for memoization/dynamic programming

3. **State Definition**: A state is uniquely defined by:
   - Current index in the array
   - Current sum accumulated so far
   - State: `(idx, current_sum)`

4. **Base Case**: When we've processed all numbers (idx >= n):
   - Return 1 if current_sum equals target (found valid expression)
   - Return 0 otherwise

5. **Recurrence Relation**:
   - `count(idx, sum) = count(idx+1, sum+nums[idx]) + count(idx+1, sum-nums[idx])`
   - Add the number of ways from both choices

## Solution

### Approach: Top-Down Dynamic Programming (Memoization)

**Algorithm:**
1. Start from index 0 with sum = 0
2. At each index, try both operations:
   - Add the current number: `generating(idx+1, sum+nums[idx])`
   - Subtract the current number: `generating(idx+1, sum-nums[idx])`
3. Use memoization to cache results for each `(idx, sum)` state
4. When reaching the end of array, check if sum equals target

**Complexity Analysis:**
- **Time Complexity**: O(n × S) where:
  - n = length of nums
  - S = range of possible sums = 2 × sum(nums) + 1
  - Each state (idx, sum) is computed once and cached
  - Maximum sum range: [-1000, 1000] based on constraints

- **Space Complexity**: O(n × S)
  - Memoization dictionary stores at most n × S states
  - Recursion stack depth: O(n)

**Why This Works:**
- The memoization eliminates redundant calculations
- Without memo: O(2^n) - trying all combinations
- With memo: O(n × S) - each unique state computed once
- The problem has optimal substructure: solution to larger problem built from solutions to subproblems

**Alternative Approach - Mathematical Insight:**
This problem can be converted to a subset sum problem:
- Let P = sum of numbers with '+' sign
- Let N = sum of numbers with '-' sign
- P - N = target
- P + N = sum(nums)
- Therefore: P = (target + sum(nums)) / 2

This transforms the problem into: "Find number of subsets with sum = (target + sum) / 2"

# Tags

Dynamic Programming, Memoization, Recursion, Backtracking, Subset Sum

