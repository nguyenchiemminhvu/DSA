## Problem

https://leetcode.com/problems/groups-of-special-equivalent-strings/description/

You are given an array of strings of the same length `words`.

In one **move**, you can swap any two even indexed characters or any two odd indexed characters of a string `words[i]`.

Two strings `words[i]` and `words[j]` are **special-equivalent** if after any number of moves, `words[i] == words[j]`.

A **group of special-equivalent strings** from `words` is a non-empty subset of words such that every pair of strings in the group are special equivalent, and the group is the largest size possible.

Return the number of **groups of special-equivalent strings** from `words`.

**Example 1:**
```
Input: words = ["abcd","cdab","cbad","xyzz","zzxy","zzyx"]
Output: 3
```

**Example 2:**
```
Input: words = ["abc","acb","bac","bca","cab","cba"]
Output: 3
```

**Constraints:**
- `1 <= words.length <= 1000`
- `1 <= words[i].length <= 20`
- `words[i]` consist of lowercase English letters.
- All the strings are of the same length.

## Ideas

### Key Insight

Two strings are special-equivalent if and only if they have the same **multiset of even-indexed characters** and the same **multiset of odd-indexed characters**.

Since we can freely swap any two even-indexed characters among themselves, and any two odd-indexed characters among themselves, the only invariant is the sorted collection of even-position chars and the sorted collection of odd-position chars.

### Approach: Signature / Canonical Form

For each word, compute a **signature**:
- Extract characters at even indices (0, 2, 4, ...) → sort them
- Extract characters at odd indices (1, 3, 5, ...) → sort them
- Concatenate both sorted strings as a single key (e.g., separated by `#`)

Two words are special-equivalent iff their signatures are equal. So the answer is the number of **distinct signatures**.

**Example:**
- `"abcd"` → even: `"ac"` → sorted: `"ac"`, odd: `"bd"` → sorted: `"bd"` → key: `"ac#bd"`
- `"cdab"` → even: `"ca"` → sorted: `"ac"`, odd: `"db"` → sorted: `"bd"` → key: `"ac#bd"` ✓ same group

### Algorithm

1. For each word, compute its signature (sorted even chars + sorted odd chars).
2. Insert all signatures into a hash set.
3. Return the size of the set.

**Time Complexity:** $O(n \cdot L \log L)$ where $n$ = number of words, $L$ = word length (sorting each half).  
**Space Complexity:** $O(n \cdot L)$ for storing signatures.
