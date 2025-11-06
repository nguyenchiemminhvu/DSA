## Problem

https://leetcode.com/problems/sum-of-unique-elements/description/

```
You are given an integer array nums. The unique elements of an array are the elements that appear exactly once in the array.

Return the sum of all the unique elements of nums.

Example 1:

Input: nums = [1,2,3,2]
Output: 4
Explanation: The unique elements are [1,3], and the sum is 4.

Example 2:

Input: nums = [1,1,1,1,1]
Output: 0
Explanation: There are no unique elements, and the sum is 0.

Example 3:

Input: nums = [1,2,3,4,5]
Output: 15
Explanation: The unique elements are [1,2,3,4,5], and the sum is 15.

Constraints:

1 <= nums.length <= 100
1 <= nums[i] <= 100
```

## Observations

1. **Problem Definition**: We need to find elements that appear exactly once in the array and return their sum.

2. **Key Insight**: This is a frequency counting problem where we need to:
   - Count the frequency of each element
   - Sum only those elements with frequency = 1

3. **Constraints Analysis**:
   - Small array size (≤ 100) and small element values (≤ 100)
   - This allows for simple O(n) solutions without optimization concerns

4. **Edge Cases**:
   - All elements are duplicated → return 0
   - All elements are unique → return sum of all elements
   - Mixed case → return sum of unique elements only

## Solution

**Approach: Hash Map Frequency Counting**

The solution uses a two-pass approach:

1. **First Pass - Count Frequencies**: 
   - Iterate through the array and build a frequency map using a dictionary
   - `f[val] = f.get(val, 0) + 1` safely increments count for each element

2. **Second Pass - Sum Unique Elements**:
   - Iterate through the array again
   - For each element, check if its frequency is exactly 1
   - If so, add it to the running sum

**Time Complexity**: O(n) where n is the length of the array
- First loop: O(n) to build frequency map
- Second loop: O(n) to calculate sum
- Dictionary operations: O(1) average case

**Space Complexity**: O(k) where k is the number of unique elements
- In worst case (all elements unique): O(n)
- In best case (all elements same): O(1)

**Algorithm Flow**:
```
1. Initialize sum = 0 and empty frequency map
2. Count frequency of each element
3. Iterate through array again
4. Add element to sum if frequency == 1
5. Return final sum
```

**Alternative Approaches**:
- **Single Pass with Counter**: Use `collections.Counter` for cleaner code
- **Set Operations**: Use sets to track seen/duplicate elements
- **Direct Frequency Check**: Count occurrences on-the-fly (less efficient)

**Why This Solution Works**:
- Simple and readable
- Handles all edge cases correctly
- Efficient for the given constraints
- Uses standard Python dictionary operations

# Tags

`Array` `Hash Table` `Frequency Counting` `Easy`

