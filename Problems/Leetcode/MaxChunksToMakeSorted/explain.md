## Problem

https://leetcode.com/problems/max-chunks-to-make-sorted/description/

```
# Max Chunks To Make Sorted

## Problem Statement

You are given an integer array `arr` of length `n` that represents a permutation of the integers in the range `[0, n - 1]`.

We split `arr` into some number of chunks (i.e., partitions), and individually sort each chunk. After concatenating them, the result should equal the sorted array.

Return the largest number of chunks we can make to sort the array.

### Examples

**Example 1:**
```
Input: arr = [4,3,2,1,0]
Output: 1
Explanation:
Splitting into two or more chunks will not return the required result.
For example, splitting into [4, 3], [2, 1, 0] will result in [3, 4, 0, 1, 2], which isn't sorted.
```

**Example 2:**
```
Input: arr = [1,0,2,3,4]
Output: 4
Explanation:
We can split into two chunks, such as [1, 0], [2, 3, 4].
However, splitting into [1, 0], [2], [3], [4] is the highest number of chunks possible.
```

### Constraints
- `n == arr.length`
- `1 <= n <= 10`
- `0 <= arr[i] < n`
- All the elements of `arr` are unique.

---

## Key Observations

1. **Permutation Property**: The array is a permutation of integers from `0` to `n-1`, meaning each number appears exactly once.

2. **Chunk Validity**: A valid chunk can be formed when we've seen all values in a contiguous range `[cur_min, cur_max]`. Once we have all values in this range, sorting this chunk will put them in the correct positions.

3. **Greedy Approach**: To maximize the number of chunks, we should create a chunk as soon as we encounter a valid one (i.e., we have all values in a contiguous range).

4. **Critical Insight**: For a chunk to be valid:
   - We need to track the minimum value we're looking for (`cur_min`)
   - We need to track the maximum value we've seen so far (`cur_max`)
   - We need to verify that all values between `cur_min` and `cur_max` have been seen

5. **Example Analysis**:
   - `[1,0,2,3,4]`:
     - Position 0-1: We have {1,0}, range [0,1] complete → Chunk 1
     - Position 2: We have {2}, range [2,2] complete → Chunk 2
     - Position 3: We have {3}, range [3,3] complete → Chunk 3
     - Position 4: We have {4}, range [4,4] complete → Chunk 4
     - Total: 4 chunks

   - `[4,3,2,1,0]`:
     - We keep adding elements but never complete a contiguous range until we have all elements
     - Only at the end do we have range [0,4] complete → 1 chunk

---

## Solution Explanation

### Algorithm

The solution uses a **greedy approach** with set-based tracking:

1. **Initialize Variables**:
   - `cur_min`: The next minimum value we're looking for (starts at 0)
   - `found_cur_min`: Flag to check if we've found the current minimum
   - `cur_max`: The maximum value seen in the current potential chunk
   - `s`: A set to track all values seen so far
   - `count`: Number of chunks formed

2. **Iterate Through Array**:
   - Add each element to the set
   - Check if it's the current minimum we're looking for
   - Update the maximum value seen
   
3. **Check for Complete Chunk**:
   - If we've found `cur_min` AND all values in range `[cur_min, cur_max]` are in the set
   - Then we have a valid chunk!
   - Update `cur_min` to `cur_max + 1` (start looking for the next chunk)
   - Increment chunk count
   - Reset flags

4. **Return** the total count of chunks

### Code Walkthrough

```python
class Solution:
    def maxChunksToSorted(self, arr: List[int]) -> int:
        cur_min = 0              # Start looking for 0
        found_cur_min = False    # Haven't found it yet
        cur_max = 0              # Maximum in current chunk
        s = set()                # Track all values seen
        count = 0                # Number of chunks
        i = 0
        
        while i < len(arr):
            s.add(arr[i])        # Add current element
            
            if arr[i] == cur_min:
                found_cur_min = True  # Found the minimum we're looking for
            
            cur_max = max(cur_max, arr[i])  # Update maximum
            
            # Check if we have a complete contiguous range
            if found_cur_min and all(val in s for val in range(cur_min, cur_max + 1)):
                cur_min = cur_max + 1    # Next chunk starts here
                cur_max = cur_min        # Reset max
                count += 1               # Increment chunk count
                found_cur_min = False    # Reset flag
            
            i += 1
        
        return count
```

### Example Trace: `arr = [1,0,2,3,4]`

| i | arr[i] | s | cur_min | cur_max | found_cur_min | Complete Range? | count |
|---|--------|---|---------|---------|---------------|-----------------|-------|
| 0 | 1 | {1} | 0 | 1 | False | No | 0 |
| 1 | 0 | {1,0} | 0 | 1 | True | Yes [0,1] | 1 |
| - | - | - | 2 | 2 | False | - | - |
| 2 | 2 | {1,0,2} | 2 | 2 | True | Yes [2,2] | 2 |
| - | - | - | 3 | 3 | False | - | - |
| 3 | 3 | {1,0,2,3} | 3 | 3 | True | Yes [3,3] | 3 |
| - | - | - | 4 | 4 | False | - | - |
| 4 | 4 | {1,0,2,3,4} | 4 | 4 | True | Yes [4,4] | 4 |

---

## Complexity Analysis

- **Time Complexity**: O(n²)
  - Outer loop: O(n)
  - `all(val in s for val in range(cur_min, cur_max + 1))`: O(n) in worst case
  - Overall: O(n²)

- **Space Complexity**: O(n)
  - Set `s` stores all elements: O(n)

---

## Alternative Approach (More Efficient)

A more efficient O(n) solution uses the observation that we can form a chunk at position `i` if `max(arr[0:i+1]) == i`.

```python
def maxChunksToSorted(self, arr: List[int]) -> int:
    count = 0
    max_so_far = 0
    
    for i in range(len(arr)):
        max_so_far = max(max_so_far, arr[i])
        # If max value seen so far equals current index,
        # we can form a chunk
        if max_so_far == i:
            count += 1
    
    return count
```

**Why this works**: If the maximum value from index 0 to i equals i, it means all values from 0 to i are present in positions 0 to i. After sorting this chunk, each value will be in its correct position.
```

# Tags

