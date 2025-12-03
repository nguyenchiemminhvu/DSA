## Problem

https://leetcode.com/problems/minimum-difference-between-highest-and-lowest-of-k-scores/description/

```
You are given a 0-indexed integer array nums, where nums[i] represents the score of the ith student. 
You are also given an integer k.

Pick the scores of any k students from the array so that the difference between the highest and the 
lowest of the k scores is minimized.

Return the minimum possible difference.

Example 1:
Input: nums = [90], k = 1
Output: 0
Explanation: There is one way to pick score(s) of one student:
- [90]. The difference between the highest and lowest score is 90 - 90 = 0.
The minimum possible difference is 0.

Example 2:
Input: nums = [9,4,1,7], k = 2
Output: 2
Explanation: There are six ways to pick score(s) of two students:
- [9,4,1,7]. The difference between the highest and lowest score is 9 - 4 = 5.
- [9,4,1,7]. The difference between the highest and lowest score is 9 - 1 = 8.
- [9,4,1,7]. The difference between the highest and lowest score is 9 - 7 = 2.
- [9,4,1,7]. The difference between the highest and lowest score is 4 - 1 = 3.
- [9,4,1,7]. The difference between the highest and lowest score is 7 - 4 = 3.
- [9,4,1,7]. The difference between the highest and lowest score is 7 - 1 = 6.
The minimum possible difference is 2.

Constraints:
- 1 <= k <= nums.length <= 1000
- 0 <= nums[i] <= 10^5
```

## Observations

1. **Key Insight**: To minimize the difference between the highest and lowest scores among k students, we should pick k consecutive scores from a sorted array.

2. **Why sorting helps**: After sorting, any window of k consecutive elements will have:
   - The leftmost element as the minimum
   - The rightmost element as the maximum
   - The minimum possible difference for those k elements

3. **Sliding window approach**: We can use a sliding window of size k on the sorted array and find the window with the minimum difference.

4. **Time complexity**: O(n log n) for sorting + O(n) for sliding window = O(n log n)

5. **Space complexity**: O(1) if we don't count the space used by sorting (or O(n) depending on sorting algorithm)

## Solution

1. **Sort the array**: `nums.sort()` - arranges scores in ascending order

2. **Sliding window iteration**: 
   - Loop from index 0 to `len(nums) - k + 1` (inclusive)
   - This ensures we can always take k elements starting from index i

3. **Calculate difference for each window**:
   - For window starting at index i: `nums[i + k - 1] - nums[i]`
   - `nums[i]` is the lowest score in the window (leftmost)
   - `nums[i + k - 1]` is the highest score in the window (rightmost)

4. **Track minimum**: Keep updating `res` with the minimum difference found

**Example Walkthrough** (nums = [9,4,1,7], k = 2):
- After sorting: [1, 4, 7, 9]
- Window [1, 4]: difference = 4 - 1 = 3
- Window [4, 7]: difference = 7 - 4 = 3
- Window [7, 9]: difference = 9 - 7 = 2
- Minimum difference = 2

# Tags
#sorting #sliding-window #array #greedy

