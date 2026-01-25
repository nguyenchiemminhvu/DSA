## Problem

https://leetcode.com/problems/most-frequent-ids/description/

You are tracking the frequency of IDs in a collection that changes over time. You have two integer arrays, `nums` and `freq`, of equal length `n`. Each element in `nums` represents an ID, and the corresponding element in `freq` indicates how many times that ID should be added to or removed from the collection at each step.

**Operations:**
- **Addition of IDs**: If `freq[i]` is positive, it means `freq[i]` IDs with the value `nums[i]` are added to the collection at step `i`.
- **Removal of IDs**: If `freq[i]` is negative, it means `-freq[i]` IDs with the value `nums[i]` are removed from the collection at step `i`.

**Task**: Return an array `ans` of length `n`, where `ans[i]` represents the count of the most frequent ID in the collection after the `i`th step. If the collection is empty at any step, `ans[i]` should be 0 for that step.

### Example 1:
```
Input: nums = [2,3,2,1], freq = [3,2,-3,1]
Output: [3,3,2,2]

Explanation:
- After step 0: 3 IDs with value 2 → ans[0] = 3
- After step 1: 3 IDs with value 2, 2 IDs with value 3 → ans[1] = 3
- After step 2: 2 IDs with value 3 → ans[2] = 2
- After step 3: 2 IDs with value 3, 1 ID with value 1 → ans[3] = 2
```

### Example 2:
```
Input: nums = [5,5,3], freq = [2,-2,1]
Output: [2,0,1]

Explanation:
- After step 0: 2 IDs with value 5 → ans[0] = 2
- After step 1: no IDs → ans[1] = 0
- After step 2: 1 ID with value 3 → ans[2] = 1
```

### Constraints:
- `1 <= nums.length == freq.length <= 10^5`
- `1 <= nums[i] <= 10^5`
- `-10^5 <= freq[i] <= 10^5`
- `freq[i] != 0`
- The input guarantees that the occurrences of an ID will not be negative at any step.

## Observations

1. **Dynamic Frequency Tracking**: At each step, we need to:
   - Update the frequency of a specific ID
   - Find the maximum frequency among all IDs

2. **Naive Approach Issues**: 
   - Simply iterating through all IDs to find the max after each update would be O(n²) or O(n·m) where m is the number of unique IDs
   - For `n = 10^5`, this would be too slow

3. **Max Heap Insight**:
   - We need to efficiently track the maximum frequency
   - A max heap can give us O(log n) insertion and O(1) access to the maximum
   - However, frequencies change over time, so heap entries can become stale

4. **Lazy Deletion Strategy**:
   - Instead of actively removing/updating entries in the heap, we can use lazy deletion
   - Keep stale entries in the heap, but validate them when accessing the top
   - Clean up stale entries only when necessary (when they reach the top)

5. **Key Data Structures**:
   - **Counter/HashMap**: Track the current frequency of each ID - O(1) update and lookup
   - **Max Heap**: Track frequencies to quickly find the maximum - O(log n) insertion

## Solution

### Algorithm

The solution uses a **max heap with lazy deletion** combined with a **frequency counter**:

```python
import heapq
from collections import defaultdict

class Solution:
    def mostFrequentIDs(self, nums: List[int], freq: List[int]) -> List[int]:
        n = len(nums)
        res = [0] * n
        counter = defaultdict(int)  # Tracks actual frequency of each ID
        pq = []  # Max heap (using negative values for min heap)
        
        for i in range(n):
            val, f = nums[i], freq[i]
            
            # Step 1: Update the counter
            counter[val] += f
            
            # Step 2: Remove old entries for this specific ID
            while pq and pq[0][1] == val:
                heapq.heappop(pq)
            
            # Step 3: Clean up stale entries at the top
            while pq and (counter[pq[0][1]] == 0 or counter[pq[0][1]] != -pq[0][0]):
                heapq.heappop(pq)
            
            # Step 4: Add new frequency to heap if not zero
            if counter[val] != 0:
                heapq.heappush(pq, (-counter[val], val))
            
            # Step 5: Get the max frequency (top of heap)
            if pq:
                res[i] = -pq[0][0]
        
        return res
```

### Step-by-Step Breakdown

1. **Initialize Data Structures**:
   - `counter`: Dictionary to store the current frequency of each ID
   - `pq`: Min heap (simulating max heap using negative values)
   - `res`: Result array to store answers

2. **For Each Step**:
   
   a. **Update Counter**: 
      ```python
      counter[val] += f
      ```
      - Add/subtract the frequency for the current ID
   
   b. **Remove Old Entries for Current ID**:
      ```python
      while pq and pq[0][1] == val:
          heapq.heappop(pq)
      ```
      - Remove all heap entries that match the current ID being updated
      - This prevents duplicates since we're about to push a new entry
   
   c. **Lazy Deletion - Clean Stale Entries**:
      ```python
      while pq and (counter[pq[0][1]] == 0 or counter[pq[0][1]] != -pq[0][0]):
          heapq.heappop(pq)
      ```
      - Remove entries where:
        - The ID's counter is now 0 (removed from collection)
        - The heap frequency doesn't match the counter (stale entry)
   
   d. **Push New Frequency**:
      ```python
      if counter[val] != 0:
          heapq.heappush(pq, (-counter[val], val))
      ```
      - Add the updated frequency to the heap (if non-zero)
      - Use negative value to simulate max heap
   
   e. **Record Result**:
      ```python
      if pq:
          res[i] = -pq[0][0]
      ```
      - The top of heap has the maximum frequency
      - Negate back to get positive value

### Why This Works

- **Correctness**: 
  - The `counter` always has the true current frequency
  - The heap may have stale entries, but we clean them when accessing the top
  - After cleaning, the top of heap represents the true maximum frequency

- **Efficiency**:
  - Each heap operation: O(log n)
  - Each step may have multiple pops, but amortized it's O(log n) per operation
  - Overall: **O(n log n)** time complexity
  - Space: **O(n)** for counter and heap

### Example Walkthrough

Let's trace `nums = [2,3,2,1]`, `freq = [3,2,-3,1]`:

**Step 0** (ID=2, freq=+3):
- `counter[2] = 3`
- Push `(-3, 2)` to heap
- Heap: `[(-3, 2)]` → max = 3

**Step 1** (ID=3, freq=+2):
- `counter[3] = 2`
- Push `(-2, 3)` to heap
- Heap: `[(-3, 2), (-2, 3)]` → max = 3

**Step 2** (ID=2, freq=-3):
- `counter[2] = 0`
- Remove entries with ID=2: heap becomes `[(-2, 3)]`
- Don't push since counter[2] = 0
- Heap: `[(-2, 3)]` → max = 2

**Step 3** (ID=1, freq=+1):
- `counter[1] = 1`
- Push `(-1, 1)` to heap
- Heap: `[(-2, 3), (-1, 1)]` → max = 2

Result: `[3, 3, 2, 2]` ✓

### Complexity Analysis

- **Time Complexity**: O(n log n)
  - Each of n steps involves O(log n) heap operations
  - Lazy deletion amortizes the cleanup cost

- **Space Complexity**: O(n)
  - Counter: O(unique IDs) ≤ O(n)
  - Heap: O(entries) ≤ O(n)

### Key Insights

1. **Lazy Deletion Pattern**: Instead of actively maintaining heap consistency, validate on access
2. **Heap + HashMap**: Combine fast lookup (counter) with efficient max tracking (heap)
3. **Duplicate Prevention**: Remove old entries for an ID before pushing new ones
4. **Stale Entry Cleanup**: Only clean when necessary (at heap top)

# Tags

`Heap` `Priority Queue` `Hash Map` `Lazy Deletion` `Greedy`

