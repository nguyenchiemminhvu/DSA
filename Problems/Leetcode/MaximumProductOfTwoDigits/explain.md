## Problem

https://leetcode.com/problems/maximum-product-of-two-digits/description/

```
You are given a positive integer n.

Return the maximum product of any two digits in n.

Note: You may use the same digit twice if it appears more than once in n.

Example 1:

Input: n = 31

Output: 3

Explanation:

The digits of n are [3, 1].
The possible products of any two digits are: 3 * 1 = 3.
The maximum product is 3.

Example 2:

Input: n = 22

Output: 4

Explanation:

The digits of n are [2, 2].
The possible products of any two digits are: 2 * 2 = 4.
The maximum product is 4.

Example 3:

Input: n = 124

Output: 8

Explanation:

The digits of n are [1, 2, 4].
The possible products of any two digits are: 1 * 2 = 2, 1 * 4 = 4, 2 * 4 = 8.
The maximum product is 8.

Constraints:

10 <= n <= 109
```

## Observations

- We need to find the maximum product of any two digits in a positive integer n
- We can use the same digit twice if it appears more than once
- The key insight is that to maximize the product of two numbers, we should choose the two largest digits
- We need to extract all digits from the number and find the two largest ones


## Solution

1. **Extract digits**: Use a while loop to extract each digit from the number n
   - `n % 10` gets the last digit
   - `n //= 10` removes the last digit from n
   - Continue until n becomes 0

2. **Sort digits**: Sort the array of digits in ascending order
   - This allows us to easily access the largest digits

3. **Find maximum product**: Multiply the two largest digits
   - `arr[-1]` is the largest digit (last element after sorting)
   - `arr[-2]` is the second largest digit (second to last element)

**Time Complexity**: O(d log d) where d is the number of digits in n
**Space Complexity**: O(d) for storing the digits

**Example walkthrough with n = 124:**
- Extract digits: [4, 2, 1] (extracted in reverse order)
- Sort: [1, 2, 4]
- Maximum product: 4 * 2 = 8

# Tags

