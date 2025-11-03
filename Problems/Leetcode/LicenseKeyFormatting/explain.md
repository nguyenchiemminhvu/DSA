## Problem

https://leetcode.com/problems/license-key-formatting/

```
You are given a license key represented as a string s that consists of only alphanumeric characters and dashes. The string is separated into n + 1 groups by n dashes. You are also given an integer k.

We want to reformat the string s such that each group contains exactly k characters, except for the first group, which could be shorter than k but still must contain at least one character. Furthermore, there must be a dash inserted between two groups, and you should convert all lowercase letters to uppercase.

Return the reformatted license key.

Example 1:

Input: s = "5F3Z-2e-9-w", k = 4
Output: "5F3Z-2E9W"
Explanation: The string s has been split into two parts, each part has 4 characters.
Note that the two extra dashes are not needed and can be removed.

Example 2:

Input: s = "2-5g-3-J", k = 2
Output: "2-5G-3J"
Explanation: The string s has been split into three parts, each part has 2 characters except the first part as it could be shorter as mentioned above.

Constraints:

1 <= s.length <= 105
s consists of English letters, digits, and dashes '-'.
1 <= k <= 104
```

## Observations

1. **Input Processing**: We need to remove all existing dashes and convert lowercase letters to uppercase.

2. **Group Formation**: After cleaning the string, we need to group characters from right to left (reverse direction) with exactly `k` characters per group, except possibly the first group.

3. **First Group Special Case**: The first group can have fewer than `k` characters (but at least 1), while all other groups must have exactly `k` characters.

4. **Direction Matters**: Since we want the first group to potentially be shorter, we should process from the end of the string backwards. This ensures that if there are remaining characters that don't form a complete group of size `k`, they'll naturally become the first group.

5. **Edge Cases**: 
   - If the cleaned string is empty, return empty string
   - If `k = 1`, each character becomes its own group
   - If the cleaned string length is ≤ `k`, return the cleaned string as is

## Solution

**Approach: Reverse Processing**

The key insight is to process the cleaned string from right to left, forming groups of size `k`, then reverse the final result.

**Algorithm:**
1. **Clean the input**: Remove all dashes and convert to uppercase
2. **Handle edge case**: If cleaned string is empty, return empty
3. **Group formation**: Starting from the end of the cleaned string, take `k` characters at a time to form groups
4. **Build result**: Join groups with dashes
5. **Handle remainder**: Any remaining characters (< k) form the first group

**Time Complexity**: O(n) where n is the length of the input string
- One pass to clean the string: O(n)
- One pass to form groups: O(n)
- Overall: O(n)

**Space Complexity**: O(n) for storing the cleaned string and result

**Implementation Strategy:**
```
1. Remove dashes and convert to uppercase: "5F3Z2E9W" from "5F3Z-2e-9-w"
2. Process from right to left with k=4:
   - Take last 4 chars: "2E9W"
   - Take next 4 chars: "5F3Z" 
3. Result: "5F3Z-2E9W"
```

**Alternative approach**: Build result string directly by iterating from right to left and inserting dashes at appropriate positions.

# Tags

- String Manipulation
- Two Pointers
- Simulation

