## Problem

https://leetcode.com/problems/find-the-lexicographically-smallest-valid-sequence/description

You are given two strings `word1` and `word2`. A string `x` is **almost equal** to `y` if you can change **at most one** character in `x` to make it identical to `y`.

A sequence of indices `seq` is **valid** if:
- Indices are sorted in ascending order.
- Concatenating `word1[seq[0]], word1[seq[1]], ...` gives a string almost equal to `word2`.

Return the **lexicographically smallest** valid sequence of indices of length `word2.length`, or an empty array if none exists.

**Constraints:** `1 <= word2.length < word1.length <= 3 * 10^5`, lowercase English letters only.

---

## Ideas

### Observation

We need to pick `m = len(word2)` indices from `word1` (in order) such that the resulting subsequence differs from `word2` in at most 1 position. We are allowed at most one **wild card** match (a mismatch we "fix" for free).

For the lexicographically smallest index array, greedily pick the **smallest available index** at each step. This means:
- If an exact match and a wild card match are both available at the same position, prefer exact match — it preserves the wild card for later.
- If only a wild card match is available (and affordable), take it — a smaller index now beats any larger index later.

### Key Precomputation: `suffix[i]`

Scan `word1` **right to left**, greedily matching `word2` **from its end**:

```
i2 = m - 1
for i1 from n-1 down to 0:
    if word1[i1] == word2[i2]:
        i2 -= 1
    suffix[i1] = m - i2 - 1   # how many trailing chars of word2 are matchable from i1..n-1
```

`suffix[i]` = the number of characters of `word2` (from the back) that can be matched as a subsequence in `word1[i..n-1]`.

**Wild card condition at position `i1` for `word2[i2]`:**  
After using the wild card at `i1`, we must match `word2[i2+1..m-1]` (length `m - i2 - 1`) from `word1[i1+1..n-1]`. This is possible iff:

$$\text{suffix}[i1 + 1] \geq m - i2 - 1$$

### Algorithm

1. **Precompute** `suffix[i]` for all `i` via right-to-left greedy scan. `O(n)`
2. **Forward greedy scan** with `i2 = 0` (pointer into `word2`) and `wildcardUsed = false`:
   - For each `i1` in `word1`:
     - If `word1[i1] == word2[i2]`: exact match → append `i1`, advance `i2`.
     - Else if wild card not used **and** `suffix[i1+1] >= m - i2 - 1`: use wild card → append `i1`, advance `i2`, mark wild card used.
   - If `i2 == m` at the end, return the result; otherwise return `[]`. `O(n)`

### Complexity

| | |
|---|---|
| Time | `O(n + m)` |
| Space | `O(n)` for the suffix array |

### Correctness of Greedy

**Taking the wild card at the earliest opportunity is optimal:**  
Suppose at step `j` of the sequence, we can use the wild card at index `i1` (mismatch) but could also wait for an exact match at `i2 > i1`. Picking `i1` gives a strictly smaller index at position `j`. Since we start the next step from `i1+1 < i2+1`, subsequent positions can only be equal or smaller — never larger. So early wild card usage never hurts and often helps.

**Preferring exact match over wild card at same index:**  
When `word1[i1] == word2[i2]`, using the exact match is always at least as good as using the wild card (same index chosen, wild card preserved for future use).
