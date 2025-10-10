## Problem

https://leetcode.com/problems/reverse-integer/description/

```
Given a signed 32-bit integer x, return x with its digits reversed. If reversing x causes the value to go outside the signed 32-bit integer range [-231, 231 - 1], then return 0.

Assume the environment does not allow you to store 64-bit integers (signed or unsigned).

Example 1:

Input: x = 123
Output: 321

Example 2:

Input: x = -123
Output: -321

Example 3:

Input: x = 120
Output: 21

Constraints:

-231 <= x <= 231 - 1
```

## Observations

The problem asks to reverse the digits of a given integer.

If the reversed integer overflows a `32-bit` signed integer, return `0`.

Negative numbers should remain negative after reversal.

## Solution

Take the absolute value of the input to simplify digit extraction.

Use a loop to extract digits from the end (using `% 10`) and build the reversed number.

After each extraction, update the reversed number by multiplying by `10` and adding the digit.

Check for overflow: if the reversed number exceeds (`0x7FFFFFFF`), return `0`.

Restore the sign: if the original number was negative, return the negative of the reversed number.

## Tags

math