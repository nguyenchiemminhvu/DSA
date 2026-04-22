## Problem

https://leetcode.com/problems/words-within-two-edits-of-dictionary/description/

```
You are given two string arrays, queries and dictionary. All words in each array comprise of lowercase English letters and have the same length.

In one edit you can take a word from queries, and change any letter in it to any other letter. Find all words from queries that, after a maximum of two edits, equal some word from dictionary.

Return a list of all words from queries, that match with some word from dictionary after a maximum of two edits. Return the words in the same order they appear in queries.

Example 1:
Input: queries = ["word","note","ants","wood"], dictionary = ["wood","joke","moat"]
Output: ["word","note","wood"]

Example 2:
Input: queries = ["yes"], dictionary = ["not"]
Output: []

Constraints:
- 1 <= queries.length, dictionary.length <= 100
- n == queries[i].length == dictionary[j].length
- 1 <= n <= 100
- All queries[i] and dictionary[j] are composed of lowercase English letters.
```

## Observations

1. **All words have the same length**: This is a key constraint that simplifies the problem. We only need to compare characters at the same positions.

2. **Edit distance is limited to character substitution**: Unlike the general edit distance problem (Levenshtein distance), we don't need to consider insertions or deletions—only character replacements.

3. **At most 2 edits allowed**: A query word matches if it differs from any dictionary word in at most 2 positions.

4. **Brute force is feasible**: With constraints of at most 100 queries, 100 dictionary words, and word length up to 100, the worst case is $O(100 \times 100 \times 100) = O(10^6)$ operations, which is acceptable.

5. **Early termination possible**: Once we find more than 2 differences, we can stop comparing and move to the next dictionary word. Also, once a query matches any dictionary word, we can move to the next query.

## Solution

The solution uses a straightforward brute-force approach with early termination optimization:

```python
class Solution:
    def twoEditWords(self, queries: List[str], dictionary: List[str]) -> List[str]:
        res = []
        for query in queries:
            n = len(query)
            for word in dictionary:
                count_diff = 0
                for i in range(n):
                    if query[i] != word[i]:
                        count_diff += 1
                        if count_diff > 2:
                            break
                if count_diff <= 2:
                    res.append(query)
                    break
        return res
```

**Algorithm:**

1. **Iterate through each query word**: For each word in `queries`, we check if it can match any word in the dictionary.

2. **Compare with each dictionary word**: For each dictionary word, count the number of positions where characters differ.

3. **Early termination on mismatch**: If the difference count exceeds 2, immediately break out of the character comparison loop—no need to continue checking.

4. **Match found**: If after comparing all characters (or early termination with ≤2 differences), the count is at most 2, add the query to the result and break out of the dictionary loop.

5. **Return results**: Return all matching queries in their original order.

**Time Complexity:** $O(Q \times D \times N)$ where Q = number of queries, D = number of dictionary words, N = word length. With early termination, practical performance is often better.

**Space Complexity:** $O(1)$ extra space (excluding the output array).

# Tags

- String
- Array
- Brute Force

