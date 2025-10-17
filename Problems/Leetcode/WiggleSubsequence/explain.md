## Problem

https://leetcode.com/problems/wiggle-subsequence/

```
A wiggle sequence is a sequence where the differences between successive numbers strictly alternate between positive and negative. The first difference (if one exists) may be either positive or negative. A sequence with one element and a sequence with two non-equal elements are trivially wiggle sequences.

For example, [1, 7, 4, 9, 2, 5] is a wiggle sequence because the differences (6, -3, 5, -7, 3) alternate between positive and negative.
In contrast, [1, 4, 7, 2, 5] and [1, 7, 4, 5, 5] are not wiggle sequences. The first is not because its first two differences are positive, and the second is not because its last difference is zero.
A subsequence is obtained by deleting some elements (possibly zero) from the original sequence, leaving the remaining elements in their original order.

Given an integer array nums, return the length of the longest wiggle subsequence of nums.

Example 1:

Input: nums = [1,7,4,9,2,5]
Output: 6
Explanation: The entire sequence is a wiggle sequence with differences (6, -3, 5, -7, 3).

Example 2:

Input: nums = [1,17,5,10,13,15,10,5,16,8]
Output: 7
Explanation: There are several subsequences that achieve this length.
One is [1, 17, 10, 13, 10, 16, 8] with differences (16, -7, 3, -3, 6, -8).

Example 3:

Input: nums = [1,2,3,4,5,6,7,8,9]
Output: 2

Constraints:

1 <= nums.length <= 1000
0 <= nums[i] <= 1000
 

Follow up: Could you solve this in O(n) time?
```

## Observations

1. **Wiggle Pattern**: A wiggle sequence alternates between increasing and decreasing differences. The pattern is: `up-down-up-down...` or `down-up-down-up...`

2. **Subsequence Property**: We can skip elements to maintain the wiggle pattern. We don't need consecutive elements.

3. **Two Starting Patterns**: Since the first difference can be either positive or negative, we need to consider both:
   - Starting with an increasing difference (looking for next decreasing)
   - Starting with a decreasing difference (looking for next increasing)

4. **Greedy Insight**: At each position, we want to find the next element that maintains the wiggle pattern. We can explore all valid next positions.

5. **Base Cases**: 
   - Single element: length = 1
   - Two different elements: length = 2
   - Array of identical elements: length = 1

## Recursive Solution Analysis

The provided recursive solution uses a brute-force approach with backtracking:

```python
from typing import List

class Solution:
    def wiggleMaxLength(self, nums: List[int]) -> int:
        n = len(nums)

        # F(i) is the longest wiggle subsequence length starting from index i
        def F(i: int, cur_len: int, next_sign: int = -1) -> int:
            if i == n:
                return cur_len
            
            max_len = cur_len
            for j in range(i + 1, n):
                if (nums[j] - nums[i]) * next_sign > 0:
                    max_len = max(max_len, F(j, cur_len + 1, next_sign * -1))
            return max_len
        
        return max(F(0, 1, -1), F(0, 1, 1))
```

### How it works:

1. **Parameters**:
   - `i`: current index in the array
   - `cur_len`: current length of wiggle subsequence
   - `next_sign`: expected sign of next difference (-1 for negative, 1 for positive)

2. **Base Case**: When `i == n`, we've reached the end, return current length

3. **Recursive Case**: 
   - Try all possible next positions `j` where `j > i`
   - Check if `(nums[j] - nums[i]) * next_sign > 0` to ensure correct wiggle pattern
   - If valid, recursively explore with flipped sign: `next_sign * -1`
   - Keep track of maximum length found

4. **Two Starting Scenarios**:
   - `F(0, 1, -1)`: Start expecting next difference to be negative
   - `F(0, 1, 1)`: Start expecting next difference to be positive
   - Return maximum of both scenarios

### Time Complexity: O(2^n) - exponential due to exploring all possible subsequences
### Space Complexity: O(n) - recursion depth

## Improvements

The recursive solution, while correct, is inefficient due to overlapping subproblems and exponential time complexity. Here are several improvements:

### 1. Memoization (Top-Down DP)
Add memoization to cache results for `(i, next_sign)` pairs:

```python
def wiggleMaxLength(self, nums: List[int]) -> int:
    n = len(nums)
    memo = {}
    
    def F(i: int, next_sign: int) -> int:
        if i == n - 1:
            return 1
        
        if (i, next_sign) in memo:
            return memo[(i, next_sign)]
        
        max_len = 1  # At least current element
        for j in range(i + 1, n):
            if (nums[j] - nums[i]) * next_sign > 0:
                max_len = max(max_len, 1 + F(j, -next_sign))
        
        memo[(i, next_sign)] = max_len
        return max_len
    
    if n <= 1:
        return n
    
    return max(F(0, 1), F(0, -1))
```
**Time Complexity: O(n²)**, **Space Complexity: O(n)**

### 2. Bottom-Up DP
Use two arrays to track longest wiggle ending with up/down:

```python
def wiggleMaxLength(self, nums: List[int]) -> int:
    n = len(nums)
    if n <= 1:
        return n
    
    up = [1] * n    # up[i] = longest wiggle ending at i with last diff > 0
    down = [1] * n  # down[i] = longest wiggle ending at i with last diff < 0
    
    for i in range(1, n):
        for j in range(i):
            if nums[i] > nums[j]:
                up[i] = max(up[i], down[j] + 1)
            elif nums[i] < nums[j]:
                down[i] = max(down[i], up[j] + 1)
    
    return max(max(up), max(down))
```
**Time Complexity: O(n²)**, **Space Complexity: O(n)**

### 3. Optimal Greedy Solution
The most efficient approach uses a greedy strategy:

```python
def wiggleMaxLength(self, nums: List[int]) -> int:
    n = len(nums)
    if n <= 1:
        return n
    
    up = down = 1
    
    for i in range(1, n):
        if nums[i] > nums[i-1]:
            up = down + 1
        elif nums[i] < nums[i-1]:
            down = up + 1
    
    return max(up, down)
```
**Time Complexity: O(n)**, **Space Complexity: O(1)**

### Key Insights for Optimization:
1. **Overlapping Subproblems**: Same `(index, expected_sign)` states are computed multiple times
2. **Greedy Property**: We only need to track the longest wiggle sequences ending with up/down patterns
3. **State Reduction**: Instead of exploring all possible jumps, we can process elements sequentially
4. **Space Optimization**: Only need to track two values (up/down lengths) instead of arrays

The greedy solution is optimal because at each step, we're making the locally optimal choice that leads to the globally optimal solution.

## Solution

## Tags

array, dynamic programming