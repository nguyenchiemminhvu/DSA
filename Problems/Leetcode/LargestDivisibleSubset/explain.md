## Problem

https://leetcode.com/problems/largest-divisible-subset/description

# Largest Divisible Subset

## Problem

https://leetcode.com/problems/largest-divisible-subset/description

Given a set of distinct positive integers `nums`, return the largest subset `answer` such that every pair `(answer[i], answer[j])` of elements in this subset satisfies:

- `answer[i] % answer[j] == 0`, or
- `answer[j] % answer[i] == 0`

If there are multiple solutions, return any of them.

### Examples

**Example 1:**
```
Input: nums = [1,2,3]
Output: [1,2]
Explanation: [1,3] is also accepted.
```

**Example 2:**
```
Input: nums = [1,2,4,8]
Output: [1,2,4,8]
```

### Constraints

- `1 <= nums.length <= 1000`
- `1 <= nums[i] <= 2 * 10^9`
- All the integers in `nums` are unique.

---

## Observations

### Key Insight: Transitivity Property

The crucial observation is that divisibility has a **transitive property**:
- If `a % b == 0` and `b % c == 0`, then `a % c == 0`

This means that if we sort the array and find pairs where each element divides the next, we automatically satisfy the constraint for all pairs in the chain.

### Building a Valid Chain

If we sort the array, we can build divisible subsets as **chains** where:
$$\text{a}_1 | \text{a}_2 | \text{a}_3 | \ldots | \text{a}_k$$

(where `|` means "divides")

This is similar to finding the **Longest Increasing Subsequence (LIS)**, but instead of comparing values directly, we check divisibility relationships.

### Why Sorting Helps

After sorting, if we find a valid chain ending at index `i`, any element we add to it must be divisible by the last element in the chain. We only need to look backward through previously processed elements.

---

## Solution Approach: Dynamic Programming

### Algorithm Overview

This solution uses **Dynamic Programming with backtracking**:

1. **Sort the array** to establish a partial order
2. **Build a DP table** where `dp[i]` = length of the longest divisible chain ending at `nums[i]`
3. **Track parent pointers** to reconstruct the actual chain
4. **Backtrack** from the longest chain to build the result

### Step-by-Step Breakdown

**Initialization:**
```python
nums.sort()                    # Sort to enable the chain property
n = len(nums)
dp = [1] * n                  # Each number forms a chain of length 1
parent = [-1] * n             # Track the previous element in the chain
max_dp = 1                    # Track the longest chain found
max_dp_idx = 0                # Track where the longest chain ends
```

**DP Transition:**
```python
for i in range(n):
    for j in range(i):        # Look at all smaller indices
        if nums[i] % nums[j] == 0:  # Can we extend chain from j to i?
            if dp[i] < 1 + dp[j]:   # If this creates a longer chain
                dp[i] = 1 + dp[j]   # Update chain length
                parent[i] = j       # Mark j as predecessor
```

For each element at index `i`, we check all previous elements at index `j`:
- If `nums[i]` is divisible by `nums[j]`, we can extend the chain ending at `j`
- We update `dp[i]` if this extension creates a longer chain than what we had before

**Reconstruction:**
```python
res = []
while max_dp_idx != -1:
    res.append(nums[max_dp_idx])  # Add current element
    max_dp_idx = parent[max_dp_idx]  # Move to predecessor
return res
```

We follow the parent pointers backward from the longest chain to build the result.

### Example Walkthrough

**Input:** `nums = [1,2,4,8]`

After sorting: `[1,2,4,8]`

| i | nums[i] | dp[i] | parent[i] | Explanation |
|---|---------|-------|-----------|------------|
| 0 | 1 | 1 | -1 | Start: chain is just [1] |
| 1 | 2 | 2 | 0 | 2 % 1 == 0, extend: [1,2] |
| 2 | 4 | 3 | 1 | 4 % 2 == 0, extend: [1,2,4] |
| 3 | 8 | 4 | 2 | 8 % 4 == 0, extend: [1,2,4,8] |

**Reconstruction from max_dp_idx = 3:**
- Add nums[3] = 8, parent[3] = 2
- Add nums[2] = 4, parent[2] = 1
- Add nums[1] = 2, parent[1] = 0
- Add nums[0] = 1, parent[0] = -1 (stop)

**Output:** `[8,4,2,1]` (or in any order)

### Complexity Analysis

**Time Complexity:** $O(n^2)$
- Outer loop: $O(n)$ iterations
- Inner loop: $O(n)$ comparisons in worst case
- Total: $O(n^2)$

**Space Complexity:** $O(n)$
- `dp` array: $O(n)$
- `parent` array: $O(n)$
- Result array: $O(n)$

---

## Tags

`Dynamic Programming` | `Longest Subsequence` | `Number Theory` | `Greedy` | `Backtracking`
