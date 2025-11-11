## Problem

https://leetcode.com/problems/find-lucky-integer-in-an-array/description/

```
Given an array of integers arr, a lucky integer is an integer that has a frequency in the array equal to its value.

Return the largest lucky integer in the array. If there is no lucky integer return -1.

Example 1:

Input: arr = [2,2,3,4]
Output: 2
Explanation: The only lucky number in the array is 2 because frequency[2] == 2.

Example 2:

Input: arr = [1,2,2,3,3,3]
Output: 3
Explanation: 1, 2 and 3 are all lucky numbers, return the largest of them.

Example 3:

Input: arr = [2,2,2,3,3]
Output: -1
Explanation: There are no lucky numbers in the array.

Constraints:

1 <= arr.length <= 500
1 <= arr[i] <= 500
```

## Observations

1. **Lucky Integer Definition**: A lucky integer is a number whose value equals its frequency in the array.
   - If number `x` appears `x` times in the array, then `x` is lucky.

2. **Problem Requirements**:
   - Find the **largest** lucky integer in the array
   - If no lucky integer exists, return -1

3. **Examples Analysis**:
   - `[2,2,3,4]`: Only 2 appears 2 times → 2 is lucky → return 2
   - `[1,2,2,3,3,3]`: 1 appears 1 time, 2 appears 2 times, 3 appears 3 times → all are lucky → return max = 3
   - `[2,2,2,3,3]`: 2 appears 3 times (not lucky), 3 appears 2 times (not lucky) → return -1

4. **Key Insights**:
   - We need to count frequency of each number
   - Check if frequency equals the number itself
   - Among all lucky numbers, return the maximum

## Solution

**Approach**: Hash Map (Counter) + Linear Scan

**Algorithm**:
1. Use `Counter` to count frequency of each number in the array
2. Iterate through the array and check each number:
   - If `frequency[number] == number`, it's a lucky integer
   - Track the maximum lucky integer found
3. Return the maximum lucky integer, or -1 if none exists

**Time Complexity**: O(n)
- Counter creation: O(n)
- Linear scan: O(n)
- Overall: O(n)

**Space Complexity**: O(k) where k is the number of unique elements
- Counter storage: O(k)
- In worst case k = n, so O(n)

**Alternative Approach**: We could iterate through unique values in the Counter instead of the entire array, but the complexity remains the same.

# Tags

`Array` `Hash Table` `Counting`

