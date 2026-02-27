## Problem

https://leetcode.com/problems/find-the-smallest-divisor-given-a-threshold/description/

Given an array of integers `nums` and an integer `threshold`, choose a positive integer divisor, divide all elements of the array by it, and sum the results (each division rounded up to the nearest integer). Find the **smallest divisor** such that the resulting sum is **less than or equal to** `threshold`.

**Example 1:**
- Input: `nums = [1,2,5,9]`, `threshold = 6`
- Output: `5`
- Explanation: divisor=4 → sum=7; divisor=5 → sum=5 ✓

**Example 2:**
- Input: `nums = [44,22,33,11,1]`, `threshold = 5`
- Output: `44`

**Constraints:**
- `1 <= nums.length <= 5 * 10^4`
- `1 <= nums[i] <= 10^6`
- `nums.length <= threshold <= 10^6`

## Observations

1. **Monotonic relationship:** As the divisor increases, the sum of ceiling-divisions decreases (or stays the same). This monotonicity is the key insight — it makes binary search applicable.

2. **Search space:** The smallest possible divisor is `1` (sum equals the total of all elements). The largest useful divisor is `max(nums)` — any divisor ≥ `max(nums)` rounds every element down to 1, giving a sum of `n`, which is the minimum possible sum. So the answer always lies in `[1, max(nums)]`.

3. **Ceiling division trick:** `ceil(a / b)` can be computed with integer arithmetic as `(a + b - 1) // b`, avoiding floating-point operations.

4. **Binary search for the leftmost valid divisor:** Among all valid divisors (those for which the sum ≤ threshold), we want the smallest one. Binary search on the divisor value finds this efficiently in O(n log(max(nums))) time.

## Solution

```python
class Solution:
    def smallestDivisor(self, nums: List[int], threshold: int) -> int:
        n = len(nums)

        def check_possible(div: int) -> bool:
            s = 0
            for val in nums:
                s += ((val + div - 1) // div)  # ceiling division
            return s <= threshold

        left = 1
        right = max(nums)
        res = right
        while left <= right:
            mid = left + (right - left) // 2
            if check_possible(mid):
                res = mid          # mid is valid; try smaller
                right = mid - 1
            else:
                left = mid + 1     # mid is too small; try larger
        return res
```

**Step-by-step walkthrough (Example 1: nums=[1,2,5,9], threshold=6):**

| Iteration | left | right | mid | sum(ceil division) | valid? | action |
|-----------|------|-------|-----|--------------------|--------|--------|
| 1 | 1 | 9 | 5 | ceil(1/5)+ceil(2/5)+ceil(5/5)+ceil(9/5) = 1+1+1+2 = 5 | ✓ | res=5, right=4 |
| 2 | 1 | 4 | 2 | ceil(1/2)+ceil(2/2)+ceil(5/2)+ceil(9/2) = 1+1+3+5 = 10 | ✗ | left=3 |
| 3 | 3 | 4 | 3 | ceil(1/3)+ceil(2/3)+ceil(5/3)+ceil(9/3) = 1+1+2+3 = 7 | ✗ | left=4 |
| 4 | 4 | 4 | 4 | ceil(1/4)+ceil(2/4)+ceil(5/4)+ceil(9/4) = 1+1+2+3 = 7 | ✗ | left=5 |
| — | 5 | 4 | — | loop ends | — | return res=5 |

**Complexity:**
- Time: $O(n \log(\max(\text{nums})))$ — binary search over `[1, max(nums)]` with an O(n) check each step.
- Space: $O(1)$ — only a few integer variables used.

# Tags

`Binary Search` `Array`

