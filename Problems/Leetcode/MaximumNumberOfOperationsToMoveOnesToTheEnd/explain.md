## Problem

https://leetcode.com/problems/maximum-number-of-operations-to-move-ones-to-the-end/description/

```
You are given a binary string s.

You can perform the following operation on the string any number of times:

Choose any index i from the string where i + 1 < s.length such that s[i] == '1' and s[i + 1] == '0'.
Move the character s[i] to the right until it reaches the end of the string or another '1'. For example, for s = "010010", if we choose i = 1, the resulting string will be s = "000110".
Return the maximum number of operations that you can perform.

Example 1:

Input: s = "1001101"

Output: 4

Explanation:

We can perform the following operations:

Choose index i = 0. The resulting string is s = "0011101".
Choose index i = 4. The resulting string is s = "0011011".
Choose index i = 3. The resulting string is s = "0010111".
Choose index i = 2. The resulting string is s = "0001111".

Example 2:

Input: s = "00111"

Output: 0

Constraints:

1 <= s.length <= 105
s[i] is either '0' or '1'.
```

## Observations

1. **Operation Definition**: We can move a '1' to the right when it's followed by '0's, until it reaches the end or another '1'.

2. **Key Insight**: Each '1' can potentially contribute to multiple operations:
   - When we encounter a '1' followed by some '0's, that '1' can be moved through all those '0's
   - The number of operations for each '1' equals the number of '0's it can pass through

3. **Pattern Recognition**: 
   - When we see a pattern like "1000", the '1' can be moved 3 times (through each '0')
   - When we see "11000", both '1's can be moved through the '0's, contributing 2×3=6 operations
   - The key is to count how many '1's we've seen before encountering '0's

4. **Greedy Approach**: We want to maximize operations, so we should move '1's as much as possible to the right.

## Solution

The algorithm works by tracking:
- `count_1`: Number of '1's encountered so far
- `count_0`: Number of consecutive '0's in current segment  
- `res`: Total number of operations

**Key Steps**:

1. **Add sentinel '1'**: `s += '1'` ensures we process the last segment of '0's (if any)

2. **Process each character**:
   - **If current char is '1'**:
     - If there were '0's before this '1' (`count_0 > 0`), it means we can move all previously seen '1's through these '0's
     - Add `count_1` to result (each previous '1' contributes one operation through this segment of '0's)
     - Reset `count_0 = 0` (start counting new segment)
     - Increment `count_1` (add current '1' to our count)
   - **If current char is '0'**:
     - Increment `count_0` (extend current segment of '0's)

**Example walkthrough** with `s = "1001101"`:
- Original: `"1001101"` → After adding sentinel: `"10011011"`
- `i=0, s[0]='1'`: count_1=1, count_0=0, res=0
- `i=1, s[1]='0'`: count_1=1, count_0=1, res=0  
- `i=2, s[2]='0'`: count_1=1, count_0=2, res=0
- `i=3, s[3]='1'`: count_0>0, so res += count_1 → res=1, count_1=2, count_0=0
- `i=4, s[4]='1'`: count_0=0, so count_1=3, res=1
- `i=5, s[5]='0'`: count_1=3, count_0=1, res=1
- `i=6, s[6]='1'`: count_0>0, so res += count_1 → res=4, count_1=4, count_0=0
- `i=7, s[7]='1'`: count_0=0, so count_1=5, res=4

**Why it works**: Each time we encounter a '1' after a segment of '0's, all the '1's we've seen before can each be moved one step closer to the end through that segment of '0's.

**Time Complexity**: O(n) - single pass through string  
**Space Complexity**: O(1) - only using constant extra variables

# Tags

- String
- Greedy  
- Simulation
- Pattern Recognition

