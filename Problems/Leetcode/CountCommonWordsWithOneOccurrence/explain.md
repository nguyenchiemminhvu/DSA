## Problem

https://leetcode.com/problems/count-common-words-with-one-occurrence/description/

```
Given two string arrays words1 and words2, return the number of strings that appear exactly once in each of the two arrays.

Example 1:

Input: words1 = ["leetcode","is","amazing","as","is"], words2 = ["amazing","leetcode","is"]
Output: 2
Explanation:
- "leetcode" appears exactly once in each of the two arrays. We count this string.
- "amazing" appears exactly once in each of the two arrays. We count this string.
- "is" appears in each of the two arrays, but there are 2 occurrences of it in words1. We do not count this string.
- "as" appears once in words1, but does not appear in words2. We do not count this string.
Thus, there are 2 strings that appear exactly once in each of the two arrays.

Example 2:

Input: words1 = ["b","bb","bbb"], words2 = ["a","aa","aaa"]
Output: 0
Explanation: There are no strings that appear in each of the two arrays.

Example 3:

Input: words1 = ["a","ab"], words2 = ["a","a","a","ab"]
Output: 1
Explanation: The only string that appears exactly once in each of the two arrays is "ab".

Constraints:

1 <= words1.length, words2.length <= 1000
1 <= words1[i].length, words2[j].length <= 30
words1[i] and words2[j] consists only of lowercase English letters.
```

## Observations

1. **Problem Requirements**: We need to count words that appear exactly once in **both** arrays.
2. **Key Insight**: A word must satisfy two conditions simultaneously:
   - Appears exactly once in `words1`
   - Appears exactly once in `words2`
3. **Edge Cases**: 
   - Words that appear multiple times in either array should be excluded
   - Words that don't appear in one of the arrays should be excluded
4. **Data Structure**: Using `Counter` from collections module is efficient for frequency counting
5. **Optimization**: We only need to iterate through one array (`words1`) since we're checking conditions for both arrays

## Solution

The solution uses a **frequency counting** approach with hash maps:

### Algorithm:
1. **Count Frequencies**: Use `Counter` to count occurrences of each word in both arrays
2. **Single Pass Check**: Iterate through `words1` and for each word:
   - Check if it appears exactly once in `words1` (`f1[word] == 1`)
   - Check if it appears exactly once in `words2` (`f2[word] == 1`)
   - If both conditions are met, increment the result counter

### Time Complexity: O(n + m)
- O(n) to create Counter for `words1`
- O(m) to create Counter for `words2`  
- O(n) to iterate through `words1`
- Overall: O(n + m) where n and m are lengths of the arrays

### Space Complexity: O(n + m)
- O(n) space for Counter of `words1`
- O(m) space for Counter of `words2`

### Example Trace:
For `words1 = ["leetcode","is","amazing","as","is"]`, `words2 = ["amazing","leetcode","is"]`:
- `f1 = {"leetcode":1, "is":2, "amazing":1, "as":1}`
- `f2 = {"amazing":1, "leetcode":1, "is":1}`
- Checking each word in words1:
  - "leetcode": f1["leetcode"]=1 ✓, f2["leetcode"]=1 ✓ → count++
  - "is": f1["is"]=2 ✗ → skip
  - "amazing": f1["amazing"]=1 ✓, f2["amazing"]=1 ✓ → count++
  - "as": f1["as"]=1 ✓, f2["as"]=0 ✗ → skip
- Result: 2

# Tags

`Hash Map` `Frequency Count` `Two Arrays` `Easy`

