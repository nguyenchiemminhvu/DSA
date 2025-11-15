## Problem

https://leetcode.com/problems/count-substrings-that-satisfy-k-constraint-i/description/

```
You are given a binary string s and an integer k.

A binary string satisfies the k-constraint if either of the following conditions holds:

The number of 0's in the string is at most k.
The number of 1's in the string is at most k.
Return an integer denoting the number of substrings of s that satisfy the k-constraint.

Example 1:

Input: s = "10101", k = 1

Output: 12

Explanation:

Every substring of s except the substrings "1010", "10101", and "0101" satisfies the k-constraint.

Example 2:

Input: s = "1010101", k = 2

Output: 25

Explanation:

Every substring of s except the substrings with a length greater than 5 satisfies the k-constraint.

Example 3:

Input: s = "11111", k = 1

Output: 15

Explanation:

All substrings of s satisfy the k-constraint.

Constraints:

1 <= s.length <= 50 
1 <= k <= s.length
s[i] is either '0' or '1'.
```

## Observations

1. **Problem Understanding**: We need to count all substrings of a binary string that satisfy the k-constraint, where a substring satisfies the constraint if it has at most k zeros OR at most k ones.

2. **Key Insight**: A substring is valid if either `count_of_0s ≤ k` OR `count_of_1s ≤ k`. This means we only need to break when BOTH counts exceed k.

3. **Brute Force Approach**: For each starting position, we can extend the substring character by character and count valid substrings until the constraint is violated.

4. **Constraint Analysis**: 
   - If a substring has more than k zeros AND more than k ones, it's invalid
   - Otherwise, it's valid (satisfies the k-constraint)

5. **Examples Analysis**:
   - `s = "10101", k = 1`: Substrings like "1010" have 2 zeros and 2 ones (both > 1), so invalid
   - `s = "11111", k = 1`: All substrings have 0 zeros, so all are valid

## Solution

1. **Outer Loop**: Iterate through each possible starting position `i`
2. **Inner Loop**: For each starting position, extend the substring by moving the end position `j`
3. **Count Tracking**: Maintain running counts of 0s and 1s in the current substring
4. **Constraint Check**: A substring is invalid only when both `c0 > k` AND `c1 > k`
5. **Early Termination**: Once constraint is violated, no longer substrings from this start position will be valid
6. **Result**: Count all valid substrings found

### Time & Space Complexity:
- **Time**: O(n²) in worst case, but often better due to early termination
- **Space**: O(1) - only using constant extra space

### Why Early Termination Works:
If substring s[i:j] violates the constraint (both counts > k), then any longer substring s[i:j+x] will also violate it since we're only adding more characters.

# Tags

Two Pointers, String, Sliding Window, Brute Force

