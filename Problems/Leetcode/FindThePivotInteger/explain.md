## Problem

https://leetcode.com/problems/find-the-pivot-integer/description/

```
Given a positive integer n, find the pivot integer x such that:

The sum of all elements between 1 and x inclusively equals the sum of all elements between x and n inclusively.
Return the pivot integer x. If no such integer exists, return -1. It is guaranteed that there will be at most one pivot index for the given input.

Example 1:

Input: n = 8
Output: 6
Explanation: 6 is the pivot integer since: 1 + 2 + 3 + 4 + 5 + 6 = 6 + 7 + 8 = 21.

Example 2:

Input: n = 1
Output: 1
Explanation: 1 is the pivot integer since: 1 = 1.

Example 3:

Input: n = 4
Output: -1
Explanation: It can be proved that no such integer exist.

Constraints:

1 <= n <= 1000
```

## Observations

1. **Problem Understanding**: We need to find an integer `x` where the sum from 1 to x equals the sum from x to n.
   - Left sum: 1 + 2 + ... + x
   - Right sum: x + (x+1) + ... + n
   - Both sums include x, so we need: sum(1 to x) = sum(x to n)

2. **Mathematical Insight**: 
   - Total sum from 1 to n = n*(n+1)/2
   - If x is the pivot, then: sum(1 to x) + sum(x+1 to n) = total_sum
   - Since sum(1 to x) = sum(x to n), we have: 2*sum(1 to x) - x = total_sum
   - Rearranging: sum(1 to x) = (total_sum + x)/2

3. **Brute Force Approach**: 
   - Calculate total sum first
   - For each potential pivot x from 1 to n, check if the condition holds
   - Time complexity: O(n), Space complexity: O(1)

4. **Key Insight in Solution**: 
   - The condition `cur_sum == sum_to_n - cur_sum + i` checks if:
   - sum(1 to i) == sum(i to n)
   - This is equivalent to: sum(1 to i) == total_sum - sum(1 to i-1)
   - Which simplifies to: sum(1 to i) == total_sum - sum(1 to i) + i

## Solution

1. **Calculate Total Sum**: `sum_to_n = n * (n + 1) // 2` gives us the sum of all numbers from 1 to n.

2. **Iterate Through Potential Pivots**: For each number `i` from 1 to n:
   - Maintain `cur_sum` as the running sum from 1 to i
   - Calculate the sum from i to n as: `sum_to_n - cur_sum + i`
     - `sum_to_n - cur_sum` gives sum from (i+1) to n
     - Adding `i` back gives sum from i to n

3. **Check Pivot Condition**: If `cur_sum == sum_to_n - cur_sum + i`, then i is our pivot.

4. **Return Result**: Return the pivot if found, otherwise -1.

**Time Complexity**: O(n) - single pass through numbers 1 to n  
**Space Complexity**: O(1) - only using constant extra space

**Example Walkthrough** (n=8):
- Total sum = 8*9/2 = 36
- i=1: cur_sum=1, right_sum=36-1+1=36 ❌
- i=2: cur_sum=3, right_sum=36-3+2=35 ❌
- ...
- i=6: cur_sum=21, right_sum=36-21+6=21 ✅ → Return 6

# Tags

- Math
- Prefix Sum
- Simulation

