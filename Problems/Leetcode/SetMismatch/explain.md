## Problem

https://leetcode.com/problems/set-mismatch/description/

```
You have a set of integers s, which originally contains all the numbers from 1 to n. Unfortunately, due to some error, one of the numbers in s got duplicated to another number in the set, which results in repetition of one number and loss of another number.

You are given an integer array nums representing the data status of this set after the error.

Find the number that occurs twice and the number that is missing and return them in the form of an array.

Example 1:

Input: nums = [1,2,2,4]
Output: [2,3]

Example 2:

Input: nums = [1,1]
Output: [1,2]

Constraints:

2 <= nums.length <= 104
1 <= nums[i] <= 104
```

## Observations

1. **Original Set Properties**: The original set contains all integers from 1 to n exactly once.

2. **Error Pattern**: Exactly one number appears twice (duplicate) and exactly one number is missing.

3. **Sum Relationships**: 
   - Expected sum: `1 + 2 + 3 + ... + n = n * (n + 1) / 2`
   - Current sum: sum of all elements in the given array (includes duplicate)
   - Non-duplicate sum: sum of unique elements only

4. **Mathematical Insight**: 
   - `current_sum - non_duplicate_sum = duplicate_value`
   - `expected_sum - non_duplicate_sum = missing_value`
   - Alternative: `missing_value = expected_sum - current_sum + duplicate_value`

5. **Time/Space Complexity**:
   - Time: O(n) for calculating sums
   - Space: O(n) for creating the set to find unique elements

## Solution

The solution uses mathematical properties to find both the duplicate and missing numbers efficiently:

1. **Calculate expected sum**: For numbers 1 to n, use the formula `n * (n + 1) // 2`

2. **Calculate current sum**: Sum all elements in the input array (includes the duplicate)

3. **Calculate non-duplicate sum**: Convert array to set (removes duplicate) and sum unique elements

4. **Find duplicate**: `duplicate = current_sum - non_duplicate_sum`
   - The difference between these sums is exactly the duplicate value

5. **Find missing**: `missing = expected_sum - non_duplicate_sum`
   - Or alternatively: `missing = expected_sum - current_sum + duplicate`
   - This accounts for the fact that current_sum has an extra duplicate but is missing one number

**Example walkthrough** with `nums = [1,2,2,4]`:
- n = 4
- expected_sum = 4 * 5 // 2 = 10
- cur_sum = 1 + 2 + 2 + 4 = 9  
- non_dup_sum = sum({1,2,4}) = 7
- dup_val = 9 - 7 = 2
- mis_val = 10 - 9 + 2 = 3
- Result: [2, 3] ✓

## Tags

math, array