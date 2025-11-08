## Problem

https://leetcode.com/problems/minimum-pair-removal-to-sort-array-i/description/

```
Given an array nums, you can perform the following operation any number of times:

Select the adjacent pair with the minimum sum in nums. If multiple such pairs exist, choose the leftmost one.
Replace the pair with their sum.
Return the minimum number of operations needed to make the array non-decreasing.

An array is said to be non-decreasing if each element is greater than or equal to its previous element (if it exists).

Example 1:

Input: nums = [5,2,3,1]

Output: 2

Explanation:

The pair (3,1) has the minimum sum of 4. After replacement, nums = [5,2,4].
The pair (2,4) has the minimum sum of 6. After replacement, nums = [5,6].
The array nums became non-decreasing in two operations.

Example 2:

Input: nums = [1,2,2]

Output: 0

Explanation:

The array nums is already sorted.

Constraints:

1 <= nums.length <= 50
-1000 <= nums[i] <= 1000
```

## Observations

1. **Problem Understanding**: We need to repeatedly find adjacent pairs with minimum sum and replace them with their sum until the array becomes non-decreasing (sorted).

2. **Greedy Strategy**: At each step, we always choose the adjacent pair with the minimum sum. If there are ties, we choose the leftmost one.

3. **Array Reduction**: Each operation reduces the array size by 1 (two elements become one), so we gradually simplify the problem.

4. **Key Insight**: The order matters - we must always pick the pair with minimum sum first, as this affects subsequent operations and the final result.

5. **Termination Condition**: We stop when the array becomes non-decreasing (each element ≥ previous element).

6. **Edge Cases**: 
   - Already sorted arrays require 0 operations
   - Single element arrays are always sorted
   - Arrays with negative numbers work the same way

## Solution

The solution uses a **greedy simulation** approach:

### Algorithm Steps:
1. **Check if sorted**: Use a helper function to check if the current array is non-decreasing
2. **Find minimum sum pair**: Iterate through all adjacent pairs to find the one with minimum sum
3. **Handle ties**: If multiple pairs have the same minimum sum, choose the leftmost one
4. **Merge pair**: Replace the selected pair with their sum
5. **Repeat**: Continue until the array becomes sorted
6. **Count operations**: Track the number of merge operations performed

### Time Complexity: 
- **O(n³)** in worst case
  - Outer loop runs at most n-1 times (each operation reduces array size by 1)
  - Each iteration scans n-1 adjacent pairs: O(n)
  - Array reconstruction after merge: O(n)
  - Total: O(n) × O(n) × O(n) = O(n³)

### Space Complexity:
- **O(n)** for creating new arrays during merge operations

### Why This Works:
- **Greedy Choice**: Always selecting the minimum sum pair is optimal because it creates the smallest possible intermediate values, which are more likely to maintain or create sorted order
- **Local Optimal → Global Optimal**: Each greedy choice leads to the minimum number of total operations needed

### Example Walkthrough:
```
nums = [5,2,3,1]

Step 1: Find min sum pair
- (5,2) = 7, (2,3) = 5, (3,1) = 4  → minimum is (3,1)
- Replace: [5,2,4]

Step 2: Find min sum pair  
- (5,2) = 7, (2,4) = 6  → minimum is (2,4)
- Replace: [5,6]

Step 3: Check sorted
- [5,6] is non-decreasing → DONE
- Operations: 2
```

# Tags

- **Greedy Algorithm**
- **Array Simulation** 
- **Adjacent Elements**
- **Pair Selection**

