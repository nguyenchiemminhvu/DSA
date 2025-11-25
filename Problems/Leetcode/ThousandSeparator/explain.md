## Problem

https://leetcode.com/problems/thousand-separator/description/

```
Given an integer n, add a dot (".") as the thousands separator and return it in string format.

Example 1:
Input: n = 987
Output: "987"

Example 2:
Input: n = 1234
Output: "1.234"

Constraints:
0 <= n <= 2^31 - 1
```

## Observations

1. We need to insert a dot every 3 digits from right to left
2. Numbers with 3 or fewer digits don't need separators
3. We need to be careful not to add a separator at the beginning
4. The approach processes digits from right to left, then reverses the result

## Solution

1. Convert the integer to a list of characters for easy manipulation
2. Process digits from right to left by popping from the list
3. Keep a counter to track every 3 digits
4. Add a dot after every 3 digits
5. Remove trailing dot if it exists (happens when total digits is divisible by 3)
6. Reverse the result since we built it backwards

**Time Complexity:** O(n) where n is the number of digits
**Space Complexity:** O(n) for storing the string representations

# Tags
String Manipulation, Implementation

