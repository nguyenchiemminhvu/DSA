## Problem

https://leetcode.com/problems/minimum-sum-of-four-digit-number-after-splitting-digits/

```
You are given a positive integer num consisting of exactly four digits. Split num into two new integers new1 and new2 by using the digits found in num. Leading zeros are allowed in new1 and new2, and all the digits found in num must be used.

For example, given num = 2932, you have the following digits: two 2's, one 9 and one 3. Some of the possible pairs [new1, new2] are [22, 93], [23, 92], [223, 9] and [2, 329].
Return the minimum possible sum of new1 and new2.

Example 1:

Input: num = 2932
Output: 52
Explanation: Some possible pairs [new1, new2] are [29, 23], [223, 9], etc.
The minimum sum can be obtained by the pair [29, 23]: 29 + 23 = 52.

Example 2:

Input: num = 4009
Output: 13
Explanation: Some possible pairs [new1, new2] are [0, 49], [490, 0], etc. 
The minimum sum can be obtained by the pair [4, 9]: 4 + 9 = 13.

Constraints:

1000 <= num <= 9999
```

## Observations

1. **Problem Understanding**: We need to split a 4-digit number into two new numbers using all digits, then find the minimum possible sum of these two numbers.

2. **Key Insight**: To minimize the sum, we want to minimize the tens digits of both numbers since they contribute more to the total than ones digits.

3. **Optimal Strategy**: After sorting the digits in ascending order, we should:
   - Put the two smallest digits as the tens digits of our two numbers
   - Put the two largest digits as the ones digits of our two numbers
   - This gives us: `(smallest * 10 + third_smallest) + (second_smallest * 10 + largest)`

4. **Why this works**: 
   - We want to minimize `10a + c + 10b + d` where a,b are tens digits and c,d are ones digits
   - Since tens digits are multiplied by 10, putting smaller values there has maximum impact
   - The cross-pairing (smallest with third-smallest, second-smallest with largest) ensures optimal distribution

5. **Example Walkthrough**:
   - For `num = 2932`: digits = [2, 3, 2, 9] → sorted = [2, 2, 3, 9]
   - Form numbers: (2×10 + 3) + (2×10 + 9) = 23 + 29 = 52
   - Alternative like (2×10 + 2) + (3×10 + 9) = 22 + 39 = 61 (worse)

## Solution

**Time Complexity**: O(1) - We always process exactly 4 digits, and sorting 4 elements is constant time.

**Space Complexity**: O(1) - We use a fixed-size array of 4 elements.

**Algorithm Explanation**:
1. **Digit Extraction**: Use modulo and integer division to extract each digit
   - `num % 10`: ones digit
   - `num // 10 % 10`: tens digit  
   - `num // 100 % 10`: hundreds digit
   - `num // 1000 % 10`: thousands digit

2. **Sort**: Arrange digits in ascending order to identify smallest/largest values

3. **Optimal Pairing**: Create two 2-digit numbers where:
   - Smaller digits become tens places (higher impact on sum)
   - Cross-pair to balance the distribution optimally

**Why Cross-Pairing Works**:
Given sorted digits [a, b, c, d] where a ≤ b ≤ c ≤ d:
- Our approach: (10a + c) + (10b + d) = 10(a + b) + (c + d)
- Alternative: (10a + b) + (10c + d) = 10(a + c) + (b + d)
- Since a ≤ b and c ≤ d, we have (a + b) ≤ (a + c), making our approach optimal

## Tags

math