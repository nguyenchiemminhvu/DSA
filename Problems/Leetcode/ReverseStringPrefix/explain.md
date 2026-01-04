## Problem

https://leetcode.com/problems/reverse-string-prefix/description/

Given a string `s` and an integer `k`, reverse the first `k` characters of `s` and return the resulting string.

**Constraints:**
- `1 <= s.length <= 100`
- `s` consists of lowercase English letters
- `1 <= k <= s.length`

**Examples:**
- Input: `s = "abcd"`, `k = 2` → Output: `"bacd"`
- Input: `s = "xyz"`, `k = 3` → Output: `"zyx"`
- Input: `s = "hey"`, `k = 1` → Output: `"hey"`

## Observations

1. **In-place reversal**: Since we only need to reverse the first `k` characters, we can use a two-pointer approach focusing on just that substring.

2. **String immutability in Python**: Strings are immutable in Python, so we convert the string to a list to perform in-place swaps.

3. **Two-pointer technique**: Using left and right pointers starting at positions `0` and `k-1` respectively, we swap elements and move the pointers toward each other until they meet.

4. **Time complexity**: O(k) for the reversal + O(n) for list conversion and string join = O(n) overall.

5. **Space complexity**: O(n) due to the list conversion (Python requirement for mutability).

## Solution

```python
class Solution:
    def reversePrefix(self, s: str, k: int) -> str:
        s = list(s)
        left, right = 0, k - 1
        while left <= right:
            s[left], s[right] = s[right], s[left]
            left += 1
            right -= 1
        return "".join(s)
```

**Algorithm Explanation:**

1. **Convert to list**: `s = list(s)` converts the string to a mutable list of characters.

2. **Initialize pointers**: 
   - `left = 0` points to the start of the substring to reverse
   - `right = k - 1` points to the end of the substring (k-th character, 0-indexed)

3. **Swap loop**: While `left <= right`:
   - Swap characters at positions `left` and `right`
   - Move `left` forward (`left += 1`)
   - Move `right` backward (`right -= 1`)
   - Continue until pointers meet or cross

4. **Convert back**: `"".join(s)` converts the list back to a string.

**Example Walkthrough** (`s = "abcd"`, `k = 2`):
```
Initial:  ['a', 'b', 'c', 'd']
          left=0, right=1

Step 1:   Swap s[0] and s[1]
          ['b', 'a', 'c', 'd']
          left=1, right=0

Loop ends (left > right)
Result:   "bacd"
```

**Complexity Analysis:**
- **Time**: O(n) where n is the length of string (O(n) for conversion + O(k) for reversal + O(n) for join)
- **Space**: O(n) for the list representation

# Tags

`two-pointers` `string` `array` `in-place-algorithm`

