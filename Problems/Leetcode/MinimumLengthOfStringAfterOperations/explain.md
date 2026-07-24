## Problem

https://leetcode.com/problems/minimum-length-of-string-after-operations/description/

Given a string `s`, you can repeatedly perform the following operation:
- Choose index `i` such that `s[i]` has at least one equal character to its **left** and at least one to its **right**.
- Delete the **closest** equal character on each side of `i` (removes exactly 2 characters per operation).

Return the **minimum length** of the resulting string.

---

## Observations

1. **Each operation removes exactly 2 characters** — always a pair of the same character flanking a chosen index.

2. **Operations on different characters are independent.** The minimum for each character can be reasoned about in isolation, and the final answer is the sum across all characters.

3. **For a character with frequency `f`:**
   - An operation requires at least 3 occurrences (left, chosen, right), and eliminates 2.
   - Applying the operation repeatedly: `f → f-2 → f-4 → ...`
   - If `f` is **odd**: we can reduce down to **1** (can always peel 2 off while ≥ 3).
   - If `f` is **even**: we can reduce down to **2** (stop when only 2 remain, since 2 < 3).

4. **Minimum contribution per character:**
   - `freq % 2 == 1` → contributes **1**
   - `freq % 2 == 0` → contributes **2**

5. **Verification with examples:**
   - `"abaacbcbb"`: `a`=3(odd→1), `b`=4(even→2), `c`=2(even→2) → **5** ✓
   - `"aa"`: `a`=2(even→2) → **2** ✓

---

## Approach

**Frequency Counting — O(n) time, O(1) space**

1. Count the frequency of each character in `s`.
2. For each character:
   - If frequency is odd, add `1` to the answer.
   - If frequency is even, add `2` to the answer.
3. Return the total.

```cpp
int minimumLength(string s) {
    int freq[26] = {};
    for (char c : s) freq[c - 'a']++;
    int result = 0;
    for (int f : freq) {
        if (f == 0) continue;
        result += (f % 2 == 1) ? 1 : 2;
    }
    return result;
}
```
