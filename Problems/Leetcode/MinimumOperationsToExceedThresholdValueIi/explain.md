## Problem

https://leetcode.com/problems/minimum-operations-to-exceed-threshold-value-ii/description/

```
You are given a 0-indexed integer array nums, and an integer k.

You are allowed to perform some operations on nums, where in a single operation, you can:
- Select the two smallest integers x and y from nums.
- Remove x and y from nums.
- Insert (min(x, y) * 2 + max(x, y)) at any position in the array.

Note that you can only apply the described operation if nums contains at least two elements.

Return the minimum number of operations needed so that all elements of the array are 
greater than or equal to k.

Example 1:
Input: nums = [2,11,10,1,3], k = 10
Output: 2
Explanation:
- Operation 1: Remove 1 and 2, add 1*2 + 2 = 4. nums = [4, 11, 10, 3]
- Operation 2: Remove 3 and 4, add 3*2 + 4 = 10. nums = [10, 11, 10]
All elements >= 10, so we stop.

Example 2:
Input: nums = [1,1,2,4,9], k = 20
Output: 4
Explanation:
- After 1 operation: [2, 4, 9, 3]
- After 2 operations: [7, 4, 9]
- After 3 operations: [15, 9]
- After 4 operations: [33]
All elements >= 20, so we stop.

Constraints:
- 2 <= nums.length <= 2 * 10^5
- 1 <= nums[i] <= 10^9
- 1 <= k <= 10^9
- The input guarantees that a solution always exists
```

## Observations

1. **Key Insight**: We must always select the **two smallest** elements in each operation
   - This is not optional - the problem explicitly requires selecting the two smallest values
   - This naturally suggests using a min-heap data structure

2. **Operation Formula**: `min(x, y) * 2 + max(x, y)`
   - If x <= y, then: `x * 2 + y`
   - This operation always produces a value >= min(x, y) and usually larger than both
   - The smaller value gets doubled weight, helping us eliminate small values faster

3. **Greedy Approach**:
   - We should keep performing operations as long as the minimum element is < k
   - Each operation removes two elements and adds one back, reducing array size by 1
   - We continue until all remaining elements are >= k

4. **Optimization with Min-Heap**:
   - A min-heap allows O(log n) access to the minimum element
   - Each operation involves 2 pops and 1 push, all O(log n) operations
   - Overall time complexity: O(n log n) where n is the initial array size

5. **Termination Condition**:
   - Check if the smallest element (heap root) is >= k
   - If yes, all elements must be >= k (property of min-heap)
   - No need to check all elements individually

## Solution

```python
import heapq

class Solution:
    def minOperations(self, pq: List[int], k: int) -> int:
        # Convert array to min-heap in O(n) time
        heapq.heapify(pq)
        
        count = 0
        
        # Continue while the minimum element is less than k
        while pq[0] < k:
            # Extract the two smallest elements
            a = heapq.heappop(pq)  # smallest
            b = heapq.heappop(pq)  # second smallest
            
            # Combine them using the formula: min*2 + max
            combined = min(a, b) * 2 + max(a, b)
            
            # Insert the combined value back into the heap
            heapq.heappush(pq, combined)
            
            # Increment operation counter
            count += 1
        
        return count
```

**Algorithm Explanation**:

1. **Initialization**: Convert the input array into a min-heap using `heapq.heapify()`
   - Time: O(n), where n is the length of nums
   - After this, `pq[0]` always contains the minimum element

2. **Main Loop**: While the minimum element is < k:
   - Pop the two smallest elements (a and b) from the heap
   - Calculate the combined value: `min(a, b) * 2 + max(a, b)`
   - Push the combined value back into the heap
   - Increment the operation counter

3. **Termination**: When `pq[0] >= k`, we know all elements are >= k
   - This is guaranteed by the min-heap property
   - Return the operation count

**Time Complexity**: O(n log n)
- Heapify: O(n)
- Each operation: O(log n) for 2 pops and 1 push
- Worst case: n-1 operations (reducing n elements to 1)
- Total: O(n + (n-1) log n) = O(n log n)

**Space Complexity**: O(1)
- Using the input array as the heap (in-place)
- No additional data structures needed

**Why This Works**:
- The greedy approach of always combining the two smallest elements is optimal
- By eliminating the smallest values first, we minimize the number of operations
- The formula `min*2 + max` ensures the combined value grows sufficiently
- The problem guarantees a solution exists, so we won't run out of elements

# Tags
`heap` `min-heap` `priority-queue` `greedy` `array` `medium`

