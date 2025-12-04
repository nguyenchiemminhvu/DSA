## Problem

https://leetcode.com/problems/form-smallest-number-from-two-digit-arrays/description/

Given two arrays of unique digits `nums1` and `nums2`, return the smallest number that contains at least one digit from each array.

**Example 1:**
```
Input: nums1 = [4,1,3], nums2 = [5,7]
Output: 15
Explanation: The number 15 contains the digit 1 from nums1 and the digit 5 from nums2. 
It can be proven that 15 is the smallest number we can have.
```

**Example 2:**
```
Input: nums1 = [3,5,2,6], nums2 = [3,1,7]
Output: 3
Explanation: The number 3 contains the digit 3 which exists in both arrays.
```

**Constraints:**
- `1 <= nums1.length, nums2.length <= 9`
- `1 <= nums1[i], nums2[i] <= 9`
- All digits in each array are unique

## Observations

1. **Common Digit Case**: If there's a digit that exists in both arrays, that single digit is the smallest possible number. We just need to find the minimum among common digits.

2. **No Common Digit Case**: If there are no common digits, we need to form a two-digit number:
   - Take the smallest digit from each array
   - Arrange them to form the smallest two-digit number (smaller digit first)

3. **Why This Works**:
   - A single-digit number is always smaller than a two-digit number
   - For two-digit numbers, the one starting with a smaller digit is smaller
   - We must use at least one digit from each array

4. **Time Complexity**: O(n + m) where n and m are the lengths of the arrays
   - Finding intersection: O(min(n, m))
   - Finding minimum in intersection: O(min(n, m))
   - Finding minimum of each array: O(n) + O(m)

5. **Space Complexity**: O(min(n, m)) for storing the intersection set

## Solution

1. **Check for Common Digits**: 
   - Use set intersection (`set(a) & set(b)`) to find digits present in both arrays
   - If any common digits exist, return the smallest one (single digit is always smallest)

2. **Handle No Common Digits**:
   - Find `min(a)` and `min(b)` - the smallest digit from each array
   - Sort these two minimums to ensure smaller digit comes first
   - Construct the two-digit number: `smaller * 10 + larger`

**Example Walkthrough:**

*Example 1:* `nums1 = [4,1,3], nums2 = [5,7]`
- Common digits: `{}` (empty)
- `min(nums1) = 1`, `min(nums2) = 5`
- `sorted([1, 5]) = [1, 5]`
- Result: `1 * 10 + 5 = 15`

*Example 2:* `nums1 = [3,5,2,6], nums2 = [3,1,7]`
- Common digits: `{3}`
- Result: `min({3}) = 3`

# Tags

`Array` `Hash Table` `Math` `Set Intersection` `Greedy`

