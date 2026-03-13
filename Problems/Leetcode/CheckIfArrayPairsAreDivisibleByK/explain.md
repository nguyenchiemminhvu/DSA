## Problem

https://leetcode.com/problems/check-if-array-pairs-are-divisible-by-k/description/

Given an array of integers `arr` of even length `n` and an integer `k`, divide the array into exactly `n / 2` pairs such that the sum of each pair is divisible by `k`. Return `true` if you can find a way to do that, or `false` otherwise.

**Example 1:**
```
Input: arr = [1,2,3,4,5,10,6,7,8,9], k = 5
Output: true
Explanation: Pairs are (1,9),(2,8),(3,7),(4,6) and (5,10).
```

**Example 2:**
```
Input: arr = [1,2,3,4,5,6], k = 7
Output: true
Explanation: Pairs are (1,6),(2,5) and (3,4).
```

**Example 3:**
```
Input: arr = [1,2,3,4,5,6], k = 10
Output: false
Explanation: No valid pairing exists.
```

**Constraints:**
- `1 <= n <= 10^5`, `n` is even
- `-10^9 <= arr[i] <= 10^9`
- `1 <= k <= 10^5`

## Observations

1. **Pair sum divisibility reduces to remainder complementarity.** For a pair `(a, b)` to satisfy `(a + b) % k == 0`, their remainders mod `k` must sum to `k` (or both be `0`). That is, if `a % k == r`, then `b % k` must equal `k - r`.

2. **Remainder 0 is a special case.** Elements with `a % k == 0` can only pair with other elements with remainder `0`. So `freq[0]` must be even.

3. **Remainder `k/2` (when `k` is even) is also self-complementary** because `k - k/2 == k/2`. However, an explicit even-count check is not needed: since `n` is even and `freq[0]` must be even, and all other pairs `(i, k-i)` must match, `freq[k/2]` is forced to be even automatically.

4. **Handling negative numbers.** Python's `%` operator can return negative results for negative inputs. Using `((val % k) + k) % k` ensures the remainder is always in `[0, k-1]`.

5. **For all remainders `i` in `[1, k-1]`**, `freq[i]` must equal `freq[k - i]`, because every element with remainder `i` must be paired with an element with remainder `k - i`.

## Solution

```python
from collections import defaultdict

class Solution:
    def canArrange(self, arr: List[int], k: int) -> bool:
        freq = defaultdict(int)
        for val in arr:
            rem = ((val % k) + k) % k   # normalize to [0, k-1] for negative values
            freq[rem] += 1
        
        # Elements with remainder 0 must pair among themselves → count must be even
        if freq[0] & 1:
            return False
        
        # For every remainder i, there must be an equal count of remainder k-i
        # (when i == k-i, the check is trivially true and freq[i] is even by parity of n)
        for i in range(1, k):
            if freq[i] != freq[k - i]:
                return False
        
        return True
```

**Step-by-step walkthrough (Example 1: arr = [1,2,3,4,5,10,6,7,8,9], k = 5):**

| value | remainder mod 5 |
|-------|-----------------|
| 1     | 1               |
| 2     | 2               |
| 3     | 3               |
| 4     | 4               |
| 5     | 0               |
| 10    | 0               |
| 6     | 1               |
| 7     | 2               |
| 8     | 3               |
| 9     | 4               |

`freq = {0:2, 1:2, 2:2, 3:2, 4:2}`

- `freq[0] = 2` (even) ✓
- `freq[1] == freq[4]` → `2 == 2` ✓
- `freq[2] == freq[3]` → `2 == 2` ✓

→ `true`

**Complexity:**
- **Time:** O(n + k) — O(n) to build the frequency map, O(k) to verify all remainder pairs.
- **Space:** O(k) — at most `k` distinct remainders stored.

# Tags

`Hash Map` `Array` `Math`

