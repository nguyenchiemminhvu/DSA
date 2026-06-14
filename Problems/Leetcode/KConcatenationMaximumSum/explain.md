## Problem

https://leetcode.com/problems/k-concatenation-maximum-sum/description

```
Given an integer array arr and an integer k, modify the array by repeating it k times.

For example, if arr = [1, 2] and k = 3 then the modified array will be [1, 2, 1, 2, 1, 2].

Return the maximum sub-array sum in the modified array. Note that the length of the sub-array
can be 0 and its sum in that case is 0.

As the answer can be very large, return the answer modulo 10^9 + 7.

Example 1:
  Input: arr = [1,2], k = 3
  Output: 9

Example 2:
  Input: arr = [1,-2,1], k = 5
  Output: 2

Example 3:
  Input: arr = [-1,-2], k = 7
  Output: 0

Constraints:
  1 <= arr.length <= 10^5
  1 <= k <= 10^5
  -10^4 <= arr[i] <= 10^4
```

## Observations

1. **Brute force is infeasible**: The repeated array can have up to $10^{10}$ elements ($10^5 \times 10^5$), so we cannot literally construct it and run Kadane's algorithm on it.

2. **The optimal subarray spans at most 2 full copies when `total <= 0`**: If the total sum of `arr` is non-positive, including more repetitions of `arr` in the middle of a subarray can only hurt (or at best not help). So the answer lives entirely within 2 consecutive copies.

3. **When `total > 0`, adding middle copies is always beneficial**: If `total > 0`, any subarray that crosses a copy boundary benefits from including as many full intermediate copies as possible. The best subarray looks like:
   ```
   [best suffix of copy 1] + [full copies 2..k-1] + [best prefix of copy k]
   ```
   which equals `second_max_all + (k - 2) * total`, where `second_max_all` is the best subarray over 2 copies.

4. **Kadane's algorithm can be "chained" across copies**: Kadane maintains a `cur_max` representing the maximum subarray sum ending at the current position. After one full pass over `arr`, `cur_max` captures the best suffix ending value. Starting the second pass with this `cur_max` naturally continues subarrays from copy 1 into copy 2, covering the suffix + prefix overlap without explicitly concatenating the arrays.

5. **`k == 1` is a special case**: Running Kadane once over `arr` gives the answer directly, since there is no second copy to connect to.

## Solution

### Approach: Chained Kadane's Algorithm

The key insight is to run Kadane's algorithm **twice** over `arr`, passing the ending state of the first run as the starting state of the second run. This simulates the concatenation of two copies without building the actual array.

**Step 1 — Single pass (copy 1):**

Run Kadane starting from `cur_max = 0`. After the pass:
- `first_max_all`: best subarray sum found in one copy.
- `first_cur_max`: the running maximum subarray sum ending at the last element, i.e., the best suffix of one copy carried forward.

**Step 2 — Handle `k == 1`:**

Return `first_max_all % mod` immediately.

**Step 3 — Second pass (copy 2), starting from `first_cur_max`:**

Run Kadane again over `arr`, but initialise `cur_max = first_cur_max`. Because Kadane's recurrence is:
```
cur_max = max(val, cur_max + val)
```
seeding it with `first_cur_max` means the algorithm can extend a subarray that began in copy 1 into copy 2. After the pass:
- `second_max_all`: best subarray spanning at most 2 copies.

**Step 4 — Decide based on `total`:**

- If `total <= 0`: adding more copies in the middle is never beneficial → return `second_max_all % mod`.
- If `total > 0`: the `k - 2` middle copies each contribute `total` → return `(second_max_all + (k - 2) * total) % mod`.

```python
class Solution:
    def kConcatenationMaxSum(self, arr: List[int], k: int) -> int:
        mod = 10**9 + 7

        def kadane(cur_max, max_all):
            for val in arr:
                cur_max = max(val, cur_max + val)
                max_all = max(max_all, cur_max)
            return cur_max, max_all

        total = sum(arr)

        first_cur_max, first_max_all = kadane(0, 0)

        if k == 1:
            return first_max_all % mod

        second_cur_max, second_max_all = kadane(first_cur_max, first_max_all)

        if total <= 0:
            return second_max_all % mod

        return (second_max_all + (k - 2) * total) % mod
```

**Complexity:** $O(n)$ time, $O(1)$ extra space.
