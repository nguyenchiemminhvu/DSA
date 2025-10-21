## Problem

https://leetcode.com/problems/lexicographically-smallest-palindrome/

```
You are given a string s consisting of lowercase English letters, and you are allowed to perform operations on it. In one operation, you can replace a character in s with another lowercase English letter.

Your task is to make s a palindrome with the minimum number of operations possible. If there are multiple palindromes that can be made using the minimum number of operations, make the lexicographically smallest one.

A string a is lexicographically smaller than a string b (of the same length) if in the first position where a and b differ, string a has a letter that appears earlier in the alphabet than the corresponding letter in b.

Return the resulting palindrome string.

Example 1:

Input: s = "egcfe"
Output: "efcfe"
Explanation: The minimum number of operations to make "egcfe" a palindrome is 1, and the lexicographically smallest palindrome string we can get by modifying one character is "efcfe", by changing 'g'.

Example 2:

Input: s = "abcd"
Output: "abba"
Explanation: The minimum number of operations to make "abcd" a palindrome is 2, and the lexicographically smallest palindrome string we can get by modifying two characters is "abba".

Example 3:

Input: s = "seven"
Output: "neven"
Explanation: The minimum number of operations to make "seven" a palindrome is 1, and the lexicographically smallest palindrome string we can get by modifying one character is "neven".

Constraints:

1 <= s.length <= 1000
s consists of only lowercase English letters.
```

## Observations

1. **Palindrome Property**: For a string to be a palindrome, characters at symmetric positions must be equal: `s[i] == s[n-1-i]`

2. **Minimum Operations**: To minimize operations, we only change characters when `s[left] != s[right]`. Each mismatch requires exactly one operation.

3. **Lexicographically Smallest**: When we have a mismatch between `s[left]` and `s[right]`, we should choose the smaller character (earlier in alphabet) for both positions to get the lexicographically smallest result.

4. **Two Pointers Approach**: We can use two pointers starting from the center and expanding outward, or starting from ends and moving inward.

5. **Center Handling**: 
   - For odd-length strings: middle character doesn't need a pair
   - For even-length strings: all characters need pairs

## Solution

**Algorithm**: Two-pointers from center expanding outward

**Step-by-step breakdown**:

1. **Initialize pointers**:
   - `left = right = n // 2` (start from center)
   - For even length: move `left` one position left (`left -= 1`)
   - This ensures we start from the center pair

2. **Expand outward**:
   - Compare characters at `left` and `right` positions
   - If they're different, replace both with the smaller character: `min(s[left], s[right])`
   - Move pointers outward: `left -= 1`, `right += 1`

3. **Continue until boundaries**: Stop when `left < 0` or `right >= n`

**Why this works**:
- **Correctness**: We ensure every pair of symmetric positions has the same character
- **Minimum operations**: We only change characters when necessary (mismatch)
- **Lexicographically smallest**: Always choosing the smaller character ensures the result is lexicographically smallest

**Time Complexity**: O(n) - visit each character at most once
**Space Complexity**: O(n) - convert string to list for mutability

**Example walkthrough** (`s = "egcfe"`):
```
Initial: e g c f e
Indices: 0 1 2 3 4
         ↑     ↑
       left=2, right=2 (center)

Step 1: left=1, right=3
- s[1]='g', s[3]='f' → different
- Choose min('g','f') = 'f'
- Result: e f c f e

Step 2: left=0, right=4  
- s[0]='e', s[4]='e' → same
- No change needed
- Final: e f c f e
```

## Tags

array, string, greedy