## Problem Description

https://leetcode.com/problems/add-binary/

```
Given two binary strings a and b, return their sum as a binary string.

Example 1:

Input: a = "11", b = "1"
Output: "100"

Example 2:

Input: a = "1010", b = "1011"
Output: "10101"

Constraints:

1 <= a.length, b.length <= 10^4
a and b consist only of '0' or '1' characters.
Each string does not contain leading zeros except for the zero itself.
```

## Observations

Binary numbers use only `0` and `1`. Adding them is similar to normal addition, but whenever the sum is `2`, we write `0` and carry over `1` to the next digit.

Key Points
- We need to add two binary strings digit by digit, starting from the rightmost digit (least significant).
- If the sum at any position is `2`, we carry over `1` to the next position.

## Solution

Let's break down the provided Python solution step by step:

1. **Reverse and Convert Strings to Digits**
	- The code reverses both strings so we can add from right to left.
	- Each character is converted to an integer (0 or 1).

2. **Prepare a Temporary List for the Result**
	- A list ```temp``` is created to store the sum, with an extra space for possible carry at the end.

3. **Add Digits from Both Numbers**
	- The digits from ```a``` and ```b``` are added to ```temp``` at their respective positions.

4. **Handle Carry-Over**
	- For each position in ```temp```, if the value is greater than 1 (i.e., 2), set the current position to 0 or 1 and add 1 to the next position (carry).

5. **Remove Leading Zero (if any)**
	- If the last digit in ```temp``` is 0, it is removed to avoid leading zeros in the result.

6. **Convert Back to String**
	- The digits in `temp` are reversed back to the correct order and converted to characters ('0' or '1').
	- The result is joined into a string and returned.

### Example

Suppose `a = "101"` and `b = "11"`:
- Reverse: `a = [1,0,1]`, `b = [1,1]`
- Add: `temp = [2,1,1,0]` (after addition)
- Carry: `temp = [0,2,1,0]` → `temp = [0,0,2,0]` → `temp = [0,0,0,1]`
- Remove leading zero: `temp = [0,0,0,1]` (no leading zero to remove)
- Reverse and convert: Result is "1000"

## Tags

array, string