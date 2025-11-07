## Problem

https://leetcode.com/problems/rearrange-characters-to-make-target-string/

```
You are given two 0-indexed strings s and target. You can take some letters from s and rearrange them to form new strings.

Return the maximum number of copies of target that can be formed by taking letters from s and rearranging them.

Example 1:

Input: s = "ilovecodingonleetcode", target = "code"
Output: 2
Explanation:
For the first copy of "code", take the letters at indices 4, 5, 6, and 7.
For the second copy of "code", take the letters at indices 17, 18, 19, and 20.
The strings that are formed are "ecod" and "code" which can both be rearranged into "code".
We can make at most two copies of "code", so we return 2.

Example 2:

Input: s = "abcba", target = "abc"
Output: 1
Explanation:
We can make one copy of "abc" by taking the letters at indices 0, 1, and 2.
We can make at most one copy of "abc", so we return 1.
Note that while there is an extra 'a' and 'b' at indices 3 and 4, we cannot reuse the letter 'c' at index 2, so we cannot make a second copy of "abc".

Example 3:

Input: s = "abbaccaddaeea", target = "aaaaa"
Output: 1
Explanation:
We can make one copy of "aaaaa" by taking the letters at indices 0, 3, 6, 9, and 12.
We can make at most one copy of "aaaaa", so we return 1.

Constraints:

1 <= s.length <= 100
1 <= target.length <= 10
s and target consist of lowercase English letters.
```

## Observations

1. **Character Frequency Analysis**: To form copies of the target string, we need to count how many times each character appears in both strings.

2. **Limiting Factor**: The maximum number of copies we can make is limited by the character that has the smallest ratio of available count to required count.

3. **Mathematical Approach**: For each character in target, we calculate `available_count // required_count`. The minimum of these ratios gives us the answer.

4. **Edge Cases**: 
   - If any character in target doesn't exist in s, we can't form even one copy (ratio = 0)
   - Characters in s that aren't in target don't affect the result

## Solution

1. **Count Target Characters (`ft`)**: Create a frequency map of characters in the target string. This tells us how many of each character we need for one copy.

2. **Count Source Characters (`fs`)**: Create a frequency map of characters in the source string `s`. This tells us how many of each character we have available.

3. **Find the Bottleneck**: For each unique character in target:
   - Calculate how many complete copies we can make with that character: `fs[c] // ft[c]`
   - Take the minimum across all characters - this is our bottleneck

4. **Return Result**: The minimum ratio represents the maximum number of complete target strings we can form.

**Example Walkthrough:**
- `s = "ilovecodingonleetcode"`, `target = "code"`
- Target frequencies: `{'c': 1, 'o': 1, 'd': 1, 'e': 1}`
- Source frequencies: `{'i': 2, 'l': 2, 'o': 4, 'v': 1, 'e': 4, 'c': 2, 'd': 2, 'n': 4, 'g': 2, 't': 1}`
- Ratios: `c: 2//1 = 2`, `o: 4//1 = 4`, `d: 2//1 = 2`, `e: 4//1 = 4`
- Minimum ratio: `min(2, 4, 2, 4) = 2`

**Time Complexity:** O(|s| + |target|) - we iterate through both strings once
**Space Complexity:** O(|s| + |target|) - for the frequency maps

# Tags

- Hash Table
- String
- Counting
- Greedy Algorithm

