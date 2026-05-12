## Problem

https://leetcode.com/problems/factorial-trailing-zeroes/description

Given an integer `n`, return the number of trailing zeroes in `n!`.

Note that `n! = n * (n - 1) * (n - 2) * ... * 3 * 2 * 1`.

### Examples:

**Example 1:**
- Input: `n = 3`
- Output: `0`
- Explanation: `3! = 6`, no trailing zero.

**Example 2:**
- Input: `n = 5`
- Output: `1`
- Explanation: `5! = 120`, one trailing zero.

**Example 3:**
- Input: `n = 0`
- Output: `0`

### Constraints:
- `0 <= n <= 10^4`

### Follow up:
Could you write a solution that works in logarithmic time complexity?

## Observations

**Key Insight:** Trailing zeroes are produced by factors of 10, and `10 = 2 × 5`. In the factorial of any number, there are always more factors of 2 than factors of 5. Therefore, the number of trailing zeroes is determined by **how many times 5 appears as a factor** in n!.

**Why count factors of 5?**
- `n!` is a product of all numbers from 1 to n
- Each trailing zero comes from a pair of factors (2, 5) making 10
- There are always more factors of 2 than 5 in n! (every even number contributes at least one 2)
- So we only need to count factors of 5

**Counting factors of 5:**
- Numbers divisible by 5 contribute one factor of 5: `5, 10, 15, 20, ...`
- Numbers divisible by 25 (5²) contribute an additional factor of 5: `25, 50, 75, 100, ...`
- Numbers divisible by 125 (5³) contribute another additional factor of 5: `125, 250, ...`
- And so on...

**Example with n = 25:**
- Numbers divisible by 5: 5, 10, 15, 20, 25 → count = 5
- Numbers divisible by 25: 25 → count = 1 (additional factor)
- Total = 5 + 1 = 6

## Solution

```python
class Solution:
    def trailingZeroes(self, n: int) -> int:
        count = 0
        while n >= 5:
            n //= 5
            count += n
        return count
```

### Algorithm Explanation:

**Step-by-step breakdown:**

1. **Initialize counter:** Start with `count = 0`

2. **Iterate while n ≥ 5:**
   - Divide `n` by 5 (integer division): `n //= 5`
   - This gives us how many multiples of the current power of 5 exist
   - Add this to the count: `count += n`

3. **Why this works:**
   - First iteration (n ÷ 5): Counts multiples of 5¹ = 5
   - Second iteration (n ÷ 25): Counts multiples of 5² = 25 (which contribute an extra 5)
   - Third iteration (n ÷ 125): Counts multiples of 5³ = 125 (which contribute another extra 5)
   - And so on...

**Example walkthrough with n = 25:**
```
Initial: n = 25, count = 0

Iteration 1:
  n = 25 // 5 = 5
  count += 5 → count = 5

Iteration 2:
  n = 5 // 5 = 1
  count += 1 → count = 6

Iteration 3:
  n = 1 // 5 = 0
  Loop exits (n < 5)

Result: 6
```

**Verification:** 25! contains factors of 5 from: 5, 10, 15, 20, 25
- 5 contributes one 5
- 10 contributes one 5
- 15 contributes one 5
- 20 contributes one 5
- 25 contributes two 5s (5²)
- Total = 1 + 1 + 1 + 1 + 2 = 6 ✓

### Complexity Analysis:

- **Time Complexity:** $O(\log_5 n)$ - We divide n by 5 repeatedly until n becomes less than 5
  - This is logarithmic with base 5, which satisfies the follow-up requirement
  
- **Space Complexity:** $O(1)$ - Only using a constant amount of extra space

### Key Takeaways:

✓ Trailing zeroes in n! = count of factor pairs (2, 5), which equals count of 5s
✓ Must account for multiples of higher powers of 5 (25, 125, 625, ...)
✓ Simple division by 5 in a loop naturally handles all powers
✓ Logarithmic time complexity makes it efficient for large n values

# Tags

- Math
- Number Theory
- Factorial
- Trailing Zeroes
- Logarithmic Time Complexity

