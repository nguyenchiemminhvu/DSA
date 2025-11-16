## Problem

https://leetcode.com/problems/number-of-substrings-with-only-1s/description/

```
Given a binary string s, return the number of substrings with all characters 1's. Since the answer may be too large, return it modulo 109 + 7.

Example 1:

Input: s = "0110111"
Output: 9
Explanation: There are 9 substring in total with only 1's characters.
"1" -> 5 times.
"11" -> 3 times.
"111" -> 1 time.

Example 2:

Input: s = "101"
Output: 2
Explanation: Substring "1" is shown 2 times in s.

Example 3:

Input: s = "111111"
Output: 21
Explanation: Each substring contains only 1's characters.

Constraints:

1 <= s.length <= 105
s[i] is either '0' or '1'.
```

## Observations

1. **Key Insight**: For a sequence of consecutive '1's of length `n`, the number of possible substrings containing only '1's is `n * (n + 1) / 2`.
   - This is because we can choose any starting position (n choices) and any ending position from that start to the end of the sequence.
   - For example, "111" (length 3) gives us: "1", "1", "1", "11", "11", "111" = 6 substrings = 3*(3+1)/2

2. **Pattern Recognition**: We need to:
   - Find all groups of consecutive '1's
   - For each group of length `count`, add `count * (count + 1) / 2` to our result
   - Handle the modulo operation as the result can be large

3. **Edge Cases**:
   - String with only '0's → result = 0
   - String with only '1's → result = n*(n+1)/2 where n is the length
   - Mixed string → sum of contributions from each group of consecutive '1's

4. **Optimization**: Adding '0' at the end ensures the last group of '1's is processed without needing special handling.

## Solution

### Approach: Group Counting with Mathematical Formula

**Algorithm:**
1. **Setup**: Add '0' to the end of string to ensure last group is processed
2. **Iterate**: Go through each character in the string
3. **Count**: Keep track of consecutive '1's in current group
4. **Calculate**: When we hit '0', calculate substrings for current group using `count * (count + 1) / 2`
5. **Reset**: Reset counter for next group
6. **Accumulate**: Add result to total with modulo operation

**Step-by-step walkthrough with example "0110111":**

```
Original: "0110111"
Modified: "01101110" (added '0' at end)

i=0: c='0', count=0 → res += 0*(0+1)/2 = 0, reset count=0
i=1: c='1', count=1
i=2: c='1', count=2  
i=3: c='0', count=2 → res += 2*(2+1)/2 = 3, reset count=0
i=4: c='1', count=1
i=5: c='1', count=2
i=6: c='1', count=3
i=7: c='0', count=3 → res += 3*(3+1)/2 = 6, reset count=0

Final result: 0 + 3 + 6 = 9
```

**Why this works:**
- Each group of consecutive '1's contributes `n*(n+1)/2` substrings
- The added '0' ensures we process the final group without special handling
- Modulo operation prevents integer overflow for large results

**Time Complexity:** O(n) - single pass through the string
**Space Complexity:** O(1) - only using constant extra space

**Key Implementation Details:**
- `s += '0'`: Elegant way to handle the last group
- `count * (count + 1) // 2`: Mathematical formula for triangular numbers
- `% int(1e9 + 7)`: Modulo operation as required by problem constraints

# Tags

- **String**: Working with binary string manipulation
- **Math**: Using triangular number formula n*(n+1)/2
- **Greedy**: Processing groups of consecutive characters
- **Modular Arithmetic**: Handling large numbers with modulo operation
- **Two Pointers/Sliding Window**: Implicit grouping technique
- **Easy-Medium Difficulty**
- **Time Complexity**: O(n)
- **Space Complexity**: O(1)

