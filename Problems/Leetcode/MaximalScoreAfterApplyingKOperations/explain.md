## Problem

https://leetcode.com/problems/maximal-score-after-applying-k-operations/description/

```
You are given a 0-indexed integer array nums and an integer k. You have a starting score of 0.

In one operation:
- choose an index i such that 0 <= i < nums.length,
- increase your score by nums[i], and
- replace nums[i] with ceil(nums[i] / 3).

Return the maximum possible score you can attain after applying exactly k operations.

The ceiling function ceil(val) is the least integer greater than or equal to val.

Example 1:
Input: nums = [10,10,10,10,10], k = 5
Output: 50
Explanation: Apply the operation to each array element exactly once. 
The final score is 10 + 10 + 10 + 10 + 10 = 50.

Example 2:
Input: nums = [1,10,3,3,3], k = 3
Output: 17
Explanation: You can do the following operations:
Operation 1: Select i = 1, so nums becomes [1,4,3,3,3]. Your score increases by 10.
Operation 2: Select i = 1, so nums becomes [1,2,3,3,3]. Your score increases by 4.
Operation 3: Select i = 2, so nums becomes [1,2,1,3,3]. Your score increases by 3.
The final score is 10 + 4 + 3 = 17.

Constraints:
- 1 <= nums.length, k <= 10^5
- 1 <= nums[i] <= 10^9
```

## Observations

1. **Greedy Approach**: To maximize the score, we should always pick the largest available element in each operation. This is because:
   - We want to accumulate the highest possible scores
   - After using an element, it gets reduced to ceil(val/3), making it smaller
   - The largest element gives us the best immediate gain

2. **Max Heap Structure**: A max heap is ideal for this problem because:
   - We need to efficiently extract the maximum element (O(log n))
   - After modifying the element, we need to insert it back (O(log n))
   - Each operation takes O(log n) time

3. **Ceiling Division Trick**: The expression `(score + 2) // 3` is equivalent to `ceil(score / 3)`:
   - For integers, ceil(a/b) = (a + b - 1) // b
   - So ceil(score/3) = (score + 3 - 1) // 3 = (score + 2) // 3

4. **Time Complexity**: O(n log n + k log n)
   - O(n log n) to build the initial heap
   - O(k log n) for k operations, each involving pop and push

## Solution

The solution uses a **greedy approach with a max heap**:

1. **Initialize Max Heap**: Insert all elements from nums into a max heap. Python's heapq only provides min heap, so we use negative values to simulate a max heap.

2. **Process K Operations**:
   - Extract the maximum element from the heap
   - Add this element to the result score
   - Calculate the new value: ceil(element / 3) = (element + 2) // 3
   - Push the new value back into the heap
   - Decrement k

3. **Return Result**: After k operations, return the accumulated score.

**Why this works**: At each step, choosing the maximum element guarantees we get the highest possible score for that operation. Since we must perform exactly k operations and each operation reduces the selected element, greedily taking the maximum at each step yields the optimal total score.

**Key Implementation Details**:
- Custom max_heap class wraps Python's min heap with negation
- `__bool__` method allows checking if heap is empty with `if heap:`
- The ceiling division `(score + 2) // 3` avoids floating point operations

# Tags
#greedy #heap #priority-queue #max-heap

