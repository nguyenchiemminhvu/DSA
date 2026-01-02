## Problem

https://leetcode.com/problems/count-bowl-subarrays/description/

You are given an integer array `nums` with distinct elements.

A subarray `nums[l...r]` of `nums` is called a **bowl** if:
- The subarray has length at least 3. That is, `r - l + 1 >= 3`.
- The minimum of its two ends is strictly greater than the maximum of all elements in between. That is, `min(nums[l], nums[r]) > max(nums[l + 1], ..., nums[r - 1])`.

Return the number of bowl subarrays in `nums`.

**Example 1:**
```
Input: nums = [2,5,3,1,4]
Output: 2
Explanation:
The bowl subarrays are [3, 1, 4] and [5, 3, 1, 4].
- [3, 1, 4] is a bowl because min(3, 4) = 3 > max(1) = 1.
- [5, 3, 1, 4] is a bowl because min(5, 4) = 4 > max(3, 1) = 3.
```

**Example 2:**
```
Input: nums = [5,1,2,3,4]
Output: 3
Explanation:
The bowl subarrays are [5, 1, 2], [5, 1, 2, 3] and [5, 1, 2, 3, 4].
```

**Example 3:**
```
Input: nums = [1000000000,999999999,999999998]
Output: 0
Explanation: No subarray is a bowl.
```

**Constraints:**
- `3 <= nums.length <= 10^5`
- `1 <= nums[i] <= 10^9`
- `nums` consists of distinct elements.

## Observations

1. **Bowl Subarray Definition**: For a subarray `[l, r]` to be a bowl:
   - Length must be at least 3
   - `min(nums[l], nums[r]) > max(nums[l+1], ..., nums[r-1])`
   - This means both endpoints must be higher than all middle elements

2. **Key Insight**: If we fix a middle element `nums[i]`, we need to find:
   - The nearest element to the left that is strictly greater than `nums[i]`
   - The nearest element to the right that is strictly greater than `nums[i]`
   - If both exist, they form a bowl with `nums[i]` as the maximum middle element

3. **Monotonic Stack Pattern**: 
   - We can use a monotonic stack to find for each element:
     - `left[i]`: index of the nearest greater element to the left
     - `right[i]`: index of the nearest greater element to the right

4. **Why This Works**:
   - For each element `nums[i]` in the middle of a potential bowl
   - If `left[i]` and `right[i]` exist, then `nums[left[i]]` and `nums[right[i]]` are both greater than `nums[i]`
   - Since they are the **nearest** greater elements, all elements between them and `nums[i]` are smaller
   - Therefore, all elements in `(left[i], right[i])` are smaller than both endpoints
   - This satisfies: `min(nums[left[i]], nums[right[i]]) > max(nums[left[i]+1], ..., nums[right[i]-1])`

5. **Avoiding Duplicates**: 
   - Multiple middle elements might have the same left and right boundaries
   - We use a set to store unique `(left, right)` pairs

## Solution

### Algorithm

1. **Initialize arrays**:
   - `left[i]`: stores the index of the nearest element to the left that is strictly greater than `nums[i]`
   - `right[i]`: stores the index of the nearest element to the right that is strictly greater than `nums[i]`

2. **Build left array** (using monotonic stack):
   - Traverse from left to right
   - Maintain a decreasing stack (indices of elements in decreasing order)
   - For each element, pop smaller or equal elements
   - The top of the stack is the nearest greater element to the left

3. **Build right array** (using monotonic stack):
   - Traverse from right to left
   - Maintain a decreasing stack
   - For each element, pop smaller or equal elements
   - The top of the stack is the nearest greater element to the right

4. **Count bowl subarrays**:
   - For each middle position `i` (from 1 to n-2)
   - If both `left[i]` and `right[i]` exist, add `(left[i], right[i])` to a set
   - Return the size of the set

### Implementation

```python
class Solution:
    def bowlSubarrays(self, nums: List[int]) -> int:
        n = len(nums)
        left = [-1] * n  # left[i] = nearest greater element index to the left
        right = [n] * n  # right[i] = nearest greater element index to the right

        # Build left array using monotonic decreasing stack
        st = []
        for i in range(n):
            while st and nums[st[-1]] <= nums[i]:
                st.pop()
            if st:
                left[i] = st[-1]
            st.append(i)
        
        # Build right array using monotonic decreasing stack
        st = []
        for i in range(n - 1, -1, -1):
            while st and nums[st[-1]] <= nums[i]:
                st.pop()
            if st:
                right[i] = st[-1]
            st.append(i)
        
        # Count unique bowl subarrays
        s = set()
        for i in range(1, n - 1):  # i must be a middle element
            l, r = left[i], right[i]
            if l >= 0 and r < n:  # Both boundaries exist
                s.add((l, r))
        return len(s)
```

### Complexity Analysis

- **Time Complexity**: O(n)
  - Building `left` array: O(n) - each element is pushed and popped at most once
  - Building `right` array: O(n) - same reasoning
  - Counting unique pairs: O(n)
  - Overall: O(n)

- **Space Complexity**: O(n)
  - `left` and `right` arrays: O(n)
  - Stack: O(n) in worst case
  - Set for storing unique pairs: O(n) in worst case

### Example Walkthrough

For `nums = [2, 5, 3, 1, 4]`:

**Building left array:**
- i=0: stack=[], left[0]=-1, stack=[0]
- i=1: nums[0]=2 < nums[1]=5, pop 0, left[1]=-1, stack=[1]
- i=2: nums[1]=5 > nums[2]=3, left[2]=1, stack=[1,2]
- i=3: nums[2]=3 > nums[3]=1, left[3]=2, stack=[1,2,3]
- i=4: nums[3]=1 < nums[4]=4, pop 3, nums[2]=3 < 4, pop 2, left[4]=1, stack=[1,4]

Result: `left = [-1, -1, 1, 2, 1]`

**Building right array:**
- i=4: stack=[], right[4]=5, stack=[4]
- i=3: nums[4]=4 > nums[3]=1, right[3]=4, stack=[4,3]
- i=2: nums[3]=1 < nums[2]=3, pop 3, right[2]=4, stack=[4,2]
- i=1: nums[2]=3 < nums[1]=5, pop 2, nums[4]=4 < 5, pop 4, right[1]=5, stack=[1]
- i=0: nums[1]=5 > nums[0]=2, right[0]=1, stack=[1,0]

Result: `right = [1, 5, 4, 4, 5]`

**Counting bowls:**
- i=1: left[1]=-1, skip
- i=2: left[2]=1, right[2]=4, add (1,4) → bowl [5,3,1,4]
- i=3: left[3]=2, right[3]=4, add (2,4) → bowl [3,1,4]

Unique pairs: {(1,4), (2,4)}, count = 2

# Tags
Array, Monotonic Stack, Stack

