## Problem

https://leetcode.com/problems/kth-missing-positive-number/description/

```
Given an array arr of positive integers sorted in a strictly increasing order, and an integer k.

Return the kth positive integer that is missing from this array.

Example 1:
Input: arr = [2,3,4,7,11], k = 5
Output: 9
Explanation: The missing positive integers are [1,5,6,8,9,10,12,13,...]. The 5th missing positive integer is 9.

Example 2:
Input: arr = [1,2,3,4], k = 2
Output: 6
Explanation: The missing positive integers are [5,6,7,...]. The 2nd missing positive integer is 6.

Constraints:
- 1 <= arr.length <= 1000
- 1 <= arr[i] <= 1000
- 1 <= k <= 1000
- arr[i] < arr[j] for 1 <= i < j <= arr.length

Follow up: Could you solve this problem in less than O(n) complexity?
```

## Observations

1. **Array is sorted in strictly increasing order** - This means there are gaps between consecutive elements where missing numbers exist
2. **Missing numbers form intervals** - Between any two consecutive array elements, we can calculate how many positive integers are missing
3. **We need to find the kth missing number** - We need to track cumulative count of missing numbers across intervals
4. **Edge cases to consider**:
   - Missing numbers before the first element (1 to arr[0]-1)
   - Missing numbers between consecutive elements
   - Missing numbers after the last element (arr[-1]+1 onwards)

## Solution

### Approach: Interval-based counting

The solution identifies intervals of missing positive integers and counts through them to find the kth missing number.

**Algorithm:**
1. **Build intervals of missing numbers:**
   - Start with `left = 0` (representing position before first positive integer)
   - For each element in array:
     - If `val > left + 1`, there's a gap containing missing numbers `[left+1, val-1]`
     - Add this interval to our list
     - Update `left = val`
   - After processing all elements, add final interval `[arr[-1]+1, arr[-1]+k+1]` to ensure we have enough missing numbers

2. **Find kth missing number:**
   - Iterate through intervals
   - For each interval `[left, right]`:
     - Count of missing numbers = `(right - left) + 1`
     - If `k <= count`, the answer is at position `left + k - 1`
     - Otherwise, subtract count from k and continue to next interval

**Time Complexity:** O(n) where n is the length of arr
- Single pass to build intervals: O(n)
- Single pass to find kth missing: O(n) worst case

**Space Complexity:** O(n) for storing intervals

**Example walkthrough with arr = [2,3,4,7,11], k = 5:**
- Start: left = 0
- Process 2: gap [1,1] (1 missing number), left = 2
- Process 3: no gap, left = 3
- Process 4: no gap, left = 4
- Process 7: gap [5,6] (2 missing numbers), left = 7
- Process 11: gap [8,10] (3 missing numbers), left = 11
- Add final interval: [12,17]
- Intervals: [1,1], [5,6], [8,10], [12,17]
- Find k=5:
  - [1,1]: 1 number, k becomes 4
  - [5,6]: 2 numbers, k becomes 2
  - [8,10]: 2 numbers, k=2 fits here, return 8 + 2 - 1 = 9 ✓

```python
class Solution:
    def findKthPositive(self, arr: List[int], k: int) -> int:
        left = 0
        intervals = []
        for val in arr:
            if val > left + 1:
                # missing range is left + 1 -> val - 1
                intervals.append([left + 1, val - 1])
                left = val
            else:
                left = val
        # then add last duration arr[-1] + 1 -> max value 1001
        intervals.append([arr[-1] + 1, arr[-1] + k + 1])

        res = -1
        for left, right in intervals:
            if k <= (right - left) + 1:
                return left + k - 1
            else:
                k -= (right - left) + 1

        return res
```

### Binary Search Approach (Follow-up O(log n) solution)

For the follow-up asking for less than O(n) complexity, we can use binary search:

**Key insight:** At index i, the number of missing positive integers is `arr[i] - (i + 1)`

- If this count < k, the answer is to the right
- If this count >= k, the answer might be at or before this position

```python
class Solution:
    def findKthPositive(self, arr: List[int], k: int) -> int:
        left, right = 0, len(arr) - 1
        
        while left <= right:
            mid = (left + right) // 2
            # Number of missing positives before arr[mid]
            missing = arr[mid] - (mid + 1)
            
            if missing < k:
                left = mid + 1
            else:
                right = mid - 1
        
        # left is the insertion point
        # Missing count at position 'left-1' is arr[left-1] - left
        # We need k - missing more numbers after arr[left-1]
        return left + k
```

**Time Complexity:** O(log n)
**Space Complexity:** O(1)

# Tags
#array #binary-search #intervals #math

