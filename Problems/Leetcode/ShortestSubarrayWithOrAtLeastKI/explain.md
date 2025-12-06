## Problem

https://leetcode.com/problems/shortest-subarray-with-or-at-least-k-i/description/

```
You are given an array nums of non-negative integers and an integer k.

An array is called special if the bitwise OR of all of its elements is at least k.

Return the length of the shortest special non-empty subarray of nums, or return -1 if no special subarray exists.

Example 1:
Input: nums = [1,2,3], k = 2
Output: 1
Explanation:
The subarray [3] has OR value of 3. Hence, we return 1.
Note that [2] is also a special subarray.

Example 2:
Input: nums = [2,1,8], k = 10
Output: 3
Explanation:
The subarray [2,1,8] has OR value of 11. Hence, we return 3.

Example 3:
Input: nums = [1,2], k = 0
Output: 1
Explanation:
The subarray [1] has OR value of 1. Hence, we return 1.

Constraints:
1 <= nums.length <= 50
0 <= nums[i] <= 50
0 <= k < 64
```

## Observations

1. **Bitwise OR Properties**:
   - OR operation is monotonic: once a bit is set to 1, it stays 1
   - For any subarray, OR value can only increase (or stay the same) as we add more elements
   - `a | b >= max(a, b)` for any non-negative integers a and b

2. **Search Space**:
   - We need to find the shortest subarray whose OR >= k
   - For each starting position, we can extend right until OR >= k
   - Once we find a valid subarray, extending it further won't give a shorter result from that position

3. **Brute Force Approach**:
   - Try all possible subarrays: O(n²) subarrays
   - For each subarray, compute OR value: O(n) in worst case
   - Total: O(n³) but can be optimized to O(n²)

4. **Key Insight**:
   - For a fixed starting position i, we only need to find the first position j where `nums[i] | nums[i+1] | ... | nums[j] >= k`
   - No need to check longer subarrays starting from i once we find a valid one

5. **Constraints Analysis**:
   - Small array size (n <= 50) allows O(n²) solution
   - Small element values (0 <= nums[i] <= 50) means OR values are bounded
   - Maximum possible OR value is < 64 (6 bits needed)

## Solution

### Approach: Recursion with Early Termination

The solution uses a recursive approach that explores each starting position and finds the minimum length subarray from that position.

**Algorithm**:
1. Define recursive function `F(i)` that returns the minimum subarray length starting from index i or beyond
2. For each position i:
   - Initialize OR value to 0
   - Extend right from i, updating OR value incrementally
   - Stop as soon as OR >= k (found shortest from this position)
   - Recursively check starting positions i+1, i+2, ...
3. Return minimum across all starting positions

**Time Complexity**: O(n²)
- For each starting position i (n positions)
- We iterate through remaining elements (n-i elements)
- Early termination when OR >= k helps in practice

**Space Complexity**: O(n)
- Recursion stack depth can be up to n in worst case
- No additional data structures used

**Why This Works**:
- OR operation is cumulative and monotonic
- Once `val >= k`, we found the shortest subarray starting at i
- No need to extend further from i since it would only increase length
- Recursively checking all starting positions ensures we find the global minimum

**Optimization Notes**:
- Could convert to iterative DP or sliding window for space optimization
- For larger inputs, bit counting techniques could help
- Current solution is sufficient given constraint n <= 50

# Tags

`Array` `Bit Manipulation` `Sliding Window` `Recursion`

