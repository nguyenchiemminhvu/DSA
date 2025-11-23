## Problem

https://leetcode.com/problems/greatest-sum-divisible-by-three/description/

```
Given an integer array nums, return the maximum possible sum of elements of the array such that it is divisible by three.

Example 1:

Input: nums = [3,6,5,1,8]
Output: 18
Explanation: Pick numbers 3, 6, 1 and 8 their sum is 18 (maximum sum divisible by 3).

Example 2:

Input: nums = [4]
Output: 0
Explanation: Since 4 is not divisible by 3, do not pick any number.

Example 3:

Input: nums = [1,2,3,4,4]
Output: 12
Explanation: Pick numbers 1, 3, 4 and 4 their sum is 12 (maximum sum divisible by 3).

Constraints:

1 <= nums.length <= 4 * 104
1 <= nums[i] <= 104
```

## Observations

1. **Key Insight**: To maximize the sum divisible by 3, we should start with the total sum and remove the minimum elements to make it divisible by 3.

2. **Modular Arithmetic**: Any number can have remainder 0, 1, or 2 when divided by 3.
   - Numbers with remainder 0 don't affect divisibility by 3
   - Numbers with remainder 1 and 2 need to be balanced

3. **Sum Analysis**: If total sum has remainder `r` when divided by 3:
   - If `r = 0`: Already divisible, return total sum
   - If `r = 1`: Need to remove elements with total remainder 1
   - If `r = 2`: Need to remove elements with total remainder 2

4. **Removal Strategies**:
   - To remove remainder 1: Either remove one element with remainder 1, or two elements with remainder 2 (since 2+2=4, 4%3=1)
   - To remove remainder 2: Either remove one element with remainder 2, or two elements with remainder 1 (since 1+1=2, 2%3=2)

5. **Greedy Approach**: Always remove the smallest possible elements to maximize the remaining sum.

## Solution

1. **Calculate Total Sum**: Start with sum of all elements
2. **Check Divisibility**: If sum % 3 == 0, return immediately
3. **Group by Remainder**: Categorize numbers by their remainder when divided by 3
4. **Remove Strategy**:
   - If remainder = 2: Remove either smallest number with remainder 2, or two smallest numbers with remainder 1
   - If remainder = 1: Remove either smallest number with remainder 1, or two smallest numbers with remainder 2
5. **Choose Optimal**: Pick the removal strategy that removes the smallest total value

### Time Complexity: O(n log n)
- O(n) to calculate sum and group numbers
- O(k log k) to sort remainder groups (where k ≤ n)

### Space Complexity: O(n)
- Storage for remainder groups

### Example Walkthrough:
For `nums = [3,6,5,1,8]`:
- Total sum = 23, remainder = 2
- Remainder groups: {0: [3,6], 1: [1], 2: [5,8]}
- Need to remove remainder 2: min(smallest from remainder 2, two smallest from remainder 1)
- Option 1: Remove 5 (remainder 2) → sum = 18
- Option 2: Need 2 elements with remainder 1, but only have 1
- Choose option 1: final answer = 18

## Alternative Solution: Dynamic Programming with Memoization

```python
class Solution:
    def maxSumDivThree(self, nums: List[int]) -> int:
        n = len(nums)
        self.memo = {}

        # F(i, mod) = sum from 0 to i that having remainder = mod
        def F(idx: int, mod: int) -> int:
            if idx == n:
                return 0 if mod == 0 else float('-inf')
            
            if (idx, mod) in self.memo:
                return self.memo[(idx, mod)]
            
            sum_skip = F(idx + 1, mod)
            sum_pick = nums[idx] + F(idx + 1, (nums[idx] + mod) % 3)
            self.memo[(idx, mod)] = max(sum_skip, sum_pick)
            return max(sum_skip, sum_pick)
        
        return F(0, 0)
```

### DP Approach Explanation:

1. **State Definition**: `F(idx, mod)` represents the maximum sum we can achieve starting from index `idx` such that the current remainder is `mod`.

2. **Base Case**: When `idx == n` (reached end of array):
   - If `mod == 0`: return 0 (valid sum divisible by 3)
   - Otherwise: return negative infinity (invalid state)

3. **Recurrence**: For each element, we have two choices:
   - **Skip**: Continue with same remainder: `F(idx + 1, mod)`
   - **Pick**: Add current element and update remainder: `nums[idx] + F(idx + 1, (nums[idx] + mod) % 3)`

4. **Memoization**: Cache results to avoid redundant calculations.

### Time Complexity: O(n)
- Each state (idx, mod) is computed once
- Total states: n × 3 = O(n)

### Space Complexity: O(n)
- Memoization table size: O(n)
- Recursion depth: O(n)

# Tags
`Array` `Math` `Greedy` `Modular Arithmetic` `Dynamic Programming`

