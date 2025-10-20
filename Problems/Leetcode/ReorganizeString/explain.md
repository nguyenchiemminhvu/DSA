## Problem

https://leetcode.com/problems/reorganize-string/

```
Given a string s, rearrange the characters of s so that any two adjacent characters are not the same.

Return any possible rearrangement of s or return "" if not possible.

Example 1:

Input: s = "aab"
Output: "aba"

Example 2:

Input: s = "aaab"
Output: ""

Constraints:

1 <= s.length <= 500
s consists of lowercase English letters.
```

## Observations

1. **Core Challenge**: We need to rearrange characters so no two adjacent characters are the same.

2. **Impossibility Condition**: If any character appears more than `(n+1)/2` times (where n is string length), it's impossible to reorganize. For example, in "aaab" (length 4), 'a' appears 3 times, which is more than (4+1)/2 = 2.5, so it's impossible.

3. **Greedy Strategy**: Always try to place the most frequent character next, but avoid placing the same character consecutively.

4. **Priority Queue Approach**: Use a max heap to always get the character with highest frequency first. When we can't use the most frequent character (because it would create adjacent duplicates), we use the second most frequent.

5. **Two-Character Logic**: At any point, we only need to consider at most two different characters - the most frequent and the second most frequent.

## Solution

**Algorithm**: Greedy with Max Heap

The solution uses a greedy approach with a priority queue (max heap) to always prioritize characters with higher frequencies:

1. **Frequency Count**: First, count the frequency of each character in the input string.

2. **Max Heap Setup**: Create a max heap where characters are ordered by their frequency (using negative values since Python's heapq is a min heap).

3. **Greedy Construction**: 
   - Always try to use the character with the highest remaining frequency
   - If the last character in our result is the same as the most frequent character, use the second most frequent character instead
   - If we can't find an alternative character, return empty string (impossible case)

4. **Frequency Management**: After using a character, decrease its frequency and put it back in the heap if it still has remaining occurrences.

**Time Complexity**: O(n log k) where n is the length of string and k is the number of unique characters (at most 26 for lowercase letters).

**Space Complexity**: O(k) for the frequency map and priority queue.

**Key Insight**: By always using the most frequent available character (that doesn't violate the adjacency rule), we maximize our chances of successfully placing all characters while avoiding impossible situations.

## Tags

array, string, max heap, priority queue, greedy