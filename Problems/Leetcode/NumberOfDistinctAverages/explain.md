## Problem

https://leetcode.com/problems/number-of-distinct-averages/description/

```
You are given a 0-indexed integer array nums of even length.

As long as nums is not empty, you must repetitively:
- Find the minimum number in nums and remove it.
- Find the maximum number in nums and remove it.
- Calculate the average of the two removed numbers.

The average of two numbers a and b is (a + b) / 2.

For example, the average of 2 and 3 is (2 + 3) / 2 = 2.5.

Return the number of distinct averages calculated using the above process.

Note that when there is a tie for a minimum or maximum number, any can be removed.

Example 1:
Input: nums = [4,1,4,0,3,5]
Output: 2
Explanation:
1. Remove 0 and 5, and the average is (0 + 5) / 2 = 2.5. Now, nums = [4,1,4,3].
2. Remove 1 and 4. The average is (1 + 4) / 2 = 2.5, and nums = [4,3].
3. Remove 3 and 4, and the average is (3 + 4) / 2 = 3.5.
Since there are 2 distinct numbers among 2.5, 2.5, and 3.5, we return 2.

Example 2:
Input: nums = [1,100]
Output: 1
Explanation:
There is only one average to be calculated after removing 1 and 100, so we return 1.

Constraints:
- 2 <= nums.length <= 100
- nums.length is even.
- 0 <= nums[i] <= 100
```

## Observations

1. **Sorting**: Sorting the array simplifies the process of finding the minimum and maximum values.
2. **Set for Uniqueness**: Using a set ensures that only distinct averages are counted.
3. **Two Pointers**: A two-pointer approach (one pointer at the start and one at the end) is efficient for this problem.
4. **Key Insight**: After sorting, the smallest element is always at the left end and the largest at the right end, so we can use two pointers moving towards each other.

## Solution

The solution involves:
1. **Sort the array** to position the smallest and largest elements at the ends.
2. **Use two pointers** (left at start, right at end) to calculate averages of the smallest and largest numbers.
3. **Store averages in a set** to automatically handle uniqueness.
4. **Return the size of the set** which represents the count of distinct averages.

### Python Implementation

```python
class Solution:
    def distinctAverages(self, nums: List[int]) -> int:
        nums.sort()
        l, r = 0, len(nums) - 1
        s = set()
        while l < r:
            s.add((nums[l] + nums[r]) / 2)
            l += 1
            r -= 1
        return len(s)
```

### Explanation of Code

1. **Sorting**: `nums.sort()` arranges elements in ascending order, ensuring the smallest and largest numbers are at the ends.
2. **Two Pointers**: Initialize `l = 0` (left pointer) and `r = len(nums) - 1` (right pointer).
3. **Set for Averages**: Calculate `(nums[l] + nums[r]) / 2` and add to set `s`. The set automatically handles duplicates.
4. **Move Pointers**: Increment `l` and decrement `r` to process the next pair.
5. **Return Result**: `len(s)` gives the count of distinct averages.

### Example Walkthrough

#### Example 1: `nums = [4,1,4,0,3,5]`
- **Sort**: `nums = [0,1,3,4,4,5]`
- **Iteration 1**: `l=0, r=5` → Average = `(0+5)/2 = 2.5` → Set: `{2.5}`
- **Iteration 2**: `l=1, r=4` → Average = `(1+4)/2 = 2.5` → Set: `{2.5}`
- **Iteration 3**: `l=2, r=3` → Average = `(3+4)/2 = 3.5` → Set: `{2.5, 3.5}`
- **Output**: `2` (two distinct averages)

#### Example 2: `nums = [1,100]`
- **Sort**: `nums = [1,100]`
- **Iteration 1**: `l=0, r=1` → Average = `(1+100)/2 = 50.5` → Set: `{50.5}`
- **Output**: `1` (one distinct average)

### Complexity Analysis

- **Time Complexity**: O(n log n) where n is the length of the array
  - Sorting takes O(n log n)
  - Two-pointer traversal takes O(n)
  - Overall: O(n log n)
- **Space Complexity**: O(n)
  - Set can store at most n/2 distinct averages
  - Sorting may use O(log n) stack space depending on implementation

# Tags

`Array` `Sorting` `Two Pointers` `Hash Set` `Math`
