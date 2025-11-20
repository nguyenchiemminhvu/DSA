## Problem

https://leetcode.com/problems/find-the-k-or-of-an-array/description/

```
You are given an integer array nums, and an integer k. Let's introduce K-or operation by extending the standard bitwise OR. In K-or, a bit position in the result is set to 1 if at least k numbers in nums have a 1 in that position.

Return the K-or of nums.

Example 1:

Input: nums = [7,12,9,8,9,15], k = 4

Output: 9

Explanation:

Represent numbers in binary:

Number	Bit 3	Bit 2	Bit 1	Bit 0
7	0	1	1	1
12	1	1	0	0
9	1	0	0	1
8	1	0	0	0
9	1	0	0	1
15	1	1	1	1
Result = 9	1	0	0	1
Bit 0 is set in 7, 9, 9, and 15. Bit 3 is set in 12, 9, 8, 9, and 15.
Only bits 0 and 3 qualify. The result is (1001)2 = 9.

Example 2:

Input: nums = [2,12,1,11,4,5], k = 6

Output: 0

Explanation: No bit appears as 1 in all six array numbers, as required for K-or with k = 6. Thus, the result is 0.

Example 3:

Input: nums = [10,8,5,9,11,6,8], k = 1

Output: 15

Explanation: Since k == 1, the 1-or of the array is equal to the bitwise OR of all its elements. Hence, the answer is 10 OR 8 OR 5 OR 9 OR 11 OR 6 OR 8 = 15.

Constraints:

1 <= nums.length <= 50
0 <= nums[i] < 231
1 <= k <= nums.length
```

## Observations

1. **Understanding K-OR Operation**: The K-OR operation is a modification of bitwise OR where a bit position in the result is set to 1 only if at least k numbers in the array have a 1 in that position.

2. **Bit Position Analysis**: We need to examine each bit position (0 to 31 for 32-bit integers) across all numbers in the array and count how many numbers have a 1 in each position.

3. **Frequency Counting**: For each bit position, we count the frequency of 1s across all numbers. If the frequency is >= k, then that bit should be set to 1 in the result.

4. **Edge Cases**:
   - When k = 1: K-OR becomes regular bitwise OR of all elements
   - When k = array.length: K-OR becomes bitwise AND of all elements
   - When k > array.length: Result is always 0

5. **Bit Manipulation Techniques**:
   - `val & (1 << i)` checks if the i-th bit is set in value `val`
   - `res |= (1 << i)` sets the i-th bit in the result
   - We examine 32 bit positions to cover all possible integer values (0 to 2^31 - 1)

## Solution

1. **Initialize Frequency Counter**: Use `defaultdict(int)` to count occurrences of 1s at each bit position.

2. **Count Bit Frequencies**: 
   - For each number in the array, examine all 32 bit positions
   - Use `val & (1 << i)` to check if the i-th bit is set
   - Increment the counter for that bit position

3. **Build Result**:
   - Initialize result as 0
   - For each bit position, if the frequency >= k, set that bit in the result
   - Use `res |= (1 << i)` to set the i-th bit

**Time Complexity**: O(32 * n) = O(n) where n is the length of nums array
**Space Complexity**: O(32) = O(1) for the frequency counter

**Example Walkthrough** (nums = [7,12,9,8,9,15], k = 4):
- Bit 0: appears in 7,9,9,15 → count = 4 ≥ k → set bit 0
- Bit 1: appears in 7,15 → count = 2 < k → don't set
- Bit 2: appears in 7,12,15 → count = 3 < k → don't set  
- Bit 3: appears in 12,9,8,9,15 → count = 5 ≥ k → set bit 3
- Result: bits 0 and 3 are set → (1001)₂ = 9

# Tags

- **Bit Manipulation**: Core technique for examining individual bits
- **Frequency Counting**: Track occurrences of 1s at each bit position
- **Array Processing**: Iterate through array elements
- **Bitwise Operations**: AND (&), OR (|), bit shifting (<<)

