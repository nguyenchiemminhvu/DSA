## Problem

https://leetcode.com/problems/check-if-number-has-equal-digit-count-and-digit-value/description/

```
You are given a 0-indexed string num of length n consisting of digits.

Return true if for every index i in the range 0 <= i < n, the digit i occurs num[i] times in num, otherwise return false.

Example 1:

Input: num = "1210"
Output: true
Explanation:
num[0] = '1'. The digit 0 occurs once in num.
num[1] = '2'. The digit 1 occurs twice in num.
num[2] = '1'. The digit 2 occurs once in num.
num[3] = '0'. The digit 3 occurs zero times in num.
The condition holds true for every index in "1210", so return true.

Example 2:

Input: num = "030"
Output: false
Explanation:
num[0] = '0'. The digit 0 should occur zero times, but actually occurs twice in num.
num[1] = '3'. The digit 1 should occur three times, but actually occurs zero times in num.
num[2] = '0'. The digit 2 occurs zero times in num.
The indices 0 and 1 both violate the condition, so return false.

Constraints:

n == num.length
1 <= n <= 10
num consists of digits.
```

## Observations

1. **Problem Understanding**: For each index `i` in the string `num`, the digit at position `i` should equal the count of digit `i` in the entire string.

2. **Key Insight**: We need to count the frequency of each digit (0-9) and compare it with what each position claims it should be.

3. **Edge Cases**: 
   - The string length is at most 10, so we only need to check digits 0 through (length-1)
   - If a digit doesn't appear in the string, its count is 0

4. **Approach**: Use a frequency counter to count occurrences of each digit, then verify the condition for each position.

## Solution

1. **Convert to integers**: `arr = [int(val) for val in list(num)]` converts each character to an integer for easier manipulation.

2. **Count frequencies**: `Counter(arr)` creates a dictionary-like object where keys are digits and values are their frequencies. For missing keys, Counter returns 0.

3. **Validation loop**: For each position `i`:
   - `f[i]` gives the actual count of digit `i` in the string
   - `arr[i]` gives what the digit at position `i` claims should be the count of digit `i`
   - If these don't match, return `False`

**Time Complexity**: O(n) where n is the length of the string (at most 10)
**Space Complexity**: O(1) since we only store counts for digits 0-9

**Example Walkthrough** with `num = "1210"`:
- `arr = [1, 2, 1, 0]`
- `f = Counter({1: 2, 2: 1, 0: 1})` (digit 1 appears twice, digit 2 once, digit 0 once, digit 3 zero times)
- Check each position:
  - `i=0`: `f[0] = 1`, `arr[0] = 1` ✓
  - `i=1`: `f[1] = 2`, `arr[1] = 2` ✓  
  - `i=2`: `f[2] = 1`, `arr[2] = 1` ✓
  - `i=3`: `f[3] = 0`, `arr[3] = 0` ✓
- All conditions satisfied, return `True`

# Tags

Array, Hash Table, Counting, String

