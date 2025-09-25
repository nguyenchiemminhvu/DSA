## Problem Description

https://leetcode.com/problems/remove-all-occurrences-of-a-substring/

```
Given two strings s and part, perform the following operation on s until all occurrences of the substring part are removed:

Find the leftmost occurrence of the substring part and remove it from s.
Return s after removing all occurrences of part.

A substring is a contiguous sequence of characters in a string.

Example 1:

Input: s = "daabcbaabcbc", part = "abc"
Output: "dab"
Explanation: The following operations are done:
- s = "daabcbaabcbc", remove "abc" starting at index 2, so s = "dabaabcbc".
- s = "dabaabcbc", remove "abc" starting at index 4, so s = "dababc".
- s = "dababc", remove "abc" starting at index 3, so s = "dab".
Now s has no occurrences of "abc".

Example 2:

Input: s = "axxxxyyyyb", part = "xy"
Output: "ab"
Explanation: The following operations are done:
- s = "axxxxyyyyb", remove "xy" starting at index 4 so s = "axxxyyyb".
- s = "axxxyyyb", remove "xy" starting at index 3 so s = "axxyyb".
- s = "axxyyb", remove "xy" starting at index 2 so s = "axyb".
- s = "axyb", remove "xy" starting at index 1 so s = "ab".
Now s has no occurrences of "xy".

Constraints:

1 <= s.length <= 1000
1 <= part.length <= 1000
s​​​​​​ and part consists of lowercase English letters.
```

## Observations

The constraints are small.

Removing one occurrence of part might create a new opportunity for another occurrence.
Example:
```
s = "daabcbaabcbc", part = "abc".
After removing the first "abc" at index 2 → "dabaabcbc".
Now a new "abc" appears at index 4, which didn’t exist before.
```

A simple approach:

(1) Find the first (left-most) occurrence of substring in main string
(2) Erase the string at found index, length of substring.
(3) Repeat steps above until can not find the substring in main string anymore.

## Complexity

Worst case, each removal takes ```O(n)``` time.

In the worst case, we do up to ```O(n / m)``` removals, where ```m = len(part)```.

Total: ```O(n²)``` in the worst case.

Given ```n ≤ 1000```, this is efficient enough.

## Tags

string