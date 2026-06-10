## Problem

https://leetcode.com/problems/longest-happy-prefix/description

```
A string is called a happy prefix if it is a non-empty prefix which is also a suffix (excluding itself).

Given a string s, return the longest happy prefix of s.
Return an empty string "" if no such prefix exists.

Example 1:
Input: s = "level"
Output: "l"
Explanation: s contains 4 prefixes excluding itself ("l", "le", "lev", "leve"),
and 4 suffixes ("l", "el", "vel", "evel"). The largest prefix which is also a suffix is "l".

Example 2:
Input: s = "ababab"
Output: "abab"
Explanation: "abab" is the largest prefix which is also a suffix. They can overlap in the original string.

Constraints:
1 <= s.length <= 10^5
s contains only lowercase English letters.
```

---

## Observations

1. **Definition Recap**: A "happy prefix" of length `L` satisfies:
   - `s[0..L-1] == s[n-L..n-1]` (it is both a prefix and a suffix)
   - `L < n` (it must exclude the string itself)

2. **Search Direction**: We want the *longest* such prefix, so scanning from the longest candidate (`L = n-1`) down to `1` and returning the first match is correct for brute force.

3. **Overlap is Allowed**: As shown in Example 2, the prefix and suffix may overlap (e.g., "abab" in "ababab"). This makes character-by-character comparison necessary rather than only checking non-overlapping halves.

4. **This is the KMP Failure Function**: The core of the problem is computing the *longest proper prefix that is also a suffix* (LPS) for the entire string — which is exactly what the KMP failure function (also called the *prefix function* or *partial match table*) computes, in O(n) time.

5. **Rolling Hash Equivalence**: Instead of comparing substrings directly, we can build a prefix hash from the left and a suffix hash from the right simultaneously. When both hashes match at position `i`, `s[0..i]` is a happy prefix candidate.

6. **Z-function Alternative**: The Z-array `z[i]` gives the length of the longest substring starting at index `i` that matches a prefix of `s`. A happy prefix of length `z[i]` exists whenever `i + z[i] == n`.

---

## Solution 1: Brute Force

### Idea
Iterate over every possible prefix length `L` from `n-1` down to `1`. For each `L`, compare the prefix `s[0..L-1]` with the suffix `s[n-L..n-1]`. Return the first match.

### Algorithm
```
for L from n-1 down to 1:
    if s[0..L-1] == s[n-L..n-1]:
        return s[0..L-1]
return ""
```

### Example Trace — `s = "level"` (n=5)
| L | Prefix    | Suffix    | Match? |
|---|-----------|-----------|--------|
| 4 | "leve"    | "evel"    | ✗      |
| 3 | "lev"     | "vel"     | ✗      |
| 2 | "le"      | "el"      | ✗      |
| 1 | "l"       | "l"       | ✓ → return "l" |

### C++ Implementation
```cpp
string longestPrefix(string s) {
    int n = s.length();
    for (int L = n - 1; L >= 1; L--) {
        if (s.substr(0, L) == s.substr(n - L, L)) {
            return s.substr(0, L);
        }
    }
    return "";
}
```

### Complexity
- **Time**: O(n²) — up to O(n) comparisons each of length up to O(n)
- **Space**: O(n) for `substr` copies

---

## Solution 2: KMP Failure Function (Optimal)

### Idea
The KMP *failure function* `fail[i]` is defined as the length of the longest *proper* prefix of `s[0..i]` that is also a suffix. "Proper" means it cannot be the string itself.

By definition, `fail[n-1]` is exactly the length of the longest happy prefix of the entire string.

### How the Failure Function is Built
We fill `fail` left to right. At each index `i`:
1. Start with the candidate length `j = fail[i-1]` (the best known match for the previous position).
2. **Mismatch resolution**: While `j > 0` and `s[i] != s[j]`, fall back using `j = fail[j-1]` (reuse already-computed shorter matches).
3. **Match extension**: If `s[i] == s[j]`, increment `j` (extend the match by one).
4. Store `fail[i] = j`.

The fallback `j = fail[j-1]` is the key insight: if the current extension fails, the next best candidate length is the LPS of the current match — we don't restart from scratch.

### Example Trace — `s = "ababab"` (n=6)

| i | s[0..i] | j before | s[i] vs s[j] | fail[i] |
|---|---------|----------|--------------|---------|
| 0 | "a"     | —        | —            | 0       |
| 1 | "ab"    | 0        | 'b' ≠ 'a'    | 0       |
| 2 | "aba"   | 0        | 'a' = 'a' ✓  | 1       |
| 3 | "abab"  | 1        | 'b' = 'b' ✓  | 2       |
| 4 | "ababa" | 2        | 'a' = 'a' ✓  | 3       |
| 5 | "ababab"| 3        | 'b' = 'b' ✓  | 4       |

`fail[5] = 4` → answer = `s.substr(0, 4)` = **"abab"** ✓

### Example Trace — `s = "level"` (n=5)

| i | s[0..i] | j before | s[i] vs s[j] | fail[i] |
|---|---------|----------|--------------|---------|
| 0 | "l"     | —        | —            | 0       |
| 1 | "le"    | 0        | 'e' ≠ 'l'    | 0       |
| 2 | "lev"   | 0        | 'v' ≠ 'l'    | 0       |
| 3 | "leve"  | 0        | 'e' ≠ 'l'    | 0       |
| 4 | "level" | 0        | 'l' = 'l' ✓  | 1       |

`fail[4] = 1` → answer = `s.substr(0, 1)` = **"l"** ✓

### C++ Implementation
```cpp
string longestPrefix(string s) {
    int n = s.length();
    vector<int> fail(n, 0);

    for (int i = 1; i < n; i++) {
        int j = fail[i - 1];                        // start from best known match
        while (j > 0 && s[i] != s[j]) {
            j = fail[j - 1];                        // fall back to shorter match
        }
        if (s[i] == s[j]) {
            j++;                                    // extend match
        }
        fail[i] = j;
    }

    return s.substr(0, fail[n - 1]);
}
```

### Why the Fallback Works
When a mismatch happens at position `j` in the pattern, we know `s[0..j-1]` matched. The longest prefix of `s[0..j-1]` that is also its suffix is `fail[j-1]`. That suffix is already a prefix of `s`, so we can restart matching from position `fail[j-1]` without rescanning the already matched portion — this is what makes KMP O(n).

### Complexity
- **Time**: O(n) — each character is processed at most twice (advance + fallback)
- **Space**: O(n) for the `fail` array

---

## Solution 3: Rolling Hash

### Idea
Build a prefix hash from the **left** and a suffix hash from the **right** simultaneously in a single pass. At each step `i` (0-indexed, from 0 to n-2):
- `prefix_hash` represents `s[0..i]`
- `suffix_hash` represents `s[n-1-i..n-1]`

Whenever the two hashes are equal, `s[0..i]` is a happy prefix candidate. We keep updating the answer with the longest such `i`.

### Hash Design
Use a polynomial hash with base `B` and modulus `MOD`:
- **Prefix** (left-to-right): `prefix_hash = prefix_hash * B + val(s[i])`
- **Suffix** (right-to-left): `suffix_hash = suffix_hash + val(s[n-1-i]) * power`
  where `power = B^i`

Both represent length-(i+1) strings as polynomials evaluated at B. The suffix is built with the lowest power assigned to the rightmost character, which mirrors exactly the prefix polynomial ordering.

### Example Trace — `s = "ababab"`, B=31, showing hash conceptually

| i | Prefix covers | Suffix covers | Hashes equal? | ans_len |
|---|---------------|---------------|---------------|---------|
| 0 | "a"           | "b"           | ✗             | 0       |
| 1 | "ab"          | "ab"          | ✓             | 2       |
| 2 | "aba"         | "bab"         | ✗             | 2       |
| 3 | "abab"        | "abab"        | ✓             | 4       |
| 4 | "ababa"       | "babab"       | ✗             | 4       |

Answer = `s.substr(0, 4)` = **"abab"** ✓

### C++ Implementation
```cpp
string longestPrefix(string s) {
    int n = s.length();
    const long long MOD1 = 1e9 + 7, MOD2 = 1e9 + 9;
    const long long B1 = 31, B2 = 37;

    long long ph1 = 0, ph2 = 0;   // prefix hashes
    long long sh1 = 0, sh2 = 0;   // suffix hashes
    long long pw1 = 1, pw2 = 1;   // current power of base

    int ans_len = 0;

    for (int i = 0; i < n - 1; i++) {
        int lc = s[i] - 'a' + 1;          // left character value
        int rc = s[n - 1 - i] - 'a' + 1;  // right character value

        ph1 = (ph1 * B1 + lc) % MOD1;
        ph2 = (ph2 * B2 + lc) % MOD2;

        sh1 = (sh1 + rc * pw1) % MOD1;
        sh2 = (sh2 + rc * pw2) % MOD2;

        pw1 = pw1 * B1 % MOD1;
        pw2 = pw2 * B2 % MOD2;

        if (ph1 == sh1 && ph2 == sh2) {
            ans_len = i + 1;               // length of current prefix/suffix
        }
    }

    return s.substr(0, ans_len);
}
```

> **Note on double hashing**: Using two independent hash functions (different bases and moduli) reduces the collision probability to negligibly small values (~10⁻¹⁸), making this effectively collision-free in practice.

### Complexity
- **Time**: O(n) — single linear pass
- **Space**: O(1) — only a constant number of hash variables

---

## Solution 4: Z-Function

### Idea
The Z-array `z[i]` gives the length of the longest substring starting at position `i` that is also a prefix of `s`. For the purposes of this problem:

A happy prefix of length `L` exists if and only if there is some position `i` such that:
- `z[i] == L` (the substring starting at `i` matches the first `L` characters of `s`)
- `i + z[i] == n` (the matched substring reaches exactly the end of `s`, making it a suffix)

We scan all positions and take the maximum qualifying `z[i]`.

### Building the Z-Array (Linear Time)
Maintain a window `[l, r)` — the rightmost interval where a prefix match is known.
- For `i < r`: `z[i] >= min(r - i, z[i - l])` (reuse known match)
- Extend the match naively while `s[z[i]] == s[i + z[i]]`
- Update `[l, r)` if `i + z[i]` exceeds `r`

### Example Trace — `s = "ababab"` (n=6)
| i | z[i] | i + z[i] | == n? |
|---|------|----------|-------|
| 1 | 0    | 1        | ✗     |
| 2 | 4    | 6        | ✓     |
| 3 | 0    | 3        | ✗     |
| 4 | 2    | 6        | ✓     |
| 5 | 0    | 5        | ✗     |

Qualifying positions: `i=2` (z=4), `i=4` (z=2). Maximum = 4 → **"abab"** ✓

### C++ Implementation
```cpp
string longestPrefix(string s) {
    int n = s.length();
    vector<int> z(n, 0);

    // Build Z-array
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i < r) {
            z[i] = min(r - i, z[i - l]);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }

    // Find the maximum z[i] where the match reaches the end of the string
    int ans_len = 0;
    for (int i = 1; i < n; i++) {
        if (i + z[i] == n) {
            ans_len = max(ans_len, z[i]);
        }
    }

    return s.substr(0, ans_len);
}
```

### Complexity
- **Time**: O(n) — each character is visited at most twice by the Z-array construction
- **Space**: O(n) for the Z-array

---

## Comparison of Solutions

| Solution          | Time  | Space | Notes                                               |
|-------------------|-------|-------|-----------------------------------------------------|
| Brute Force       | O(n²) | O(n)  | Simple but too slow for n=10⁵                       |
| KMP Failure Func  | O(n)  | O(n)  | Classic, elegant, directly solves the problem       |
| Rolling Hash      | O(n)  | O(1)  | Minimal space; use double hashing to avoid collisions |
| Z-Function        | O(n)  | O(n)  | Natural fit; slightly more indirect than KMP        |

**Recommended**: The **KMP Failure Function** is the most direct and well-known solution for this problem, as the definition of `fail[n-1]` is literally the answer.

---

## Tags

string, KMP, failure function, prefix function, rolling hash, Z-function, string hashing
