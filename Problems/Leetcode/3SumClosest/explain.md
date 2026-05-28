## Problem

https://leetcode.com/problems/3sum-closest/description/

Given an integer array `nums` of length `n` and an integer `target`, find three integers at **distinct indices** such that the sum is closest to `target`. Return the sum of the three integers. Each input has exactly one solution.

**Example 1:**
```
Input: nums = [-1,2,1,-4], target = 1
Output: 2   # -1 + 2 + 1 = 2
```

**Example 2:**
```
Input: nums = [0,0,0], target = 1
Output: 0   # 0 + 0 + 0 = 0
```

**Constraints:**
- `3 <= nums.length <= 500`
- `-1000 <= nums[i] <= 1000`
- `-10^4 <= target <= 10^4`

---

## Observations

1. **Brute force is O(n³)** — try every triplet, track the one with smallest `|sum - target|`. Too slow for n=500 but fine as a baseline idea.

2. **Sorting enables two-pointer search.** Once sorted, fixing one element `nums[i]` reduces the problem to finding the best pair in the remaining subarray using two pointers `l` and `r`.

3. **Two-pointer convergence:** With `l < r`:
   - If `sum > target` → the sum is too large, move `r` left to decrease it.
   - If `sum < target` → the sum is too small, move `l` right to increase it.
   - If `sum == target` → can't get any closer, return immediately.

4. **Only one global answer needs tracking.** Maintain `res` (best sum so far) and `dist` (best distance so far). Update both whenever a strictly closer sum is found.

5. **Complexity:** Sorting is O(n log n). The outer loop is O(n) and the inner two-pointer scan is O(n), giving **O(n²)** overall — optimal for this problem.

---

## Solution

```python
class Solution:
    def threeSumClosest(self, nums: List[int], target: int) -> int:
        n = len(nums)
        nums.sort()                          # Step 1: sort to enable two-pointer

        dist = 0xFFFFFFFF                    # best distance seen so far (start huge)
        res  = 0xFFFFFFFF                    # best sum seen so far
        for i in range(n - 2):              # fix the first element of the triplet
            l = i + 1
            r = n - 1
            while l < r:
                s = nums[i] + nums[l] + nums[r]
                if s == target:             # perfect match — can't do better
                    return s
                if abs(s - target) < dist:  # found a closer sum → update answer
                    res  = s
                    dist = abs(s - target)
                if s > target:              # sum too large → shrink right pointer
                    r -= 1
                else:                       # sum too small → grow left pointer
                    l += 1
        return res
```

### Walk-through on Example 1

`nums = [-1, 2, 1, -4]`, `target = 1`

After sorting: `[-4, -1, 1, 2]`

| i | nums[i] | l | r | sum | action |
|---|---------|---|---|-----|--------|
| 0 | -4 | 1 | 3 | -4+(-1)+2 = -3 | dist=4, res=-3; sum<target → l++ |
| 0 | -4 | 2 | 3 | -4+1+2 = -1 | dist=2, res=-1; sum<target → l++ |
| 0 | -4 | 3 | 3 | l==r, exit inner loop |
| 1 | -1 | 2 | 3 | -1+1+2 = 2 | dist=1, res=2; sum>target → r-- |
| 1 | -1 | 2 | 2 | l==r, exit inner loop |

Result: **2**
