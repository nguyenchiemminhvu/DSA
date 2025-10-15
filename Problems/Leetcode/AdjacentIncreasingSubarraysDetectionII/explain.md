## Problem

https://leetcode.com/problems/adjacent-increasing-subarrays-detection-ii/description/

```
Given an array nums of n integers, your task is to find the maximum value of k for which there exist two adjacent subarrays of length k each, such that both subarrays are strictly increasing. Specifically, check if there are two subarrays of length k starting at indices a and b (a < b), where:

Both subarrays nums[a..a + k - 1] and nums[b..b + k - 1] are strictly increasing.
The subarrays must be adjacent, meaning b = a + k.
Return the maximum possible value of k.

A subarray is a contiguous non-empty sequence of elements within an array.

Example 1:

Input: nums = [2,5,7,8,9,2,3,4,3,1]

Output: 3

Explanation:

The subarray starting at index 2 is [7, 8, 9], which is strictly increasing.
The subarray starting at index 5 is [2, 3, 4], which is also strictly increasing.
These two subarrays are adjacent, and 3 is the maximum possible value of k for which two such adjacent strictly increasing subarrays exist.

Example 2:

Input: nums = [1,2,3,4,4,4,4,5,6,7]

Output: 2

Explanation:

The subarray starting at index 0 is [1, 2], which is strictly increasing.
The subarray starting at index 2 is [3, 4], which is also strictly increasing.
These two subarrays are adjacent, and 2 is the maximum possible value of k for which two such adjacent strictly increasing subarrays exist.

Constraints:

2 <= nums.length <= 2 * 105
-109 <= nums[i] <= 109
```

## Observations

### Key Insights

1. **Precompute Increasing Lengths**: Instead of checking every possible position and length, we can precompute for each position how long the strictly increasing subarray ending at that position is.

2. **Binary Search on Answer**: The maximum value of `k` has a nice property - if `k` works, then all values less than `k` also work. This monotonic property allows us to use binary search to find the maximum valid `k`.

3. **Two Scenarios for Valid k**: For a given `k`, two adjacent increasing subarrays can exist in two ways:
   - **Scenario 1**: A single continuous increasing subarray of length `2k` (which naturally contains two adjacent increasing subarrays of length `k`)
   - **Scenario 2**: Two separate adjacent increasing subarrays, each of length at least `k`

4. **Search Space**: The maximum possible `k` is `n // 2` because we need at least `2k` elements for two adjacent subarrays of length `k`.

### Algorithm Breakdown

**Step 1: Dynamic Programming to Build Increasing Lengths**
- `dp[i]` = length of the longest strictly increasing subarray ending at index `i`
- For each position, if `nums[i] > nums[i-1]`, extend the previous increasing length
- Time complexity: O(n)

**Step 2: Binary Search for Maximum k**
- Search range: `[1, n//2]`
- For each candidate `k`, verify if valid adjacent increasing subarrays exist
- Time complexity: O(log n) iterations

**Step 3: Validation Function**
- For each position `i` starting from index `k`:
  - Check if `dp[i] >= 2*k`: one long increasing sequence covering both subarrays
  - Check if `dp[i] >= k AND dp[i-k] >= k`: two separate adjacent increasing subarrays
- Time complexity per check: O(n)

**Overall Time Complexity**: O(n log n)
**Space Complexity**: O(n) for the dp array

### Example Walkthrough

**Example 1**: `nums = [2,5,7,8,9,2,3,4,3,1]`

1. **Build dp array**:
   - Index:  0  1  2  3  4  5  6  7  8  9
   - nums:   2  5  7  8  9  2  3  4  3  1
   - dp:     1  2  3  4  5  1  2  3  1  1

2. **Binary search**: range [1, 5]
   - Try k=3: Check positions 3-9
     - i=4: dp[4]=5 >= 2*3=6? No. dp[4]=5 >= 3 AND dp[1]=2 >= 3? No
     - i=5: dp[5]=1 >= 6? No. dp[5]=1 >= 3? No
     - i=6: dp[6]=2 >= 6? No. dp[6]=2 >= 3? No
     - i=7: dp[7]=3 >= 6? No. dp[7]=3 >= 3 AND dp[4]=5 >= 3? **Yes!**
   - k=3 works! Try larger...
   - Try k=4: No valid position found
   - Answer: 3

**Example 2**: `nums = [1,2,3,4,4,4,4,5,6,7]`

1. **Build dp array**:
   - dp: [1,2,3,4,1,1,1,2,3,4]

2. **Binary search**: finds k=2
   - At i=3: dp[3]=4 >= 2*2=4? Yes!
   - Answer: 2

## Tags

array, binary search