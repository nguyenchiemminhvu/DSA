## Problem

https://leetcode.com/problems/check-if-one-string-swap-can-make-strings-equal/description/

```
You are given two strings s1 and s2 of equal length. A string swap is an operation where you choose two indices in a string (not necessarily different) and swap the characters at these indices.

Return true if it is possible to make both strings equal by performing at most one string swap on exactly one of the strings. Otherwise, return false.

Example 1:

Input: s1 = "bank", s2 = "kanb"
Output: true
Explanation: For example, swap the first character with the last character of s2 to make "bank".

Example 2:

Input: s1 = "attack", s2 = "defend"
Output: false
Explanation: It is impossible to make them equal with one string swap.

Example 3:

Input: s1 = "kelb", s2 = "kelb"
Output: true
Explanation: The two strings are already equal, so no string swap operation is required.

Constraints:

1 <= s1.length, s2.length <= 100
s1.length == s2.length
s1 and s2 consist of only lowercase English letters.
```

## Observations

1. **Problem Understanding**: We need to determine if exactly one string swap in either `s1` or `s2` can make both strings equal.

2. **Key Insights**:
   - **Case 1: Strings are already equal** → Return `True` (no swap needed, which satisfies "at most one swap")
   - **Case 2: Strings differ at exactly 2 positions** → Check if swapping those 2 characters in one string makes them equal
   - **Case 3: Strings differ at 0, 1, or more than 2 positions** → Impossible with one swap

3. **Critical Logic**:
   - If `s1 == s2`, we can return `True` immediately since no swap is needed
   - We collect all positions where `s1[i] != s2[i]` into a `diff` array
   - For exactly 2 differences at positions `i` and `j`:
     - We can swap `s1[i]` with `s1[j]` to potentially make `s1 == s2`
     - This works only if `s1[i] == s2[j]` AND `s1[j] == s2[i]`
     - Alternatively, we could swap in `s2`, but the condition remains the same

4. **Edge Cases**:
   - **0 differences**: Strings already equal → `True`
   - **1 difference**: Impossible to fix with one swap → `False`
   - **3+ differences**: Impossible to fix with one swap → `False`

5. **Algorithm Efficiency**: 
   - Time: O(n) where n is string length
   - Space: O(k) where k is number of differences (at most n)

## Solution

The solution uses a **difference-counting approach** with the following strategy:

### Algorithm:
1. **Early Exit**: If `s1 == s2`, return `True` immediately
2. **Find Differences**: Iterate through both strings and collect indices where characters differ
3. **Validate Difference Count**: 
   - If exactly 2 differences → check if characters can be swapped to match
   - Otherwise → return `False`
4. **Swap Validation**: For positions `i` and `j` where strings differ:
   - Check if `s1[i] == s2[j]` AND `s1[j] == s2[i]`
   - This ensures swapping `s1[i]` with `s1[j]` makes both positions match

### Example Walkthrough:

**Example 1**: `s1 = "bank"`, `s2 = "kanb"`
- Differences at positions: [0, 3] (s1[0]='b'≠s2[0]='k', s1[3]='k'≠s2[3]='b')
- Check: `s1[0] == s2[3]` → 'b' == 'b' ✓
- Check: `s1[3] == s2[0]` → 'k' == 'k' ✓
- Result: `True` (swap s1[0] with s1[3] → "kank" → wait, that's not right...)

Actually, let me reconsider: if we swap s2[0] with s2[3]: "kanb" → "bank" ✓

**Example 2**: `s1 = "attack"`, `s2 = "defend"`
- Multiple differences at positions: [0,1,2,3,4,5]
- Since len(diff) = 6 ≠ 2, return `False`

**Example 3**: `s1 = "kelb"`, `s2 = "kelb"`
- No differences, strings already equal
- Return `True`

### Time Complexity: O(n)
- Single pass through both strings to find differences
- Constant time validation of swap possibility

### Space Complexity: O(k)
- Where k is the number of differences (at most n)
- In practice, often O(1) since we expect few differences

### Why This Works:
- A single character swap can fix at most 2 position mismatches
- If there are exactly 2 mismatches, they must be "complementary" (swappable)
- The condition `s1[diff[0]] == s2[diff[1]] and s1[diff[1]] == s2[diff[0]]` ensures the swap creates a perfect match

# Tags

string, array, two-pointers, simulation

