## Problem

https://leetcode.com/problems/range-sum-query-immutable

```
Given an integer array nums, handle multiple queries of the following type:

Calculate the sum of the elements of nums between indices left and right inclusive where left <= right.
Implement the NumArray class:

NumArray(int[] nums) Initializes the object with the integer array nums.
int sumRange(int left, int right) Returns the sum of the elements of nums between indices left and right inclusive (i.e. nums[left] + nums[left + 1] + ... + nums[right]).

Example 1:

Input
["NumArray", "sumRange", "sumRange", "sumRange"]
[[[-2, 0, 3, -5, 2, -1]], [0, 2], [2, 5], [0, 5]]
Output
[null, 1, -1, -3]

Explanation
NumArray numArray = new NumArray([-2, 0, 3, -5, 2, -1]);
numArray.sumRange(0, 2); // return (-2) + 0 + 3 = 1
numArray.sumRange(2, 5); // return 3 + (-5) + 2 + (-1) = -1
numArray.sumRange(0, 5); // return (-2) + 0 + 3 + (-5) + 2 + (-1) = -3

Constraints:

1 <= nums.length <= 104
-105 <= nums[i] <= 105
0 <= left <= right < nums.length
At most 104 calls will be made to sumRange.
```

## Observations

1. **Multiple Queries**: The problem involves handling multiple `sumRange` queries (up to 10^4 calls), which suggests we need an efficient approach that avoids recalculating sums repeatedly.

2. **Immutable Array**: The input array `nums` doesn't change after initialization, so we can preprocess it once and use the preprocessed data for all queries.

3. **Range Sum Pattern**: We need to calculate the sum of elements between indices `left` and `right` inclusive. This is a classic use case for prefix sums.

4. **Time vs Space Tradeoff**: We can trade some space (O(n)) for much faster query time (O(1) vs O(n) for naive approach).

5. **Constraints Analysis**: 
   - Array length up to 10^4 and up to 10^4 queries means naive O(n) per query could result in O(n*m) = O(10^8) operations in worst case
   - Prefix sum approach gives us O(n) preprocessing + O(1) per query = O(n + m) total

## Solution

### Approach: Prefix Sum Array

The solution uses a **prefix sum array** to achieve O(1) query time after O(n) preprocessing.

#### Key Concept:
- **Prefix Sum**: `prefix[i]` represents the sum of all elements from index 0 to i-1 in the original array
- **Range Sum Formula**: `sum(left, right) = prefix[right + 1] - prefix[left]`

#### Implementation Details:

1. **Constructor (`__init__`)**:
   ```python
   self.prefix = [0] * (len(nums) + 1)
   for i in range(len(nums)):
       self.prefix[i + 1] = self.prefix[i] + nums[i]
   ```
   - Creates a prefix array of size `n + 1` (one extra element)
   - `prefix[0] = 0` (sum of 0 elements)
   - `prefix[i + 1] = prefix[i] + nums[i]` (cumulative sum)

2. **Query Method (`sumRange`)**:
   ```python
   return self.prefix[right + 1] - self.prefix[left]
   ```
   - Uses the prefix sum formula to get range sum in O(1) time

#### Example Walkthrough:
For `nums = [-2, 0, 3, -5, 2, -1]`:

**Prefix Array Construction:**
```
nums:   [-2,  0,  3, -5,  2, -1]
index:   0   1   2   3   4   5
prefix: [0, -2, -2,  1, -4, -2, -3]
index:   0   1   2   3   4   5   6
```

**Query Examples:**
- `sumRange(0, 2)`: `prefix[3] - prefix[0] = 1 - 0 = 1` ✓
- `sumRange(2, 5)`: `prefix[6] - prefix[2] = -3 - (-2) = -1` ✓
- `sumRange(0, 5)`: `prefix[6] - prefix[0] = -3 - 0 = -3` ✓

#### Complexity Analysis:
- **Time Complexity**: 
  - Constructor: O(n) for building prefix array
  - sumRange: O(1) per query
- **Space Complexity**: O(n) for the prefix array

#### Why This Works:
The prefix sum at index `i` contains the sum of all elements from index 0 to i-1. To get the sum from `left` to `right`:
- `sum(0, right) = prefix[right + 1]`
- `sum(0, left-1) = prefix[left]`
- `sum(left, right) = sum(0, right) - sum(0, left-1) = prefix[right + 1] - prefix[left]`

# Tags
- Array
- Prefix Sum
- Design
- Range Queries

