## Problem

https://leetcode.com/problems/maximum-number-of-pairs-in-array/description/

```
You are given a 0-indexed integer array nums. In one operation, you may do the following:

Choose two integers in nums that are equal.
Remove both integers from nums, forming a pair.
The operation is done on nums as many times as possible.

Return a 0-indexed integer array answer of size 2 where answer[0] is the number of pairs that are formed and answer[1] is the number of leftover integers in nums after doing the operation as many times as possible.

Example 1:

Input: nums = [1,3,2,1,3,2,2]
Output: [3,1]
Explanation:
Form a pair with nums[0] and nums[3] and remove them from nums. Now, nums = [3,2,3,2,2].
Form a pair with nums[0] and nums[2] and remove them from nums. Now, nums = [2,2,2].
Form a pair with nums[0] and nums[1] and remove them from nums. Now, nums = [2].
No more pairs can be formed. A total of 3 pairs have been formed, and there is 1 number leftover in nums.

Example 2:

Input: nums = [1,1]
Output: [1,0]
Explanation: Form a pair with nums[0] and nums[1] and remove them from nums. Now, nums = [].
No more pairs can be formed. A total of 1 pair has been formed, and there are 0 numbers leftover in nums.

Example 3:

Input: nums = [0]
Output: [0,1]
Explanation: No pairs can be formed, and there is 1 number leftover in nums.

Constraints:

1 <= nums.length <= 100
0 <= nums[i] <= 100
```

## Observations

1. **Pair Formation Rule**: We can only form pairs with identical numbers. For example, if we have `[1,1,3,3,3]`, we can form 1 pair of 1's and 1 pair of 3's, leaving one 3 unpaired.

2. **Maximum Pairs from Frequency**: For any number that appears `n` times in the array, we can form at most `n // 2` pairs (integer division). The remaining numbers after pairing will be `n % 2`.

3. **Counting Strategy**: Instead of simulating the actual pairing process, we can:
   - Count the frequency of each unique number
   - For each frequency, calculate how many pairs can be formed
   - Sum up all possible pairs
   - Calculate leftovers as `total_numbers - (pairs_formed * 2)`

4. **Example Analysis**:
   - `nums = [1,3,2,1,3,2,2]`
   - Frequencies: `{1: 2, 3: 2, 2: 3}`
   - Pairs: `2//2 + 2//2 + 3//2 = 1 + 1 + 1 = 3`
   - Leftovers: `7 - 3*2 = 1`

## Solution

The solution uses a **frequency counting approach** with the following steps:

1. **Count Frequencies**: Use `Counter(nums)` to get the frequency of each unique number in the array.

2. **Calculate Pairs**: For each unique number with frequency `v`, we can form `v // 2` pairs. Sum these up across all unique numbers.

3. **Calculate Leftovers**: Since each pair removes 2 numbers, the leftover count is:
   `len(nums) - count * 2`
   where `count` is the total number of pairs formed.

**Time Complexity**: O(n) where n is the length of the input array
- O(n) to count frequencies
- O(k) to iterate through unique numbers (k ≤ n)

**Space Complexity**: O(k) where k is the number of unique elements in the array
- Counter stores at most n unique elements

**Key Insight**: We don't need to simulate the actual pairing process. Mathematical calculation based on frequencies is sufficient and more efficient.

# Tags

- Array
- Hash Table
- Counting
- Math

