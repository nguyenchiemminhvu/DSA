## Problem

https://leetcode.com/problems/find-unique-binary-string/description/

```
Given an array of strings nums containing n unique binary strings each of length n, return a binary string of length n that does not appear in nums. If there are multiple answers, you may return any of them.

Example 1:

Input: nums = ["01","10"]
Output: "11"
Explanation: "11" does not appear in nums. "00" would also be correct.

Example 2:

Input: nums = ["00","01"]
Output: "11"
Explanation: "11" does not appear in nums. "10" would also be correct.

Example 3:

Input: nums = ["111","011","001"]
Output: "101"
Explanation: "101" does not appear in nums. "000", "010", "100", and "110" would also be correct.

Constraints:

n == nums.length
1 <= n <= 16
nums[i].length == n
nums[i] is either '0' or '1'.
All the strings of nums are unique.
```

## Observations

1. **Problem Space**: We have `n` unique binary strings, each of length `n`. We need to find any binary string of length `n` that's not in the given array.

2. **Total Possibilities**: For binary strings of length `n`, there are exactly `2^n` possible combinations (from "00...0" to "11...1").

3. **Guaranteed Solution Exists**: Since we have `n` strings and there are `2^n` possible strings, and `n ≤ 2^n` for all valid inputs (n ≥ 1), there's always at least one missing string.

4. **Small Constraint**: With `n ≤ 16`, we have at most `2^16 = 65,536` possibilities, making brute force feasible.

5. **Conversion Strategy**: We can convert binary strings to integers for easier comparison and generation.

## Solution

### Approach: Brute Force with Set Lookup

The solution uses a straightforward brute force approach:

1. **Convert to Integers**: Convert all input binary strings to integers and store them in a set for O(1) lookup.
   ```python
   s = set([int(val, 2) for val in nums])
   ```
   - `int(val, 2)` converts binary string to decimal integer
   - Set provides constant time membership testing

2. **Iterate Through All Possibilities**: Check every possible integer value from `0` to `2^n - 1`.
   ```python
   for val in range((1 << n)):  # (1 << n) is 2^n
   ```

3. **Find Missing Value**: Return the first integer not present in our set.
   ```python
   if val not in s:
       res = bin(val)[2:]  # Convert back to binary, remove '0b' prefix
       return ('0' * (n - len(res))) + res  # Pad with leading zeros
   ```

4. **Format Result**: Convert the integer back to binary string with proper padding.
   - `bin(val)[2:]` gives binary representation without "0b" prefix
   - Pad with leading zeros to ensure length `n`

### Time Complexity: O(n × 2^n)
- Converting input strings to integers: O(n²) 
- Iterating through 2^n possibilities: O(2^n)
- For each iteration, set lookup is O(1), binary conversion is O(n)
- Overall: O(n × 2^n)

### Space Complexity: O(n)
- Set storage for n integers: O(n)
- Additional variables: O(1)

### Alternative Approach (Cantor's Diagonalization)
A more elegant O(n) solution exists using Cantor's diagonalization theorem:
```python
def findDifferentBinaryString(self, nums: List[str]) -> str:
    return ''.join('1' if nums[i][i] == '0' else '0' for i in range(len(nums)))
```
This constructs a string that differs from each input string in at least one position (the diagonal position).

## Tags

- **Array**: Input is an array of strings
- **String**: Working with binary string representations  
- **Hash Table**: Using set for fast lookups
- **Bit Manipulation**: Converting between binary strings and integers
- **Brute Force**: Checking all possible combinations
- **Math**: Understanding 2^n total possibilities

