## Problem

https://leetcode.com/problems/count-special-quadruplets/description/

Given a 0-indexed integer array `nums`, return the number of distinct quadruplets `(a, b, c, d)` such that:
- `nums[a] + nums[b] + nums[c] == nums[d]`
- `a < b < c < d`

**Examples:**

**Example 1:**
```
Input: nums = [1,2,3,6]
Output: 1
Explanation: The only quadruplet that satisfies the requirement is (0, 1, 2, 3) because 1 + 2 + 3 == 6.
```

**Example 2:**
```
Input: nums = [3,3,6,4,5]
Output: 0
Explanation: There are no such quadruplets in [3,3,6,4,5].
```

**Example 3:**
```
Input: nums = [1,1,1,3,5]
Output: 4
Explanation: The 4 quadruplets that satisfy the requirement are:
- (0, 1, 2, 3): 1 + 1 + 1 == 3
- (0, 1, 3, 4): 1 + 1 + 3 == 5
- (0, 2, 3, 4): 1 + 1 + 3 == 5
- (1, 2, 3, 4): 1 + 1 + 3 == 5
```

**Constraints:**
- `4 <= nums.length <= 50`
- `1 <= nums[i] <= 100`

## Observations

1. **Brute Force Approach**: A naive solution would use 4 nested loops to check all possible combinations of indices, resulting in O(n⁴) time complexity.

2. **Mathematical Transformation**: We can rearrange the equation `nums[a] + nums[b] + nums[c] == nums[d]` to `nums[d] - nums[b] - nums[c] == nums[a]`. This allows us to:
   - Fix indices `b` and `c` (with `b < c`)
   - Calculate the target value `nums[d] - nums[b] - nums[c]` for each `d > c`
   - Check if this target value exists among the elements at indices `a < b`

3. **Hash Map Optimization**: Instead of searching linearly for valid `a` values, we can use a hash map to store the frequency of elements we've seen so far (elements at indices less than the current `b`).

4. **Processing Order**: By processing elements from left to right and maintaining a frequency map of previously seen elements, we ensure the constraint `a < b < c < d` is automatically satisfied.

## Solution

1. **Outer Loop (i)**: Represents index `b` in our quadruplet. We iterate through each position as a potential second element.

2. **Middle Loop (j)**: Represents index `c` in our quadruplet (with `j > i`).

3. **Inner Loop (k)**: Represents index `d` in our quadruplet (with `k > j`).

4. **Target Calculation**: For each combination of `(i, j, k)`, we calculate what `nums[a]` should be using the rearranged equation: `val = nums[k] - nums[i] - nums[j]`.

5. **Frequency Check**: We check if this target value exists in our frequency map `f`, which contains all elements at indices less than `i` (satisfying `a < b`).

6. **Count Update**: If the target exists, we add its frequency to our count (handling duplicate values).

7. **Map Update**: After processing all combinations where `i` is the second index, we add `nums[i]` to our frequency map for future iterations.

**Time Complexity**: O(n³) - Three nested loops
**Space Complexity**: O(n) - Hash map storing at most n elements

This approach is significantly more efficient than the brute force O(n⁴) solution while maintaining correctness.

# Tags
`Array` `Hash Table` `Enumeration` `Nested Loops` `Mathematical Transformation`

