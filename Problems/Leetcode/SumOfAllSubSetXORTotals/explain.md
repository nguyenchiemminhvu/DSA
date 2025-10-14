## Problem

https://leetcode.com/problems/sum-of-all-subset-xor-totals/description/

```
The XOR total of an array is defined as the bitwise XOR of all its elements, or 0 if the array is empty.

For example, the XOR total of the array [2,5,6] is 2 XOR 5 XOR 6 = 1.
Given an array nums, return the sum of all XOR totals for every subset of nums. 

Note: Subsets with the same elements should be counted multiple times.

An array a is a subset of an array b if a can be obtained from b by deleting some (possibly zero) elements of b.

Example 1:

Input: nums = [1,3]
Output: 6
Explanation: The 4 subsets of [1,3] are:
- The empty subset has an XOR total of 0.
- [1] has an XOR total of 1.
- [3] has an XOR total of 3.
- [1,3] has an XOR total of 1 XOR 3 = 2.
0 + 1 + 3 + 2 = 6

Example 2:

Input: nums = [5,1,6]
Output: 28
Explanation: The 8 subsets of [5,1,6] are:
- The empty subset has an XOR total of 0.
- [5] has an XOR total of 5.
- [1] has an XOR total of 1.
- [6] has an XOR total of 6.
- [5,1] has an XOR total of 5 XOR 1 = 4.
- [5,6] has an XOR total of 5 XOR 6 = 3.
- [1,6] has an XOR total of 1 XOR 6 = 7.
- [5,1,6] has an XOR total of 5 XOR 1 XOR 6 = 2.
0 + 5 + 1 + 6 + 4 + 3 + 7 + 2 = 28

Example 3:

Input: nums = [3,4,5,6,7,8]
Output: 480
Explanation: The sum of all XOR totals for every subset is 480.

Constraints:

1 <= nums.length <= 12
1 <= nums[i] <= 20
```

## Observations

1. **Subset Generation**: The problem requires us to find all possible subsets of the given array and calculate their XOR totals.

2. **Total Number of Subsets**: For an array of length `n`, there are `2^n` total subsets (including the empty subset).

3. **Bit Manipulation for Subset Generation**: We can use bitmasks to represent subsets. Each bit in the mask represents whether an element at that index is included in the subset.

4. **XOR Properties**: 
   - XOR is commutative and associative
   - Any number XORed with itself equals 0
   - Any number XORed with 0 equals the number itself

5. **Constraint Analysis**: With `n ≤ 12`, we have at most `2^12 = 4096` subsets, making a brute force approach feasible.

## Solution

1. **Initialize**: 
   - `n = len(nums)` - array length
   - `nn = (1 << n)` - total number of subsets (2^n)
   - `res = 0` - accumulator for sum

2. **Subset Generation**:
   - Loop from `1` to `2^n - 1` (skipping empty subset since it contributes 0)
   - Each number `mask` represents a subset using binary representation

3. **Subset Processing**:
   - For each mask, check each bit position `i`
   - If bit `i` is set (`(1 << i) & mask`), include `nums[i]` in the current subset
   - Calculate XOR of all elements in the current subset

4. **Accumulation**:
   - Add each subset's XOR total to the result

**Example Walkthrough** (`nums = [1,3]`):
- Subsets: `[]`, `[1]`, `[3]`, `[1,3]`
- Masks: `00`, `01`, `10`, `11` (binary)
- XOR totals: `0`, `1`, `3`, `1⊕3=2`
- Sum: `0 + 1 + 3 + 2 = 6`

**Time Complexity**: O(n × 2^n) - for each of 2^n subsets, we check n bits
**Space Complexity**: O(1) - only using constant extra space

## Tags

array, bit manipulation