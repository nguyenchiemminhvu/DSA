## Problem

https://leetcode.com/problems/minimum-sum-of-squared-difference/

```
You are given two positive 0-indexed integer arrays nums1 and nums2, both of length n.

The sum of squared difference of arrays nums1 and nums2 is defined as the sum of (nums1[i] - nums2[i])^2 for each 0 <= i < n.

You are also given two positive integers k1 and k2. You can modify any of the elements of nums1 by +1 or -1 at most k1 times. Similarly, you can modify any of the elements of nums2 by +1 or -1 at most k2 times.

Return the minimum sum of squared difference after modifying array nums1 at most k1 times and modifying array nums2 at most k2 times.

Note: You are allowed to modify the array elements to become negative integers.

Constraints:
- n == nums1.length == nums2.length
- 1 <= n <= 10^5
- 0 <= nums1[i], nums2[i] <= 10^5
- 0 <= k1, k2 <= 10^9
```

## Observations

1. **Operations are equivalent**: Whether we increase nums1[i] or decrease nums2[i], both reduce the difference by 1. Therefore, `k = k1 + k2` gives us the total operations available.

2. **Work with absolute differences**: We only care about `|nums1[i] - nums2[i]|`, not the sign. The goal is to reduce these differences optimally.

3. **Greedy is optimal**: To minimize sum of squares, we should reduce larger differences first. This is because reducing a larger difference has more impact on the result: reducing 10→9 saves 10^2 - 9^2 = 19, while reducing 2→1 only saves 2^2 - 1^2 = 3.

4. **Early termination**: If k >= sum of all differences, we can make all differences zero, resulting in 0.

5. **Level-by-level reduction**: Think of differences as heights. We want to "level down" the tallest ones to match shorter ones, using a greedy approach.

## Solution

### Approach: Greedy Level Reduction

**Algorithm:**

1. **Compute differences**: Create an array of absolute differences between corresponding elements.

2. **Check if k is sufficient**: If k >= sum of all differences, return 0 (we can eliminate all differences).

3. **Sort differences**: Sort in descending order to process largest differences first.

4. **Greedy reduction**: Iterate through groups of equal differences:
   - Find the current maximum value and count how many elements have this value
   - Find the next smaller value (or 0 if none exists)
   - Calculate operations needed to bring all current max values down to the next level
   - If we have enough operations, do it and continue
   - If not enough operations, distribute remaining operations optimally:
     - Use `quo = k // cur_count` to reduce all by this amount
     - Use `rem = k % cur_count` to reduce rem elements by one additional unit
     - This distributes the k operations as evenly as possible

5. **Calculate result**: Sum the squares of the final differences.

**Time Complexity**: O(n log n) for sorting
**Space Complexity**: O(n) for the differences array

**Key Insight**: When we have leftover operations that can't bring all elements to the next level, we distribute them evenly. If we have `cur_count` elements at value `cur_val` and `k` operations left:
- Reduce all by `k // cur_count`
- Reduce an additional `k % cur_count` elements by 1 more
- This minimizes the sum of squares due to the convexity of the square function

**Example walkthrough** (Example 2):
- nums1 = [1,4,10,12], nums2 = [5,8,6,9], k1 = 1, k2 = 1
- diffs = [4, 4, 4, 3], k = 2
- After sorting: [4, 4, 4, 3]
- Reduce three 4's to 3 (need 3 ops, but only have 2)
- quo = 2 // 3 = 0, rem = 2
- So: two elements become 3, one stays at 4
- Result: [4, 3, 3, 3] → 16 + 9 + 9 + 9 = 43

# Tags
#greedy #array #sorting #optimization #math

