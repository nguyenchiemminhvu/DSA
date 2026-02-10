## Problem

https://leetcode.com/problems/longest-balanced-subarray-i/description/

```
You are given an integer array nums.

A subarray is called balanced if the number of distinct even numbers in the subarray 
is equal to the number of distinct odd numbers.

Return the length of the longest balanced subarray.

Example 1:
Input: nums = [2,5,4,3]
Output: 4
Explanation: The longest balanced subarray is [2, 5, 4, 3].
It has 2 distinct even numbers [2, 4] and 2 distinct odd numbers [5, 3].

Example 2:
Input: nums = [3,2,2,5,4]
Output: 5
Explanation: The longest balanced subarray is [3, 2, 2, 5, 4].
It has 2 distinct even numbers [2, 4] and 2 distinct odd numbers [3, 5].

Example 3:
Input: nums = [1,2,3,2]
Output: 3
Explanation: The longest balanced subarray is [2, 3, 2].
It has 1 distinct even number [2] and 1 distinct odd number [3].

Constraints:
- 1 <= nums.length <= 1500
- 1 <= nums[i] <= 10^5
```

## Observations

1. **Key Insight**: We need to count **distinct** even and odd numbers, not the total count of elements
   - `[2, 2, 3]` has 1 distinct even (2) and 1 distinct odd (3), so it's balanced
   - Duplicates don't increase the distinct count

2. **Subarray Property**: A subarray must be contiguous elements from the original array

3. **Balance Condition**: A subarray is balanced when:
   - Number of unique even numbers == Number of unique odd numbers

4. **Brute Force Approach**: 
   - Check all possible subarrays O(n²)
   - For each subarray, track distinct evens and odds using sets
   - Time Complexity: O(n²) where n ≤ 1500, which is acceptable

## Solution

### Approach: Brute Force with Two Pointers and Sets

```python
from typing import List

class Solution:
    def longestBalanced(self, nums: List[int]) -> int:
        n = len(nums)
        best = 0

        for l in range(n):
            evens = set()
            odds = set()
            for r in range(l, n):
                x = nums[r]
                if x % 2 == 0:
                    evens.add(x)
                else:
                    odds.add(x)

                if len(evens) == len(odds):
                    best = max(best, r - l + 1)

        return best
```

### Explanation

1. **Outer Loop (Left Pointer `l`)**: 
   - Iterate through each possible starting position of a subarray
   - Initialize empty sets for tracking distinct even and odd numbers

2. **Inner Loop (Right Pointer `r`)**:
   - Extend the subarray from position `l` to position `r`
   - For each new element `nums[r]`:
     - Add it to `evens` set if even (x % 2 == 0)
     - Add it to `odds` set if odd
   - Sets automatically handle duplicates (only store unique values)

3. **Balance Check**:
   - After adding each element, check if `len(evens) == len(odds)`
   - If balanced, calculate subarray length: `r - l + 1`
   - Update `best` if this is the longest balanced subarray found

4. **Return Result**: The maximum length found across all balanced subarrays

### Complexity Analysis

- **Time Complexity**: O(n²)
  - Outer loop: O(n)
  - Inner loop: O(n) for each outer iteration
  - Set operations (add, len): O(1) average case
  - Total: O(n²)

- **Space Complexity**: O(n)
  - Two sets can store at most n distinct numbers in worst case
  - O(n) for evens + O(n) for odds = O(n) total

### Example Walkthrough

For `nums = [2, 5, 4, 3]`:

- l=0, r=0: evens={2}, odds={}, not balanced
- l=0, r=1: evens={2}, odds={5}, balanced! length=2
- l=0, r=2: evens={2,4}, odds={5}, not balanced
- l=0, r=3: evens={2,4}, odds={5,3}, balanced! length=4 ✓
- ... (continue for other starting positions)

The longest balanced subarray has length 4.

# Tags
`Array` `Hash Set` `Two Pointers` `Sliding Window` `Brute Force`

