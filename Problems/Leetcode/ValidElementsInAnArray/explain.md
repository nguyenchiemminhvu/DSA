## Problem

https://leetcode.com/problems/valid-elements-in-an-array/

An element in an array is considered **valid** if it satisfies at least one of these conditions:
1. It is **strictly greater than every element to its left**
2. It is **strictly greater than every element to its right**
3. **Special case**: The first and last elements are always valid (they have no elements on one side)

**Task**: Return all valid elements in their original order from the input array.

**Constraints**:
- 1 <= nums.length <= 100
- 1 <= nums[i] <= 100

## Observations

1. **Key Insight**: For each element to be valid, we need to know:
   - The **maximum value to its left** (to check if current element is strictly greater)
   - The **maximum value to its right** (to check if current element is strictly greater)

2. **Boundary Handling**: First and last elements are always valid because:
   - First element has no left side, so the "strictly greater than left" condition is vacuously true
   - Last element has no right side, so the "strictly greater than right" condition is vacuously true

3. **Optimization Opportunity**: Instead of checking each element against all others (O(n²)), we can **precompute prefix and suffix maximums** in two passes (O(n))

4. **Validation Logic**: An element at index `i` is valid if:
   - `i == 0` (first element), OR
   - `i == n-1` (last element), OR
   - `nums[i] > max(all elements left of i)`, OR
   - `nums[i] > max(all elements right of i)`

## Solution

### Algorithm: Prefix-Suffix Maximum Arrays

**Approach**: Precompute the maximum values to the left and right of each element, then validate in a single pass.

### Step-by-Step Breakdown

**Step 1: Initialize Arrays**
```python
left = nums[:]   # left[i] will store max element from index 0 to i
right = nums[:]  # right[i] will store max element from index i to n-1
```

**Step 2: Build Left Maximum Array**
```python
for i in range(1, n):
    left[i] = max(left[i - 1], nums[i])
```
- Traverse left to right, storing the maximum seen so far
- After this loop: `left[i]` = maximum value from index 0 to i

**Step 3: Build Right Maximum Array**
```python
for i in range(n - 2, -1, -1):
    right[i] = max(right[i + 1], nums[i])
```
- Traverse right to left, storing the maximum seen so far
- After this loop: `right[i]` = maximum value from index i to n-1

**Step 4: Validate Each Element**
```python
for i in range(n):
    check_left = check_right = True
    if i > 0:
        check_left = nums[i] > left[i - 1]   # Is current element > all left?
    if i < n - 1:
        check_right = nums[i] > right[i + 1]  # Is current element > all right?
    if check_left or check_right:
        res.append(nums[i])
```
- For element at index `i`:
  - `check_left`: True if `i == 0` OR `nums[i] > max of all elements to its left`
  - `check_right`: True if `i == n-1` OR `nums[i] > max of all elements to its right`
  - Add element to result if **either** condition is true

### Example Trace: nums = [1, 2, 4, 2, 3, 2]

| i | nums[i] | left (0..i-1) | right (i+1..n-1) | > left? | > right? | Valid? |
|---|---------|---------------|------------------|---------|----------|--------|
| 0 | 1       | - (first)     | 4                | ✓       | ✗        | ✓      |
| 1 | 2       | 1             | 4                | ✓       | ✗        | ✓      |
| 2 | 4       | 2             | 3                | ✓       | ✓        | ✓      |
| 3 | 2       | 4             | 3                | ✗       | ✗        | ✗      |
| 4 | 3       | 4             | 2                | ✗       | ✓        | ✓      |
| 5 | 2       | 4             | - (last)         | ✗       | ✓        | ✓      |

**Result**: [1, 2, 4, 3, 2] ✓

### Complexity Analysis

- **Time Complexity**: O(n)
  - Three passes through the array (left prefix, right suffix, validation)
  
- **Space Complexity**: O(n)
  - Two auxiliary arrays: `left` and `right`

### Why This Works

The key insight is that checking "strictly greater than ALL elements on one side" is equivalent to checking "strictly greater than the MAXIMUM element on that side". By preprocessing these maximums, we avoid redundant comparisons.

# Tags

