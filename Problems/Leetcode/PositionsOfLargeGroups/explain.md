## Problem

https://leetcode.com/problems/positions-of-large-groups/description/

```
In a string s of lowercase letters, these letters form consecutive groups of the same character.

For example, a string like s = "abbxxxxzyy" has the groups "a", "bb", "xxxx", "z", and "yy".

A group is identified by an interval [start, end], where start and end denote the start and end indices (inclusive) of the group. In the above example, "xxxx" has the interval [3,6].

A group is considered large if it has 3 or more characters.

Return the intervals of every large group sorted in increasing order by start index.

Example 1:
Input: s = "abbxxxxzzy"
Output: [[3,6]]
Explanation: "xxxx" is the only large group with start index 3 and end index 6.

Example 2:
Input: s = "abc"
Output: []
Explanation: We have groups "a", "b", and "c", none of which are large groups.

Example 3:
Input: s = "abcdddeeeeaabbbcd"
Output: [[3,5],[6,9],[12,14]]
Explanation: The large groups are "ddd", "eeee", and "bbb".

Constraints:
- 1 <= s.length <= 1000
- s contains lowercase English letters only.
```

## Observations

1. **Group Definition**: A group consists of consecutive identical characters in the string.
2. **Large Group Criteria**: A group is considered "large" if it contains 3 or more characters.
3. **Two-Pointer Approach**: We can use two pointers to identify the start and end of each group.
4. **Sequential Processing**: Since we need results sorted by start index, we can process the string from left to right.
5. **Edge Cases**: Single characters and pairs of characters should be skipped as they don't form large groups.

## Solution

1. **Initialize**: Start with two pointers `l` and `r` both at position 0, and an empty result list.

2. **Expand Group**: For each position, expand the right pointer `r` while the next character matches the character at the left pointer `s[l]`.

3. **Check Group Size**: After finding the end of a group, check if the group size (`r - l + 1`) is at least 3.

4. **Record Large Groups**: If the group is large enough, add the interval `[l, r]` to the result.

5. **Move to Next Group**: Move both pointers to start checking the next group (`r += 1`, `l = r`).

**Time Complexity**: O(n) - Each character is visited at most twice (once by each pointer).

**Space Complexity**: O(1) - Only using constant extra space (excluding the output array).

**Key Insight**: The inner while loop extends `r` to find the end of the current group, then we check if this group meets the "large" criteria before moving to the next group.

# Tags

- Two Pointers
- String Processing
- Array
- Easy Difficulty

