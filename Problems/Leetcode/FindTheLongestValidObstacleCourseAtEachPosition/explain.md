## Problem

https://leetcode.com/problems/find-the-longest-valid-obstacle-course-at-each-position/

You are given a 0-indexed integer array `obstacles` of length `n`, where `obstacles[i]` describes the height of the i-th obstacle.

For every index `i` between 0 and n - 1 (inclusive), find the length of the longest obstacle course in `obstacles` such that:

1. You choose any number of obstacles between 0 and i inclusive.
2. You must include the i-th obstacle in the course.
3. You must put the chosen obstacles in the same order as they appear in `obstacles`.
4. Every obstacle (except the first) is **taller than or the same height** as the obstacle immediately before it.

Return an array `ans` of length n, where `ans[i]` is the length of the longest obstacle course for index i as described above.

### Examples

**Example 1:**
```
Input: obstacles = [1,2,3,2]
Output: [1,2,3,3]
Explanation: The longest valid obstacle course at each position is:
- i = 0: [1], length 1.
- i = 1: [1,2], length 2.
- i = 2: [1,2,3], length 3.
- i = 3: [1,2,3,2], but [1,2,2] has length 3 (optimal).
```

**Example 2:**
```
Input: obstacles = [2,2,1]
Output: [1,2,1]
Explanation: The longest valid obstacle course at each position is:
- i = 0: [2], length 1.
- i = 1: [2,2], length 2.
- i = 2: [2,2,1], but [1] has length 1 (optimal).
```

**Example 3:**
```
Input: obstacles = [3,1,5,6,4,2]
Output: [1,1,2,3,2,2]
Explanation: The longest valid obstacle course at each position is:
- i = 0: [3], length 1.
- i = 1: [3,1], [1] has length 1.
- i = 2: [3,1,5], [3,5] or [1,5] has length 2.
- i = 3: [3,1,5,6], [3,5,6] or [1,5,6] has length 3.
- i = 4: [3,1,5,6,4], [3,4] or [1,4] has length 2.
- i = 5: [3,1,5,6,4,2], [1,2] has length 2.
```

### Constraints
- `n == obstacles.length`
- `1 <= n <= 10^5`
- `1 <= obstacles[i] <= 10^7`

## Observations

1. **Non-Decreasing Subsequence**: This is fundamentally an **Longest Non-Decreasing Subsequence (LNDS)** problem. We must choose elements in order where each element is **greater than or equal to** the previous one (note: not strictly greater, which makes it different from typical LIS).

2. **Brute Force Approach**: For each position `i`, we could check all previous positions `j` where `obstacles[i] >= obstacles[j]` and track the longest chain. This is O(n²) with memoization.

3. **Greedy Insight**: We can use a **tails array** similar to LIS, where `tails[k]` stores the **smallest ending value** of all non-decreasing subsequences of length `k+1`. However, since we allow equal elements, we need to be careful with the binary search strategy.

4. **Binary Search Advantage**: 
   - The `tails` array is maintained in **non-decreasing order**.
   - For each new element, we find the position where it should go using `bisect_right()` (upper bound).
   - `bisect_right(tails, obstacles[i])` returns the index of the first element strictly greater than `obstacles[i]`.
   - This index directly gives us the length of the longest non-decreasing subsequence ending at position `i`.

5. **Why bisect_right()?**: 
   - For non-decreasing sequences, if we have a tail with value `x`, we can append any value `>= x`.
   - `bisect_right()` finds the position to insert to maintain order, which represents: "how many previous values are `<= obstacles[i]`?"
   - This count + 1 is the length of the longest non-decreasing subsequence ending at `obstacles[i]`.

6. **Updating tails**: After finding the position, if we're extending beyond the current length of `tails`, we append. Otherwise, we update `tails[idx]` to the new (smaller or equal) value. This maintains the invariant that smaller ending values are easier to extend.

## Solution

### Approach: Binary Search with Greedy Tails Array

The key insight is to maintain an array `tails` where:
- `tails[k]` = the **minimum possible ending value** of all non-decreasing subsequences of length `k+1`.
- This array is always kept in **non-decreasing order**.

**Algorithm:**

For each obstacle at index `i`:
1. Use `bisect.bisect_right(tails, obstacles[i])` to find the position where `obstacles[i]` should go.
   - This position represents the length of the longest non-decreasing subsequence ending at `obstacles[i]`.
2. If the position is at the end of `tails`, append the new obstacle (extending the longest sequence).
3. Otherwise, update `tails[position]` with the new obstacle (potentially enabling better future extensions).
4. Store the length in the result array.

**Time Complexity**: O(n log n)
- For each of n elements, we perform a binary search on `tails` (O(log n)).

**Space Complexity**: O(n)
- `tails` array can have at most n elements.
- Result array is always of size n.

### Code

```python
class Solution:
    def longestObstacleCourseAtEachPosition(self, arr: List[int]) -> List[int]:
        n = len(arr)
        res = [1 for _ in range(n)]
        tails = []
        
        for i in range(n):
            # Find the position where arr[i] should be inserted in tails
            # bisect_right returns the index of first element > arr[i]
            idx = bisect.bisect_right(tails, arr[i])
            
            if idx == len(tails):
                # Extending the longest sequence
                tails.append(arr[i])
            else:
                # Update with a smaller/equal value for better future extensions
                tails[idx] = arr[i]
            
            # The length of the longest non-decreasing subsequence is idx + 1
            res[i] = idx + 1
        
        return res
```

### Example Walkthrough: `obstacles = [1,2,3,2]`

| i | obstacles[i] | tails | bisect_right | Action | res[i] |
|---|---|---|---|---|---|
| 0 | 1 | [] | 0 | append 1 | tails=[1] | 1 |
| 1 | 2 | [1] | 1 | append 2 | tails=[1,2] | 2 |
| 2 | 3 | [1,2] | 2 | append 3 | tails=[1,2,3] | 3 |
| 3 | 2 | [1,2,3] | 2 | update tails[2]=2 | tails=[1,2,2] | 3 |

Result: `[1,2,3,3]` ✓

### Example Walkthrough: `obstacles = [3,1,5,6,4,2]`

| i | obstacles[i] | tails | bisect_right | Action | res[i] |
|---|---|---|---|---|---|
| 0 | 3 | [] | 0 | append 3 | tails=[3] | 1 |
| 1 | 1 | [3] | 0 | update tails[0]=1 | tails=[1] | 1 |
| 2 | 5 | [1] | 1 | append 5 | tails=[1,5] | 2 |
| 3 | 6 | [1,5] | 2 | append 6 | tails=[1,5,6] | 3 |
| 4 | 4 | [1,5,6] | 1 | update tails[1]=4 | tails=[1,4,6] | 2 |
| 5 | 2 | [1,4,6] | 1 | update tails[1]=2 | tails=[1,2,6] | 2 |

Result: `[1,1,2,3,2,2]` ✓

# Tags

- **Binary Search**: Using `bisect_right()` for efficient position finding
- **Greedy Algorithm**: Maintaining optimal tails for subsequence extension
- **Dynamic Programming**: Building up longest sequences incrementally
- **Longest Non-Decreasing Subsequence (LNDS)**: Core problem pattern

