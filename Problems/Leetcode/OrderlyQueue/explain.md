## Problem

https://leetcode.com/problems/orderly-queue/description/

You are given a string `s` and an integer `k`. You can choose **one of the first `k` letters** of `s` and **append it at the end** of the string.

Return the **lexicographically smallest** string you could have after applying the mentioned step any number of moves.

**Example 1:**
```
Input:  s = "cba", k = 1
Output: "acb"

Explanation:
Move 1: take s[0]='c', append → "bac"
Move 2: take s[0]='b', append → "acb"
```

**Example 2:**
```
Input:  s = "baaca", k = 3
Output: "aaabc"

Explanation:
Move 1: take s[0]='b', append → "aacab"
Move 2: take s[2]='c', append → "aaabc"
```

**Constraints:**
- `1 <= k <= s.length <= 1000`
- `s` consists of lowercase English letters.

---

## Observations

1. **What does one move do?**  
   A move picks some index `i` (where `0 <= i < k`) and rotates the character `s[i]` to the back, shifting everything between `i` and the end one position to the left.

2. **When `k = 1`:**  
   - You can only ever take `s[0]` and move it to the end.  
   - This is a **pure left rotation** of the whole string.  
   - After at most `n` rotations you cycle back to the original string.  
   - The best you can achieve is the **lexicographically smallest rotation** of `s`.

3. **When `k >= 2`:**  
   - You have enough freedom to perform **arbitrary permutations** of the string.  
   - With two positions accessible, you can implement a *bubble-sort-like* swap of any two adjacent characters by a sequence of moves.  
   - Because any permutation can be decomposed into adjacent swaps, you can rearrange `s` into **any order**.  
   - The answer is therefore simply the **sorted string**.

4. **Why does `k >= 2` unlock full sorting?**  
   - Consider characters at positions 0 and 1. You can move `s[1]` to the back, or move `s[0]` to the back.  
   - By choosing carefully between moving index 0 vs index 1, you can effectively bubble a small character toward the front, eventually sorting the entire string.  
   - A formal proof uses the fact that with access to two adjacent "slots," the group of reachable permutations is the full symmetric group $S_n$.

---

## Approach & Explanation

### Case 1 — `k = 1`: Smallest Rotation

Since only pure left rotations are allowed, generate all `n` rotations of `s` and return the minimum.

```
best = s
for i in 1 .. n-1:
    rotation = s[i:] + s[:i]
    best = min(best, rotation)
return best
```

- **Time:** $O(n^2)$ — $n$ rotations, each comparison $O(n)$.  
- **Space:** $O(n)$.

### Case 2 — `k >= 2`: Sort the String

Since any permutation is reachable, the answer is just `sort(s)`.

```
return sorted(s)
```

- **Time:** $O(n \log n)$.  
- **Space:** $O(n)$.

### Combined Solution

```cpp
string orderlyQueue(string s, int k) {
    if (k == 1) {
        // Find the lexicographically smallest rotation
        string best = s;
        int n = s.size();
        for (int i = 1; i < n; i++) {
            string rotation = s.substr(i) + s.substr(0, i);
            best = min(best, rotation);
        }
        return best;
    } else {
        // k >= 2: full sorting is possible
        sort(s.begin(), s.end());
        return s;
    }
}
```

### Complexity Summary

| Case    | Time         | Space  |
|---------|--------------|--------|
| `k = 1` | $O(n^2)$     | $O(n)$ |
| `k ≥ 2` | $O(n \log n)$| $O(n)$ |

---

## Key Insight (One-liner)

> The problem has a **sharp phase transition** at `k = 1` vs `k ≥ 2`:  
> - `k = 1` → only rotations are possible → find the **minimum rotation**.  
> - `k ≥ 2` → all permutations are reachable → return the **sorted string**.

