## Problem

https://leetcode.com/problems/largest-even-number/description/

You are given a string `s` consisting only of the characters '1' and '2'.

You may delete any number of characters from `s` without changing the order of the remaining characters.

Return the largest possible resultant string that represents an even integer. If there is no such string, return the empty string `""`.

**Example 1:**
- Input: `s = "1112"`
- Output: `"1112"`
- Explanation: The string already represents the largest possible even number, so no deletions are needed.

**Example 2:**
- Input: `s = "221"`
- Output: `"22"`
- Explanation: Deleting '1' results in the largest possible even number which is equal to 22.

**Example 3:**
- Input: `s = "1"`
- Output: `""`
- Explanation: There is no way to get an even number.

**Constraints:**
- `1 <= s.length <= 100`
- `s` consists only of the characters '1' and '2'.

## Observations

1. **Even Number Requirement**: A number is even if and only if its last digit is even. Since `s` contains only '1' and '2', the number must end with '2' to be even.

2. **Maximize the Result**: To get the largest possible even number, we want to keep as many digits as possible while ensuring the last digit is '2'.

3. **Deletion Strategy**: We should only delete characters from the end, not from the middle or beginning, because:
   - Deleting from the beginning or middle would make the number smaller
   - We only need to ensure the last digit is even

4. **Optimal Approach**: Remove all trailing '1's (odd digits) from the end until we encounter a '2' (even digit) or the string becomes empty.

## Solution

```python
class Solution:
    def largestEven(self, s: str) -> str:
        arr = list(map(int, list(s)))
        while arr and arr[-1] & 1:
            arr.pop()
        return "".join(list(map(str, arr)))
```

**Algorithm Explanation:**

1. **Convert to Integer List**: `arr = list(map(int, list(s)))`
   - Convert the string to a list of integers for easier manipulation

2. **Remove Trailing Odd Digits**: `while arr and arr[-1] & 1:`
   - Check if the array is non-empty (`arr`) and the last element is odd (`arr[-1] & 1`)
   - The bitwise AND operation `& 1` checks if a number is odd (returns 1 for odd, 0 for even)
   - Keep removing the last element with `arr.pop()` until we find an even digit or array is empty

3. **Convert Back to String**: `return "".join(list(map(str, arr)))`
   - Convert the integer list back to a string and return it

**Time Complexity**: $O(n)$ where $n$ is the length of the string
- We iterate through the string once to convert it
- In the worst case, we pop all elements from the end

**Space Complexity**: $O(n)$ for storing the array

**Why This Works:**
- Since we can only delete characters (not reorder), the relative order is preserved
- To maximize the number, we keep as many digits as possible
- To make it even, we only need the last digit to be '2'
- By removing trailing '1's, we find the rightmost '2' which gives us the largest even number possible

# Tags

