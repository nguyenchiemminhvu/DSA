## Problem

https://leetcode.com/problems/longest-consecutive-sequence/description

```
## Problem

https://leetcode.com/problems/longest-consecutive-sequence/description

Given an unsorted array of integers `nums`, return the length of the longest consecutive elements sequence.

You must write an algorithm that runs in **O(n) time**.

### Examples:

**Example 1:**
```
Input: nums = [100,4,200,1,3,2]
Output: 4
Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Therefore its length is 4.
```

**Example 2:**
```
Input: nums = [0,3,7,2,5,8,4,6,0,1]
Output: 9
Explanation: The longest consecutive elements sequence is [0, 1, 2, 3, 4, 5, 6, 7, 8]. Therefore its length is 9.
```

**Example 3:**
```
Input: nums = [1,0,1,2]
Output: 3
Explanation: The longest consecutive elements sequence is [0, 1, 2]. Therefore its length is 3 (duplicates are removed).
```

### Constraints:
- `0 <= nums.length <= 10^5`
- `-10^9 <= nums[i] <= 10^9`

---

## Observations

1. **Order doesn't matter**: The input is unsorted, and we need to find consecutive elements regardless of their order in the array.

2. **Duplicates don't matter**: If the array has duplicates (e.g., Example 3), we only count unique elements.

3. **Naive approach is slow**: A naive approach using sorting would be O(n log n), which violates the O(n) time requirement.

4. **Set lookup is O(1)**: Converting the array to a set gives us O(1) lookup time for checking if a number exists.

5. **Start from sequence beginnings**: Instead of checking every number, we should only start counting from numbers that are the beginning of a sequence (i.e., numbers where `val - 1` is NOT in the set).

6. **Each element is visited once**: While it seems like we have nested loops, each element is visited and counted only once:
   - When we process a number that starts a sequence, we count all consecutive numbers following it
   - We never recount these numbers because they won't be the start of a new sequence (their predecessor exists)

---

## Solution

```python
class Solution:
    def longestConsecutive(self, nums: List[int]) -> int:
        res = 0
        s = set(nums)
        
        for val in s:
            # Only start counting from the beginning of a sequence
            if val - 1 not in s:
                # val is the start of a sequence
                cur = 1
                
                # Count consecutive elements
                while val + 1 in s:
                    val += 1
                    cur += 1
                
                # Update the maximum length
                res = max(res, cur)
        
        return res
```

### Algorithm Explanation:

1. **Convert to Set**: Convert the input array to a set for O(1) lookup time.
   ```
   nums = [100,4,200,1,3,2] → s = {1, 2, 3, 4, 100, 200}
   ```

2. **Iterate through set**: For each unique value in the set:
   - Check if `val - 1` exists in the set
   - If it doesn't exist, `val` is the start of a consecutive sequence

3. **Count consecutive sequence**: If `val` is the start of a sequence:
   - Initialize counter to 1
   - Keep checking if the next consecutive number (`val + 1`) exists
   - Keep incrementing `val` and the counter
   - Stop when the next consecutive number doesn't exist

4. **Track maximum**: Keep track of the longest sequence found.

### Step-by-step Walkthrough (Example 1):

Input: `nums = [100,4,200,1,3,2]`

| Iteration | val | val-1 in s? | Is Start? | Count | Sequence |
|-----------|-----|------------|-----------|-------|----------|
| 1         | 1   | No (0∉s)   | ✓ YES     | 4     | [1,2,3,4] |
| 2         | 2   | Yes (1∈s)  | ✗ NO      | -     | (skip)   |
| 3         | 3   | Yes (2∈s)  | ✗ NO      | -     | (skip)   |
| 4         | 4   | Yes (3∈s)  | ✗ NO      | -     | (skip)   |
| 5         | 100 | No (99∉s)  | ✓ YES     | 1     | [100]    |
| 6         | 200 | No (199∉s) | ✓ YES     | 1     | [200]    |

**Result**: max(4, 1, 1) = **4**

### Time and Space Complexity:

- **Time Complexity: O(n)**
  - Creating the set: O(n)
  - Iterating through the set: O(n)
  - Each element is visited at most twice (once in the outer loop, once in the while loop across all iterations)
  - Total: O(n)

- **Space Complexity: O(n)**
  - The set stores up to n unique elements

### Key Insight:

The solution is O(n) because even though there appear to be nested loops, each element is only processed a constant number of times:
- Each number from the input is visited exactly once in the outer loop
- Each number is counted in the inner while loop exactly once (when it's part of a sequence)
- A number that is not the start of a sequence is skipped in the outer loop

This is a clever optimization that avoids the O(n log n) cost of sorting while maintaining O(n) time complexity.

---

## Tags

- Hash Set
- Array
- Optimization
- Time Complexity: O(n)
```

## Observations

## Solution

# Tags

