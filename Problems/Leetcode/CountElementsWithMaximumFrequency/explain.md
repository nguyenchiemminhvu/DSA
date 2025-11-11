## Problem

https://leetcode.com/problems/count-elements-with-maximum-frequency/

```
You are given an array nums consisting of positive integers.

Return the total frequencies of elements in nums such that those elements all have the maximum frequency.

The frequency of an element is the number of occurrences of that element in the array.

Example 1:

Input: nums = [1,2,2,3,1,4]
Output: 4
Explanation: The elements 1 and 2 have a frequency of 2 which is the maximum frequency in the array.
So the number of elements in the array with maximum frequency is 4.

Example 2:

Input: nums = [1,2,3,4,5]
Output: 5
Explanation: All elements of the array have a frequency of 1 which is the maximum.
So the number of elements in the array with maximum frequency is 5.

Constraints:

1 <= nums.length <= 100
1 <= nums[i] <= 100
```

## Observations

1. **Problem Understanding**: We need to find the total count of all elements that have the maximum frequency in the array.

2. **Key Insight**: This is a two-step process:
   - First, find what the maximum frequency is across all elements
   - Then, count how many elements in the original array have this maximum frequency

3. **Example Analysis**:
   - For `[1,2,2,3,1,4]`: frequencies are {1:2, 2:2, 3:1, 4:1}
   - Maximum frequency is 2
   - Elements with max frequency: 1 appears 2 times, 2 appears 2 times
   - Total count: 2 + 2 = 4

4. **Algorithm Strategy**:
   - Use a hash map to count frequencies
   - Find the maximum frequency value
   - Iterate through original array and count elements with max frequency

## Solution

1. **Frequency Counting**: 
   - `f = {}` creates a frequency map
   - `f[val] = f.get(val, 0) + 1` counts occurrences of each element
   - `f.get(val, 0)` returns current count or 0 if element not seen before

2. **Find Maximum Frequency**:
   - `pivot = max(f.values())` finds the highest frequency among all elements

3. **Count Elements with Max Frequency**:
   - Iterate through the original array `nums`
   - For each element, check if its frequency equals the maximum frequency
   - If yes, increment the count

**Time Complexity**: O(n) where n is the length of nums
- First loop: O(n) to build frequency map
- Finding max: O(k) where k is number of unique elements (k ≤ n)
- Second loop: O(n) to count elements with max frequency

**Space Complexity**: O(k) where k is the number of unique elements for the frequency map

**Alternative Approach**: Could optimize slightly by counting elements with max frequency during the first pass, but would require two passes through the frequency map.

# Tags

- Hash Map
- Frequency Counting
- Array Processing

