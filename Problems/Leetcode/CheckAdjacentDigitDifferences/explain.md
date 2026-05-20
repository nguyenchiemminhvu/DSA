## Problem

https://leetcode.com/problems/check-adjacent-digit-differences/description/

## Problem

You are given a string `s` consisting of digits.

Return `true` if the absolute difference between every pair of adjacent digits is at most 2, otherwise return `false`.

The absolute difference between `a` and `b` is defined as `abs(a - b)`.

**Example 1:**
- Input: `s = "132"`
- Output: `true`
- Explanation: The absolute difference between digits at `s[0]` and `s[1]` is `abs(1 - 3) = 2`. The absolute difference between digits at `s[1]` and `s[2]` is `abs(3 - 2) = 1`. Since both differences are at most 2, the answer is `true`.

**Example 2:**
- Input: `s = "129"`
- Output: `false`
- Explanation: The absolute difference between digits at `s[0]` and `s[1]` is `abs(1 - 2) = 1`. The absolute difference between digits at `s[1]` and `s[2]` is `abs(2 - 9) = 7`, which is greater than 2. Therefore, the answer is `false`.

**Constraints:**
- `2 <= s.length <= 100`
- `s` consists only of digits.

## Observations

1. **Linear iteration required**: We need to check all consecutive pairs of adjacent digits in the string, which naturally requires iterating through the string once.

2. **Early termination possible**: If we find any pair of adjacent digits with a difference greater than 2, we can immediately return `false` without checking the rest.

3. **String to integer conversion**: We need to convert each character digit to an integer to perform the arithmetic operation for calculating the absolute difference.

4. **Simple condition check**: The problem reduces to checking a single condition for each pair: `abs(a - b) <= 2`.

## Solution

```python
class Solution:
    def isAdjacentDiffAtMostTwo(self, s: str) -> bool:
        n = len(s)
        for i in range(1, n):
            a, b = int(s[i - 1]), int(s[i])
            if abs(a - b) > 2:
                return False
        return True
```

**Algorithm Explanation:**

1. **Initialize loop**: Start from index 1 since we need to check pairs of adjacent digits.

2. **Convert and compare**: For each position `i`, convert both the previous digit `s[i-1]` and current digit `s[i]` to integers.

3. **Check condition**: Calculate the absolute difference between the two digits. If it exceeds 2, return `false` immediately.

4. **Return result**: If we successfully iterate through all adjacent pairs without finding a violation, return `true`.

**Complexity Analysis:**
- **Time Complexity**: $O(n)$ where $n$ is the length of the string. We iterate through the string once, and each operation (conversion and comparison) takes constant time.
- **Space Complexity**: $O(1)$ as we only use a constant amount of extra space regardless of input size.

**Why this works:**
- The problem only requires checking if all consecutive pairs satisfy the condition, which is a straightforward traversal.
- By checking each pair sequentially and returning early on the first violation, we ensure both correctness and efficiency.

# Tags

String, Array, Linear Scan

## Observations

## Solution

# Tags

