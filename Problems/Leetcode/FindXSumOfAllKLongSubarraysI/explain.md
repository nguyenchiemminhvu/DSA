## Problem

https://leetcode.com/problems/find-x-sum-of-all-k-long-subarrays-i/description/

```
You are given an array nums of n integers and two integers k and x.

The x-sum of an array is calculated by the following procedure:

Count the occurrences of all elements in the array.
Keep only the occurrences of the top x most frequent elements. If two elements have the same number of occurrences, the element with the bigger value is considered more frequent.
Calculate the sum of the resulting array.
Note that if an array has less than x distinct elements, its x-sum is the sum of the array.

Return an integer array answer of length n - k + 1 where answer[i] is the x-sum of the subarray nums[i..i + k - 1].

Example 1:

Input: nums = [1,1,2,2,3,4,2,3], k = 6, x = 2

Output: [6,10,12]

Explanation:

For subarray [1, 1, 2, 2, 3, 4], only elements 1 and 2 will be kept in the resulting array. Hence, answer[0] = 1 + 1 + 2 + 2.
For subarray [1, 2, 2, 3, 4, 2], only elements 2 and 4 will be kept in the resulting array. Hence, answer[1] = 2 + 2 + 2 + 4. Note that 4 is kept in the array since it is bigger than 3 and 1 which occur the same number of times.
For subarray [2, 2, 3, 4, 2, 3], only elements 2 and 3 are kept in the resulting array. Hence, answer[2] = 2 + 2 + 2 + 3 + 3.

Example 2:

Input: nums = [3,8,7,8,7,5], k = 2, x = 2

Output: [11,15,15,15,12]

Explanation:

Since k == x, answer[i] is equal to the sum of the subarray nums[i..i + k - 1].

Constraints:

1 <= n == nums.length <= 50
1 <= nums[i] <= 50
1 <= x <= k <= nums.length
```

## Observations

1. **X-Sum Definition**: For any subarray, we need to:
   - Count frequency of each element
   - Select top `x` most frequent elements (with tie-breaking by value in descending order)
   - Sum all occurrences of these selected elements

2. **Sliding Window Pattern**: We need to compute x-sum for all subarrays of length `k`, which suggests a sliding window approach.

3. **Frequency & Priority**: When elements have the same frequency, we prioritize the larger value. This requires custom sorting.

4. **Edge Case**: If a subarray has fewer than `x` distinct elements, we include all elements in the sum.

5. **Time Complexity Consideration**: For each subarray, we need to count frequencies and sort, making it O(k log k) per subarray.

## Solution

1. **Helper Function `xsum(arr)`:**
   - Creates frequency map for all elements in the array
   - Sorts array by custom key: `(-freq[x], -x)` 
     - Primary: frequency in descending order
     - Secondary: value in descending order (for tie-breaking)
   - Iterates through sorted array, counting distinct elements
   - Stops after processing `x` distinct elements
   - Returns sum of all occurrences of selected elements

2. **Main Function:**
   - Generates all subarrays of length `k` using sliding window
   - For each subarray, calls `xsum()` to compute the x-sum
   - Collects results in output array

**Time Complexity:** O((n-k+1) × k log k)
- We process (n-k+1) subarrays
- Each subarray requires O(k log k) for sorting

**Space Complexity:** O(k)
- Frequency map and temporary subarray storage

**Key Insight:** The sorting approach ensures we process elements in the correct priority order (most frequent first, then largest value for ties), allowing us to simply sum the first `x` distinct elements we encounter.

# Tags

- Array
- Hash Table
- Sliding Window
- Sorting
- Frequency Counting

