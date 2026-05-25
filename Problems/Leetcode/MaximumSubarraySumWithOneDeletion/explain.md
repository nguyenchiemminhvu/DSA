## Problem

https://leetcode.com/problems/maximum-subarray-sum-with-one-deletion/description/

# Maximum Subarray Sum With One Deletion

## Problem

https://leetcode.com/problems/maximum-subarray-sum-with-one-deletion/description/

Given an array of integers, return the maximum sum for a non-empty subarray (contiguous elements) with **at most one element deletion**. In other words, you want to choose a subarray and optionally delete one element from it so that there is still at least one element left and the sum of the remaining elements is maximum possible.

**Constraint:** The subarray needs to be non-empty after deleting one element.

### Examples

**Example 1:**
- **Input:** `arr = [1,-2,0,3]`
- **Output:** `4`
- **Explanation:** We can choose `[1, -2, 0, 3]` and drop `-2`, resulting in subarray `[1, 0, 3]` with sum 4.

**Example 2:**
- **Input:** `arr = [1,-2,-2,3]`
- **Output:** `3`
- **Explanation:** We choose `[3]` with the maximum sum.

**Example 3:**
- **Input:** `arr = [-1,-1,-1,-1]`
- **Output:** `-1`
- **Explanation:** The final subarray must be non-empty. We can only choose one element.

### Constraints

- $1 \leq \text{arr.length} \leq 10^5$
- $-10^4 \leq \text{arr}[i] \leq 10^4$

---

## Observations

1. **Dynamic Programming with Two States:** We must track two distinct scenarios at each position:
   - **No deletion used:** Maximum sum of subarray ending at $i$ without any deletion
   - **One deletion used:** Maximum sum of subarray ending at $i$ with exactly one deletion (or we can treat it as "at most one")

2. **State Transition Logic:**
   - For the **no deletion** state, this is the classic Kadane's algorithm:
     - $\text{no\_del}[i] = \max(\text{no\_del}[i-1] + \text{arr}[i], \text{arr}[i])$
     - Either extend the previous subarray or start a new one
   
   - For the **with deletion** state, we have two choices:
     - **Option A:** Add current element to an existing subarray that already had one deletion
     - **Option B:** Delete the current element and carry forward the best no-deletion subarray from $i-1$
     - $\text{with\_del}[i] = \max(\text{with\_del}[i-1] + \text{arr}[i], \text{no\_del}[i-1])$
     - Option B is key: by using `no_del[i-1]`, we're effectively saying "skip position $i$ and use what we had before"

3. **Why This Works:**
   - The deletion represents a gap of exactly one element in the subarray
   - We don't need to track which element was deleted—we only need the best sum achievable at each point
   - The `with_del` state can incorporate any previous deletion state, allowing the deleted element to be anywhere in the subarray

4. **Order of Updates Matters:**
   - We must update `cur_with_del` **before** `cur_without_del` 
   - This ensures `cur_with_del` uses the old `cur_without_del` value when choosing `max(cur_with_del + arr[i], cur_without_del)`
   - If we updated in reverse order, we'd accidentally use the new `cur_without_del` value

5. **Edge Cases:**
   - **All negative:** Must pick at least one element, so return the least negative
   - **Single element:** Cannot achieve non-empty subarray if we delete it, so return that element
   - **Optimal deletion:** Most useful when a single large negative number is surrounded by positives

---

## Solution

```python
class Solution:
    def maximumSum(self, arr: List[int]) -> int:
        n = len(arr)
        
        # Initialize with first element
        max_all = arr[0]           # Global maximum sum found so far
        cur_without_del = arr[0]   # Best subarray sum ending at position i, no deletion
        cur_with_del = arr[0]      # Best subarray sum ending at position i, with ≤1 deletion
        
        for i in range(1, n):
            # UPDATE ORDER IS CRITICAL: with_del first, then without_del
            
            # Option 1: Add current element to existing deletion state
            # Option 2: Skip current element (delete it), use previous non-deletion state
            cur_with_del = max(cur_with_del + arr[i], cur_without_del)
            
            # Standard Kadane's: extend previous or start fresh
            cur_without_del = max(cur_without_del + arr[i], arr[i])
            
            # Track the global maximum
            max_all = max(max_all, cur_with_del, cur_without_del)
        
        return max_all
```

### Detailed Walkthrough

**Example 1: `arr = [1, -2, 0, 3]`**

| Step | i | arr[i] | without_del | with_del | max_all | Explanation |
|------|---|--------|------------|----------|---------|-------------|
| Init | - | - | 1 | 1 | 1 | Start with arr[0] |
| 1 | 1 | -2 | max(1-2, -2)=-1 | max(1-2, 1)=1 | 1 | Extend gives -1, restart gives -2. Skip -2 gives 1. |
| 2 | 2 | 0 | max(-1+0, 0)=0 | max(1+0, -1)=1 | 1 | No deletion: fresh start better. With deletion: extend old state. |
| 3 | 3 | 3 | max(0+3, 3)=3 | max(1+3, 0)=**4** | **4** | **Best:** subarray [1,-2,0,3] with -2 deleted = [1,0,3] = 4 |

**Example 2: `arr = [1, -2, -2, 3]`**

| Step | i | arr[i] | without_del | with_del | max_all | Explanation |
|------|---|--------|------------|----------|---------|-------------|
| Init | - | - | 1 | 1 | 1 | Start with arr[0] |
| 1 | 1 | -2 | max(1-2, -2)=-1 | max(1-2, 1)=1 | 1 | Similar to example 1 |
| 2 | 2 | -2 | max(-1-2, -2)=-2 | max(1-2, -1)=-1 | 1 | Both states worsen |
| 3 | 3 | 3 | max(-2+3, 3)=**3** | max(-1+3, -2)=2 | **3** | Restart fresh is best (just [3]) |

---

## Complexity Analysis

| Aspect | Complexity | Notes |
|--------|-----------|-------|
| **Time** | $O(n)$ | Single pass through the array |
| **Space** | $O(1)$ | Only three variables, no extra data structures |

---

## Key Insights

1. **Two-State DP:** Problems involving "at most k operations" often require tracking $k+1$ states (before op, after 1st op, after 2nd op, etc.)

2. **Update Order Critical:** Always update dependent states before dependencies to avoid using updated values incorrectly.

3. **Implicit Deletion Position:** We don't track *which* element was deleted—the DP handles all possibilities through state transitions.

4. **Generalization:** 
   - For "at most 0 deletions" → Classic Kadane's (just `without_del`)
   - For "at most 1 deletion" → Current solution (2 states)
   - For "at most k deletions" → Would need $k+1$ states (more complex)

5. **Why Greedy Fails:** Unlike selecting k maximum elements, we need **contiguous** elements. A greedy approach of "skip the minimum element" doesn't always work because that element might break an optimal subarray.

---

## Tags

- Dynamic Programming
- Array
- Kadane's Algorithm
- Greedy
- Subarray Problems

## Observations

## Solution

# Tags

