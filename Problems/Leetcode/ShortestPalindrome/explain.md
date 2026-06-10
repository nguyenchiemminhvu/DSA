## Problem

https://leetcode.com/problems/shortest-palindrome/description

Given a string `s`, you may **only add characters to the front** of it. Return the **shortest palindrome** you can form.

```
Input: s = "aacecaaa"   →   Output: "aaacecaaa"
Input: s = "abcd"       →   Output: "dcbabcd"
```

---

## Observations

**1. Adding only to the front narrows our search.**  
Because we can never touch the original string or append to its back, every valid result looks like:

```
[some prefix reversed] + s
```

The goal is to minimize the length of that prefix — ideally make it empty.

---

**2. The key insight: find the longest palindromic prefix of `s`.**

Let `s = P + Q` where `P = s[0..k]` is the **longest prefix of `s` that is already a palindrome**, and `Q = s[k+1..n-1]` is the remaining suffix.

To make the whole string a palindrome we prepend the reverse of `Q`:

```
result = reverse(Q) + s  =  reverse(Q) + P + Q
```

Why does this work?
- `reverse(Q)` mirrors `Q` on the left.
- `P` is already a palindrome, so it sits symmetrically in the middle.
- The result is `reverse(Q) + P + Q`, which reads the same forwards and backwards.

Why is this the **shortest** possible answer?
- Every additional character we prepend corresponds to one character of `Q` we didn't absorb.
- The longer the palindromic prefix `P`, the shorter `Q` is, and the fewer characters we need to prepend.
- So the optimal strategy is to maximise `|P|`.

**Worked example — `s = "aacecaaa"`:**

| Prefix        | Is palindrome? |
|---------------|---------------|
| `"aacecaaa"`  | No            |
| `"aacecaa"`   | Yes ✓         |

Longest palindromic prefix = `"aacecaa"` (`k = 6`).  
Remaining suffix `Q = "a"`, reversed = `"a"`.  
Result = `"a"` + `"aacecaaa"` = `"aaacecaaa"`. ✓

**Worked example — `s = "abcd"`:**

| Prefix  | Is palindrome? |
|---------|---------------|
| `"abcd"` | No           |
| `"abc"`  | No           |
| `"ab"`   | No           |
| `"a"`    | Yes ✓        |

Longest palindromic prefix = `"a"` (`k = 0`).  
Remaining suffix `Q = "bcd"`, reversed = `"dcb"`.  
Result = `"dcb"` + `"abcd"` = `"dcbabcd"`. ✓

---

## Solution Explanation

### Approach 1 — Brute Force (O(n²) time, O(1) extra space)

Scan from the **longest** possible prefix down to the shortest.  
The first one that is a palindrome is the answer.

```python
for i in range(n - 1, -1, -1):
    if s[0:i + 1] == s[0:i + 1][::-1]:   # O(n) palindrome check
        return s[i + 1:][::-1] + s
return ''
```

- We iterate `i` from `n-1` down to `0`, so the **first hit** is the longest palindromic prefix.
- Checking `s[0:i+1] == reverse` costs O(n), and we do this up to n times → **O(n²) total**.
- The `return ''` at the end is only reached when `s` is empty (the empty string is vacuously a palindrome, but the loop's `i=0` check covers that case; an explicit guard is fine).

---

### Approach 2 — DP Table (O(n²) time, O(n²) space) — commented in code

The commented block pre-computes a boolean table `dp[i][j]` meaning *"is `s[i..j]` a palindrome?"*.

**Initialization:**
```python
dp[i][i] = True             # every single character is a palindrome
dp[i-1][i] = True           # adjacent equal characters form a palindrome
  if s[i-1] == s[i]
```

**Filling via expand-around-center:**

For every center `i` (odd-length substrings centered at `i`, even-length centered between `i-1` and `i`), expand outward as long as:
1. The inner substring is already a palindrome (`dp[l+1][r-1]` is True), **and**
2. The two boundary characters match (`s[l] == s[r]`).

If both conditions hold, mark `dp[l][r] = True` and keep expanding.  
As soon as the boundaries don't match, `dp[l][r]` stays False, and the next iteration sees `dp[l+1][r-1]` = False, halting expansion — correctly preventing any further outer substrings from being marked as palindromes from that center.

**Finding the answer:**
```python
pivot = 0
for i in range(n):
    if dp[0][i]:          # is s[0..i] a palindrome?
        pivot = i         # keep the rightmost one
return s[pivot + 1:][::-1] + s
```

This approach is conceptually clearer but uses O(n²) space for the table.

---

### Approach 3 — KMP Failure Function (O(n) time, O(n) space) — optimal

Construct the string:

```
t = s + "#" + reverse(s)
```

The `#` separator prevents the two halves from overlapping.  
Compute the **KMP failure (partial-match) function** on `t`.

The last value `fail[-1]` equals the length of the longest proper prefix of `t` that is also a suffix of `t`. Because of the structure of `t`, this is exactly the length of the longest palindromic prefix of `s`.

```python
def shortestPalindrome(s):
    t = s + '#' + s[::-1]
    fail = [0] * len(t)
    j = 0
    for i in range(1, len(t)):
        while j > 0 and t[i] != t[j]:
            j = fail[j - 1]
        if t[i] == t[j]:
            j += 1
        fail[i] = j
    k = fail[-1]            # length of longest palindromic prefix
    return s[k:][::-1] + s
```

This runs in **O(n) time** and **O(n) space** — the best possible complexity for this problem.
