## Problem

https://leetcode.com/problems/three-consecutive-odds/description/

```
Given an integer array arr, return true if there are three consecutive odd numbers in the array. Otherwise, return false.

Example 1:

Input: arr = [2,6,4,1]
Output: false
Explanation: There are no three consecutive odds.

Example 2:

Input: arr = [1,2,34,3,4,5,7,23,12]
Output: true
Explanation: [5,7,23] are three consecutive odds.

Constraints:

1 <= arr.length <= 1000
1 <= arr[i] <= 1000
```

## Observations

1. **Problem Goal**: We need to find if there are three consecutive odd numbers in the array.

2. **Key Insights**:
   - We need to track consecutive odd numbers, not just any three odd numbers
   - As soon as we find an even number, the consecutive count resets to 0
   - We can use bit manipulation (`val & 1`) to check if a number is odd more efficiently than modulo operation
   - We only need to return `True` as soon as we find 3 consecutive odds; no need to continue checking

3. **Edge Cases**:
   - Array with less than 3 elements cannot have 3 consecutive odds
   - Array with all even numbers will return `False`
   - Array with exactly 3 consecutive odds should return `True`

## Solution

1. **Initialize**: Start with `count = 0` to track consecutive odd numbers
2. **Iterate**: Loop through each number in the array
3. **Odd Check**: Use `val & 1` to check if current number is odd (more efficient than `val % 2`)
4. **Count Logic**: 
   - If odd: increment count and check if we've reached 3 consecutive odds
   - If even: reset count to 0 since consecutive sequence is broken
5. **Early Return**: Return `True` immediately when 3 consecutive odds are found
6. **Final Return**: Return `False` if we complete the loop without finding 3 consecutive odds

**Time Complexity**: O(n) - single pass through the array
**Space Complexity**: O(1) - only using constant extra space

**Why Bitwise AND (`val & 1`)**:
- Odd numbers have their least significant bit set to 1
- Even numbers have their least significant bit set to 0  
- `val & 1` returns 1 for odd numbers, 0 for even numbers
- This is slightly more efficient than modulo operation

# Tags
Array, Bit Manipulation, Sliding Window

