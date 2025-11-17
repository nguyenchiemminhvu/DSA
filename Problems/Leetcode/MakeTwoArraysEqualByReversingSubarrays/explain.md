## Problem

https://leetcode.com/problems/make-two-arrays-equal-by-reversing-subarrays/

```
You are given two integer arrays of equal length target and arr. In one step, you can select any non-empty subarray of arr and reverse it. You are allowed to make any number of steps.

Return true if you can make arr equal to target or false otherwise.

Example 1:

Input: target = [1,2,3,4], arr = [2,4,1,3]
Output: true
Explanation: You can follow the next steps to convert arr to target:
1- Reverse subarray [2,4,1], arr becomes [1,4,2,3]
2- Reverse subarray [4,2], arr becomes [1,2,4,3]
3- Reverse subarray [4,3], arr becomes [1,2,3,4]
There are multiple ways to convert arr to target, this is not the only way to do so.

Example 2:

Input: target = [7], arr = [7]
Output: true
Explanation: arr is equal to target without any reverses.

Example 3:

Input: target = [3,7,9], arr = [3,7,11]
Output: false
Explanation: arr does not have value 9 and it can never be converted to target.

Constraints:

target.length == arr.length
1 <= target.length <= 1000
1 <= target[i] <= 1000
1 <= arr[i] <= 1000
```

## Observations

1. **Key Insight**: The problem is asking whether we can rearrange array `arr` to match array `target` using subarray reversals.

2. **Critical Realization**: Any permutation of an array can be achieved through a series of subarray reversals. This means if two arrays contain the same elements with the same frequencies, one can always be transformed into the other.

3. **Problem Reduction**: The problem reduces to checking if both arrays are anagrams of each other - i.e., they contain exactly the same elements with the same frequencies.

4. **Why Reversals Don't Matter**: 
   - Reversing subarrays is a way to rearrange elements
   - Any sorting algorithm (like bubble sort) can be implemented using adjacent swaps
   - Adjacent swaps can be achieved by reversing subarrays of length 2
   - Therefore, any permutation is achievable through reversals

5. **Examples Analysis**:
   - `target = [1,2,3,4], arr = [2,4,1,3]`: Both have {1:1, 2:1, 3:1, 4:1} → True
   - `target = [7], arr = [7]`: Both have {7:1} → True  
   - `target = [3,7,9], arr = [3,7,11]`: target has {9:1}, arr has {11:1} → False

## Solution

**Algorithm**: Frequency Count Comparison

The solution uses a frequency map approach:

1. **Count frequencies in `arr`**: Create a hash map that stores the frequency of each element in the `arr` array.

2. **Verify against `target`**: For each element in `target`:
   - Check if the element exists in the frequency map (from `arr`)
   - If it doesn't exist, return `False` (impossible to transform)
   - If it exists, decrement its frequency
   - If frequency goes below 0, return `False` (not enough of this element in `arr`)

3. **Return result**: If we successfully process all elements in `target`, return `True`.

**Why this works**: 
- If both arrays have the same length and same element frequencies, they are permutations of each other
- Any permutation can be achieved through subarray reversals
- The frequency check ensures we have exactly the right elements in the right quantities

**Time Complexity**: O(n) where n is the length of the arrays
- Single pass to build frequency map: O(n)
- Single pass to verify against target: O(n)

**Space Complexity**: O(n) for the frequency map in the worst case (all elements unique)

**Alternative Approach**: Simply sort both arrays and compare: `return sorted(arr) == sorted(target)`
- Time: O(n log n), Space: O(1) if in-place sorting allowed
- The frequency approach is more efficient

# Tags

`Array` `Hash Table` `Sorting` `Frequency Count` `Permutation`

