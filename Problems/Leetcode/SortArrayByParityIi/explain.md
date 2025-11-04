## Problem

https://leetcode.com/problems/sort-array-by-parity-ii/

```
Given an array of integers nums, half of the integers in nums are odd, and the other half are even.

Sort the array so that whenever nums[i] is odd, i is odd, and whenever nums[i] is even, i is even.

Return any answer array that satisfies this condition.

Example 1:

Input: nums = [4,2,5,7]
Output: [4,5,2,7]
Explanation: [4,7,2,5], [2,5,4,7], [2,7,4,5] would also have been accepted.

Example 2:

Input: nums = [2,3]
Output: [2,3]

Constraints:

2 <= nums.length <= 2 * 104
nums.length is even.
Half of the integers in nums are even.
0 <= nums[i] <= 1000

Follow Up: Could you solve it in-place?
```

## Observations

1. **Problem Requirements:**
   - We need to rearrange the array so that even numbers are at even indices (0, 2, 4, ...) and odd numbers are at odd indices (1, 3, 5, ...)
   - The array has exactly half even and half odd numbers
   - We need to solve this in-place for the follow-up

2. **Key Insights:**
   - A straightforward approach would be to use two pointers or create a new array
   - The given solution uses a very clever bit manipulation technique to achieve O(1) extra space
   - It stores two values in a single integer by using the upper and lower 16 bits

3. **Bit Manipulation Technique:**
   - Uses 32-bit integers where lower 16 bits store one value and upper 16 bits store another
   - `0xFFFF` = 65535 (all 1s in lower 16 bits) - used as a mask for lower 16 bits
   - `0xFFFF0000` - mask for upper 16 bits
   - Left shift by 16 (`<< 16`) moves value to upper 16 bits
   - Right shift by 16 (`>> 16`) moves value from upper 16 bits to lower 16 bits

## Solution

This solution uses an ingenious bit manipulation approach to solve the problem in-place with O(1) extra space.

### Algorithm Breakdown:

**Phase 1: Separate and Store**
```python
for i in range(n):
    if nums[i] & 1:  # If number is odd
        nums[upper_right] = (nums[upper_right] & 0xFFFF) | ((nums[i] & 0xFFFF) << 16)
        upper_right -= 1
    else:  # If number is even
        nums[upper_left] = (nums[upper_left] & 0xFFFF) | ((nums[i] & 0xFFFF) << 16)
        upper_left += 1
```

- Iterates through the array once
- For each odd number: stores it in the upper 16 bits of positions from the right side
- For each even number: stores it in the upper 16 bits of positions from the left side
- `upper_left` and `upper_right` track where to store the next even/odd numbers

**Phase 2: Redistribute**
```python
for i in range(n):
    if i & 1:  # If index is odd
        nums[i] = (nums[i] & 0xFFFF0000) | ((nums[upper_right] & 0xFFFF0000) >> 16)
        upper_right += 1
    else:  # If index is even
        nums[i] = (nums[i] & 0xFFFF0000) | ((nums[upper_left] & 0xFFFF0000) >> 16)
        upper_left -= 1
```

- Places odd numbers at odd indices by retrieving from upper 16 bits
- Places even numbers at even indices by retrieving from upper 16 bits
- Keeps the original values in lower 16 bits intact during this phase

**Phase 3: Clean Up**
```python
for i in range(n):
    nums[i] = nums[i] & 0xFFFF
```

- Removes the temporary values from upper 16 bits
- Keeps only the final result in lower 16 bits

### Example Walkthrough:

Input: `[4,2,5,7]`

**Phase 1:** Separate odds and evens
- `4` (even) → stored in upper bits of left side
- `2` (even) → stored in upper bits of left side  
- `5` (odd) → stored in upper bits of right side
- `7` (odd) → stored in upper bits of right side

**Phase 2:** Place in correct positions
- Index 0 (even): get even number from stored positions
- Index 1 (odd): get odd number from stored positions
- Index 2 (even): get even number from stored positions
- Index 3 (odd): get odd number from stored positions

**Phase 3:** Clean up bit manipulation artifacts

### Complexity:
- **Time Complexity:** O(n) - three passes through the array
- **Space Complexity:** O(1) - uses bit manipulation to store extra data in-place

### Alternative Simpler Approach:
```python
def sortArrayByParityII(self, nums: List[int]) -> List[int]:
    even_idx, odd_idx = 0, 1
    while even_idx < len(nums) and odd_idx < len(nums):
        if nums[even_idx] % 2 == 0:
            even_idx += 2
        elif nums[odd_idx] % 2 == 1:
            odd_idx += 2
        else:
            nums[even_idx], nums[odd_idx] = nums[odd_idx], nums[even_idx]
    return nums
```

# Tags

- Array
- Two Pointers  
- Bit Manipulation
- In-place Algorithm

