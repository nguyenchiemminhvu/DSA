## Problem

https://leetcode.com/problems/make-array-non-decreasing/description/

You are given an integer array `nums`. In one operation, you can select a subarray and replace it with a single element equal to its maximum value.

Return the maximum possible size of the array after performing zero or more operations such that the resulting array is non-decreasing.

**Example 1:**
```
Input: nums = [4,2,5,3,5]
Output: 3

Explanation:
- Replace subarray nums[1..2] = [2, 5] with 5 → [4, 5, 3, 5]
- Replace subarray nums[2..3] = [3, 5] with 5 → [4, 5, 5]
- The final array [4, 5, 5] is non-decreasing with size 3
```

**Example 2:**
```
Input: nums = [1,2,3]
Output: 3

Explanation:
No operation is needed as the array [1,2,3] is already non-decreasing.
```

**Constraints:**
- `1 <= nums.length <= 2 * 10^5`
- `1 <= nums[i] <= 2 * 10^5`

## Observations

### 1. **Greedy Strategy**
When we replace a subarray with its maximum value, we want to maximize the remaining array size. The key insight is: **we should keep elements that can form a non-decreasing sequence**.

### 2. **When to Merge Elements**
If we encounter an element that is smaller than a previous element, we have two choices:
- Remove the current element (merge it into a previous group)
- Remove previous elements (merge them with the current element)

To maximize size, we should merge as few elements as possible.

### 3. **Monotonic Stack Pattern**
The solution uses a **monotonic stack** to find, for each position `i`, the next position `j` where `nums[j] >= nums[i]`. This helps identify which elements can potentially stay in the final array.

### 4. **Key Insight: "Right Greater or Equal" Index**
For each element at index `i`, we find `right_gt[i]` = the next index `j` where `nums[j] >= nums[i]`.
- If such `j` exists, all elements between `i` and `j` (exclusive) must be merged
- These elements are smaller than `nums[i]` and appear before `nums[j]`, creating a violation

### 5. **Counting Remaining Elements**
Starting from index 0:
- Keep the element at index `i`
- Find the next element that can be kept (at `right_gt[i]`)
- All elements between them must be removed (merged)
- Continue this process until reaching the end

## Solution

### Algorithm

```python
class Solution:
    def maximumPossibleSize(self, nums: List[int]) -> int:
        n = len(nums)
        
        # Step 1: Build right_gt array using monotonic stack
        right_gt = [n] * n  # Default: no greater/equal element found
        st = []
        
        for i in range(n - 1, -1, -1):
            # Pop elements smaller than nums[i]
            while st and nums[st[-1]] < nums[i]:
                st.pop()
            
            # Top of stack is the next greater or equal element
            if st:
                right_gt[i] = st[-1]
            
            st.append(i)
        
        # Step 2: Count remaining elements
        i = 0
        remain = n
        
        while i < n:
            right = right_gt[i]
            # Remove elements between i and right (exclusive)
            remain -= (right - i - 1)
            i = right
        
        return remain
```

### Detailed Walkthrough

#### Step 1: Build `right_gt` Array

**Purpose:** For each index `i`, find the nearest index `j > i` where `nums[j] >= nums[i]`.

**Example:** `nums = [4, 2, 5, 3, 5]`

Process from right to left, maintaining a monotonic stack:

| i | nums[i] | Stack before | Action | Stack after | right_gt[i] |
|---|---------|--------------|--------|-------------|-------------|
| 4 | 5 | [] | Add 4 | [4] | 5 (none) |
| 3 | 3 | [4] | nums[4]=5 >= 3, Add 3 | [4, 3] | 4 |
| 2 | 5 | [4, 3] | Pop 3 (3<5), keep 4 (5≥5), Add 2 | [4, 2] | 4 |
| 1 | 2 | [4, 2] | nums[2]=5 >= 2, Add 1 | [4, 2, 1] | 2 |
| 0 | 4 | [4, 2, 1] | Pop 1 (2<4), nums[2]=5 >= 4, Add 0 | [4, 2, 0] | 2 |

Result: `right_gt = [2, 2, 4, 4, 5]`

#### Step 2: Count Remaining Elements

Start with `remain = 5` (all elements):

| i | right_gt[i] | Elements removed (indices) | Calculation | remain |
|---|-------------|---------------------------|-------------|--------|
| 0 | 2 | Index 1 | 5 - (2-0-1) = 5 - 1 | 4 |
| 2 | 4 | Index 3 | 4 - (4-2-1) = 4 - 1 | 3 |
| 4 | 5 | None | 3 - (5-4-1) = 3 - 0 | 3 |
| 5 | End loop | - | - | **3** |

**Final Answer: 3** ✓

The kept elements form the sequence: `[4, 5, 5]`
- Element at index 0: `4`
- Element at index 2: `5` (after merging [2,5])
- Element at index 4: `5` (after merging [3,5])

### Why This Works

1. **Monotonic Stack finds next valid position:** For each element, we find the next position where we can "jump" to while maintaining non-decreasing order.

2. **Greedy removal:** All elements between position `i` and `right_gt[i]` are smaller than `nums[i]` and must come before `nums[right_gt[i]]`. They cannot form a valid non-decreasing sequence, so they must be merged.

3. **Optimal partitioning:** By always jumping to the next valid position, we partition the array optimally, keeping the maximum number of "anchor" elements that can form a non-decreasing sequence.

### Visual Example

```
nums = [4, 2, 5, 3, 5]
      ↓     ↓     ↓
Keep: 0     2     4

Partitions:
[4] → merge nothing → 4
[2, 5] → merge together → 5  
[3, 5] → merge together → 5

Result: [4, 5, 5] with size 3
```

### Complexity Analysis

**Time Complexity:** O(n)
- Building `right_gt` array: O(n) - each element is pushed and popped from stack at most once
- Counting remaining elements: O(n) - we visit each "segment" once

**Space Complexity:** O(n)
- `right_gt` array: O(n)
- Monotonic stack: O(n) in worst case

# Tags

`Array` `Stack` `Monotonic Stack` `Greedy`

