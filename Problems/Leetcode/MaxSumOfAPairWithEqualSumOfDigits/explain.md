## Problem

https://leetcode.com/problems/max-sum-of-a-pair-with-equal-sum-of-digits/description/

You are given a 0-indexed array `nums` consisting of positive integers. You can choose two indices `i` and `j`, such that `i != j`, and the sum of digits of the number `nums[i]` is equal to that of `nums[j]`.

Return the maximum value of `nums[i] + nums[j]` that you can obtain over all possible indices `i` and `j` that satisfy the conditions. If no such pair of indices exists, return `-1`.

**Example 1:**
```
Input: nums = [18,43,36,13,7]
Output: 54
Explanation: The pairs (i, j) that satisfy the conditions are:
- (0, 2), both numbers have a sum of digits equal to 9, and their sum is 18 + 36 = 54.
- (1, 4), both numbers have a sum of digits equal to 7, and their sum is 43 + 7 = 50.
So the maximum sum that we can obtain is 54.
```

**Example 2:**
```
Input: nums = [10,12,19,14]
Output: -1
Explanation: There are no two numbers that satisfy the conditions, so we return -1.
```

**Constraints:**
- `1 <= nums.length <= 10^5`
- `1 <= nums[i] <= 10^9`

## Observations

1. **Digit Sum Grouping**: We need to group numbers by their digit sum. Numbers with the same digit sum are candidates for forming pairs.

2. **Maximum Pair Sum**: For each group of numbers with the same digit sum, we need to find the two largest numbers to maximize their sum.

3. **Edge Cases**: 
   - If no group has at least 2 numbers, return -1
   - Need to handle single-element groups

4. **Optimization**: Using a max heap (priority queue) allows us to efficiently extract the two largest values from each group.

5. **Digit Sum Range**: For a number up to 10^9, the maximum digit sum is 9 * 9 = 81 (for 999,999,999), so we'll have at most 82 different groups (0-81).

## Solution

**Approach: Hash Map + Max Heap**

The solution uses a hash map to group numbers by their digit sum, with each group stored as a max heap:

1. **Calculate Digit Sum**: For each number in the array, calculate its digit sum by repeatedly taking modulo 10 and dividing by 10.

2. **Group by Digit Sum**: Use a hash map where:
   - Key: digit sum
   - Value: max heap (stored as min heap with negative values) containing all numbers with that digit sum

3. **Find Maximum Pair**: For each digit sum group:
   - If the group has less than 2 numbers, skip it
   - Extract the two largest numbers (pop twice from the heap)
   - Calculate their sum and update the result

4. **Return Result**: Return the maximum sum found, or -1 if no valid pair exists.

**Time Complexity**: O(n * d + g * log m)
- n: length of nums
- d: average number of digits (at most 10 for 10^9)
- g: number of unique digit sums (at most 82)
- m: average size of each group
- Overall: O(n log n) in worst case

**Space Complexity**: O(n) for the hash map storing all numbers

**Python Code:**
```python
import heapq

class Solution:
    def maximumSum(self, nums: List[int]) -> int:
        res = -1
        f = {}
        
        # Group numbers by digit sum
        for val in nums:
            tmp = val
            d = 0
            # Calculate digit sum
            while tmp:
                d += tmp % 10
                tmp //= 10
            
            # Add to max heap (using negative values)
            if d not in f:
                f[d] = []
            heapq.heappush(f[d], -val)
        
        # Find maximum pair sum for each digit sum group
        for k, arr in f.items():
            if len(arr) < 2:
                continue
            
            # Extract two largest values
            a = -heapq.heappop(arr)
            b = -heapq.heappop(arr)
            res = max(res, a + b)

        return res
```

**Key Insights:**
- Python's `heapq` is a min heap, so we store negative values to simulate a max heap
- We only need the top 2 values from each group, so we don't need to sort the entire group
- The hash map naturally handles the grouping without explicit sorting or searching

# Tags

