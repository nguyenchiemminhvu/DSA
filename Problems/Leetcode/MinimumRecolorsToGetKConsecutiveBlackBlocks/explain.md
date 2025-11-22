## Problem

https://leetcode.com/problems/minimum-recolors-to-get-k-consecutive-black-blocks/

```
You are given a 0-indexed string blocks of length n, where blocks[i] is either 'W' or 'B', representing the color of the ith block. The characters 'W' and 'B' denote the colors white and black, respectively.

You are also given an integer k, which is the desired number of consecutive black blocks.

In one operation, you can recolor a white block such that it becomes a black block.

Return the minimum number of operations needed such that there is at least one occurrence of k consecutive black blocks.

Example 1:

Input: blocks = "WBBWWBBWBW", k = 7
Output: 3
Explanation:
One way to achieve 7 consecutive black blocks is to recolor the 0th, 3rd, and 4th blocks
so that blocks = "BBBBBBBWBW". 
It can be shown that there is no way to achieve 7 consecutive black blocks in less than 3 operations.
Therefore, we return 3.

Example 2:

Input: blocks = "WBWBBBW", k = 2
Output: 0
Explanation:
No changes need to be made, since 2 consecutive black blocks already exist.
Therefore, we return 0.

Constraints:

n == blocks.length
1 <= n <= 100
blocks[i] is either 'W' or 'B'.
1 <= k <= n
```

## Observations

1. **Problem Type**: This is a sliding window problem where we need to find the optimal window of size k.

2. **Key Insight**: To minimize operations, we need to find a window of k consecutive blocks that contains the minimum number of white blocks ('W'). The number of white blocks in that window equals the number of operations needed.

3. **Approach**: Use a sliding window of size k and track the count of white blocks in each window. The minimum count across all windows is our answer.

4. **Edge Cases**: 
   - If there's already a sequence of k consecutive black blocks, return 0
   - If k equals the string length, count all white blocks in the entire string

5. **Time Complexity**: O(n) where n is the length of the string
   **Space Complexity**: O(1) using only a few variables

## Solution

The solution uses a **sliding window technique** to efficiently find the minimum number of white blocks in any window of size k.

### Algorithm Steps:

1. **Initialize Variables**:
   - `cur_black`, `cur_white`: Count of black and white blocks in current window
   - `l`, `r`: Left and right pointers for the sliding window
   - `min_white`: Track minimum white blocks found so far

2. **Initial Window Setup**: 
   - **Bug Fix Needed**: The original code has `range(l, r)` which should be `range(l, r+1)` or `range(k)` to include all k elements
   - Count white and black blocks in the first window

3. **Sliding Window**:
   - Expand window by moving right pointer
   - Update counts for the new element
   - Track minimum white count
   - Shrink window by moving left pointer
   - Update counts by removing the leftmost element

4. **Return Result**: The minimum white count represents the minimum operations needed

### Time & Space Complexity:
- **Time**: O(n) - single pass through the string
- **Space**: O(1) - only using constant extra space

### Example Walkthrough:
For `blocks = "WBBWWBBWBW"`, `k = 7`:
- Windows of size 7: WBBWWBB(3W), BBWWBBW(3W), BWWBBWB(3W), WWBBWBW(4W)
- Minimum white blocks: 3
- Answer: 3 operations needed

# Tags

