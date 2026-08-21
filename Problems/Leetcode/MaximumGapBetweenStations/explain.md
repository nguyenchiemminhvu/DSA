## Problem

https://leetcode.com/problems/maximum-gap-between-stations/description/

Given two strings `skill` (length `n`) and `station` (length `m`), assign every worker `i` to a distinct station `j_i` such that:
- `station[j_i] == skill[i]` for every worker `i`
- Station indices are strictly increasing: `j_0 < j_1 < ... < j_{n-1}`

The **gap** of an assignment is `max(j_i - j_{i-1})` for consecutive workers. Return the **maximum possible gap** over all valid assignments.

---

## Ideas

### Key Observation

We want to **maximize** the largest gap between any two consecutive assigned station indices. The idea is to concentrate as much "slack" as possible into a single interval between two consecutive workers.

For a pair of consecutive workers `(i-1, i)`, the maximum achievable gap when we "stretch" between them is:
- Assign workers `0 .. i-1` as **early** (left) as possible
- Assign workers `i .. n-1` as **late** (right) as possible
- The gap = `(latest station for worker i)` − `(earliest station for worker i-1)`

### Algorithm: Prefix-Earliest + Suffix-Latest

**Step 1 — Left-to-right pass (earliest positions):**

Build `pre[i]` = the minimum station index worker `i` can be assigned to, assuming all previous workers take the earliest possible station.

Scan `station` left-to-right with a pointer for `skill`. When `station[j] == skill[i]`, record `pre[i] = j` and advance the worker pointer.

**Step 2 — Right-to-left pass (latest positions):**

Build `suf[i]` = the maximum station index worker `i` can be assigned to, assuming all later workers take the latest possible station.

Scan `station` right-to-left with a pointer for `skill`. When `station[j] == skill[i]`, record `suf[i] = j` and move the worker pointer left.

**Step 3 — Compute answer:**

For each consecutive pair `(i-1, i)`:

$$\text{gap}_i = \text{suf}[i] - \text{pre}[i-1]$$

$$\text{answer} = \max_{1 \le i < n} \text{gap}_i$$

### Verification with Examples

**Example 1:** `skill = "aa"`, `station = "aaaa"`
- `pre = [0, 1]`, `suf = [2, 3]`
- gap at pair (0,1): `suf[1] - pre[0]` = 3 − 0 = **3** ✓

**Example 2:** `skill = "xyz"`, `station = "xyzz"`
- `pre = [0, 1, 2]`, `suf = [0, 1, 3]`
- gap at (0,1): `1 - 0 = 1`, gap at (1,2): `3 - 1 = 2` → **2** ✓

**Example 3:** `skill = "cbc"`, `station = "cbcdbc"`
- `pre = [0, 1, 2]`, `suf = [2, 4, 5]`
- gap at (0,1): `4 - 0 = 4`, gap at (1,2): `5 - 1 = 4` → **4** ✓

### Complexity

| | Value |
|---|---|
| Time | $O(n + m)$ |
| Space | $O(n)$ |
