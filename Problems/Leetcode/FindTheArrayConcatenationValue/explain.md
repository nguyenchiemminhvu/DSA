## Problem

https://leetcode.com/problems/find-the-array-concatenation-value/

```
You are given a 0-indexed integer array nums.

The concatenation of two numbers is the number formed by concatenating their numerals.

For example, the concatenation of 15, 49 is 1549.
The concatenation value of nums is initially equal to 0. Perform this operation until nums becomes empty:

If nums has a size greater than one, add the value of the concatenation of the first and the last element to the concatenation value of nums, and remove those two elements from nums. For example, if the nums was [1, 2, 4, 5, 6], add 16 to the concatenation value.
If only one element exists in nums, add its value to the concatenation value of nums, then remove it.
Return the concatenation value of nums.

Example 1:

Input: nums = [7,52,2,4]
Output: 596
Explanation: Before performing any operation, nums is [7,52,2,4] and concatenation value is 0.
 - In the first operation:
We pick the first element, 7, and the last element, 4.
Their concatenation is 74, and we add it to the concatenation value, so it becomes equal to 74.
Then we delete them from nums, so nums becomes equal to [52,2].
 - In the second operation:
We pick the first element, 52, and the last element, 2.
Their concatenation is 522, and we add it to the concatenation value, so it becomes equal to 596.
Then we delete them from the nums, so nums becomes empty.
Since the concatenation value is 596 so the answer is 596.

Example 2:

Input: nums = [5,14,13,8,12]
Output: 673
Explanation: Before performing any operation, nums is [5,14,13,8,12] and concatenation value is 0.
 - In the first operation:
We pick the first element, 5, and the last element, 12.
Their concatenation is 512, and we add it to the concatenation value, so it becomes equal to 512.
Then we delete them from the nums, so nums becomes equal to [14,13,8].
 - In the second operation:
We pick the first element, 14, and the last element, 8.
Their concatenation is 148, and we add it to the concatenation value, so it becomes equal to 660.
Then we delete them from the nums, so nums becomes equal to [13].
 - In the third operation:
nums has only one element, so we pick 13 and add it to the concatenation value, so it becomes equal to 673.
Then we delete it from nums, so nums become empty.
Since the concatenation value is 673 so the answer is 673.

Constraints:

1 <= nums.length <= 1000
1 <= nums[i] <= 104
```

## Observations

1. **Two-pointer approach**: We process the array from both ends simultaneously using left and right pointers.

2. **Concatenation logic**: 
   - When we have two different elements (l < r), we concatenate them by converting to strings and joining them
   - When we have only one element left (l == r), we just take that element's value

3. **String concatenation for numbers**: The key insight is using string concatenation to join numbers:
   - `str(nums[l]) + str(nums[r])` creates the concatenated string
   - `int(...)` converts it back to an integer

4. **Process until empty**: We continue until all elements are processed (l <= r condition)

5. **Time complexity**: O(n * k) where n is the number of elements and k is the average number of digits per number (due to string operations)

6. **Space complexity**: O(k) for temporary string creation during concatenation

## Solution

The solution uses a **two-pointer technique** to efficiently process the array from both ends:

### Algorithm Steps:
1. **Initialize**: Set left pointer `l = 0`, right pointer `r = n-1`, and result `res = 0`
2. **Process pairs**: While `l <= r`:
   - If `l < r`: Concatenate `nums[l]` and `nums[r]` by converting to strings
   - If `l == r`: Take the single remaining element
   - Add the computed value to the result
   - Move pointers inward: `l++`, `r--`
3. **Return**: The accumulated concatenation value

### Example Walkthrough:
For `nums = [7,52,2,4]`:
- **Step 1**: l=0, r=3 → concat(7,4) = 74, res = 74
- **Step 2**: l=1, r=2 → concat(52,2) = 522, res = 596
- **Result**: 596

For `nums = [5,14,13,8,12]`:
- **Step 1**: l=0, r=4 → concat(5,12) = 512, res = 512
- **Step 2**: l=1, r=3 → concat(14,8) = 148, res = 660
- **Step 3**: l=2, r=2 → single element 13, res = 673
- **Result**: 673

### Key Implementation Details:
- **String concatenation**: `str(nums[l]) + str(nums[r])` handles different digit lengths correctly
- **Boundary condition**: `l < r` check ensures we handle the middle element correctly in odd-length arrays
- **Efficient processing**: Each element is processed exactly once

# Tags

Two Pointers, Array, String Manipulation, Simulation

