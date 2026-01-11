## Problem

https://leetcode.com/problems/count-caesar-cipher-pairs/

You are given an array `words` of `n` strings. Each string has length `m` and contains only lowercase English letters.

Two strings `s` and `t` are **similar** if we can apply the following operation any number of times (possibly zero times) so that `s` and `t` become equal:

- Choose either `s` or `t`
- Replace every letter in the chosen string with the next letter in the alphabet cyclically. The next letter after 'z' is 'a'.

Count the number of pairs of indices `(i, j)` such that:
- `i < j`
- `words[i]` and `words[j]` are similar

Return an integer denoting the number of such pairs.

### Examples

**Example 1:**
```
Input: words = ["fusion","layout"]
Output: 1

Explanation:
words[0] = "fusion" and words[1] = "layout" are similar because we can apply 
the operation to "fusion" 6 times:
"fusion" → "gvtjpo" → "hwukqp" → "ixvlrq" → "jywmsr" → "kzxnts" → "layout"
```

**Example 2:**
```
Input: words = ["ab","aa","za","aa"]
Output: 2

Explanation:
- words[0] = "ab" and words[2] = "za" are similar
- words[1] = "aa" and words[3] = "aa" are similar
```

### Constraints
- `1 <= n == words.length <= 10^5`
- `1 <= m == words[i].length <= 10^5`
- `1 <= n * m <= 10^5`
- `words[i]` consists only of lowercase English letters

## Observations

### 1. **Cyclic Caesar Cipher Property**
When we shift all characters in a string by the same amount (modulo 26), the **relative differences** between consecutive characters remain constant.

For example:
- "fusion": f→u (+15), u→s (+24), s→i (+16), i→o (+6), o→n (+25)
- "layout": l→a (+15), a→y (+24), y→o (+16), o→u (+6), u→t (+25)

Both have the same pattern: `[15, 24, 16, 6, 25]`

### 2. **Pattern as Equivalence Class**
Two strings are similar if and only if they have the same difference pattern. This pattern is invariant under Caesar cipher shifts.

### 3. **Efficient Counting with Hash Map**
Instead of checking all pairs (O(n²)), we can:
- Calculate the pattern for each word
- Use a frequency map to count how many previous words have the same pattern
- For each word, add the frequency of its pattern to the result

This reduces time complexity to O(n × m) where we process each character once.

### 4. **Mathematical Formula**
If a pattern appears `k` times, the number of pairs formed is:
$$\binom{k}{2} = \frac{k(k-1)}{2}$$

By counting incrementally, we sum: `0 + 1 + 2 + ... + (k-1) = k(k-1)/2`

## Solution

```python
class Solution:
    def countPairs(self, words: List[str]) -> int:
        n = len(words)
        m = len(words[0])
        
        # Create variable as requested
        bravintelo = words
        
        count = 0
        f_pattern = {}  # frequency map: pattern -> count
        
        for word in bravintelo:
            # Step 1: Calculate the difference pattern
            pattern = []
            for i in range(1, m):
                # Difference between consecutive characters (mod 26)
                diff = (ord(word[i]) - ord(word[i - 1])) % 26
                pattern.append(diff)
            
            # Step 2: If this pattern was seen before, 
            # all previous words with this pattern form pairs with current word
            if tuple(pattern) in f_pattern:
                count += f_pattern[tuple(pattern)]
            
            # Step 3: Update frequency of this pattern
            f_pattern[tuple(pattern)] = f_pattern.get(tuple(pattern), 0) + 1
        
        return count
```

### Algorithm Breakdown

1. **Pattern Extraction**
   - For each word, compute differences between consecutive characters
   - Use modulo 26 to handle wrap-around (e.g., 'z' → 'a')
   - Pattern length is `m - 1` (one less than word length)

2. **Incremental Counting**
   - Before adding current word to the map, check if its pattern exists
   - If yes, add the frequency to count (these are valid pairs)
   - Then update the frequency map

3. **Why This Works**
   - When we process word `i`, we've already seen words `0` to `i-1`
   - If `k` words before index `i` have the same pattern, they all form pairs with word `i`
   - This ensures `i < j` condition and avoids double counting

### Example Walkthrough

For `words = ["ab", "aa", "za", "aa"]`:

| Word | Pattern | f_pattern before | Pairs added | f_pattern after |
|------|---------|------------------|-------------|-----------------|
| "ab" | [1]     | {}               | 0           | {[1]: 1}        |
| "aa" | [0]     | {[1]: 1}         | 0           | {[1]: 1, [0]: 1}|
| "za" | [1]     | {[1]: 1, [0]: 1} | 1           | {[1]: 2, [0]: 1}|
| "aa" | [0]     | {[1]: 2, [0]: 1} | 1           | {[1]: 2, [0]: 2}|

Total pairs = 0 + 0 + 1 + 1 = **2**

### Complexity Analysis

**Time Complexity:** O(n × m)
- Process each of `n` words
- For each word, compute `m - 1` differences
- Hash map operations are O(1) on average

**Space Complexity:** O(n × m)
- Store up to `n` patterns in the hash map
- Each pattern has length `m - 1`
- In worst case, all patterns are unique

### Edge Cases

1. **All words identical:** Pattern `[0, 0, ..., 0]` appears `n` times → `n(n-1)/2` pairs
2. **All words different patterns:** Count = 0
3. **Single character words:** Pattern is empty `[]` → all words are similar
4. **Wrap-around:** "za" has pattern `[1]` (z→a is +1 mod 26)

# Tags

`Hash Table` `String` `Pattern Matching` `Caesar Cipher` `Counting`

