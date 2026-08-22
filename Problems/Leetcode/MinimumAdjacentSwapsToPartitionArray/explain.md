## Problem

https://leetcode.com/problems/minimum-adjacent-swaps-to-partition-array/description/

Given `nums` and `a < b`, make the array **good** in minimum adjacent swaps (mod 10⁹+7).  
A good array splits into three contiguous parts: `[< a] | [a..b] | [> b]` (any part may be empty).

---

## Key Insight

Label every element by its **category**:
- **L** (Low):  value `< a`
- **M** (Mid):  value `∈ [a, b]`
- **H** (High): value `> b`

The target arrangement is `L...L M...M H...H`.  
Minimum adjacent swaps to reach any sorted order = **number of inversions** in the label sequence.

An inversion is any pair `(i, j)` with `i < j` but `category[i] > category[j]`:
- M before L → inversion
- H before L → inversion
- H before M → inversion

Relative order *within* each category is irrelevant (no inversion among same-category elements).

---

## Ideas

### Idea 1 — O(n) Prefix Count (Optimal)

Because there are only 3 categories, we can count inversions in a single left-to-right pass using running counters.

For each element at position `i`:
- If **H**: increment `count_h`
- If **M**: `inversions += count_h` (every H seen so far is before this M); increment `count_m`
- If **L**: `inversions += count_m + count_h` (every M and H seen so far is before this L)

**Complexity:** O(n) time, O(1) space

**Trace — Example 1:** `nums=[1,3,2,4,5,6]`, a=3, b=4  
Labels: `L M L M H H`

| pos | label | count_m | count_h | inv added | total |
|-----|-------|---------|---------|-----------|-------|
| 0   | L     | 0       | 0       | 0         | 0     |
| 1   | M     | 0→1     | 0       | 0         | 0     |
| 2   | L     | 1       | 0       | 1         | 1     |
| 3   | M     | 1→2     | 0       | 0         | 1     |
| 4   | H     | 2       | 0→1     | —         | 1     |
| 5   | H     | 2       | 1→2     | —         | 1     |

Output: **1** ✓

**Trace — Example 2:** `nums=[9,7,5,3]`, a=4, b=8  
Labels: `H M M L`

| pos | label | count_m | count_h | inv added | total |
|-----|-------|---------|---------|-----------|-------|
| 0   | H     | 0       | 0→1     | —         | 0     |
| 1   | M     | 0→1     | 1       | 1         | 1     |
| 2   | M     | 1→2     | 1       | 1         | 2     |
| 3   | L     | 2       | 1       | 3         | 5     |

Output: **5** ✓

---

### Idea 2 — Merge Sort Inversion Count

Encode each element as its category rank (0/1/2), then count inversions via merge sort.  
**Complexity:** O(n log n) time, O(n) space — overkill given Idea 1, but generalizes.

---

### Idea 3 — BIT / Fenwick Tree

Process right to left; for each element query the BIT for count of smaller-category elements seen so far.  
**Complexity:** O(n log n) — also overkill here.

---

## Solution (Idea 1)

```python
MOD = 10**9 + 7

class Solution:
    def minSwaps(self, nums: list[int], a: int, b: int) -> int:
        count_m = count_h = inversions = 0
        for x in nums:
            if x > b:
                count_h += 1
            elif x >= a:        # x in [a, b]
                inversions += count_h
                count_m += 1
            else:               # x < a
                inversions += count_m + count_h
        return inversions % MOD
```

