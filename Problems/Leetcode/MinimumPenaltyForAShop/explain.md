## Problem

https://leetcode.com/problems/minimum-penalty-for-a-shop/description/

```
You are given the customer visit log of a shop represented by a 0-indexed string customers 
consisting only of characters 'N' and 'Y':
- if the ith character is 'Y', it means that customers come at the ith hour
- 'N' indicates that no customers come at the ith hour

If the shop closes at the jth hour (0 <= j <= n), the penalty is calculated as follows:
- For every hour when the shop is open and no customers come, the penalty increases by 1
- For every hour when the shop is closed and customers come, the penalty increases by 1

Return the earliest hour at which the shop must be closed to incur a minimum penalty.

Note: if a shop closes at the jth hour, it means the shop is closed at the hour j.

Example 1:
Input: customers = "YYNY"
Output: 2
Explanation: 
- Closing at 0th hour: penalty = 1+1+0+1 = 3
- Closing at 1st hour: penalty = 0+1+0+1 = 2
- Closing at 2nd hour: penalty = 0+0+0+1 = 1 (minimum)
- Closing at 3rd hour: penalty = 0+0+1+1 = 2
- Closing at 4th hour: penalty = 0+0+1+0 = 1 (minimum)
Closing at 2nd hour is the earliest minimum.

Example 2:
Input: customers = "NNNNN"
Output: 0

Example 3:
Input: customers = "YYYY"
Output: 4

Constraints:
- 1 <= customers.length <= 10^5
- customers consists only of characters 'Y' and 'N'
```

## Observations

1. **Penalty Composition**: For any closing hour `j`:
   - Penalty = (count of 'N' in [0, j)) + (count of 'Y' in [j, n))
   - Before closing: we lose penalty for each 'N' (shop open, no customers)
   - After closing: we lose penalty for each 'Y' (shop closed, but customers came)

2. **Closing Time Range**: We can close at any hour from 0 to n (inclusive)
   - Close at 0: shop never opens, penalty = count of all 'Y'
   - Close at n: shop always open, penalty = count of all 'N'

3. **Brute Force**: Check all n+1 possible closing times - O(n²) time

4. **Optimization**: Use prefix/suffix arrays to precompute counts
   - Suffix array: store count of 'Y' from each position to end
   - As we iterate, track count of 'N' seen so far
   - Penalty at hour i = count_N_before_i + suffix_Y[i]

5. **Edge Case**: Must check closing at hour n (after all hours)

## Solution

### Approach: Suffix Array + Running Counter

The solution uses a two-pass approach:

**Pass 1 - Build Suffix Y Array** (backwards):
```python
suffix_y = [0] * n
count_y = 0
for i in range(n - 1, -1, -1):
    if customers[i] == 'Y':
        count_y += 1
    suffix_y[i] = count_y
```
- `suffix_y[i]` stores the count of 'Y' from position i to the end
- This represents the penalty if we close at hour i (all future customers are missed)

**Pass 2 - Find Minimum Penalty** (forwards):
```python
count_n = 0
for i in range(n):
    penalty_at_i = count_n + suffix_y[i]
    if penalty_at_i < min_pen:
        min_pen = penalty_at_i
        close_time = i
    if customers[i] == 'N':
        count_n += 1
```
- Track running count of 'N' seen before hour i
- Penalty at hour i = 'N' count before i + 'Y' count from i onwards
- Update minimum when we find a better closing time

**Pass 3 - Check Closing at Hour n**:
```python
if min_pen > count_n:
    close_time = n
```
- If closing after all hours (count_n = all 'N's) gives lower penalty, choose it

### Complexity Analysis

- **Time Complexity**: O(n)
  - First pass to build suffix array: O(n)
  - Second pass to find minimum: O(n)
  
- **Space Complexity**: O(n)
  - Suffix array storage: O(n)

### Alternative Optimization

Could reduce space to O(1) by:
- Computing total 'Y' count initially
- Decrementing when passing 'Y', incrementing 'N' count when passing 'N'
- No need for suffix array

# Tags
`Array` `Prefix Sum` `String` `Greedy`

