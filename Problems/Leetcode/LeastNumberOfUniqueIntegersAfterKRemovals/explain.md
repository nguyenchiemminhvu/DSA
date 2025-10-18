## Problem

https://leetcode.com/problems/least-number-of-unique-integers-after-k-removals/

```
Given an array of integers arr and an integer k. Find the least number of unique integers after removing exactly k elements.

Example 1:

Input: arr = [5,5,4], k = 1
Output: 1
Explanation: Remove the single 4, only 5 is left.

Example 2:
Input: arr = [4,3,1,1,3,3,2], k = 3
Output: 2
Explanation: Remove 4, 2 and either one of the two 1s or three 3s. 1 and 3 will be left.

Constraints:

1 <= arr.length <= 10^5
1 <= arr[i] <= 10^9
0 <= k <= arr.length
```

## Observations

1. **Goal**: Minimize the number of unique integers after removing exactly k elements
2. **Greedy Strategy**: To minimize unique integers, we should remove complete frequencies of elements, starting with the least frequent ones
3. **Key Insight**: If we can completely remove an element (all its occurrences), we reduce the unique count by 1. If we can only partially remove an element, the unique count stays the same for that element
4. **Optimal Approach**: 
   - Count frequency of each element
   - Sort elements by their frequency (ascending order)
   - Remove elements starting from the least frequent until k removals are exhausted
5. **Edge Cases**: 
   - If k = 0, return original unique count
   - If k >= array length, return 0
   - If we can't completely remove an element with remaining k, stop there

## Solution

**Algorithm:**
1. **Frequency Counting**: Build a frequency map of all elements in the array
2. **Sort by Frequency**: Create a list of unique elements sorted by their frequency (ascending)
3. **Greedy Removal**: Iterate through sorted elements and remove complete frequencies while k allows
4. **Return Result**: Count remaining unique elements

**Time Complexity**: O(n log n) - where n is the number of unique elements
- O(n) for frequency counting
- O(n log n) for sorting unique elements
- O(n) for greedy removal

**Space Complexity**: O(n) - for frequency map and sorted list

**Example Walkthrough:**
- `arr = [4,3,1,1,3,3,2], k = 3`
- Frequency: {4:1, 3:3, 1:2, 2:1}
- Sorted by frequency: [4, 2, 1, 3] (frequencies: 1, 1, 2, 3)
- Remove 4 (k=2), remove 2 (k=1), can't remove 1 completely (need 2, have 1)
- Remaining: {3:3, 1:2} → 2 unique integers

## Tags

array, hash table, greedy