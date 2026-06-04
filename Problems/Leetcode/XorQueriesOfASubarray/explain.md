## Problem

https://leetcode.com/problems/xor-queries-of-a-subarray/description/

Given an array `arr` of positive integers and a list of `queries`, where each query `[left, right]` asks for the XOR of all elements from index `left` to `right` (inclusive), return an array of answers for each query.

---

## Observations

- **Brute force** computes XOR for each query from scratch → $O(n)$ per query → $O(n \cdot q)$ total → **TLE** for large inputs.

- **Precompute all pairs** `mp[i][j]` → $O(n^2)$ space → **MLE** for large inputs.

- XOR has a useful cancellation property: `a ^ a = 0`. This means if we define a **prefix XOR** array:

$$\text{prefix}[i] = \text{arr}[0] \oplus \text{arr}[1] \oplus \cdots \oplus \text{arr}[i-1]$$

Then the XOR of a subarray `arr[left..right]` can be derived as:

$$\text{XOR}(left, right) = \text{prefix}[right+1] \oplus \text{prefix}[left]$$

  This works because the elements before index `left` appear **twice** (once in each prefix), and `x ^ x = 0`, so they cancel out — leaving only `arr[left..right]`.

---

## Solution — Prefix XOR

**Build the prefix XOR array:**

```
prefix_xor[0] = 0
prefix_xor[i+1] = prefix_xor[i] ^ arr[i]
```

**Answer each query in O(1):**

```
answer[i] = prefix_xor[right + 1] ^ prefix_xor[left]
```

**Example walkthrough** with `arr = [1, 3, 4, 8]`:

| i | arr[i] | prefix_xor[i+1] |
|---|--------|-----------------|
| 0 | 1      | 0 ^ 1 = 1       |
| 1 | 3      | 1 ^ 3 = 2       |
| 2 | 4      | 2 ^ 4 = 6       |
| 3 | 8      | 6 ^ 8 = 14      |

So `prefix_xor = [0, 1, 2, 6, 14]`.

- `[0,1]` → `prefix[2] ^ prefix[0]` = `2 ^ 0` = **2** ✓  
- `[1,2]` → `prefix[3] ^ prefix[1]` = `6 ^ 1` = **7** ✓  
- `[0,3]` → `prefix[4] ^ prefix[0]` = `14 ^ 0` = **14** ✓  
- `[3,3]` → `prefix[4] ^ prefix[3]` = `14 ^ 6` = **8** ✓  

**Complexity:**
- Time: $O(n + q)$ — one pass to build prefix XOR, $O(1)$ per query
- Space: $O(n)$ for the prefix XOR array

```python
class Solution:
    def xorQueries(self, arr: List[int], queries: List[List[int]]) -> List[int]:
        n = len(arr)

        prefix_xor = [0] * (n + 1)
        for i in range(n):
            prefix_xor[i + 1] = prefix_xor[i] ^ arr[i]
        
        res = []
        for left, right in queries:
            x = prefix_xor[right + 1] ^ prefix_xor[left]
            res.append(x)
        return res
```
