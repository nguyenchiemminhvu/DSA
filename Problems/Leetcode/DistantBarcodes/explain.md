## Problem

https://leetcode.com/problems/distant-barcodes/

```
In a warehouse, there is a row of barcodes, where the ith barcode is barcodes[i].

Rearrange the barcodes so that no two adjacent barcodes are equal. You may return any answer, 
and it is guaranteed an answer exists.

Example 1:
Input: barcodes = [1,1,1,2,2,2]
Output: [2,1,2,1,2,1]

Example 2:
Input: barcodes = [1,1,1,1,2,2,3,3]
Output: [1,3,1,3,1,2,1,2]

Constraints:
- 1 <= barcodes.length <= 10000
- 1 <= barcodes[i] <= 10000
- An answer is guaranteed to exist
```

## Observations

1. **Greedy Approach Works**: We need to ensure no two adjacent elements are the same. The key insight is to always place the most frequent remaining elements first, alternating between different values.

2. **Max Heap Strategy**: By using a max heap (priority queue) based on frequency, we can efficiently retrieve the most frequent elements at each step.

3. **Pairing Elements**: To avoid adjacent duplicates, we take two different elements from the heap at each iteration. We place the most frequent one, then the second most frequent one, ensuring they're different.

4. **Frequency Management**: After placing an element, we decrease its count. If it still has remaining occurrences (count > 0), we push it back to the heap.

5. **Edge Case**: When only one element remains in the heap, we can safely place it since the previous element was different (we just paired it with something else).

## Solution

**Time Complexity**: O(n log k) where n is the length of barcodes and k is the number of unique barcodes.
**Space Complexity**: O(k) for the heap and counter.

### Algorithm Steps:

1. **Count Frequencies**: Use `Counter` to count the frequency of each barcode value.

2. **Build Max Heap**: Create a max heap storing `(-frequency, value)` pairs. We use negative frequency because Python's `heapq` is a min-heap by default.

3. **Greedy Pairing**:
   - While the heap is not empty:
     - Pop the most frequent element (k with frequency v)
     - Add it to the result and decrease its frequency
     - If the heap still has elements:
       - Pop the second most frequent element (kk with frequency vv)
       - Add it to the result and decrease its frequency
       - If vv > 0, push it back to the heap
     - If v > 0, push the first element back to the heap

4. **Why This Works**: By always alternating between the two most frequent remaining elements, we ensure:
   - No two adjacent elements in the result are the same
   - We maximize the distribution of frequent elements
   - The element we just placed won't be immediately reused (unless it's the last one)

### Example Walkthrough:

For `barcodes = [1,1,1,1,2,2,3,3]`:
- Counter: {1: 4, 2: 2, 3: 2}
- Heap: [(-4,1), (-2,2), (-2,3)]
- Iteration 1: Pop 1 (freq 4), pop 2 (freq 2) → result = [1,2], push back 1 (freq 3), push back 2 (freq 1)
- Iteration 2: Pop 1 (freq 3), pop 3 (freq 2) → result = [1,2,1,3], push back 1 (freq 2), push back 3 (freq 1)
- Iteration 3: Pop 1 (freq 2), pop 2 (freq 1) → result = [1,2,1,3,1,2], push back 1 (freq 1)
- Iteration 4: Pop 1 (freq 1), pop 3 (freq 1) → result = [1,2,1,3,1,2,1,3]

Final result: `[1,2,1,3,1,2,1,3]` or similar valid arrangement.

# Tags
#greedy #heap #priority-queue #hash-table #sorting #counting

