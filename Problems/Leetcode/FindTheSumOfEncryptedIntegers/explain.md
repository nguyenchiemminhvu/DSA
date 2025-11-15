## Problem

https://leetcode.com/problems/find-the-sum-of-encrypted-integers/description/

```
You are given an integer array nums containing positive integers. We define a function encrypt such that encrypt(x) replaces every digit in x with the largest digit in x. For example, encrypt(523) = 555 and encrypt(213) = 333.

Return the sum of encrypted elements.

Example 1:

Input: nums = [1,2,3]

Output: 6

Explanation: The encrypted elements are [1,2,3]. The sum of encrypted elements is 1 + 2 + 3 == 6.

Example 2:

Input: nums = [10,21,31]

Output: 66

Explanation: The encrypted elements are [11,22,33]. The sum of encrypted elements is 11 + 22 + 33 == 66.

Constraints:

1 <= nums.length <= 50
1 <= nums[i] <= 1000
```

## Observations

1. **Encryption Rule**: For each number, we replace every digit with the largest digit in that number
   - Example: 523 → 555 (largest digit is 5)
   - Example: 213 → 333 (largest digit is 3)

2. **Process**: 
   - Extract all digits from the number
   - Find the maximum digit
   - Construct a new number with the same length but all digits are the maximum digit

3. **Edge Cases**:
   - Single digit numbers remain unchanged (e.g., 7 → 7)
   - Numbers with all same digits remain unchanged (e.g., 333 → 333)

4. **Constraints Analysis**:
   - Small array size (≤ 50) and small numbers (≤ 1000) make efficiency less critical
   - Simple digit manipulation approach is sufficient

## Solution

1. **Encrypt Function**:
   - Extract digits using modulo and integer division
   - Keep track of digit count to maintain original number length
   - Find maximum digit using `max(digits)`
   - Reconstruct number by repeatedly adding max digit and shifting left

2. **Main Logic**:
   - Apply encryption to each number in the array
   - Sum all encrypted values and return the result

**Time Complexity**: O(n × d) where n is array length and d is average number of digits
**Space Complexity**: O(d) for storing digits of each number

**Example Walkthrough**:
- nums = [10, 21, 31]
- encrypt(10): digits=[0,1], max=1, result=11
- encrypt(21): digits=[1,2], max=2, result=22  
- encrypt(31): digits=[1,3], max=3, result=33
- Sum: 11 + 22 + 33 = 66

# Tags

Array, Math, Simulation

