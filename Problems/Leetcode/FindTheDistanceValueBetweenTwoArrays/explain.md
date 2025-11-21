## Problem

https://leetcode.com/problems/find-the-distance-value-between-two-arrays/description/

```
Given two integer arrays arr1 and arr2, and the integer d, return the distance value between the two arrays.

The distance value is defined as the number of elements arr1[i] such that there is not any element arr2[j] where |arr1[i]-arr2[j]| <= d.

Example 1:

Input: arr1 = [4,5,8], arr2 = [10,9,1,8], d = 2
Output: 2
Explanation: 
For arr1[0]=4 we have: 
|4-10|=6 > d=2 
|4-9|=5 > d=2 
|4-1|=3 > d=2 
|4-8|=4 > d=2 
For arr1[1]=5 we have: 
|5-10|=5 > d=2 
|5-9|=4 > d=2 
|5-1|=4 > d=2 
|5-8|=3 > d=2
For arr1[2]=8 we have:
|8-10|=2 <= d=2
|8-9|=1 <= d=2
|8-1|=7 > d=2
|8-8|=0 <= d=2

Example 2:

Input: arr1 = [1,4,2,3], arr2 = [-4,-3,6,10,20,30], d = 3
Output: 2

Example 3:

Input: arr1 = [2,1,100,3], arr2 = [-5,-2,10,-3,7], d = 6
Output: 1

Constraints:

1 <= arr1.length, arr2.length <= 500
-1000 <= arr1[i], arr2[j] <= 1000
0 <= d <= 100
```

## Observations

1. **Problem Understanding**: We need to count elements in `arr1` where NO element in `arr2` is within distance `d` (i.e., `|arr1[i] - arr2[j]| <= d` for any `j`).

2. **Brute Force Approach**: For each element in `arr1`, check all elements in `arr2` - O(n1 × n2) time complexity.

3. **Optimization Opportunity**: Since we're checking distances, we can sort `arr2` and use binary search to find the closest elements efficiently.

4. **Key Insight**: For any element `val` in `arr1`, we only need to check:
   - The smallest element in `arr2` that is greater than `val` (upper bound)
   - The largest element in `arr2` that is less than or equal to `val` (element just before upper bound)

5. **Binary Search Usage**: Instead of checking all elements in `arr2`, we can find the position where `val` would be inserted in sorted `arr2`, then check only the adjacent elements.

## Solution

1. **Sort arr2**: This allows us to use binary search to find relevant elements efficiently.

2. **Upper Bound Function**: Finds the first position in sorted `arr2` where an element is greater than `target`. This gives us the insertion point for `target`.

3. **For each element in arr1**:
   - Find its insertion position in sorted `arr2` using upper bound
   - Check only two adjacent elements:
     - `arr2[idx]`: First element ≥ val (if exists)
     - `arr2[idx-1]`: Last element < val (if exists)
   - If either of these elements is within distance `d`, then `val` doesn't contribute to the count

4. **Distance Check**: 
   - For `arr2[idx] ≥ val`: distance is `arr2[idx] - val`
   - For `arr2[idx-1] < val`: distance is `val - arr2[idx-1]`

**Time Complexity**: O(n2 log n2 + n1 log n2)
- Sorting arr2: O(n2 log n2)
- For each element in arr1, binary search in arr2: O(n1 log n2)

**Space Complexity**: O(1) if we don't count the input arrays

**Why this works**: Since `arr2` is sorted, the closest elements to any `val` must be adjacent to where `val` would be inserted. We only need to check these two positions instead of all elements in `arr2`.

# Tags
- Binary Search
- Two Pointers
- Sorting
- Array

