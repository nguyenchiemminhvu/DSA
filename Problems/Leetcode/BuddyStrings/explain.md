## Problem

https://leetcode.com/problems/buddy-strings/description/

```
Given two strings s and goal, return true if you can swap two letters in s so the result is equal to goal, otherwise, return false.

Swapping letters is defined as taking two indices i and j (0-indexed) such that i != j and swapping the characters at s[i] and s[j].

For example, swapping at indices 0 and 2 in "abcd" results in "cbad".

Example 1:

Input: s = "ab", goal = "ba"
Output: true
Explanation: You can swap s[0] = 'a' and s[1] = 'b' to get "ba", which is equal to goal.

Example 2:

Input: s = "ab", goal = "ab"
Output: false
Explanation: The only letters you can swap are s[0] = 'a' and s[1] = 'b', which results in "ba" != goal.

Example 3:

Input: s = "aa", goal = "aa"
Output: true
Explanation: You can swap s[0] = 'a' and s[1] = 'a' to get "aa", which is equal to goal.

Constraints:

1 <= s.length, goal.length <= 2 * 104
s and goal consist of lowercase letters.
```

## Observations

### Key Problem Understanding:
1. **Swap Requirement**: We must perform exactly **one swap** of two different positions in string `s` to make it equal to `goal`
2. **Edge Cases**: The strings must have the same length, otherwise impossible
3. **Two Main Scenarios**:
   - **Case 1**: Strings differ at exactly 2 positions - check if swapping fixes both differences
   - **Case 2**: Strings are identical - check if we can swap two identical characters (requires duplicates)

### Critical Insights:

#### **Scenario 1: Exactly 2 Differences**
- If `s` and `goal` differ at exactly 2 positions, we can potentially fix both with one swap
- For positions `i` and `j` where they differ:
  - `s[i] == goal[j]` AND `s[j] == goal[i]` must both be true
  - This ensures the swap fixes both mismatches simultaneously

#### **Scenario 2: No Differences (Identical Strings)**
- If `s == goal`, we still need to perform a swap
- We can only swap two positions if there are **duplicate characters**
- The condition `len(s) - len(set(s)) > 0` checks for duplicates
  - `len(set(s))` gives unique character count
  - If unique count < total length, there are duplicates

#### **Invalid Cases**:
- Different string lengths → impossible
- More than 2 differences → impossible with single swap
- Exactly 1 difference → impossible to fix with single swap
- Identical strings with no duplicates → no valid swap possible

### Algorithm Walkthrough:

**Example 1**: `s = "ab"`, `goal = "ba"`
- Length check: ✓ (both length 2)
- Differences at positions: [0, 1]
- Check: `s[0] == goal[1]` → 'a' == 'a' ✓
- Check: `s[1] == goal[0]` → 'b' == 'b' ✓
- Result: `True`

**Example 2**: `s = "ab"`, `goal = "ab"`
- Length check: ✓
- Differences: [] (no differences)
- Duplicate check: `len("ab") - len({"a", "b"}) = 2 - 2 = 0`
- No duplicates available for swapping
- Result: `False`

**Example 3**: `s = "aa"`, `goal = "aa"`
- Length check: ✓
- Differences: [] (no differences)  
- Duplicate check: `len("aa") - len({"a"}) = 2 - 1 = 1 > 0`
- Has duplicates, can swap positions 0 and 1
- Result: `True`

## Solution

1. **Efficient Difference Detection**: Single loop identifies all mismatched positions
2. **Duplicate Detection Trick**: `len(s) - len(set(s)) > 0` is a concise way to check for duplicates
3. **Cross-Validation**: For 2 differences, we verify that swapping actually resolves both mismatches
4. **Early Termination**: Length mismatch immediately returns False

## Tags

string, hash table, two pointers

