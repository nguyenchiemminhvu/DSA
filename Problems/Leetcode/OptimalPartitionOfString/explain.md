## Problem

https://leetcode.com/problems/optimal-partition-of-string/description/

```
Given a string s, partition the string into one or more substrings such that the characters in each substring are unique. That is, no letter appears in a single substring more than once.

Return the minimum number of substrings in such a partition.

Note that each character should belong to exactly one substring in a partition.

Example 1:

Input: s = "abacaba"
Output: 4
Explanation:
Two possible partitions are ("a","ba","cab","a") and ("ab","a","ca","ba").
It can be shown that 4 is the minimum number of substrings needed.

Example 2:

Input: s = "ssssss"
Output: 6
Explanation:
The only valid partition is ("s","s","s","s","s","s").

Constraints:

1 <= s.length <= 105
s consists of only English lowercase letters.
```

## Observations

1. **Greedy Approach**: To minimize the number of substrings, we should make each substring as long as possible while maintaining unique characters.

2. **When to Partition**: We need to start a new substring whenever we encounter a character that already exists in the current substring.

3. **Set for Tracking**: Using a set to keep track of characters in the current substring allows O(1) lookup time to check for duplicates.

4. **Edge Case Handling**: The solution adds the last character again to ensure the final substring is counted properly.

## Solution

1. **Initialization**: 
   - Add the last character of `s` to itself to ensure the final substring is counted
   - Use a set `check` to track characters in the current substring
   - Initialize `count` to track the number of substrings

2. **Main Logic**:
   - For each character `c` in the string:
     - If `c` is already in the current substring (exists in `check`), we've found a duplicate
     - Increment `count` (start a new substring) and clear the set
     - Add the current character to the set

3. **Edge Case**: The trick `s += s[-1]` ensures that when we reach the end of the original string, we trigger one final partition count for the last substring.

**Example Walkthrough** (`s = "abacaba"`):
- Original: "abacaba" → Modified: "abacabaa"
- Process: a(add) → b(add) → a(duplicate! count=1, clear, add a) → c(add) → a(duplicate! count=2, clear, add a) → b(add) → a(duplicate! count=3, clear, add a) → a(duplicate! count=4)
- Result: 4 substrings

**Time Complexity**: O(n) - single pass through the string
**Space Complexity**: O(k) where k is the number of unique characters (at most 26 for lowercase letters)

## Tags

array, string, hash table, greedy