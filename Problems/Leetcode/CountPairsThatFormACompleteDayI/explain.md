## Problem

https://leetcode.com/problems/count-pairs-that-form-a-complete-day-i/description/

```
Given an integer array hours representing times in hours, return an integer denoting the number of pairs i, j where i < j and hours[i] + hours[j] forms a complete day.

A complete day is defined as a time duration that is an exact multiple of 24 hours.

For example, 1 day is 24 hours, 2 days is 48 hours, 3 days is 72 hours, and so on.

Example 1:

Input: hours = [12,12,30,24,24]

Output: 2

Explanation:

The pairs of indices that form a complete day are (0, 1) and (3, 4).

Example 2:

Input: hours = [72,48,24,3]

Output: 3

Explanation:

The pairs of indices that form a complete day are (0, 1), (0, 2), and (1, 2).

Constraints:

1 <= hours.length <= 100
1 <= hours[i] <= 109
```

## Observations

1. **Complete Day Definition**: Two hours form a complete day if their sum is divisible by 24 (i.e., `(hours[i] + hours[j]) % 24 == 0`).

2. **Modular Arithmetic Insight**: Since we only care about divisibility by 24, we can work with `hours[i] % 24` instead of the actual values. This reduces the problem space significantly.

3. **Complementary Pairs**: For any hour `h`, we need to find hours that when added to `h` give a multiple of 24. If `h % 24 = r`, then we need hours with remainder `(24 - r) % 24`.

4. **Special Cases**: 
   - When `h % 24 = 0`, we need another hour that is also divisible by 24 (complement is 0)
   - When `h % 24 = 12`, we need another hour with remainder 12 (complement is 12)

5. **One-Pass Solution**: We can solve this in a single pass by maintaining a frequency map of remainders and counting valid pairs as we iterate.

## Solution

1. **Initialize**: Create a counter `count = 0` and a frequency map `f` to store the count of each remainder when divided by 24.

2. **Iterate through hours**: For each hour `h`:
   - **Find complement**: Calculate the required remainder `(24 - (h % 24)) % 24` that would make the sum divisible by 24
   - **Count pairs**: Add the frequency of the complement remainder to our count (these are all valid pairs with the current hour)
   - **Update frequency**: Increment the frequency of the current hour's remainder

3. **Key Formula**: `(24 - (h % 24)) % 24`
   - `h % 24` gives the remainder when h is divided by 24
   - `24 - (h % 24)` gives what we need to add to make it divisible by 24
   - The outer `% 24` handles the special case when `h % 24 = 0` (we get 24, but we want 0)

### Example Walkthrough:

For `hours = [12, 12, 30, 24, 24]`:

- `h = 12`: remainder = 12, complement = 12, count += f[12] = 0, f[12] = 1
- `h = 12`: remainder = 12, complement = 12, count += f[12] = 1, f[12] = 2  
- `h = 30`: remainder = 6, complement = 18, count += f[18] = 0, f[6] = 1
- `h = 24`: remainder = 0, complement = 0, count += f[0] = 0, f[0] = 1
- `h = 24`: remainder = 0, complement = 0, count += f[0] = 1, f[0] = 2

Final count = 2 ✓

### Time & Space Complexity:
- **Time**: O(n) - single pass through the array
- **Space**: O(1) - frequency map can have at most 24 entries (remainders 0-23)

# Tags

Array, Hash Table, Math, Counting

