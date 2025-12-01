## Problem

https://leetcode.com/problems/minimum-distance-between-three-equal-elements-i/description/

```
You are given an integer array nums.

A tuple (i, j, k) of 3 distinct indices is good if nums[i] == nums[j] == nums[k].

The distance of a good tuple is abs(i - j) + abs(j - k) + abs(k - i), where abs(x) denotes the absolute value of x.

Return an integer denoting the minimum possible distance of a good tuple. If no good tuples exist, return -1.

Example 1:
Input: nums = [1,2,1,1,3]
Output: 6
Explanation: The minimum distance is achieved by the good tuple (0, 2, 3).
(0, 2, 3) is a good tuple because nums[0] == nums[2] == nums[3] == 1. 
Its distance is abs(0 - 2) + abs(2 - 3) + abs(3 - 0) = 2 + 1 + 3 = 6.

Example 2:
Input: nums = [1,1,2,3,2,1,2]
Output: 8
Explanation: The minimum distance is achieved by the good tuple (2, 4, 6).
(2, 4, 6) is a good tuple because nums[2] == nums[4] == nums[6] == 2. 
Its distance is abs(2 - 4) + abs(4 - 6) + abs(6 - 2) = 2 + 2 + 4 = 8.

Example 3:
Input: nums = [1]
Output: -1
Explanation: There are no good tuples. Therefore, the answer is -1.

Constraints:
- 1 <= n == nums.length <= 100
- 1 <= nums[i] <= n
```

## Observations

1. **Good tuple requirement**: We need 3 distinct indices with equal values
2. **Distance formula simplification**: For indices i < j < k (sorted order):
   - abs(i - j) + abs(j - k) + abs(k - i) = (j - i) + (k - j) + (k - i) = 2(k - i)
   - The distance is always **2 × (last_index - first_index)**
3. **Optimal strategy**: To minimize distance, we want the 3 equal elements to be as close together as possible
4. **Key insight**: For any value with ≥3 occurrences, we should check consecutive triplets of indices (i, i+1, i+2) because they give the minimum span

## Solution

1. **Hash Map Creation**: Store all indices for each value in a hash map
   - Key: value from nums
   - Value: list of indices where this value appears

2. **Distance Calculation**: For each value with ≥3 occurrences:
   - The indices are already in sorted order (since we iterate through nums sequentially)
   - Check every consecutive triplet (v[i-2], v[i-1], v[i])
   - Distance = 2 × (v[i] - v[i-2])
   - We only need the first and last index of the triplet due to the simplified formula

3. **Return**: Minimum distance found, or -1 if no valid tuple exists

**Time Complexity**: O(n) where n is the length of nums
- O(n) to build the hash map
- O(n) total iterations across all values to check triplets

**Space Complexity**: O(n) for the hash map storing indices

# Tags
#array #hash-map #greedy #math

