## Problem

https://leetcode.com/problems/count-number-of-maximum-bitwise-or-subsets/description/

```
Given an integer array nums, find the maximum possible bitwise OR of a subset of nums and return the number of different non-empty subsets with the maximum bitwise OR.

An array a is a subset of an array b if a can be obtained from b by deleting some (possibly zero) elements of b. Two subsets are considered different if the indices of the elements chosen are different.

The bitwise OR of an array a is equal to a[0] OR a[1] OR ... OR a[a.length - 1] (0-indexed).

Example 1:
Input: nums = [3,1]
Output: 2
Explanation: The maximum possible bitwise OR of a subset is 3. There are 2 subsets with a bitwise OR of 3:
- [3]
- [3,1]

Example 2:
Input: nums = [2,2,2]
Output: 7
Explanation: All non-empty subsets of [2,2,2] have a bitwise OR of 2. There are 2^3 - 1 = 7 total subsets.

Example 3:
Input: nums = [3,2,1,5]
Output: 6
Explanation: The maximum possible bitwise OR of a subset is 7. There are 6 subsets with a bitwise OR of 7:
- [3,5], [3,1,5], [3,2,5], [3,2,1,5], [2,5], [2,1,5]

Constraints:
- 1 <= nums.length <= 16
- 1 <= nums[i] <= 10^5
```

## Observations

1. **Maximum OR value**: The maximum possible bitwise OR of any subset is achieved by OR-ing ALL elements together, since the OR operation only sets bits (never clears them). Once a bit is set to 1 by any element, it remains 1.

2. **Subset generation**: We need to count all possible subsets that achieve this maximum OR value. Since n ≤ 16, a brute force approach generating all 2^n subsets is feasible.

3. **Key insight**: Not every subset will achieve the maximum OR. A subset achieves the maximum OR only if it contains enough elements to "activate" all the bits present in the maximum OR value.

4. **Backtracking approach**: We can use recursive backtracking to generate all possible subsets, calculate their OR value, and count those that equal the maximum.

## Solution

**Approach: Backtracking with Subset Generation**

1. **Calculate Maximum OR**: First, iterate through all elements and OR them together to find the maximum possible OR value that any subset can achieve.

2. **Generate All Subsets**: Use backtracking to generate all possible subsets:
   - At each index, we have 2 choices: include the element or exclude it
   - This creates a binary tree of choices with 2^n leaf nodes (all possible subsets)

3. **Count Valid Subsets**: For each generated subset:
   - Calculate its OR value
   - If it equals the maximum OR, increment the count

4. **Recursive Function**: The `generating(idx, tmp)` function:
   - `idx`: current index in nums array
   - `tmp`: current subset being built
   - Base case: when idx >= n, we've made decisions for all elements
   - Recursive cases: 
     - Exclude nums[idx]: `generating(idx + 1, tmp)`
     - Include nums[idx]: `generating(idx + 1, tmp + [nums[idx]])`

**Complexity Analysis**:
- Time: O(2^n × n) - Generate 2^n subsets, each requiring O(n) time to calculate OR
- Space: O(n) - Recursion depth and temporary subset storage

**Code Walkthrough**:
```python
class Solution:
    def countMaxOrSubsets(self, nums: List[int]) -> int:
        # Step 1: Calculate maximum possible OR
        OR = 0
        for val in nums:
            OR |= val
        
        n = len(nums)
        count = 0
        
        # Step 2: Generate all subsets using backtracking
        def generating(idx: int, tmp: List[int]) -> None:
            # Base case: processed all elements
            if idx >= n:
                # Calculate OR of current subset
                tmp_or = 0
                for val in tmp:
                    tmp_or |= val
                # Count if matches maximum OR
                if tmp_or == OR:
                    nonlocal count
                    count += 1
                return
            
            # Exclude current element
            generating(idx + 1, tmp)
            # Include current element
            generating(idx + 1, tmp + [nums[idx]])
        
        generating(0, [])
        return count
```

# Tags
#backtracking #bit-manipulation #subset-generation #recursion

