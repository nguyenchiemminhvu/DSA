## Problem

https://leetcode.com/problems/first-missing-positive/description/

Given an unsorted integer array `nums`, return the **smallest positive integer** that is **not present** in `nums`.

You must implement an algorithm that runs in `O(n)` time and uses `O(1)` auxiliary space.

**Examples:**

| Input | Output | Reason |
|---|---|---|
| `[1,2,0]` | `3` | 1 and 2 are present; 3 is missing |
| `[3,4,-1,1]` | `2` | 1 is present; 2 is missing |
| `[7,8,9,11,12]` | `1` | 1 is missing entirely |

**Constraints:**
- `1 <= nums.length <= 10^5`
- `-2^31 <= nums[i] <= 2^31 - 1`

---

## Key Observation

The answer is always in the range **[1, n+1]** where `n = len(nums)`.

**Why?** In the best case, `nums` contains exactly `{1, 2, ..., n}`, so the answer is `n+1`. Any gap or out-of-range value only makes the answer smaller. This means we never need to look beyond `n+1`.

---

## Approach 1 — HashSet (given solution): O(n) time, O(n) space

```python
class Solution:
    def firstMissingPositive(self, nums: List[int]) -> int:
        n = len(nums)
        mi, ma = min(nums), max(nums)
        if mi > 1:       # Early exit: if smallest element > 1, answer is 1
            return 1
        
        s = set()
        for val in nums:
            s.add(val)
        
        for val in range(1, n + 2):   # Check 1 .. n+1 inclusive
            if val not in s:
                return val
        return ma + 1    # Dead code: the loop above always returns
```

**Step-by-step walkthrough** on `nums = [3, 4, -1, 1]`:

1. `n=4`, `mi=-1`, `ma=4`. `mi > 1` is false, so no early exit.
2. Build set: `s = {3, 4, -1, 1}`.
3. Check `val=1` → in set. Check `val=2` → **not in set** → return `2`. ✓

**Why the loop bound is `n + 2` (i.e., up to `n+1`):**  
By the pigeonhole principle, if all of `1..n` are present then the answer is `n+1`. So scanning `range(1, n+2)` guarantees we find the answer and the `return ma + 1` line is never reached.

**Complexity:**
- Time: `O(n)` — one pass to build the set, one pass over at most `n+1` integers.
- Space: `O(n)` — the set stores up to `n` elements.

> **Note:** This solution is correct and efficient in time, but uses `O(n)` auxiliary space. It does **not** satisfy the `O(1)` space constraint stated in the problem.

---

## Approach 2 — Index Hashing (optimal): O(n) time, O(1) space

Use the array itself as a hash map by placing each number `x ∈ [1, n]` at index `x - 1`.

```python
class Solution:
    def firstMissingPositive(self, nums: List[int]) -> int:
        n = len(nums)

        # Phase 1: place each number x in [1, n] at index x-1
        for i in range(n):
            while 1 <= nums[i] <= n and nums[nums[i] - 1] != nums[i]:
                nums[nums[i] - 1], nums[i] = nums[i], nums[nums[i] - 1]

        # Phase 2: find the first position where nums[i] != i+1
        for i in range(n):
            if nums[i] != i + 1:
                return i + 1

        return n + 1   # All of 1..n are present
```

**Step-by-step walkthrough** on `nums = [3, 4, -1, 1]`:

Phase 1 (swap each valid number to its correct slot):

| Step | Array state | Action |
|---|---|---|
| i=0, nums[0]=3 | `[3, 4, -1, 1]` | 3 belongs at index 2; swap nums[0] ↔ nums[2] |
| i=0, nums[0]=-1 | `[-1, 4, 3, 1]` | -1 out of range [1,4]; stop inner loop |
| i=1, nums[1]=4 | `[-1, 4, 3, 1]` | 4 belongs at index 3; swap nums[1] ↔ nums[3] |
| i=1, nums[1]=1 | `[-1, 1, 3, 4]` | 1 belongs at index 0; swap nums[1] ↔ nums[0] |
| i=1, nums[1]=-1 | `[1, -1, 3, 4]` | -1 out of range; stop inner loop |
| i=2, nums[2]=3 | `[1, -1, 3, 4]` | 3 is already at index 2; stop |
| i=3, nums[3]=4 | `[1, -1, 3, 4]` | 4 is already at index 3; stop |

Phase 2 (scan for first mismatch):

| Index | nums[i] | i+1 | Match? |
|---|---|---|---|
| 0 | 1 | 1 | ✓ |
| 1 | -1 | 2 | ✗ → return **2** |

**Why `O(1)` space?** No extra data structure is allocated; swaps happen in-place.  
**Why `O(n)` time?** Each element is moved at most once to its correct position, so the total number of swaps across all iterations of the outer loop is at most `n`.
