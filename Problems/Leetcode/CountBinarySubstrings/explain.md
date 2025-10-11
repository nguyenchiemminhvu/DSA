## Problem

https://leetcode.com/problems/count-binary-substrings/description/

```
Given a binary string s, return the number of non-empty substrings that have the same number of 0's and 1's, and all the 0's and all the 1's in these substrings are grouped consecutively.

Substrings that occur multiple times are counted the number of times they occur.

Example 1:

Input: s = "00110011"
Output: 6
Explanation: There are 6 substrings that have equal number of consecutive 1's and 0's: "0011", "01", "1100", "10", "0011", and "01".
Notice that some of these substrings repeat and are counted the number of times they occur.
Also, "00110011" is not a valid substring because all the 0's (and 1's) are not grouped together.

Example 2:

Input: s = "10101"
Output: 4
Explanation: There are 4 substrings: "10", "01", "10", "01" that have equal number of consecutive 1's and 0's.

Constraints:

1 <= s.length <= 105
s[i] is either '0' or '1'.
```

## Observations

1. **Pattern Recognition**: Valid substrings must have consecutive 0's followed by consecutive 1's (or vice versa) with equal counts.

2. **Key Insight**: For any two adjacent groups of different characters, the number of valid substrings we can form is the minimum of their lengths.
   - Example: "000011" → groups are [0,0,0,0] and [1,1] → min(4,2) = 2 valid substrings: "0011" and "01"

3. **Group-by-Group Processing**: We can process the string by identifying consecutive character groups and count valid substrings between adjacent groups.

4. **Edge Cases**: 
   - Single character strings → 0 valid substrings
   - Alternating characters "0101" → each adjacent pair forms 1 valid substring

5. **Time Complexity**: O(n) - single pass through the string
   **Space Complexity**: O(1) - only using a few variables

## Solution

1. **Sentinel Addition**: Add '2' to the end to ensure the last group is processed when the loop encounters a different character.

2. **Group Tracking**: Use `counter` array to track consecutive character counts:
   - `counter[0]`: count of consecutive '0's in current group
   - `counter[1]`: count of consecutive '1's in current group
   - `counter[2]`: for sentinel character '2'

3. **Group Transition**: When we encounter a different character (`val != prev`):
   - Calculate valid substrings from previous two groups: `min(counter[0], counter[1])`
   - Reset the counter for the new character group
   - Update `prev` to the new character

4. **Count Accumulation**: Always increment the counter for the current character.

**Example Trace** (s = "00110011"):
- Groups: "00", "11", "00", "11"
- Transitions: 
  - "00" → "11": min(2,0) = 0, then min(2,2) = 2 → substrings: "01", "0011"
  - "11" → "00": min(0,2) = 0, then min(2,2) = 2 → substrings: "10", "1100"  
  - "00" → "11": min(2,0) = 0, then min(2,2) = 2 → substrings: "01", "0011"
- Total: 6 valid substrings

## Tags

string