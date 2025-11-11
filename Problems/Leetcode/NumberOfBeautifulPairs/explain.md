## Problem

https://leetcode.com/problems/number-of-beautiful-pairs/description/

```
You are given a 0-indexed integer array nums. A pair of indices i, j where 0 <= i < j < nums.length is called beautiful if the first digit of nums[i] and the last digit of nums[j] are coprime.

Return the total number of beautiful pairs in nums.

Two integers x and y are coprime if there is no integer greater than 1 that divides both of them. In other words, x and y are coprime if gcd(x, y) == 1, where gcd(x, y) is the greatest common divisor of x and y.

Example 1:

Input: nums = [2,5,1,4]
Output: 5
Explanation: There are 5 beautiful pairs in nums:
When i = 0 and j = 1: the first digit of nums[0] is 2, and the last digit of nums[1] is 5. We can confirm that 2 and 5 are coprime, since gcd(2,5) == 1.
When i = 0 and j = 2: the first digit of nums[0] is 2, and the last digit of nums[2] is 1. Indeed, gcd(2,1) == 1.
When i = 1 and j = 2: the first digit of nums[1] is 5, and the last digit of nums[2] is 1. Indeed, gcd(5,1) == 1.
When i = 1 and j = 3: the first digit of nums[1] is 5, and the last digit of nums[3] is 4. Indeed, gcd(5,4) == 1.
When i = 2 and j = 3: the first digit of nums[2] is 1, and the last digit of nums[3] is 4. Indeed, gcd(1,4) == 1.
Thus, we return 5.

Example 2:

Input: nums = [11,21,12]
Output: 2
Explanation: There are 2 beautiful pairs:
When i = 0 and j = 1: the first digit of nums[0] is 1, and the last digit of nums[1] is 1. Indeed, gcd(1,1) == 1.
When i = 0 and j = 2: the first digit of nums[0] is 1, and the last digit of nums[2] is 2. Indeed, gcd(1,2) == 1.
Thus, we return 2.

Constraints:

2 <= nums.length <= 100
1 <= nums[i] <= 9999
nums[i] % 10 != 0
```

## Observations

1. **Problem Definition**: We need to find pairs of indices (i, j) where i < j such that the first digit of nums[i] and the last digit of nums[j] are coprime (gcd = 1).

2. **Key Components**:
   - First digit extraction: Convert number to string and take first character, then convert back to int
   - Last digit extraction: Use modulo 10 operation (n % 10)
   - Coprime check: Two numbers are coprime if gcd(a, b) == 1

3. **Constraints Analysis**:
   - Array length: 2 <= n <= 100 (small enough for O(n²) solution)
   - Number range: 1 <= nums[i] <= 9999 (4 digits max)
   - No trailing zeros: nums[i] % 10 != 0 (simplifies last digit extraction)

4. **Examples Walkthrough**:
   - nums = [2,5,1,4]: All pairs are beautiful because 1 is coprime with any digit, and 2,5 are coprime with 4
   - nums = [11,21,12]: Only (0,1) and (0,2) are beautiful since gcd(1,1)=1 and gcd(1,2)=1, but gcd(2,2)=2≠1

5. **Edge Cases**:
   - Minimum array size (n=2): Only one pair to check
   - Single digit numbers: First digit = the number itself
   - Numbers with same first/last digits: May not be coprime (e.g., gcd(2,2) = 2)

## Solution

**Approach**: Brute Force with Nested Loops

**Algorithm**:
1. Use two nested loops to generate all possible pairs (i, j) where i < j
2. For each pair:
   - Extract first digit of nums[i]: `int(str(nums[i])[0])`
   - Extract last digit of nums[j]: `nums[j] % 10`
   - Check if gcd(first_digit, last_digit) == 1
   - If coprime, increment counter
3. Return the total count

**Time Complexity**: O(n² × log(min(a,b))) where log(min(a,b)) is for GCD computation
- Since digits are 1-9, GCD computation is effectively O(1)
- Overall: O(n²)

**Space Complexity**: O(1) - only using constant extra space

**Key Implementation Details**:
- `str(a)[0]` efficiently gets the first digit by string conversion
- `b % 10` efficiently gets the last digit using modulo
- `math.gcd()` handles the coprime check
- Nested loop ensures i < j condition automatically

**Alternative Optimizations** (not implemented but possible):
- Precompute first/last digits for all numbers: O(n) preprocessing
- Use frequency counting if many duplicate digits exist
- For very large arrays, could use mathematical properties of coprime digits

# Tags

Array, Math, Number Theory, Brute Force, GCD

