## Problem

https://leetcode.com/problems/number-of-arithmetic-triplets/

```
You are given a 0-indexed, strictly increasing integer array nums and a positive integer diff. A triplet (i, j, k) is an arithmetic triplet if the following conditions are met:

i < j < k,
nums[j] - nums[i] == diff, and
nums[k] - nums[j] == diff.
Return the number of unique arithmetic triplets.

Example 1:

Input: nums = [0,1,4,6,7,10], diff = 3
Output: 2
Explanation:
(1, 2, 4) is an arithmetic triplet because both 7 - 4 == 3 and 4 - 1 == 3.
(2, 4, 5) is an arithmetic triplet because both 10 - 7 == 3 and 7 - 4 == 3. 

Example 2:

Input: nums = [4,5,6,7,8,9], diff = 2
Output: 2
Explanation:
(0, 2, 4) is an arithmetic triplet because both 8 - 6 == 2 and 6 - 4 == 2.
(1, 3, 5) is an arithmetic triplet because both 9 - 7 == 2 and 7 - 5 == 2.

Constraints:

3 <= nums.length <= 200
0 <= nums[i] <= 200
1 <= diff <= 50
nums is strictly increasing.
```

## Observations

1. **Problem Analysis**: We need to find triplets (i, j, k) where i < j < k and the values form an arithmetic sequence with common difference `diff`.

2. **Key Insight**: For an arithmetic triplet, if we have a value `x`, we need to find `x + diff` and `x + 2*diff` in the array.

3. **Array Properties**: The array is strictly increasing, which means no duplicates. However, the solution uses a frequency map, suggesting it handles the general case.

4. **Brute Force vs Optimized**: Instead of checking all O(n³) combinations, we can use a hash map to check existence in O(1) time.

5. **Mathematical Relationship**: For each potential first element `a`, we need to verify that `a + diff` and `a + 2*diff` exist in the array.

## Solution

**Approach: Hash Map with Frequency Counting**

The solution uses a frequency-based approach:

1. **Build Frequency Map**: Create a hash map to store the frequency of each number in the array.

2. **Count Triplets**: For each unique value `val` in the frequency map:
   - Check if `val + diff` exists (this would be the middle element)
   - Check if `val + 2*diff` exists (this would be the last element)
   - If both exist, multiply their frequencies: `freq[val] × freq[val + diff] × freq[val + 2*diff]`

3. **Why Multiplication**: Since we're counting combinations, we multiply the frequencies of each position.

**Time Complexity**: O(n) - Single pass to build frequency map + single pass through unique values
**Space Complexity**: O(n) - For the frequency map

**Algorithm Walkthrough**:
```python
# Example: nums = [0,1,4,6,7,10], diff = 3
# freq = {0:1, 1:1, 4:1, 6:1, 7:1, 10:1}

# For val = 0: check 0+3=3 (not found), 0+6=6 (found) → 0 triplets
# For val = 1: check 1+3=4 (found), 1+6=7 (found) → 1×1×1 = 1 triplet
# For val = 4: check 4+3=7 (found), 4+6=10 (found) → 1×1×1 = 1 triplet
# Total: 2 triplets
```

**Edge Cases Handled**:
- Numbers that don't have the required arithmetic sequence partners
- Multiple occurrences of the same number (though not possible in this strictly increasing array)
- Empty results when no valid triplets exist

## Tags

array, hash table