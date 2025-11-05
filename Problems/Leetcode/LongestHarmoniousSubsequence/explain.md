## Problem

https://leetcode.com/problems/longest-harmonious-subsequence/description/

```
We define a harmonious array as an array where the difference between its maximum value and its minimum value is exactly 1.

Given an integer array nums, return the length of its longest harmonious subsequence among all its possible subsequences.

Example 1:

Input: nums = [1,3,2,2,5,2,3,7]

Output: 5

Explanation:

The longest harmonious subsequence is [3,2,2,2,3].

Example 2:

Input: nums = [1,2,3,4]

Output: 2

Explanation:

The longest harmonious subsequences are [1,2], [2,3], and [3,4], all of which have a length of 2.

Example 3:

Input: nums = [1,1,1,1]

Output: 0

Explanation:

No harmonic subsequence exists.

Constraints:

1 <= nums.length <= 2 * 104
-109 <= nums[i] <= 109
```

## Observations

1. **Definition Analysis**: A harmonious subsequence requires exactly two distinct values where the difference between max and min is exactly 1.

2. **Key Insight**: Since the difference must be exactly 1, we only need to consider pairs of adjacent numbers (like `x` and `x+1`).

3. **Frequency Counting**: The length of a harmonious subsequence equals the sum of frequencies of the two adjacent numbers that form it.

4. **Optimization**: Instead of generating all subsequences, we can count frequencies and check adjacent pairs.

5. **Edge Cases**: 
   - Arrays with all identical elements have no harmonious subsequence (difference = 0)
   - Single element arrays cannot form harmonious subsequences
   - We need at least two distinct values

## Solution

1. **Frequency Counting (Lines 3-5)**: 
   - Build a hash map to count occurrences of each number
   - Time: O(n), Space: O(n)

2. **Adjacent Pair Checking (Lines 7-12)**:
   - For each unique number `k` in our frequency map:
     - Check if `k-1` exists: if yes, the harmonious subsequence length is `freq[k-1] + freq[k]`
     - Check if `k+1` exists: if yes, the harmonious subsequence length is `freq[k] + freq[k+1]`
   - Keep track of the maximum length found

3. **Why This Works**:
   - A harmonious subsequence can only contain two distinct values with difference 1
   - The optimal subsequence uses ALL occurrences of both values
   - By checking each number against its neighbors (±1), we cover all possible harmonious pairs

**Example Walkthrough** (`nums = [1,3,2,2,5,2,3,7]`):
- Frequencies: `{1:1, 3:2, 2:3, 5:1, 7:1}`
- Check pairs:
  - (1,2): `freq[1] + freq[2] = 1 + 3 = 4`
  - (2,3): `freq[2] + freq[3] = 3 + 2 = 5` ← Maximum
  - No valid pairs for 5 and 7
- Result: 5

**Time Complexity**: O(n) - single pass to count + single pass through unique values  
**Space Complexity**: O(n) - for the frequency hash map

# Tags

- Hash Table
- Array
- Frequency Counting
- Two Pointers Alternative

