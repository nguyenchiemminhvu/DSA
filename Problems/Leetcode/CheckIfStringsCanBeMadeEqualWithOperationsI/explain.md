## Problem

https://leetcode.com/problems/check-if-strings-can-be-made-equal-with-operations-i/description/

```
You are given two strings s1 and s2, both of length 4, consisting of lowercase English letters.

You can apply the following operation on any of the two strings any number of times:

- Choose any two indices i and j such that j - i = 2, then swap the two characters at those indices in the string.

Return true if you can make the strings s1 and s2 equal, and false otherwise.

Example 1:
Input: s1 = "abcd", s2 = "cdab"
Output: true
Explanation: We can do the following operations on s1:
- Choose the indices i = 0, j = 2. The resulting string is s1 = "cbad".
- Choose the indices i = 1, j = 3. The resulting string is s1 = "cdab" = s2.

Example 2:
Input: s1 = "abcd", s2 = "dacb"
Output: false
Explanation: It is not possible to make the two strings equal.

Constraints:
- s1.length == s2.length == 4
- s1 and s2 consist only of lowercase English letters.
```

## Observations

1. **Operation Constraint**: We can only swap characters that are exactly 2 positions apart (j - i = 2).

2. **Index Pairs**: For a string of length 4 (indices 0, 1, 2, 3), the valid swap pairs are:
   - Indices 0 and 2
   - Indices 1 and 3

3. **Independence of Positions**: Characters at positions 0 and 2 can only be swapped with each other. Similarly, characters at positions 1 and 3 can only be swapped with each other. These two groups are **independent** and never interact.

4. **Key Insight**: Since we can swap positions (0, 2) and positions (1, 3) independently:
   - Positions 0 and 2 form one group
   - Positions 1 and 3 form another group
   - Within each group, we can arrange the characters in any order through repeated swaps

5. **Equivalence Condition**: Two strings can be made equal if and only if:
   - The set of characters at positions {0, 2} in s1 equals the set at positions {0, 2} in s2
   - The set of characters at positions {1, 3} in s1 equals the set at positions {1, 3} in s2

## Solution

The solution leverages the observation that positions form independent groups:

1. **Extract Group 1** (positions 0 and 2):
   - From s1: `[s1[0], s1[2]]`
   - From s2: `[s2[0], s2[2]]`

2. **Extract Group 2** (positions 1 and 3):
   - From s1: `[s1[1], s1[3]]`
   - From s2: `[s2[1], s2[3]]`

3. **Sort and Compare**: Since we can rearrange characters within each group in any order, we sort both groups and compare:
   - If `sorted(s1 group 1) == sorted(s2 group 1)` AND
   - `sorted(s1 group 2) == sorted(s2 group 2)`
   - Then the strings can be made equal

### Example Walkthrough

**Example 1**: s1 = "abcd", s2 = "cdab"
- Group 1: sorted(['a', 'c']) = ['a', 'c'], sorted(['c', 'a']) = ['a', 'c'] ✓
- Group 2: sorted(['b', 'd']) = ['b', 'd'], sorted(['d', 'b']) = ['b', 'd'] ✓
- Result: true

**Example 2**: s1 = "abcd", s2 = "dacb"
- Group 1: sorted(['a', 'c']) = ['a', 'c'], sorted(['d', 'c']) = ['c', 'd'] ✗
- Group 2: sorted(['b', 'd']) = ['b', 'd'], sorted(['a', 'b']) = ['a', 'b'] ✗
- Result: false

### Complexity Analysis

- **Time Complexity**: O(1)
  - We're only sorting arrays of size 2, which is constant time
  - All operations are on fixed-size data (length 4)

- **Space Complexity**: O(1)
  - We only create a few small arrays of constant size

# Tags
#string #sorting #array #greedy

