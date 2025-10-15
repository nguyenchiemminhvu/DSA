## Problem

https://leetcode.com/problems/minimum-moves-to-convert-string/description/

```
You are given a string s consisting of n characters which are either 'X' or 'O'.

A move is defined as selecting three consecutive characters of s and converting them to 'O'. Note that if a move is applied to the character 'O', it will stay the same.

Return the minimum number of moves required so that all the characters of s are converted to 'O'.

Example 1:

Input: s = "XXX"
Output: 1
Explanation: XXX -> OOO
We select all the 3 characters and convert them in one move.

Example 2:

Input: s = "XXOX"
Output: 2
Explanation: XXOX -> OOOX -> OOOO
We select the first 3 characters in the first move, and convert them to 'O'.
Then we select the last 3 characters and convert them so that the final string contains all 'O's.

Example 3:

Input: s = "OOOO"
Output: 0
Explanation: There are no 'X's in s to convert.

Constraints:

3 <= s.length <= 1000
s[i] is either 'X' or 'O'.
```

## Observations

1. **Greedy Approach**: Since each move converts 3 consecutive characters to 'O', we want to maximize coverage with each move. When we encounter an 'X', we should immediately use a move to cover it and the next 2 positions.

2. **Skip Strategy**: After making a move at position `i`, the next 2 positions (i+1 and i+2) are already covered by this move. Therefore, we can skip ahead by 2 positions (i += 2), then continue scanning.

3. **No Overlap Needed**: We never need overlapping moves. The greedy strategy of always converting the leftmost 'X' and skipping the next 2 positions gives the optimal result.

4. **Time Complexity**: O(n) - single pass through the string
5. **Space Complexity**: O(1) - only using a counter and index variable

## Solution

- We scan the string from left to right
- When we find an 'X':
  - Increment the move counter (this move covers positions i, i+1, i+2)
  - Skip ahead 2 positions (`i += 2`) since they're now covered
- When we find an 'O', just move to the next position
- The `i += 1` at the end ensures we always advance through the string

**Example walkthrough** (`s = "XXOX"`):
```
i=0: s[0]='X' → count=1, i+=2 (now i=2), then i+=1 (now i=3)
     Move covers: XXO (positions 0,1,2)
i=3: s[3]='X' → count=2, i+=2 (now i=5), then i+=1 (now i=6)
     Move covers: OXX (positions 3,4,5 - but only position 3 exists in "XXOX")
i=6: i >= n, exit
Result: 2 moves
```

**Why this is optimal:**
- Greedy choice: Always convert the leftmost 'X' first
- Each move can cover up to 3 characters, and we maximize this by not re-covering already processed positions
- No better strategy exists because we must cover every 'X', and covering 3 at a time is the maximum allowed

## Tags

array, string, greedy