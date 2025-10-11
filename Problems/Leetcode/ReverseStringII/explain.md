## Problem

https://leetcode.com/problems/reverse-string-ii/

```
Given a string s and an integer k, reverse the first k characters for every 2k characters counting from the start of the string.

If there are fewer than k characters left, reverse all of them. If there are less than 2k but greater than or equal to k characters, then reverse the first k characters and leave the other as original.

Example 1:

Input: s = "abcdefg", k = 2
Output: "bacdfeg"

Example 2:

Input: s = "abcd", k = 2
Output: "bacd"

Constraints:

1 <= s.length <= 104
s consists of only lowercase English letters.
1 <= k <= 104
```

## Observations

1. **Pattern Recognition**: We need to reverse characters in chunks of k, but only for every alternate chunk of k characters
   - For every 2k characters: reverse first k, leave next k unchanged
   - This creates a pattern: reverse, skip, reverse, skip...

2. **Edge Cases**: 
   - If remaining characters < k: reverse all remaining
   - If remaining characters >= k but < 2k: reverse only first k, leave rest unchanged

3. **Algorithm Strategy**: 
   - Iterate through string in steps of k (not 2k)
   - Use a boolean flag to track whether current k-chunk should be reversed
   - Toggle the flag each iteration to create alternating pattern

4. **Two-Pointer Technique**: 
   - When reversing a chunk, use left and right pointers
   - Swap characters while moving pointers toward center

## Solution

**Approach**: Iterate through string in k-sized chunks with alternating reverse pattern

**Algorithm**:
1. Convert string to list for in-place modification
2. Use boolean flag `r` to track reverse state (starts False)
3. Loop through string in steps of k:
   - Toggle reverse flag each iteration
   - If flag is False (don't reverse), skip current chunk
   - If flag is True (reverse), reverse current k characters using two pointers
4. Convert list back to string

**Key Insight**: The boolean flag `r` creates the alternating pattern:
- Initially False → skip first k chars (indices 0 to k-1)
- Then True → reverse next k chars (indices k to 2k-1)  
- Then False → skip next k chars (indices 2k to 3k-1)
- And so on...

**Time Complexity**: O(n) where n is length of string
**Space Complexity**: O(n) for converting string to list

**Example Walkthrough** (s = "abcdefg", k = 2):
- i=0, r=True: reverse "ab" → "ba"
- i=2, r=False: skip "cd" → "cd" 
- i=4, r=True: reverse "ef" → "fe"
- i=6, r=False: skip "g" → "g"
- Result: "bacdfeg"

## Tags

string, two pointers