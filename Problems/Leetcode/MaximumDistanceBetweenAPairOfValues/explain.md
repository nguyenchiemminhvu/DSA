## Problem

https://leetcode.com/problems/maximum-distance-between-a-pair-of-values/description/

```
You are given two non-increasing 0-indexed integer arrays nums1 and nums2.

A pair of indices (i, j), where 0 <= i < nums1.length and 0 <= j < nums2.length, is valid if both:
- i <= j 
- nums1[i] <= nums2[j]

The distance of the pair is j - i.

Return the maximum distance of any valid pair (i, j). If there are no valid pairs, return 0.

An array arr is non-increasing if arr[i-1] >= arr[i] for every 1 <= i < arr.length.

Example 1:
Input: nums1 = [55,30,5,4,2], nums2 = [100,20,10,10,5]
Output: 2
Explanation: The valid pairs are (0,0), (2,2), (2,3), (2,4), (3,3), (3,4), and (4,4).
The maximum distance is 2 with pair (2,4).

Example 2:
Input: nums1 = [2,2,2], nums2 = [10,10,1]
Output: 1
Explanation: The valid pairs are (0,0), (0,1), and (1,1).
The maximum distance is 1 with pair (0,1).

Example 3:
Input: nums1 = [30,29,19,5], nums2 = [25,25,25,25,25]
Output: 2
Explanation: The valid pairs are (2,2), (2,3), (2,4), (3,3), and (3,4).
The maximum distance is 2 with pair (2,4).

Constraints:
- 1 <= nums1.length, nums2.length <= 10^5
- 1 <= nums1[i], nums2[j] <= 10^5
- Both nums1 and nums2 are non-increasing.
```

## Observations

1. **Both arrays are non-increasing**: This is the key property that makes an efficient solution possible.
   - nums1[i-1] >= nums1[i] for all valid i
   - nums2[j-1] >= nums2[j] for all valid j

2. **Valid pair conditions**:
   - i <= j (index constraint)
   - nums1[i] <= nums2[j] (value constraint)

3. **Goal**: Maximize j - i for valid pairs.

4. **Key insight**: Since both arrays are non-increasing, if we process from the end of both arrays:
   - Starting from the largest indices gives us the best chance to maximize distance (j - i)
   - If nums1[i1] <= nums2[i2], we found a valid pair. We can try to increase distance by moving i1 left (decreasing it)
   - If nums1[i1] > nums2[i2], this pair is invalid. Since nums1 is non-increasing, nums1[i1-1] >= nums1[i1] > nums2[i2], so moving i1 left won't help. We need to move i2 left to find a larger value in nums2.

5. **Why start from the end?**
   - Starting from the end maximizes j - i initially
   - The non-increasing property allows us to efficiently prune the search space
   - Moving backwards guarantees we don't miss any valid pairs

## Solution

### Algorithm: Two Pointers (from the end)

The solution uses a two-pointer approach starting from the ends of both arrays and moving backward:

```python
class Solution:
    def maxDistance(self, nums1: List[int], nums2: List[int]) -> int:
        res = 0
        n1 = len(nums1)
        n2 = len(nums2)
        i1 = n1 - 1  # Start from the end of nums1
        i2 = n2 - 1  # Start from the end of nums2
        
        while i1 >= 0 and i2 >= 0:
            if nums1[i1] <= nums2[i2]:
                # Valid pair found
                res = max(res, i2 - i1)
                i1 -= 1  # Try to find a larger distance by moving i1 left
            else:
                # Invalid pair (nums1[i1] > nums2[i2])
                i2 -= 1  # Move i2 left to find a larger value in nums2
        
        return res
```

### How it works:

1. **Initialize**: Start with pointers at the end of both arrays (i1 = n1-1, i2 = n2-1)

2. **Main loop**: While both pointers are valid:
   - **Case 1**: `nums1[i1] <= nums2[i2]` (valid pair)
     - Calculate distance: `i2 - i1`
     - Update result if this distance is larger
     - Move `i1` left (decrement) to try finding an even larger distance
     - We don't move i2 because keeping it where it is might give us a larger distance with a smaller i1
   
   - **Case 2**: `nums1[i1] > nums2[i2]` (invalid pair)
     - Move `i2` left (decrement) to find a larger value in nums2
     - Since nums1 is non-increasing, moving i1 left won't help (values will be >= current value)

3. **Return**: The maximum distance found

### Example Walkthrough (nums1 = [55,30,5,4,2], nums2 = [100,20,10,10,5]):

```
Initial: i1=4 (nums1[4]=2), i2=4 (nums2[4]=5)
- 2 <= 5 ✓ → distance = 4-4 = 0, res = 0, i1 = 3

Step 1: i1=3 (nums1[3]=4), i2=4 (nums2[4]=5)
- 4 <= 5 ✓ → distance = 4-3 = 1, res = 1, i1 = 2

Step 2: i1=2 (nums1[2]=5), i2=4 (nums2[4]=5)
- 5 <= 5 ✓ → distance = 4-2 = 2, res = 2, i1 = 1

Step 3: i1=1 (nums1[1]=30), i2=4 (nums2[4]=5)
- 30 > 5 ✗ → i2 = 3

Step 4: i1=1 (nums1[1]=30), i2=3 (nums2[3]=10)
- 30 > 10 ✗ → i2 = 2

Step 5: i1=1 (nums1[1]=30), i2=2 (nums2[2]=10)
- 30 > 10 ✗ → i2 = 1

Step 6: i1=1 (nums1[1]=30), i2=1 (nums2[1]=20)
- 30 > 20 ✗ → i2 = 0

Step 7: i1=1 (nums1[1]=30), i2=0 (nums2[0]=100)
- 30 <= 100 ✓ → distance = 0-1 = -1, no update, i1 = 0

Step 8: i1=0 (nums1[0]=55), i2=0 (nums2[0]=100)
- 55 <= 100 ✓ → distance = 0-0 = 0, no update, i1 = -1

Loop ends. Return res = 2
```

### Complexity Analysis:

- **Time Complexity**: O(n1 + n2) where n1 and n2 are the lengths of nums1 and nums2
  - Each pointer moves at most n1 or n2 times
  - Each iteration does constant work

- **Space Complexity**: O(1)
  - Only using a few variables (res, i1, i2)
  - No additional data structures

### Why this works:

The key insight is that the non-increasing property of both arrays allows us to use a greedy two-pointer approach. By starting from the end and moving backwards:
- We maximize the initial value of j - i
- When we find a valid pair, moving i1 left is the only way to potentially increase the distance
- When we find an invalid pair, moving i2 left is the only way to make it valid (since moving i1 left in a non-increasing array won't decrease the value)

# Tags

Two Pointers, Array, Greedy

