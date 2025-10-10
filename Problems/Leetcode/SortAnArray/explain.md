## Problem

https://leetcode.com/problems/sort-an-array/description/

```
Given an array of integers nums, sort the array in ascending order and return it.

You must solve the problem without using any built-in functions in O(nlog(n)) time complexity and with the smallest space complexity possible.

Example 1:

Input: nums = [5,2,3,1]
Output: [1,2,3,5]
Explanation: After sorting the array, the positions of some numbers are not changed (for example, 2 and 3), while the positions of other numbers are changed (for example, 1 and 5).

Example 2:

Input: nums = [5,1,1,2,0,0]
Output: [0,0,1,1,2,5]
Explanation: Note that the values of nums are not necessarily unique.

Constraints:

1 <= nums.length <= 5 * 104
-5 * 104 <= nums[i] <= 5 * 104
```

## Observations

1. **Constraint Analysis**: The problem requires O(n log n) time complexity without using built-in sorting functions, which eliminates simple O(n²) algorithms like bubble sort or selection sort.

2. **Optimal Algorithms**: The main candidates for O(n log n) sorting are:
   - Merge Sort (stable, guaranteed O(n log n), O(n) space)
   - Quick Sort (unstable, average O(n log n), worst O(n²), O(log n) space)
   - Heap Sort (unstable, guaranteed O(n log n), O(1) space)

3. **Space Complexity**: The problem asks for "smallest space complexity possible", but merge sort with O(n) auxiliary space is still acceptable and provides guaranteed performance.

4. **Array Size**: With up to 50,000 elements, efficiency matters, and merge sort's consistent performance is reliable.

5. **Duplicate Elements**: The problem mentions that values are not necessarily unique, so the algorithm must handle duplicates correctly.

## Solution

The provided solution implements **Merge Sort**, a divide-and-conquer algorithm that guarantees O(n log n) time complexity.

### Algorithm Breakdown:

**1. Divide Phase (`merge_sort` function):**
```python
def merge_sort(arr: List[int], left: int, right: int):
    if left < right:
        mid = left + (right - left) // 2  # Avoid overflow
        merge_sort(arr, left, mid)        # Sort left half
        merge_sort(arr, mid + 1, right)   # Sort right half
        merge_two_sorted_segment(arr, left, mid, right)  # Merge
```

**2. Conquer Phase (`merge_two_sorted_segment` function):**
```python
def merge_two_sorted_segment(arr: List[int], left: int, mid: int, right: int):
    temp = []                    # Temporary array for merging
    ileft = left                 # Pointer for left subarray
    iright = mid + 1             # Pointer for right subarray
    
    # Merge while both subarrays have elements
    while ileft <= mid and iright <= right:
        if arr[ileft] <= arr[iright]:
            temp.append(arr[ileft])
            ileft += 1
        else:
            temp.append(arr[iright])
            iright += 1
    
    # Copy remaining elements
    while ileft <= mid:
        temp.append(arr[ileft])
        ileft += 1
    
    while iright <= right:
        temp.append(arr[iright])
        iright += 1
    
    # Copy back to original array
    for i in range(left, right + 1):
        arr[i] = temp[i - left]
```

### Key Features:

- **Stability**: Uses `<=` comparison, maintaining relative order of equal elements
- **In-place**: Modifies the original array (though uses O(n) auxiliary space)
- **Overflow Prevention**: Uses `mid = left + (right - left) // 2` instead of `(left + right) // 2`
- **Guaranteed Performance**: Always O(n log n) time, never degrades to O(n²)

### Complexity Analysis:

- **Time Complexity**: O(n log n)
  - Dividing: O(log n) levels
  - Merging: O(n) work per level
  - Total: O(n log n)

- **Space Complexity**: O(n)
  - Temporary array in merge function: O(n)
  - Recursion stack: O(log n)
  - Total: O(n)

## Tags

array, sorting