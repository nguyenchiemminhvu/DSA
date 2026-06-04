## Problem

https://leetcode.com/problems/count-number-of-nice-subarrays/description/

Given an array of integers `nums` and an integer `k`, return the number of **nice** subarrays — continuous subarrays that contain exactly `k` odd numbers.

**Examples:**
- `nums = [1,1,2,1,1], k = 3` → `2` (subarrays `[1,1,2,1]` and `[1,2,1,1]`)
- `nums = [2,4,6], k = 1` → `0` (no odd numbers)
- `nums = [2,2,2,1,2,2,1,2,2,2], k = 2` → `16`

**Constraints:** `1 <= nums.length <= 50000`, `1 <= nums[i] <= 10^5`, `1 <= k <= nums.length`

---

## Observations

1. **Only odd positions matter.** Even numbers do not affect the odd count in a subarray, so we can reduce the problem by recording only the indices of odd numbers.

2. **A valid subarray must span exactly k consecutive odd numbers.** If we fix which k odd numbers are "included" (say the `io-k+1`-th through `io`-th odd numbers in the array), the left boundary of the subarray must lie somewhere between the previous odd number (exclusive) and the leftmost of the k chosen odds (inclusive), and the right boundary must lie somewhere between the rightmost of the k chosen odds (inclusive) and the next odd number (exclusive).

3. **Counting extensions.** For a fixed window of k odds:
   - Let `L` = index of the leftmost odd in the window, `R` = index of the rightmost odd.
   - The left boundary can slide left through consecutive even numbers before `L` (including `L` itself): `count_left` choices.
   - The right boundary can slide right through consecutive even numbers after `R` (including `R` itself): `count_right` choices.
   - Each combination of left and right boundary gives one valid nice subarray, so the contribution is `count_left * count_right`.

4. **Total result** is the sum of `count_left * count_right` over all valid windows of k consecutive odds.

---

## Solution

```python
class Solution:
    def numberOfSubarrays(self, nums: List[int], k: int) -> int:
        n = len(nums)

        # Step 1: Collect indices of all odd numbers.
        odd_idx = []
        for i in range(n):
            if nums[i] & 1:
                odd_idx.append(i)

        no = len(odd_idx)
        if no < k:
            return 0  # Not enough odd numbers to form any nice subarray.

        res = 0

        # Step 2: Slide a window of size k over the odd indices.
        for io in range(k - 1, no):
            # The k-th odd (rightmost) is at odd_idx[io],
            # the 1st odd (leftmost) is at odd_idx[io - k + 1].
            l, r = odd_idx[io - k + 1], odd_idx[io]

            # Count how far left we can extend (through even numbers).
            count_left = 1
            while l - 1 >= 0 and nums[l - 1] % 2 == 0:
                l -= 1
                count_left += 1

            # Count how far right we can extend (through even numbers).
            count_right = 1
            while r + 1 < n and nums[r + 1] % 2 == 0:
                r += 1
                count_right += 1

            res += count_left * count_right

        return res
```

### Walkthrough with Example 3

`nums = [2,2,2,1,2,2,1,2,2,2], k = 2`

Odd indices: `[3, 6]` → only one window of size 2: `(3, 6)`.

- **Left extension from index 3:** `nums[2]=2`, `nums[1]=2`, `nums[0]=2` → `count_left = 4`
- **Right extension from index 6:** `nums[7]=2`, `nums[8]=2`, `nums[9]=2` → `count_right = 4`
- Contribution: `4 * 4 = 16` ✓

### Complexity

| | |
|---|---|
| Time | $O(n)$ — collecting odd indices is $O(n)$; each element is visited at most once across all extension loops in aggregate |
| Space | $O(n)$ — storage for odd indices |
