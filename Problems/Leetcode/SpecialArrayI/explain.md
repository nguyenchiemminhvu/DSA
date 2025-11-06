## Problem

https://leetcode.com/problems/special-array-i/description/

```
An array is considered special if the parity of every pair of adjacent elements is different. In other words, one element in each pair must be even, and the other must be odd.

You are given an array of integers nums. Return true if nums is a special array, otherwise, return false.

Example 1:

Input: nums = [1]

Output: true

Explanation:

There is only one element. So the answer is true.

Example 2:

Input: nums = [2,1,4]

Output: true

Explanation:

There is only two pairs: (2,1) and (1,4), and both of them contain numbers with different parity. So the answer is true.

Example 3:

Input: nums = [4,3,1,6]

Output: false

Explanation:

nums[1] and nums[2] are both odd. So the answer is false.

Constraints:

1 <= nums.length <= 100
1 <= nums[i] <= 100
```

## Observations

1. **Problem Understanding**: An array is "special" if every pair of adjacent elements has different parity (one even, one odd).

2. **Key Insight**: In a special array, the parity must alternate throughout the entire array. If we start with an even number, the next must be odd, then even, then odd, and so on.

3. **Pattern Recognition**: 
   - If `nums[0]` is even (parity = 0), then the pattern should be: even, odd, even, odd, ...
   - If `nums[0]` is odd (parity = 1), then the pattern should be: odd, even, odd, even, ...

4. **Edge Cases**: 
   - Single element array is always special (no adjacent pairs to check)
   - Empty array would be special, but constraints guarantee at least 1 element

5. **Bit Manipulation Insight**: 
   - `x & 1` extracts the least significant bit, giving us 0 for even numbers and 1 for odd numbers
   - `(parity + 1) & 1` flips between 0 and 1 efficiently

## Solution

The solution uses a clever approach to check if the array maintains alternating parity:

### Algorithm:
1. **Initialize Expected Parity**: Start with the parity of the first element (`nums[0] & 1`)
2. **Iterate Through Array**: For each element, check if its actual parity matches the expected parity
3. **Update Expected Parity**: After checking each element, flip the expected parity for the next element
4. **Early Return**: If any element doesn't match the expected parity, return `False`

### Example Walkthrough:
For `nums = [2,1,4]`:
- Start: `pairity = 2 & 1 = 0` (even)
- Check `2`: `2 & 1 = 0`, matches `pairity = 0` ✓, update `pairity = 1`
- Check `1`: `1 & 1 = 1`, matches `pairity = 1` ✓, update `pairity = 0`  
- Check `4`: `4 & 1 = 0`, matches `pairity = 0` ✓, update `pairity = 1`
- Return `True`

For `nums = [4,3,1,6]`:
- Start: `pairity = 4 & 1 = 0` (even)
- Check `4`: `4 & 1 = 0`, matches `pairity = 0` ✓, update `pairity = 1`
- Check `3`: `3 & 1 = 1`, matches `pairity = 1` ✓, update `pairity = 0`
- Check `1`: `1 & 1 = 1`, doesn't match `pairity = 0` ✗
- Return `False`

### Complexity Analysis:
- **Time Complexity**: O(n) - single pass through the array
- **Space Complexity**: O(1) - only using constant extra space

### Key Advantages:
1. **Efficient**: Single pass solution with early termination
2. **Bit Manipulation**: Uses bitwise operations for fast parity checking
3. **Clean Logic**: Alternating pattern check is straightforward

# Tags

`Array` `Bit Manipulation` `Parity` `Pattern Recognition` `Linear Scan`

