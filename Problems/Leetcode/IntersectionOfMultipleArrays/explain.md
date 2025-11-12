## Problem

https://leetcode.com/problems/intersection-of-multiple-arrays/description/

```
Given a 2D integer array nums where nums[i] is a non-empty array of distinct positive integers, return the list of integers that are present in each array of nums sorted in ascending order.

Example 1:

Input: nums = [[3,1,2,4,5],[1,2,3,4],[3,4,5,6]]
Output: [3,4]
Explanation: 
The only integers present in each of nums[0] = [3,1,2,4,5], nums[1] = [1,2,3,4], and nums[2] = [3,4,5,6] are 3 and 4, so we return [3,4].

Example 2:

Input: nums = [[1,2,3],[4,5,6]]
Output: []
Explanation: 
There does not exist any integer present both in nums[0] and nums[1], so we return an empty list [].

Constraints:

1 <= nums.length <= 1000
1 <= sum(nums[i].length) <= 1000
1 <= nums[i][j] <= 1000
All the values of nums[i] are unique.
```

## Observations

1. **Problem Type**: Set intersection problem - finding common elements across multiple arrays
2. **Key Constraints**: 
   - All values in each array are unique (no duplicates within an array)
   - Need to find elements present in ALL arrays
   - Result should be sorted in ascending order
3. **Edge Cases**:
   - If any array is empty, intersection should be empty
   - If there are no common elements, return empty list
   - Single array case: return all elements of that array (sorted)

4. **Approach**: Use set intersection operations to efficiently find common elements

## Solution

**Algorithm**: Set Intersection with Bitwise AND operator

**Time Complexity**: O(n × m + k log k) where:
- n = number of arrays
- m = average length of arrays  
- k = size of final intersection (for sorting)

**Space Complexity**: O(m) for storing sets

**Step-by-step explanation**:

1. **Initialize with first array**: `s = set(nums[0])`
   - Convert the first array to a set to enable set operations
   - This becomes our starting point for intersection

2. **Iterate through all arrays**: `for row in nums:`
   - Process each array (including the first one again, which is harmless)
   - Convert each array to a set for intersection operation

3. **Perform intersection**: `s &= set(row)`
   - Use bitwise AND operator (&=) for set intersection
   - This keeps only elements that exist in both the current set `s` and the current `row`
   - After each iteration, `s` contains only elements common to all arrays processed so far

4. **Return sorted result**: `return sorted(list(s))`
   - Convert set back to list and sort in ascending order
   - Sorting ensures the required ascending order output

**Why this works**:
- Set intersection is commutative and associative
- Starting with the first array and intersecting with each subsequent array ensures we only keep elements present in ALL arrays
- The `&=` operator efficiently updates the set in-place

**Example trace**:
```
Input: nums = [[3,1,2,4,5],[1,2,3,4],[3,4,5,6]]

Step 1: s = {1,2,3,4,5} (from first array)
Step 2: s &= {3,1,2,4,5} → s = {1,2,3,4,5} (no change)
Step 3: s &= {1,2,3,4} → s = {1,2,3,4}
Step 4: s &= {3,4,5,6} → s = {3,4}
Step 5: sorted(list(s)) = [3,4]
```

# Tags

`Set`, `Hash Table`, `Array`, `Intersection`

