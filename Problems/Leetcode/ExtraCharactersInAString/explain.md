## Problem

https://leetcode.com/problems/extra-characters-in-a-string/description

````markdown
## Problem

https://leetcode.com/problems/extra-characters-in-a-string/description

You are given a 0-indexed string `s` and a dictionary of words `dictionary`. You must break `s` into one or more non-overlapping substrings such that each substring is present in `dictionary`. There may be some extra characters in `s` that are not part of any matched substring.

Return the **minimum number of extra characters** left over if you break up `s` optimally.

**Constraints:**
- 1 ≤ s.length ≤ 50
- 1 ≤ dictionary.length ≤ 50
- 1 ≤ dictionary[i].length ≤ 50
- `dictionary[i]` and `s` consist of only lowercase English letters
- `dictionary` contains distinct words

**Examples:**
1. Input: s = `"leetscode"`, dictionary = `["leet","code","leetcode"]` → Output: `1`
   - Use `"leet"` (index 0–3) and `"code"` (index 5–8). Index 4 (`'s'`) is extra.
2. Input: s = `"sayhelloworld"`, dictionary = `["hello","world"]` → Output: `3`
   - Use `"hello"` (index 3–7) and `"world"` (index 8–12). Indices 0, 1, 2 are extra.

## Observations

1. **Counting extras, not coverage**: Unlike Word Break (which is a yes/no problem), here we need to **minimize** the number of characters left uncovered. This is an optimization problem, suggesting DP where we track costs.

2. **Natural subproblem structure**: If we process `s` left to right and consider each index `i` as an endpoint, the minimum extras up to `i` depends on the minimum extras up to some earlier index `j`. This is the classic "suffix/prefix DP" shape.

3. **Two choices at each index `i`**:
   - **Skip `s[i]`**: treat it as an extra character. Cost = 1 + (minimum extras up to `i - 1`).
   - **Match a word ending at `i`**: if some `word` from the dictionary equals `s[i - nw + 1 : i + 1]`, then no extras are added for those `nw` characters. Cost = (minimum extras up to `i - nw`).

4. **DP state definition**: `dp[i]` = minimum number of extra characters in the prefix `s[0 : i + 1]`.

5. **Base / worst case**: If no dictionary word ever matches, every character is extra, so `dp[i] = i + 1` (all characters in the prefix `s[0 : i + 1]` are extra). This also serves as the initial value before taking the minimum.

6. **Transition**:
   - For each word of length `nw` ending at `i` (i.e., `s[i - nw + 1 : i + 1] == word`):
     - `dp[i] = min(dp[i], dp[i - nw] if i - nw >= 0 else 0)`
   - Regardless (the "skip" option):
     - `dp[i] = min(dp[i], 1 + (dp[i - 1] if i - 1 >= 0 else 0))`

7. **Top-down equivalence**: The memoized recursion `F(i)` defines the same recurrence; `F(i) = min(skip cost, best matching word cost)`. The bottom-up DP simply fills this table iteratively.

## Solution

**Algorithm: Dynamic Programming (Bottom-Up)**

```python
class Solution:
    def minExtraChar(self, s: str, words: List[str]) -> int:
        n = len(s)

        # dp[i] = minimum extra characters in s[0 : i + 1]
        # Start with worst case: every character in the prefix is extra
        dp = [i + 1 for i in range(n)]

        for i in range(n):
            for word in words:
                nw = len(word)
                # Option 1: a dictionary word ends exactly at index i
                if i - nw + 1 >= 0 and s[i - nw + 1: i + 1] == word:
                    dp[i] = min(dp[i], dp[i - nw] if i - nw >= 0 else 0)
                # Option 2: skip s[i] (treat it as an extra character)
                else:
                    dp[i] = min(dp[i], 1 + (dp[i - 1] if i - 1 >= 0 else 0))

        return dp[n - 1]
```

**Key Steps:**

1. **Initialization**: `dp[i] = i + 1` — the pessimistic assumption that all `i + 1` characters so far are extra.

2. **Outer loop**: iterate `i` from `0` to `n - 1`, treating `i` as the last index of the current prefix.

3. **Inner loop**: try every dictionary word:
   - If the word matches the tail of `s[0 : i + 1]`, inherit the cost from the index just before the word starts (no extras for those characters).
   - Otherwise, take the skip option: 1 extra character (`s[i]`) plus whatever was optimal for `s[0 : i]`.

4. **Answer**: `dp[n - 1]` holds the minimum extras for the entire string.

**Time Complexity**: O(n × d × L) — where `n` = length of `s`, `d` = number of dictionary words, `L` = maximum word length (string comparison cost).

**Space Complexity**: O(n) for the DP array.

**Memoized Top-Down Alternative (commented in code):**
```python
mem = {}
def F(i: int) -> int:
    if i < 0:
        return 0
    if i in mem:
        return mem[i]
    res = i + 1                          # worst case: all extras
    for word in words:
        nw = len(word)
        if i - nw + 1 >= 0 and s[i - nw + 1: i + 1] == word:
            res = min(res, F(i - nw))    # word matched, no extras for nw chars
        else:
            res = min(res, 1 + F(i - 1)) # skip s[i]
    mem[i] = res
    return res
return F(n - 1)
```
Both approaches produce identical results; the bottom-up version avoids recursion overhead.

# Tags

`Dynamic Programming`, `String`, `Memoization`, `Tabulation`, `Hash Table`
````

## Observations

## Solution

# Tags

