## Problem

https://leetcode.com/problems/final-array-state-after-k-multiplication-operations-i/description/

```
You are given an integer array nums, an integer k, and an integer multiplier.

You need to perform k operations on nums. In each operation:

Find the minimum value x in nums. If there are multiple occurrences of the minimum value, select the one that appears first.
Replace the selected minimum value x with x * multiplier.
Return an integer array denoting the final state of nums after performing all k operations.

Example 1:

Input: nums = [2,1,3,5,6], k = 5, multiplier = 2

Output: [8,4,6,5,6]

Explanation:

Operation	Result
After operation 1	[2, 2, 3, 5, 6]
After operation 2	[4, 2, 3, 5, 6]
After operation 3	[4, 4, 3, 5, 6]
After operation 4	[4, 4, 6, 5, 6]
After operation 5	[8, 4, 6, 5, 6]

Example 2:

Input: nums = [1,2], k = 3, multiplier = 4

Output: [16,8]

Explanation:

Operation	Result
After operation 1	[4, 2]
After operation 2	[4, 8]
After operation 3	[16, 8]

Constraints:

1 <= nums.length <= 100
1 <= nums[i] <= 100
1 <= k <= 10
1 <= multiplier <= 5
```

## Observations

1. **Problem Requirements:**
   - We need to perform exactly `k` operations
   - In each operation, find the minimum value in the array
   - If there are multiple minimum values, choose the one with the smallest index (leftmost)
   - Multiply that minimum value by the `multiplier`

2. **Key Insights:**
   - We need to efficiently find the minimum value in each operation
   - We need to handle ties by selecting the element with the smallest index
   - After multiplying, we need to update the array and repeat the process

3. **Data Structure Choice:**
   - A min-heap (priority queue) is perfect for this problem
   - Python's `heapq` naturally handles the minimum element extraction
   - We can store tuples `(value, index)` to handle ties correctly
   - The heap will automatically prioritize by value first, then by index for ties

4. **Time Complexity Analysis:**
   - Building initial heap: O(n log n)
   - Each of k operations: O(log n) for pop + O(log n) for push = O(log n)
   - Total for k operations: O(k log n)
   - Final reconstruction: O(n log n)
   - Overall: O((k + n) log n)

5. **Space Complexity:**
   - O(n) for the priority queue

## Solution

The solution uses a min-heap (priority queue) approach:

### Algorithm Steps:

1. **Initialize Priority Queue:**
   ```python
   pq = []
   for i, val in enumerate(nums):
       heapq.heappush(pq, (val, i))
   ```
   - Create a min-heap containing tuples of `(value, index)`
   - The heap will automatically order by value first, then by index for ties
   - This ensures we always get the minimum value with the smallest index

2. **Perform K Operations:**
   ```python
   while k:
       val, i = heapq.heappop(pq)  # Get minimum element
       val *= multiplier            # Multiply by the multiplier
       heapq.heappush(pq, (val, i)) # Put back updated value
       k -= 1
   ```
   - Extract the minimum element (guaranteed to be the leftmost minimum due to tuple ordering)
   - Multiply it by the multiplier
   - Push the updated value back into the heap
   - Repeat k times

3. **Reconstruct Final Array:**
   ```python
   while pq:
       val, i = heapq.heappop(pq)
       nums[i] = val
   ```
   - Extract all elements from the heap
   - Place each value back to its original index in the result array

### Why This Works:

- **Correctness:** The min-heap ensures we always select the true minimum value
- **Tie-breaking:** Python's tuple comparison naturally handles the "leftmost" requirement
- **Efficiency:** Heap operations are O(log n), making this much faster than repeatedly scanning the array

### Example Trace:
For `nums = [2,1,3,5,6], k = 5, multiplier = 2`:

1. Initial heap: `[(1,1), (2,0), (3,2), (5,3), (6,4)]`
2. Operation 1: Pop (1,1) → multiply → Push (2,1)
3. Operation 2: Pop (2,0) → multiply → Push (4,0)
4. Operation 3: Pop (2,1) → multiply → Push (4,1)
5. Operation 4: Pop (3,2) → multiply → Push (6,2)
6. Operation 5: Pop (4,0) → multiply → Push (8,0)
7. Final array: `[8,4,6,5,6]`

## Tags

array, priority queue