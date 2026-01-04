## Problem

https://leetcode.com/problems/four-divisors/description/

```
Given an integer array nums, return the sum of divisors of the integers in that array 
that have exactly four divisors. If there is no such integer in the array, return 0.

Example 1:
Input: nums = [21,4,7]
Output: 32
Explanation: 
21 has 4 divisors: 1, 3, 7, 21
4 has 3 divisors: 1, 2, 4
7 has 2 divisors: 1, 7
The answer is the sum of divisors of 21 only.

Example 2:
Input: nums = [21,21]
Output: 64

Example 3:
Input: nums = [1,2,3,4,5]
Output: 0

Constraints:
1 <= nums.length <= 10^4
1 <= nums[i] <= 10^5
```

## Observations

1. **What numbers have exactly 4 divisors?**
   - Numbers of the form $p^3$ where $p$ is prime (e.g., $8 = 2^3$ has divisors: 1, 2, 4, 8)
   - Numbers of the form $p \times q$ where $p$ and $q$ are distinct primes (e.g., $21 = 3 \times 7$ has divisors: 1, 3, 7, 21)

2. **Divisor finding approach:**
   - Only need to check up to $\sqrt{n}$ for divisors
   - For each divisor $i$ found, $n/i$ is also a divisor
   - Special case: if $i = \sqrt{n}$ (perfect square), only count it once

3. **Optimization opportunities:**
   - Early exit if we find more than 4 divisors during iteration
   - Can optimize by checking divisor count before computing sum

4. **Edge cases:**
   - Small numbers (1 has 1 divisor, 2 has 2 divisors)
   - Perfect squares need special handling to avoid double-counting
   - Duplicate numbers in the array (each occurrence should be processed)

## Solution

### Approach: Efficient Divisor Finding

**Algorithm:**
1. For each number in the array:
   - Find all its divisors using optimized search up to $\sqrt{n}$
   - Check if the number has exactly 4 divisors
   - If yes, sum all its divisors and add to the result

2. **Divisor finding (`get_divs` function):**
   - Iterate from 1 to $\sqrt{val}$
   - For each $i$ that divides $val$:
     - Add $i$ as a divisor
     - Add $val/i$ as a divisor (unless $i^2 = val$ to avoid duplicates)

**Time Complexity:** $O(n \times \sqrt{m})$ where:
- $n$ = length of nums array
- $m$ = maximum value in nums (up to $10^5$)
- For each number, we iterate up to $\sqrt{m}$

**Space Complexity:** $O(d)$ where $d$ is the number of divisors (at most ~100 for numbers ≤ $10^5$)

### Implementation Details

```python
class Solution:
    def sumFourDivisors(self, nums: List[int]) -> int:
        def get_divs(val: int) -> List[int]:
            divs = []
            n = int(math.sqrt(val)) + 1
            for i in range(1, n):
                if val % i == 0:
                    divs.append(i)
                    if i * i != val:  # Avoid double-counting perfect squares
                        divs.append(val // i)
            return divs
        
        s = 0
        for val in nums:
            divs = get_divs(val)
            if len(divs) == 4:
                s += sum(divs)
        return s
```

**Key Points:**
- The condition `i * i != val` prevents double-counting when the number is a perfect square
- We only iterate up to $\sqrt{val}$ for efficiency
- The `range(1, n)` starts from 1 to include 1 as a divisor

### Optimized Version (Early Exit)

```python
class Solution:
    def sumFourDivisors(self, nums: List[int]) -> int:
        def get_divs_sum(val: int) -> int:
            divs = set()
            n = int(math.sqrt(val)) + 1
            for i in range(1, n):
                if val % i == 0:
                    divs.add(i)
                    divs.add(val // i)
                    if len(divs) > 4:  # Early exit
                        return 0
            
            return sum(divs) if len(divs) == 4 else 0
        
        return sum(get_divs_sum(val) for val in nums)
```

This optimization exits early if more than 4 divisors are found, avoiding unnecessary computation.

# Tags
`Array` `Math` `Number Theory` `Divisors`

