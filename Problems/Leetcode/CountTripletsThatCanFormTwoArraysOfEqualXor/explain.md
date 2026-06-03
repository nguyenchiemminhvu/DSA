## Problem

https://leetcode.com/problems/count-triplets-that-can-form-two-arrays-of-equal-xor/description/

Given an integer array `arr`, count the number of triplets `(i, j, k)` such that:
- `0 <= i < j <= k < arr.length`
- `a = arr[i] ^ arr[i+1] ^ ... ^ arr[j-1]`
- `b = arr[j] ^ arr[j+1] ^ ... ^ arr[k]`
- `a == b`

---

## Observations

**1. If `a == b`, then `a ^ b == 0`**

XOR of identical values is 0. So `a == b` implies `a ^ b = 0`, which means:

```
arr[i] ^ arr[i+1] ^ ... ^ arr[j-1] ^ arr[j] ^ ... ^ arr[k] == 0
```

The entire subarray `arr[i..k]` XORs to zero. This is the key insight.

**Consequence:** For any subarray `[i, k]` with `XOR == 0`, *every* `j` in the range `(i, k]` is a valid split point, giving `(k - i)` valid triplets.

**2. XOR is self-inverse: `x ^ x == 0`**

If we define `prefix[t] = arr[0] ^ arr[1] ^ ... ^ arr[t-1]` (with `prefix[0] = 0`), then:
- `XOR(arr[i..k]) = prefix[k+1] ^ prefix[i]`
- We need `prefix[k+1] ^ prefix[i] == 0`, i.e., `prefix[k+1] == prefix[i]`

---

## Solution Explained

The provided solution uses a **two-pass hash map** approach, building a map of XOR values for subarrays starting at each index, then querying it.

### Pass 1 — Build `prefix_xor`

```python
for i in range(n):
    x = 0
    for j in range(i, n):
        x ^= arr[j]
        prefix_xor[i][x] += 1
```

`prefix_xor[start][x]` = number of ending indices `end >= start` such that `XOR(arr[start..end]) == x`.

### Pass 2 — Count matching pairs

```python
for i in range(n - 1):
    x = 0
    for j in range(i, -1, -1):
        x ^= arr[j]
        res += prefix_xor[i + 1][x]
```

Here `i` acts as the **split boundary** (problem's `j - 1`), and we scan backwards through all possible left-start positions `j`.

- `x = arr[j] ^ arr[j+1] ^ ... ^ arr[i]` → this is the value of `a`
- `prefix_xor[i+1][x]` → number of `k >= i+1` such that `XOR(arr[i+1..k]) == x` → valid values of `b`

When both equal `x`, we have `a == b`, so each such `k` contributes 1 valid triplet `(j, i+1, k)`.

### Walkthrough: `arr = [2, 3, 1, 6, 7]`

| Triplet     | a              | b              | a == b? |
|-------------|----------------|----------------|---------|
| (0, 1, 2)   | 2              | 3^1 = 2        | ✅      |
| (0, 2, 2)   | 2^3 = 1        | 1              | ✅      |
| (2, 3, 4)   | 1              | 6^7 = 1        | ✅      |
| (2, 4, 4)   | 1^6 = 7        | 7              | ✅      |

Output: **4**

---

## Complexity

| | Value |
|---|---|
| Time  | O(n²) — two nested loops |
| Space | O(n²) — the `prefix_xor` map stores up to n² entries |

---

## Alternative O(n²) solution (cleaner)

Using the observation that `XOR(arr[i..k]) == 0` means any `j` in `(i, k]` is valid:

```python
def countTriplets(arr):
    n = len(arr)
    res = 0
    for i in range(n - 1):
        x = arr[i]
        for k in range(i + 1, n):
            x ^= arr[k]
            if x == 0:
                res += k - i   # all j in (i, k] are valid
    return res
```

This is simpler, has the same time complexity O(n²), and uses O(1) extra space.
