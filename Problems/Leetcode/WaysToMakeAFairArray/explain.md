## Problem

https://leetcode.com/problems/ways-to-make-a-fair-array/description/

Given an integer array `nums`, you can remove **exactly one** element at any index. After the removal, the remaining array is **fair** if:

> sum of odd-indexed values == sum of even-indexed values

Return the **count of indices** whose removal results in a fair array.

**Examples:**
- `nums = [2,1,6,4]` → Output: `1` (only removing index 1 gives a fair array)
- `nums = [1,1,1]` → Output: `3` (any removal is fair)
- `nums = [1,2,3]` → Output: `0` (no removal works)

**Constraints:** `1 <= nums.length <= 10^5`, `1 <= nums[i] <= 10^4`

---

## Solution: Prefix Sums (Left + Right)

### Key Insight

When we **remove index `i`**:
- Elements at indices `0 ... i-1` (the **left part**) keep their original positions and parity.
- Elements at indices `i+1 ... n-1` (the **right part**) each shift one position to the left, so their **parity flips**: odd ↔ even.

Therefore, the new even and odd sums after removing index `i` are:

$$\text{new\_even} = \underbrace{\text{left\_even}}_{\text{left part, keep parity}} + \underbrace{\text{right\_odd}}_{\text{right part, parity flips}}$$

$$\text{new\_odd} = \underbrace{\text{left\_odd}}_{\text{left part, keep parity}} + \underbrace{\text{right\_even}}_{\text{right part, parity flips}}$$

The array is fair when `new_even == new_odd`.

### Algorithm

**Step 1 — Precompute right-side sums:**  
Traverse right-to-left, storing for each index `i`:
- `right_odd[i]` = sum of all **odd-indexed** elements strictly to the **right** of `i`
- `right_even[i]` = sum of all **even-indexed** elements strictly to the **right** of `i`

**Step 2 — Sweep left-to-right, accumulating left-side sums:**  
Maintain running `odd_sum` and `even_sum` for elements already seen (left of `i`).  
At each index `i`, check the fairness condition **before** including `nums[i]`:

$$\text{left\_even} + \text{right\_odd}[i] == \text{left\_odd} + \text{right\_even}[i]$$

### Walkthrough — `nums = [2, 1, 6, 4]`

**Right-side precomputation (right-to-left):**

| i | nums[i] | right_even[i] | right_odd[i] |
|---|---------|--------------|-------------|
| 3 | 4       | 0            | 0           |
| 2 | 6       | 4            | 0           |
| 1 | 1       | 4+6=10... wait |             |

Let me trace carefully:

- i=3: `right_even[3]=0, right_odd[3]=0`; i is odd → `odd_sum += 4` → odd_sum=4
- i=2: `right_even[2]=0, right_odd[2]=4`; i is even → `even_sum += 6` → even_sum=6
- i=1: `right_even[1]=6, right_odd[1]=4`; i is odd → `odd_sum += 1` → odd_sum=5
- i=0: `right_even[0]=6, right_odd[0]=5`; i is even → `even_sum += 2` → even_sum=8

**Left sweep (left-to-right), left_even=0, left_odd=0:**

| i | Check condition | Result | Update left sums |
|---|-----------------|--------|-----------------|
| 0 | 0 + right_odd[0]=5 == 0 + right_even[0]=6 ? → 5≠6 | ✗ | even_sum += 2 → 2 |
| 1 | 2 + right_odd[1]=4 == 0 + right_even[1]=6 ? → 6==6 | ✓ count=1 | odd_sum += 1 → 1 |
| 2 | 2 + right_odd[2]=4 == 1 + right_even[2]=6 ? → 6≠7 | ✗ | even_sum += 6 → 8 |
| 3 | 8 + right_odd[3]=0 == 1 + right_even[3]=0 ? → 8≠1 | ✗ | odd_sum += 4 → 5 |

**Result: 1 ✓**

### Implementation

```python
from collections import defaultdict
from typing import List

class Solution:
    def waysToMakeFair(self, nums: List[int]) -> int:
        n = len(nums)

        right_odd = defaultdict(int)
        right_even = defaultdict(int)

        odd_sum = 0
        even_sum = 0
        for i in range(n - 1, -1, -1):
            right_odd[i] = odd_sum
            right_even[i] = even_sum
            if i & 1:
                odd_sum += nums[i]
            else:
                even_sum += nums[i]

        count = 0
        odd_sum = 0
        even_sum = 0
        for i in range(n):
            # After removing i:
            #   new_even = even_sum (left even) + right_odd[i] (right flips)
            #   new_odd  = odd_sum  (left odd)  + right_even[i] (right flips)
            if odd_sum + right_even[i] == even_sum + right_odd[i]:
                count += 1
            if i & 1:
                odd_sum += nums[i]
            else:
                even_sum += nums[i]

        return count
```

### Complexity

| | Complexity |
|---|---|
| **Time** | $O(n)$ — two linear passes |
| **Space** | $O(n)$ — for `right_odd` and `right_even` arrays |

> **Space optimization:** The two dictionaries can be replaced with plain arrays (`right_odd = [0] * n`), or further reduced to $O(1)$ extra space by computing total sums first and updating running sums in a single pass.
