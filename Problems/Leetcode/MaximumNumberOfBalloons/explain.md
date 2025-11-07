## Problem

https://leetcode.com/problems/maximum-number-of-balloons/description/

```
Given a string text, you want to use the characters of text to form as many instances of the word "balloon" as possible.

You can use each character in text at most once. Return the maximum number of instances that can be formed.

Example 1:

Input: text = "nlaebolko"
Output: 1

Example 2:

Input: text = "loonbalxballpoon"
Output: 2

Example 3:

Input: text = "leetcode"
Output: 0

Constraints:

1 <= text.length <= 104
text consists of lower case English letters only.

Note: This question is the same as 2287: Rearrange Characters to Make Target String.
```

## Observations

1. **Character frequency analysis**: To form the word "balloon", we need specific characters with specific frequencies:
   - 'b': 1 occurrence
   - 'a': 1 occurrence  
   - 'l': 2 occurrences
   - 'o': 2 occurrences
   - 'n': 1 occurrence

2. **Limiting factor**: The maximum number of "balloon"s we can form is limited by the character that appears least frequently relative to its required count.

3. **Division for repeated characters**: Since 'l' and 'o' appear twice in "balloon", we need to divide their counts by 2 to see how many complete "balloon"s they can contribute to.

4. **Greedy approach**: We count all character frequencies first, then find the minimum among the normalized counts.

## Solution

1. **Count character frequencies**: Use a `defaultdict(int)` to count occurrences of each character in the input text. This gives us a frequency map where `f[c]` represents how many times character `c` appears.

2. **Calculate maximum balloons per character**:
   - For 'b', 'a', 'n': Each balloon needs exactly 1 of these, so `f['b']`, `f['a']`, `f['n']` directly tell us how many balloons each can support
   - For 'l', 'o': Each balloon needs 2 of these, so `f['l'] // 2` and `f['o'] // 2` tell us how many balloons each can support

3. **Find the bottleneck**: Return the minimum among all these values, as it represents the limiting factor.

**Time Complexity**: O(n) where n is the length of the input text
**Space Complexity**: O(1) since we only store counts for at most 26 lowercase letters

**Example walkthrough** with `text = "nlaebolko"`:
- Frequency count: {'n': 1, 'l': 2, 'a': 1, 'e': 1, 'b': 1, 'o': 2, 'k': 1}
- Balloon capacity per character: [b=1, a=1, l=2//2=1, o=2//2=1, n=1] 
- Result: min([1, 1, 1, 1, 1]) = 1

# Tags

