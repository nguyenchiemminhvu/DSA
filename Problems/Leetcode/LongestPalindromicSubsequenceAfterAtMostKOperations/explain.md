## Problem

https://leetcode.com/problems/longest-palindromic-subsequence-after-at-most-k-operations/description

````markdown
## Problem

https://leetcode.com/problems/longest-palindromic-subsequence-after-at-most-k-operations/description

You are given a string `s` and an integer `k`.

In one operation, you can replace the character at any position with the **next** or **previous** letter in the alphabet (wrapping around so that `'a'` is after `'z'`). For example:
- Replacing `'a'` with the next letter results in `'b'`, and replacing `'a'` with the previous letter results in `'z'`.
- Replacing `'z'` with the next letter results in `'a'`, and replacing `'z'` with the previous letter results in `'y'`.

Return the **length of the longest palindromic subsequence** of `s` that can be obtained after performing **at most k operations**.

**Example 1:**
```
Input: s = "abced", k = 2
Output: 3
Explanation:
  Replace s[1] with the next letter → "acced"
  Replace s[4] with the previous letter → "accec"
  The subsequence "ccc" is a palindrome of length 3.
```

**Example 2:**
```
Input: s = "aaazzz", k = 4
Output: 6
Explanation:
  The entire string can be turned into "zaaaaz" using 4 operations — a palindrome of length 6.
```

**Constraints:**
- `1 <= s.length <= 200`
- `1 <= k <= 200`
- `s` consists of only lowercase English letters.

## Observations

1. **Palindromic subsequence with interval DP:** The classic "Longest Palindromic Subsequence" (LPS) problem uses interval DP: `dp[l][r]` = LPS length for substring `s[l..r]`. We expand to a 3D state `dp[l][r][cnt]` where `cnt` is the number of operations already used.

2. **Cost to match two characters:** To make characters `a` and `b` identical by shifting one of them towards the other, the minimum number of steps is:
   $$\text{dist}(a, b) = \min(|a - b|,\ 26 - |a - b|)$$
   This accounts for the circular wrapping of the alphabet.

3. **Only one character needs to move:** To match `s[l]` with `s[r]`, we only need to move *one* of them (the one requiring fewer steps). Moving `s[l]` by `dist` steps either forward (`next_ch`) or backward (`prev_ch`) will land on `s[r]`. Since we track operations used as part of the DP state, we can decide whether to spend those operations at this subproblem.

4. **State space and transitions:** The DP has `O(n^2 * k)` states, and each transition is `O(1)`, giving an overall time complexity of `O(n^2 * k)` and space complexity of `O(n^2 * k)`.

5. **Iteration order matters:** We iterate `l` from right to left and `r` from `l+1` to `n-1`, ensuring that subproblems `dp[l+1][r-1]`, `dp[l+1][r]`, and `dp[l][r-1]` are computed before `dp[l][r]`. For `cnt`, we iterate from high to low so that when we look up `dp[...][cnt + dist]`, it is already computed (or we iterate forward — both work since cnt dimensions are independent).

## Solution

```python
class Solution:
    def longestPalindromicSubsequence(self, s: str, k: int) -> int:
        # Convert characters to integers 0..25 for easier arithmetic
        s = [ord(c) - ord('a') for c in s]
        n = len(s)

        def min_dist(a: int, b: int) -> int:
            # Minimum circular distance between two alphabet positions
            d = abs(a - b)
            return min(d, 26 - d)

        def prev_ch(c: int, step: int = 1) -> int:
            return ((c - step) + 26) % 26

        def next_ch(c: int, step: int = 1) -> int:
            return (c + step) % 26

        # dp[l][r][cnt] = longest palindromic subsequence of s[l..r]
        #                 using exactly 'cnt' operations so far
        dp = [[[0] * (k + 1) for _ in range(n)] for _ in range(n)]

        # Base case: single character is always a palindrome of length 1
        for i in range(n):
            for cnt in range(k + 1):
                dp[i][i][cnt] = 1

        for l in range(n - 1, -1, -1):
            for r in range(l + 1, n):
                for cnt in range(k, -1, -1):
                    if s[l] == s[r]:
                        # Characters already match — extend the inner palindrome by 2
                        dp[l][r][cnt] = max(dp[l][r][cnt], 2 + dp[l + 1][r - 1][cnt])
                    else:
                        # Skip one of the endpoints (standard LPS moves)
                        dp[l][r][cnt] = max(dp[l][r][cnt], dp[l + 1][r][cnt], dp[l][r - 1][cnt])

                        # Try spending 'dist' operations to make s[l] == s[r]
                        dist = min_dist(s[l], s[r])
                        if cnt + dist <= k:
                            # Shift s[l] backwards by dist steps
                            if prev_ch(s[l], dist) == s[r]:
                                dp[l][r][cnt] = max(dp[l][r][cnt], 2 + dp[l + 1][r - 1][cnt + dist])
                            # Shift s[l] forwards by dist steps
                            if next_ch(s[l], dist) == s[r]:
                                dp[l][r][cnt] = max(dp[l][r][cnt], 2 + dp[l + 1][r - 1][cnt + dist])

        # Answer: LPS of the full string using 0 operations spent so far
        return dp[0][n - 1][0]
```

**Step-by-step walkthrough (Example 1: `s = "abced"`, `k = 2`):**

- Characters as integers: `[0, 1, 2, 4, 3]` (a=0, b=1, c=2, e=4, d=3)
- Consider `l=0` (`a`), `r=4` (`d`), `cnt=0`:
  - `dist('a', 'd') = min(3, 23) = 3 > k=2`, cannot match → skip replacement.
- Consider `l=1` (`b`), `r=3` (`e`), `cnt=0`:
  - `dist('b', 'e') = min(3, 23) = 3 > 2` → cannot match.
  - But `l=1, r=2` (`b`, `c`): `dist = 1`, shifting `b` forward → `c == c` ✓, uses 1 op.
- The DP finds that `dp[0][4][0] = 3` (subsequence like `"ccc"` after adjustments).

**Complexity:**
- **Time:** $O(n^2 \cdot k)$
- **Space:** $O(n^2 \cdot k)$

# Tags
- Dynamic Programming
- Interval DP
- String
- Palindrome
````
