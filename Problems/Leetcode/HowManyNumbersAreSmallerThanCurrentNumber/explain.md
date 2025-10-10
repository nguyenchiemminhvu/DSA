## Problem

https://leetcode.com/problems/how-many-numbers-are-smaller-than-the-current-number/

```
Given the array nums, for each nums[i] find out how many numbers in the array are smaller than it. That is, for each nums[i] you have to count the number of valid j's such that j != i and nums[j] < nums[i].

Return the answer in an array.

Example 1:

Input: nums = [8,1,2,2,3]
Output: [4,0,1,1,3]
Explanation: 
For nums[0]=8 there exist four smaller numbers than it (1, 2, 2 and 3). 
For nums[1]=1 does not exist any smaller number than it.
For nums[2]=2 there exist one smaller number than it (1). 
For nums[3]=2 there exist one smaller number than it (1). 
For nums[4]=3 there exist three smaller numbers than it (1, 2 and 2).

Example 2:

Input: nums = [6,5,4,8]
Output: [2,1,0,3]

Example 3:

Input: nums = [7,7,7,7]
Output: [0,0,0,0]

Constraints:

2 <= nums.length <= 500
0 <= nums[i] <= 100
```

## Observations

1. **Core Problem**: For each element in the array, we need to count how many elements are strictly smaller than it.

2. **Naive Approach**: We could use a nested loop to compare each element with every other element, giving us `O(n²)` time complexity.

3. **Binary Search Optimization**: Since we only need to count smaller elements, we can:
   - Sort the array once
   - For each element, find the first position where an element >= current element appears
   - This position gives us the count of smaller elements

4. **Key Insight**: In a sorted array, all elements smaller than a target will be positioned before the first occurrence of any element >= target.

5. **Lower Bound**: The `lower_bound` function finds the first position where we could insert the target while maintaining sorted order, which is exactly the count of smaller elements.

## Solution

**Approach: Binary Search with Sorting**

1. **Sort the Array**: Create a sorted copy `s` of the input array
   - Time: `O(n log n)`

2. **Binary Search for Each Element**: For each element in the original array:
   - Use `lower_bound` to find the first position where an element >= current element appears
   - This position represents the count of elements smaller than the current element

3. **Lower Bound Implementation**:
   - Uses binary search to find the leftmost position where `target` could be inserted
   - If `arr[mid] >= target`, we move left (could be a valid position)
   - If `arr[mid] < target`, we move right (need to find larger elements)
   - Returns the index which equals the count of smaller elements

**Example Walkthrough:**
- Input: `[8,1,2,2,3]`
- Sorted: `[1,2,2,3,8]`
- For `8`: lower_bound finds index 4 → 4 smaller elements
- For `1`: lower_bound finds index 0 → 0 smaller elements  
- For `2`: lower_bound finds index 1 → 1 smaller element
- For `2`: lower_bound finds index 1 → 1 smaller element
- For `3`: lower_bound finds index 3 → 3 smaller elements
- Result: `[4,0,1,1,3]`

**Time Complexity**: `O(n log n)` for sorting + `O(n log n)` for n binary searches = `O(n log n)`
**Space Complexity**: `O(n)` for the sorted array

**Alternative Approaches:**
- **Counting Sort**: Since constraints limit values to 0-100, we could use counting sort for `O(n)` time
- **Hash Map**: Count frequencies and calculate prefix sums for `O(n)` time

## Tags

array, binary search