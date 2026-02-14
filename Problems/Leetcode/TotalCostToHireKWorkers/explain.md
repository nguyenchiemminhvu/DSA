## Problem

https://leetcode.com/problems/total-cost-to-hire-k-workers/

You are given a 0-indexed integer array `costs` where `costs[i]` is the cost of hiring the ith worker.

You are also given two integers `k` and `candidates`. We want to hire exactly k workers according to the following rules:

- You will run k sessions and hire exactly one worker in each session.
- In each hiring session, choose the worker with the lowest cost from either the first `candidates` workers or the last `candidates` workers. Break the tie by the smallest index.
- If there are fewer than `candidates` workers remaining, choose the worker with the lowest cost among them. Break the tie by the smallest index.
- A worker can only be chosen once.

Return the total cost to hire exactly k workers.

**Example 1:**
```
Input: costs = [17,12,10,2,7,2,11,20,8], k = 3, candidates = 4
Output: 11
Explanation: We hire 3 workers in total.
- Round 1: Choose from [17,12,10,2,7,2,11,20,8]. Lowest cost is 2 at index 3. Total = 2.
- Round 2: Choose from [17,12,10,7,2,11,20,8]. Lowest cost is 2 at index 4. Total = 4.
- Round 3: Choose from [17,12,10,7,11,20,8]. Lowest cost is 7 at index 3. Total = 11.
```

**Example 2:**
```
Input: costs = [1,2,4,1], k = 3, candidates = 3
Output: 4
```

**Constraints:**
- `1 <= costs.length <= 10^5`
- `1 <= costs[i] <= 10^5`
- `1 <= k, candidates <= costs.length`

## Observations

1. **Two groups of candidates**: At each hiring session, we must consider the first `candidates` workers and the last `candidates` workers. These two groups may overlap if `2 * candidates >= n`.

2. **Min-heap for efficiency**: Since we need to repeatedly find the minimum cost worker from the candidate pool, a min-heap (priority queue) is ideal. Each element stores `(cost, index)` to break ties by index.

3. **Dynamic candidate pool**: After hiring a worker, we need to add a new candidate to replace them:
   - If we hired from the left group, add the next worker from the left (increment left pointer)
   - If we hired from the right group, add the next worker from the right (decrement right pointer)

4. **Edge case - overlapping groups**: When `2 * candidates >= n`, the two groups overlap completely. In this case, all workers are candidates from the start, and we don't need to track left/right pointers.

5. **Marking chosen workers**: We need to track which workers have been chosen to avoid selecting them twice when they appear in both groups.

## Solution

The solution uses a **two-pointer approach with a min-heap**:

### Algorithm

1. **Initialize pointers and heap**:
   - `l` (left pointer) starts at 0
   - `r` (right pointer) starts at `n-1`
   - Create a min-heap to store `(cost, index)` pairs

2. **Handle overlapping case**:
   - If `2 * candidates >= n`, all workers are candidates
   - Add all workers to the heap and set pointers so no more workers will be added

3. **Add initial candidates**:
   - Add first `candidates` workers from the left
   - Add last `candidates` workers from the right

4. **Hire k workers**:
   - For each of k hiring sessions:
     - Skip any workers already chosen (using `chosen` array)
     - Pop the minimum from the heap (lowest cost, smallest index)
     - Add its cost to the result
     - Mark the worker as chosen
     - If there are still workers between `l` and `r`:
       - If hired worker was from left group, add `costs[l]` and increment `l`
       - If hired worker was from right group, add `costs[r]` and decrement `r`

### Complexity Analysis

- **Time Complexity**: O(n log n) in the worst case
  - Initial heap construction: O(candidates log candidates) ≈ O(n log n)
  - Each of k hiring sessions: O(log n) for heap operations
  - Total: O((k + candidates) log n)

- **Space Complexity**: O(n)
  - Heap stores at most 2*candidates elements: O(candidates)
  - `chosen` array: O(n)
  - Total: O(n)

### Key Implementation Details

- The `chosen` array prevents double-hiring when workers appear in both left and right candidate groups
- The condition `l <= r` ensures we only add new candidates when there are unprocessed workers remaining
- The heap automatically handles tie-breaking by index since tuples are compared element-by-element in Python

# Tags
`Heap` `Priority Queue` `Two Pointers` `Greedy`

