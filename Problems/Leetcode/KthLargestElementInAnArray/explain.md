## Problem

https://leetcode.com/problems/kth-largest-element-in-an-array/

```
Given an integer array nums and an integer k, return the kth largest element in the array.

Note that it is the kth largest element in the sorted order, not the kth distinct element.

Can you solve it without sorting?

Example 1:

Input: nums = [3,2,1,5,6,4], k = 2
Output: 5

Example 2:

Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
Output: 4

Constraints:

1 <= k <= nums.length <= 105
-104 <= nums[i] <= 104
```

## Observations

1. **Understanding "Kth Largest"**: The kth largest element means if we sort the array in descending order, it would be at index k-1. For example, in `[3,2,1,5,6,4]`, the 2nd largest is 5 (6 is 1st, 5 is 2nd).

2. **Min-Heap Approach**: We can maintain a min-heap of size k. The smallest element in this heap will be the kth largest element overall, because:
   - The heap contains the k largest elements seen so far
   - The minimum of these k largest elements is the kth largest

3. **Why Not Max-Heap?**: A max-heap would give us the maximum element easily, but finding the kth largest would require popping k-1 elements, which is less efficient for this approach.

4. **Time Complexity**: O(n log k) where n is the array length
   - Each insertion: O(log k)
   - Each removal: O(log k)
   - We do this for n elements

5. **Space Complexity**: O(k) for the heap

## Solution

1. **Initialization**: Start with an empty min-heap `arr`

2. **Processing Each Element**:
   - Push the current element onto the heap
   - If heap size exceeds k, pop the smallest element
   - This ensures we always keep only the k largest elements

3. **Result**: After processing all elements, the heap contains exactly k largest elements, and `arr[0]` (the root of min-heap) is the smallest among them, which is the kth largest overall

**Example Walkthrough** (`nums = [3,2,1,5,6,4]`, `k = 2`):

```
Step 1: Push 3 → heap = [3]
Step 2: Push 2 → heap = [2,3] → size > 2? No
Step 3: Push 1 → heap = [1,2,3] → size > 2? Yes → pop 1 → heap = [2,3]
Step 4: Push 5 → heap = [2,3,5] → size > 2? Yes → pop 2 → heap = [3,5]
Step 5: Push 6 → heap = [3,5,6] → size > 2? Yes → pop 3 → heap = [5,6]
Step 6: Push 4 → heap = [4,5,6] → size > 2? Yes → pop 4 → heap = [5,6]
Result: arr[0] = 5 ✓
```

**Alternative Approaches:**

1. **Sorting**: Sort array and return `nums[len(nums)-k]` → O(n log n) time, O(1) space
2. **QuickSelect**: Partition-based selection → O(n) average, O(n²) worst case
3. **Max-Heap**: Build max-heap and pop k-1 times → O(n + k log n) time

## Tags

array, sorting, min heap