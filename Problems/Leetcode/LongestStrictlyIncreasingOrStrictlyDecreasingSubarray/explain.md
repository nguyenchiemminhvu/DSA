## Problem

https://leetcode.com/problems/longest-strictly-increasing-or-strictly-decreasing-subarray/description/

```
You are given an array of integers nums. Return the length of the longest subarray of nums which is either strictly increasing or strictly decreasing.

Example 1:

Input: nums = [1,4,3,3,2]

Output: 2

Explanation:

The strictly increasing subarrays of nums are [1], [2], [3], [3], [4], and [1,4].

The strictly decreasing subarrays of nums are [1], [2], [3], [3], [4], [3,2], and [4,3].

Hence, we return 2.

Example 2:

Input: nums = [3,3,3,3]

Output: 1

Explanation:

The strictly increasing subarrays of nums are [3], [3], [3], and [3].

The strictly decreasing subarrays of nums are [3], [3], [3], and [3].

Hence, we return 1.

Example 3:

Input: nums = [3,2,1]

Output: 3

Explanation:

The strictly increasing subarrays of nums are [3], [2], and [1].

The strictly decreasing subarrays of nums are [3], [2], [1], [3,2], [2,1], and [3,2,1].

Hence, we return 3.

Constraints:

1 <= nums.length <= 50
1 <= nums[i] <= 50
```

## Observations

- We need to find the longest subarray that is either strictly increasing or strictly decreasing
- A subarray must be contiguous elements
- Strictly increasing means each element is greater than the previous one
- Strictly decreasing means each element is less than the previous one
- We need to track the maximum length among all possible strictly increasing and decreasing subarrays
- The minimum length is always 1 (single element)
- Key insight: We can use dynamic programming to track the length of increasing/decreasing sequences ending at each position

## Solution

1. **Initialize arrays**: Create two arrays `inc_prefix` and `dec_prefix` of size `n`, both initialized with 1s. These represent the length of strictly increasing and decreasing subarrays ending at each position.

2. **Dynamic Programming approach**:
   - `inc_prefix[i]` stores the length of the longest strictly increasing subarray ending at index `i`
   - `dec_prefix[i]` stores the length of the longest strictly decreasing subarray ending at index `i`

3. **Fill the arrays**:
   - For each position `i` from 1 to n-1:
     - If `nums[i] > nums[i-1]`: extend the increasing sequence, so `inc_prefix[i] = inc_prefix[i-1] + 1`
     - If `nums[i] < nums[i-1]`: extend the decreasing sequence, so `dec_prefix[i] = dec_prefix[i-1] + 1`
     - If `nums[i] == nums[i-1]`: both arrays remain 1 (reset to single element)

4. **Return result**: The answer is the maximum value from both arrays.

### Example walkthrough with [1,4,3,3,2]:

- Initial: `inc_prefix = [1,1,1,1,1]`, `dec_prefix = [1,1,1,1,1]`
- i=1: nums[1]=4 > nums[0]=1 → `inc_prefix[1] = 2`
- i=2: nums[2]=3 < nums[1]=4 → `dec_prefix[2] = 2`
- i=3: nums[3]=3 == nums[2]=3 → no change
- i=4: nums[4]=2 < nums[3]=3 → `dec_prefix[4] = 2`

Final arrays: `inc_prefix = [1,2,1,1,1]`, `dec_prefix = [1,1,2,1,2]`
Result: max(2, 2) = 2

### Time Complexity: O(n)
### Space Complexity: O(n)

# Tags

- Array
- Dynamic Programming
- Prefix Array
- Two Pointers (alternative approach)
- Sliding Window (alternative approach)
