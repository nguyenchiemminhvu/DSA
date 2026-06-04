## Problem

https://leetcode.com/problems/next-permutation/description

A **permutation** of an array of integers is an arrangement of its members into a sequence or linear order.

The **next permutation** is the next lexicographically greater permutation. If no such arrangement exists (i.e., the array is in descending order), rearrange to the lowest possible order (ascending).

**Examples:**
- `[1,2,3]` → `[1,3,2]`
- `[2,3,1]` → `[3,1,2]`
- `[3,2,1]` → `[1,2,3]`
- `[1,1,5]` → `[1,5,1]`

**Constraints:** `1 <= nums.length <= 100`, `0 <= nums[i] <= 100`. Must be in-place with O(1) extra memory.

---

## Observations

1. **Descending suffix means no larger permutation is possible from that suffix.** A suffix that is strictly descending is already the largest arrangement of those elements.

2. **The pivot is the first element (from the right) that breaks the descending run.** Specifically, find the rightmost index `i` such that `nums[i] < nums[i+1]`. This is the digit we need to increment.

3. **To get the *next* (smallest increment) permutation, swap the pivot with the smallest element to its right that is still greater than it.** Since the suffix is descending, a right-to-left scan finds that element efficiently.

4. **After the swap, the suffix `nums[pivot+1:]` must be sorted ascending** to ensure the result is the immediate next permutation (smallest arrangement of that suffix).

5. **If no pivot is found, the entire array is descending — return it sorted ascending** (the smallest permutation).

---

## Solution

```python
class Solution:
    def nextPermutation(self, nums: List[int]) -> None:
        n = len(nums)
        pivot = n

        # Step 1: Find the pivot — rightmost i where nums[i] < nums[i+1]
        for i in range(n - 2, -1, -1):
            if nums[i] < nums[i + 1]:
                pivot = i
                break

        # Step 2: If no pivot, array is fully descending → sort ascending
        if pivot == n:
            return nums.sort()

        # Step 3: Find the smallest element in the suffix that is > nums[pivot]
        swap_val = float('inf')
        swap_idx = pivot
        for i in range(n - 1, pivot, -1):
            if nums[i] > nums[pivot] and nums[i] < swap_val:
                swap_val = nums[i]
                swap_idx = i

        # Step 4: Swap pivot with that element
        nums[pivot], nums[swap_idx] = nums[swap_idx], nums[pivot]

        # Step 5: Sort the suffix to make it the smallest possible arrangement
        nums[pivot + 1:] = sorted(nums[pivot + 1:])
```

### Walkthrough on `[2, 3, 1]`

| Step | State | Notes |
|------|-------|-------|
| Initial | `[2, 3, 1]` | |
| Find pivot | `pivot = 0` | `nums[0]=2 < nums[1]=3` |
| Find swap target | `swap_idx = 1` | `nums[1]=3` is smallest value > 2 in suffix `[3,1]` |
| Swap | `[3, 2, 1]` | pivot (2) ↔ swap target (3) |
| Sort suffix | `[3, 1, 2]` | suffix `[2,1]` → `[1,2]` |

### Complexity

- **Time:** O(n) for pivot search + O(n) for swap target + O(n log n) for suffix sort → **O(n log n)**
- **Space:** O(1) extra (in-place)
