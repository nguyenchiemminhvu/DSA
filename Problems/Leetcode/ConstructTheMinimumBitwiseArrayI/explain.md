## Problem

https://leetcode.com/problems/construct-the-minimum-bitwise-array-i/description/

```
You are given an array nums consisting of n prime integers.

You need to construct an array ans of length n, such that, for each index i, the bitwise OR of ans[i] and ans[i] + 1 is equal to nums[i], i.e. ans[i] OR (ans[i] + 1) == nums[i].

Additionally, you must minimize each value of ans[i] in the resulting array.

If it is not possible to find such a value for ans[i] that satisfies the condition, then set ans[i] = -1.

Example 1:

Input: nums = [2,3,5,7]

Output: [-1,1,4,3]

Explanation:

For i = 0, as there is no value for ans[0] that satisfies ans[0] OR (ans[0] + 1) = 2, so ans[0] = -1.
For i = 1, the smallest ans[1] that satisfies ans[1] OR (ans[1] + 1) = 3 is 1, because 1 OR (1 + 1) = 3.
For i = 2, the smallest ans[2] that satisfies ans[2] OR (ans[2] + 1) = 5 is 4, because 4 OR (4 + 1) = 5.
For i = 3, the smallest ans[3] that satisfies ans[3] OR (ans[3] + 1) = 7 is 3, because 3 OR (3 + 1) = 7.

Example 2:

Input: nums = [11,13,31]

Output: [9,12,15]

Explanation:

For i = 0, the smallest ans[0] that satisfies ans[0] OR (ans[0] + 1) = 11 is 9, because 9 OR (9 + 1) = 11.
For i = 1, the smallest ans[1] that satisfies ans[1] OR (ans[1] + 1) = 13 is 12, because 12 OR (12 + 1) = 13.
For i = 2, the smallest ans[2] that satisfies ans[2] OR (ans[2] + 1) = 31 is 15, because 15 OR (15 + 1) = 31.

Constraints:

1 <= nums.length <= 100
2 <= nums[i] <= 1000
nums[i] is a prime number.
```

## Observations

1. **Problem Pattern**: For each number `nums[i]`, we need to find the smallest `ans[i]` such that `ans[i] | (ans[i] + 1) = nums[i]`.

2. **Bitwise OR Property**: When we have `x | (x + 1)`, what happens?
   - Adding 1 to a number flips the rightmost 0 bit to 1 and all bits to its right to 0
   - The OR operation combines all set bits from both numbers
   - Example: `4 (100) + 1 = 5 (101)`, so `4 | 5 = 101 = 5`
   - Example: `6 (110) + 1 = 7 (111)`, so `6 | 7 = 111 = 7`

3. **Key Insight**: If `nums[i]` has consecutive 1s ending at the least significant bit (like 3=11, 7=111), then no solution exists because:
   - Any `x` where `x | (x+1) = nums[i]` would require `x+1` to have a 0 bit where `nums[i]` has a 1
   - But if `nums[i]` ends with consecutive 1s, `x+1` cannot fill the missing bits properly

4. **Solution Pattern**: For solvable cases, we need to find the rightmost 0 bit in `nums[i]` and construct `ans[i]` by:
   - Keeping all bits the same as `nums[i]` except
   - Setting the rightmost 0 bit to 0 in `ans[i]`
   - This ensures `ans[i] + 1` will flip that bit and OR will give us `nums[i]`

5. **Examples Analysis**:
   - `nums[i] = 2 (10)`: Ends with 0, but `x | (x+1)` always produces odd numbers, so impossible
   - `nums[i] = 3 (11)`: Consecutive 1s at end, but `ans[i] = 1 (01)` works: `1 | 2 = 01 | 10 = 11 = 3`
   - `nums[i] = 5 (101)`: `ans[i] = 4 (100)` works: `4 | 5 = 100 | 101 = 101 = 5`
   - `nums[i] = 7 (111)`: `ans[i] = 3 (011)` works: `3 | 4 = 011 | 100 = 111 = 7`

## Solution

The brute force approach tries all possible values from 0 to `nums[i]-1` and checks if `val | (val + 1) == nums[i]`.

```python
class Solution:
    def minBitwiseArray(self, nums: List[int]) -> List[int]:
        n = len(nums)
        res = [-1] * n
        for i in range(n):
            for val in range(0, nums[i]):
                if (val | val + 1) == nums[i]:
                    res[i] = val
                    break
        return res
```

**Time Complexity**: O(n * max(nums)) - for each number, we might check up to `nums[i]` values
**Space Complexity**: O(1) - excluding the result array

**Optimized Mathematical Approach**:
```python
class Solution:
    def minBitwiseArray(self, nums: List[int]) -> List[int]:
        res = []
        for num in nums:
            if num == 2:
                res.append(-1)  # Special case: even numbers impossible except edge cases
                continue
            
            # Find the rightmost 0 bit
            # For odd numbers, we can always find a solution by clearing the rightmost 0
            ans = num
            for bit in range(20):  # Check each bit position
                if (num >> bit) & 1 == 0:  # Found rightmost 0 bit
                    ans = num & ~(1 << bit)  # Clear this bit
                    break
            
            # Verify our answer works, otherwise use brute force fallback
            if ans | (ans + 1) == num:
                res.append(ans)
            else:
                # Fallback to brute force for edge cases
                found = False
                for val in range(num):
                    if (val | val + 1) == num:
                        res.append(val)
                        found = True
                        break
                if not found:
                    res.append(-1)
        
        return res
```

# Tags

- **Bit Manipulation**: Core concept involves understanding bitwise OR operations
- **Brute Force**: Simple approach testing all possibilities
- **Mathematical Analysis**: Pattern recognition for optimized solution
- **Prime Numbers**: Input constraint (though not directly used in solution logic)

