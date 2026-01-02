# Sum of Subarray Ranges

## Problem

https://leetcode.com/problems/sum-of-subarray-ranges/description/

You are given an integer array `nums`. The **range** of a subarray of `nums` is the difference between the largest and smallest element in the subarray.

Return the **sum of all subarray ranges** of `nums`.

A subarray is a contiguous non-empty sequence of elements within an array.

### Examples

**Example 1:**
```
Input: nums = [1,2,3]
Output: 4
Explanation: The 6 subarrays of nums are:
[1], range = 1 - 1 = 0 
[2], range = 2 - 2 = 0
[3], range = 3 - 3 = 0
[1,2], range = 2 - 1 = 1
[2,3], range = 3 - 2 = 1
[1,2,3], range = 3 - 1 = 2
Sum of all ranges = 0 + 0 + 0 + 1 + 1 + 2 = 4
```

**Example 2:**
```
Input: nums = [1,3,3]
Output: 4
Explanation: The 6 subarrays of nums are:
[1], range = 1 - 1 = 0
[3], range = 3 - 3 = 0
[3], range = 3 - 3 = 0
[1,3], range = 3 - 1 = 2
[3,3], range = 3 - 3 = 0
[1,3,3], range = 3 - 1 = 2
Sum of all ranges = 0 + 0 + 0 + 2 + 0 + 2 = 4
```

**Example 3:**
```
Input: nums = [4,-2,-3,4,1]
Output: 59
```

**Constraints:**
- `1 <= nums.length <= 1000`
- `-10^9 <= nums[i] <= 10^9`

**Follow-up:** Could you find a solution with O(n) time complexity?

---

## Observations

### 1. Understanding the Problem
- For each subarray, we need to find: `max_element - min_element`
- We need to sum this value across all possible subarrays
- Total number of subarrays in array of length n: `n * (n + 1) / 2`

### 2. Brute Force Approach (O(n³))
- Generate all subarrays: O(n²)
- For each subarray, find max and min: O(n)
- This gives O(n³) time complexity

### 3. Optimized Brute Force (O(n²))
- While iterating through subarrays, maintain running max and min
- This reduces the time to find max/min from O(n) to O(1)
- This is the commented-out solution in the code

### 4. Key Insight for O(n) Solution
The range can be decomposed:
```
Sum of (max - min) = Sum of (max) - Sum of (min)
```

This means we can:
1. Calculate the sum of maximum elements across all subarrays
2. Calculate the sum of minimum elements across all subarrays
3. Subtract them to get the answer

### 5. Contribution Technique
For each element `nums[i]`, calculate:
- **How many subarrays have `nums[i]` as the maximum element?**
- **How many subarrays have `nums[i]` as the minimum element?**

If `nums[i]` appears as max in `count_max` subarrays and as min in `count_min` subarrays:
```
Contribution = nums[i] * count_max - nums[i] * count_min
```

### 6. Using Monotonic Stack
To find how many subarrays have `nums[i]` as max/min:
- Find the **left boundary**: nearest element to the left that is greater/smaller
- Find the **right boundary**: nearest element to the right that is greater/smaller
- Number of subarrays where `nums[i]` is max/min = `(i - left_boundary) * (right_boundary - i)`

---

## Solution

### Approach: Monotonic Stack with Contribution Technique

#### Algorithm Steps

1. **Initialize arrays** to store boundaries for each element:
   - `min_left[i]`: index of nearest smaller element to the left of i (or -1 if none)
   - `min_right[i]`: index of nearest smaller element to the right of i (or n if none)
   - `max_left[i]`: index of nearest larger element to the left of i (or -1 if none)
   - `max_right[i]`: index of nearest larger element to the right of i (or n if none)

2. **Find boundaries using monotonic stacks**:
   
   **Left to Right Pass** (find `min_left` and `max_left`):
   - Use a monotonic increasing stack for finding smaller elements
   - Use a monotonic decreasing stack for finding larger elements
   
   **Right to Left Pass** (find `min_right` and `max_right`):
   - Similar process but in reverse direction
   - Use strict comparisons to handle duplicates correctly

3. **Calculate contribution of each element**:
   ```
   For element at index i:
   - Count as maximum: (i - max_left[i]) * (max_right[i] - i) subarrays
   - Count as minimum: (i - min_left[i]) * (min_right[i] - i) subarrays
   
   Total contribution = nums[i] * (count_as_max - count_as_min)
   ```

#### Code Implementation

```python
class Solution:
    def subArrayRanges(self, nums: List[int]) -> int:
        n = len(nums)
        res = 0

        # Initialize boundary arrays
        min_left = [-1] * n   # Nearest smaller element on left
        min_right = [n] * n    # Nearest smaller element on right
        max_left = [-1] * n   # Nearest larger element on left
        max_right = [n] * n    # Nearest larger element on right

        # LEFT TO RIGHT PASS
        st_min = []  # Monotonic increasing stack for minimums
        st_max = []  # Monotonic decreasing stack for maximums
        
        for i in range(n):
            # Find min_left[i]: pop elements >= current
            while st_min and nums[st_min[-1]] >= nums[i]:
                st_min.pop()
            if st_min:
                min_left[i] = st_min[-1]
            st_min.append(i)

            # Find max_left[i]: pop elements <= current
            while st_max and nums[st_max[-1]] <= nums[i]:
                st_max.pop()
            if st_max:
                max_left[i] = st_max[-1]
            st_max.append(i)
        
        # RIGHT TO LEFT PASS
        st_min = []
        st_max = []
        
        for i in range(n - 1, -1, -1):
            # Find min_right[i]: pop elements > current (strict >)
            while st_min and nums[st_min[-1]] > nums[i]:
                st_min.pop()
            if st_min:
                min_right[i] = st_min[-1]
            st_min.append(i)

            # Find max_right[i]: pop elements < current (strict <)
            while st_max and nums[st_max[-1]] < nums[i]:
                st_max.pop()
            if st_max:
                max_right[i] = st_max[-1]
            st_max.append(i)

        # Calculate contribution of each element
        for i in range(n):
            # Add contribution as maximum
            res += nums[i] * (i - max_left[i]) * (max_right[i] - i)
            # Subtract contribution as minimum
            res -= nums[i] * (i - min_left[i]) * (min_right[i] - i)

        return res
```

#### Why Different Comparison Operators?

Notice the asymmetry in comparisons:
- **Left pass**: `>=` for min, `<=` for max
- **Right pass**: `>` for min, `<` for max (strict comparisons)

This handles **duplicate elements** correctly by ensuring each subarray is counted exactly once. Without this asymmetry, duplicate values would cause overcounting or undercounting of subarrays.

#### Example Walkthrough

For `nums = [1, 2, 3]`:

**After processing boundary arrays:**
```
Index:       0   1   2
nums:        1   2   3
max_left:   -1   0   1   (no larger element before 1; 1 is before 2; 2 is before 3)
max_right:   1   2   3   (2 is after 1; 3 is after 2; no element after 3)
min_left:   -1  -1  -1   (no smaller element before any of them)
min_right:   3   3   3   (no smaller element after any of them)
```

**Contributions:**

- **Index 0 (value=1):**
  - As max: 1 × (0-(-1)) × (1-0) = 1 × 1 × 1 = 1
    - Subarrays: [1]
  - As min: 1 × (0-(-1)) × (3-0) = 1 × 1 × 3 = 3
    - Subarrays: [1], [1,2], [1,2,3]
  - Net contribution: 1×1 - 1×3 = -2

- **Index 1 (value=2):**
  - As max: 2 × (1-0) × (2-1) = 2 × 1 × 1 = 2
    - Subarrays: [2]
  - As min: 2 × (1-(-1)) × (3-1) = 2 × 2 × 2 = 8
    - Subarrays: [2], [1,2], [2,3], [1,2,3]
  - Net contribution: 2×1 - 2×4 = -6

- **Index 2 (value=3):**
  - As max: 3 × (2-1) × (3-2) = 3 × 1 × 1 = 3
    - Subarrays: [3]
  - As min: 3 × (2-(-1)) × (3-2) = 3 × 3 × 1 = 9
    - Subarrays: [3], [2,3], [1,2,3]
  - Net contribution: 3×1 - 3×3 = -6

Wait, let me recalculate properly:

- **Index 0 (value=1):**
  - As max in 1 subarray: [1]
  - As min in 3 subarrays: [1], [1,2], [1,2,3]
  
- **Index 1 (value=2):**
  - As max in 2 subarrays: [2], [1,2]
  - As min in 2 subarrays: [2], [2,3]
  
- **Index 2 (value=3):**
  - As max in 3 subarrays: [3], [2,3], [1,2,3]
  - As min in 1 subarray: [3]

Sum of max contributions: 1×1 + 2×2 + 3×3 = 1 + 4 + 9 = 14
Sum of min contributions: 1×3 + 2×2 + 3×1 = 3 + 4 + 3 = 10
Result: 14 - 10 = 4 ✓

---

## Complexity Analysis

### Time Complexity: **O(n)**
- Each element is pushed and popped from stacks at most once
- Two passes through the array (left-to-right and right-to-left): O(n) each
- Final pass to calculate contributions: O(n)
- Total: O(n) + O(n) + O(n) = O(n)

### Space Complexity: **O(n)**
- Four arrays of size n for storing boundaries: O(4n)
- Two stacks that can hold up to n elements: O(2n)
- Total: O(n)

---

## Key Takeaways

1. **Decomposition**: Breaking `max - min` into `sum(max) - sum(min)` simplifies the problem
2. **Contribution Technique**: Calculate how many times each element contributes as max/min
3. **Monotonic Stack**: Efficiently finds nearest greater/smaller elements in O(n) time
4. **Boundary Handling**: Careful with duplicate elements using strict/non-strict comparisons
5. **Optimization**: Transforms O(n²) or O(n³) brute force into O(n) solution

This problem demonstrates the power of monotonic stacks and contribution-based thinking in array problems!

# Tags

#array #monotonic-stack #contribution-technique #range-queries #optimization

