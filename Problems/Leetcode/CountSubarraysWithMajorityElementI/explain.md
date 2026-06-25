## Problem

https://leetcode.com/problems/count-subarrays-with-majority-element-i/description/

```
You are given an integer array nums and an integer target.

Return the number of subarrays of nums in which target is the majority element.

The majority element of a subarray is the element that appears strictly more than
half of the times in that subarray.

Example 1:
Input: nums = [1,2,2,3], target = 2
Output: 5

Example 2:
Input: nums = [1,1,1,1], target = 1
Output: 10

Example 3:
Input: nums = [1,2,3], target = 4
Output: 0

Constraints:
1 <= nums.length <= 1000
1 <= nums[i] <= 10^9
1 <= target <= 10^9
```

## Observations

1. **Majority Element Definition**: An element is the majority of a subarray of length `L` if it appears strictly more than `L / 2` times, i.e., its count `c` satisfies `c > L / 2`, which is equivalent to `L < 2 * c`.

2. **Brute Force is Feasible**: With `n ≤ 1000`, there are at most `n*(n+1)/2 ≈ 500,500` subarrays. Checking each subarray naively is O(n³), but using prefix sums reduces it to O(n²) which is well within limits.

3. **Prefix Count Trick**: Instead of counting occurrences of `target` in every subarray from scratch, we precompute `prefix_count[i]` = number of times `target` appears in `nums[0..i-1]`. Then for any subarray `nums[i..j]`, the count of `target` is simply `prefix_count[j+1] - prefix_count[i]` in O(1).

4. **Reformulating the Condition**: For subarray `nums[i..j]`:
   - `length = j - i + 1`
   - `count = prefix_count[j+1] - prefix_count[i]`
   - `target` is the majority iff `count > length / 2` ↔ `length < 2 * count`

5. **Edge Case — target not in nums**: If `target` never appears, `prefix_count` stays all zeros, so `count = 0` for every subarray, and no subarray passes the condition, correctly returning `0`.

## Solution

### Prefix Count + Brute Force (Given Solution)

```python
class Solution:
    def countMajoritySubarrays(self, nums: List[int], target: int) -> int:
        n = len(nums)
        prefix_count = [0] * (n + 1)
        for i, val in enumerate(nums):
            temp = int(val == target)
            prefix_count[i + 1] = prefix_count[i] + temp
        
        res = 0
        for i in range(n):
            for j in range(i, n):
                count = prefix_count[j + 1] - prefix_count[i]
                length = j - i + 1
                if length < count * 2:
                    res += 1

        return res
```

**How it works:**

1. **Build Prefix Count Array**:
   - `prefix_count` has size `n + 1`, initialized to all zeros.
   - For each index `i`, `prefix_count[i + 1] = prefix_count[i] + (1 if nums[i] == target else 0)`.
   - After this step, `prefix_count[j+1] - prefix_count[i]` gives the number of occurrences of `target` in `nums[i..j]` in O(1).

2. **Enumerate All Subarrays**:
   - Use two nested loops over all pairs `(i, j)` with `0 ≤ i ≤ j < n`.
   - For each subarray `nums[i..j]`:
     - Compute `count` using the prefix array.
     - Compute `length = j - i + 1`.
     - Check the majority condition: `length < count * 2`.
   - Increment `res` whenever the condition holds.

**Step-by-step trace on Example 1** (`nums = [1,2,2,3]`, `target = 2`):

| Subarray    | length | count (2s) | length < 2*count? |
|-------------|--------|------------|-------------------|
| [1]         | 1      | 0          | No                |
| [2] (i=1)   | 1      | 1          | Yes ✓             |
| [2] (i=2)   | 1      | 1          | Yes ✓             |
| [3]         | 1      | 0          | No                |
| [1,2]       | 2      | 1          | No                |
| [2,2]       | 2      | 2          | Yes ✓             |
| [2,3]       | 2      | 1          | No                |
| [1,2,2]     | 3      | 2          | Yes ✓             |
| [2,2,3]     | 3      | 2          | Yes ✓             |
| [1,2,2,3]   | 4      | 2          | No                |

Result = **5** ✓

**Time Complexity**: O(n²) — O(n) to build prefix array + O(n²) for the double loop  
**Space Complexity**: O(n) — for the `prefix_count` array

# Tags

- Array
- Prefix Sum
- Brute Force
- Subarray
- Counting
