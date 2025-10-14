## Problem

https://leetcode.com/problems/find-the-original-array-of-prefix-xor/

```
You are given an integer array pref of size n. Find and return the array arr of size n that satisfies:

pref[i] = arr[0] ^ arr[1] ^ ... ^ arr[i].
Note that ^ denotes the bitwise-xor operation.

It can be proven that the answer is unique.

Example 1:

Input: pref = [5,2,0,3,1]
Output: [5,7,2,3,2]
Explanation: From the array [5,7,2,3,2] we have the following:
- pref[0] = 5.
- pref[1] = 5 ^ 7 = 2.
- pref[2] = 5 ^ 7 ^ 2 = 0.
- pref[3] = 5 ^ 7 ^ 2 ^ 3 = 3.
- pref[4] = 5 ^ 7 ^ 2 ^ 3 ^ 2 = 1.

Example 2:

Input: pref = [13]
Output: [13]
Explanation: We have pref[0] = arr[0] = 13.

Constraints:

1 <= pref.length <= 105
0 <= pref[i] <= 106
```

## Observations

### Key Mathematical Property of XOR

The solution relies on a fundamental property of XOR operation:
- **Self-cancellation**: `a ^ a = 0`
- **Identity**: `a ^ 0 = a`
- **Reversibility**: If `c = a ^ b`, then `a = c ^ b` and `b = c ^ a`

### Problem Analysis

Given:
- `pref[i] = arr[0] ^ arr[1] ^ ... ^ arr[i]`

We need to find `arr[i]` for each position.

**For position i:**
- `pref[i] = arr[0] ^ arr[1] ^ ... ^ arr[i]`
- `pref[i-1] = arr[0] ^ arr[1] ^ ... ^ arr[i-1]`

**Deriving arr[i]:**
```
pref[i] ^ pref[i-1] = (arr[0] ^ arr[1] ^ ... ^ arr[i]) ^ (arr[0] ^ arr[1] ^ ... ^ arr[i-1])
                     = arr[i]  (all previous elements cancel out)
```

Therefore: **`arr[i] = pref[i] ^ pref[i-1]`**

### Edge Cases

- **Base case**: `arr[0] = pref[0]` (no previous elements to XOR with)
- **Single element**: If `pref = [13]`, then `arr = [13]`

### Algorithm Walkthrough

Example: `pref = [5, 2, 0, 3, 1]`

| Step | i | Calculation | arr[i] | Current XOR | arr |
|------|---|-------------|--------|-------------|-----|
| 1 | 0 | arr[0] = pref[0] | 5 | 5 | [5] |
| 2 | 1 | 5 ^ 2 | 7 | 5 ^ 7 = 2 | [5, 7] |
| 3 | 2 | 2 ^ 0 | 2 | 2 ^ 2 = 0 | [5, 7, 2] |
| 4 | 3 | 0 ^ 3 | 3 | 0 ^ 3 = 3 | [5, 7, 2, 3] |
| 5 | 4 | 3 ^ 1 | 2 | 3 ^ 2 = 1 | [5, 7, 2, 3, 2] |

### Complexity Analysis

- **Time Complexity**: O(n) - single pass through the array
- **Space Complexity**: O(n) - for the output array (O(1) auxiliary space)

## Tags

array, bit manipulation