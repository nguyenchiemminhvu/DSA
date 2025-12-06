## Problem

https://leetcode.com/problems/maximum-subarray-with-equal-products/description/

You are given an array of positive integers `nums`.

An array `arr` is called **product equivalent** if `prod(arr) == lcm(arr) * gcd(arr)`, where:
- `prod(arr)` is the product of all elements of arr.
- `gcd(arr)` is the GCD of all elements of arr.
- `lcm(arr)` is the LCM of all elements of arr.

Return the length of the longest product equivalent subarray of `nums`.

**Example 1:**
```
Input: nums = [1,2,1,2,1,1,1]
Output: 5
Explanation: The longest product equivalent subarray is [1, 2, 1, 1, 1], 
where prod([1, 2, 1, 1, 1]) = 2, gcd([1, 2, 1, 1, 1]) = 1, and lcm([1, 2, 1, 1, 1]) = 2.
```

**Example 2:**
```
Input: nums = [2,3,4,5,6]
Output: 3
Explanation: The longest product equivalent subarray is [3, 4, 5].
```

**Example 3:**
```
Input: nums = [1,2,3,1,4,5,1]
Output: 5
```

**Constraints:**
- `2 <= nums.length <= 100`
- `1 <= nums[i] <= 10`

## Observations

### 1. Understanding Product Equivalence

For an array to be product equivalent: `prod(arr) == lcm(arr) * gcd(arr)`

Let's understand why this condition makes sense mathematically:
- For an array with elements `[a, b, c, ...]`, we have the relationship:
  - `lcm(arr) * gcd(arr) <= prod(arr)` (always true)
  - Equality holds in special cases

**When does equality hold?**
- Single element: `[a]` → `prod = a`, `lcm = a`, `gcd = a` → `a == a * a` (false unless a = 1)
- All ones: `[1,1,1]` → `prod = 1`, `lcm = 1`, `gcd = 1` → `1 == 1 * 1` ✓
- Coprime pairs: `[2,3]` → `prod = 6`, `lcm = 6`, `gcd = 1` → `6 == 6 * 1` ✓
- With ones: `[1,2,1]` → `prod = 2`, `lcm = 2`, `gcd = 1` → `2 == 2 * 1` ✓

### 2. Key Mathematical Properties

**Property 1:** If the array contains only 1s, it's product equivalent.
- `prod([1,1,...,1]) = 1`
- `lcm([1,1,...,1]) = 1`
- `gcd([1,1,...,1]) = 1`
- `1 == 1 * 1` ✓

**Property 2:** For pairwise coprime numbers (gcd of any two is 1):
- `prod([a,b,c]) = a * b * c`
- `lcm([a,b,c]) = a * b * c` (since they're coprime)
- `gcd([a,b,c]) = 1`
- `a*b*c == a*b*c * 1` ✓

**Property 3:** Including 1s in any product equivalent array keeps it product equivalent.
- Adding a 1 doesn't change gcd or lcm
- Product gets multiplied by 1 (no change)

### 3. Upper Bound Analysis

The crucial optimization: `if prod > 2520 * lcm * gcd: break`

Why 2520?
- Since `nums[i] <= 10`, the maximum LCM of any subset is `lcm(1,2,3,4,5,6,7,8,9,10) = 2520`
- This is the smallest number divisible by all integers from 1 to 10

**Why this pruning works:**
- If `prod > 2520 * lcm * gcd`, then `prod > lcm * gcd` is impossible to satisfy
- Since `lcm <= 2520` (maximum possible), we know `prod` has exceeded any possible `lcm * gcd`
- Extending the subarray further will only increase `prod`, making equality impossible

### 4. Brute Force Viability

With constraints:
- `n <= 100` → O(n²) = 10,000 operations
- For each subarray, we compute prod, lcm, gcd incrementally → O(1) per element
- Early termination with the 2520 bound prevents exponential growth
- Total complexity: O(n²) with practical optimization

## Solution

1. **Outer loop (i):** Try every possible starting position
2. **Inner loop (j):** Extend subarray from position i to j
3. **Incremental updates:**
   - `prod *= nums[j]` - Update product
   - `lcm = math.lcm(lcm, nums[j])` - Update LCM
   - `gcd = math.gcd(gcd, nums[j])` - Update GCD
4. **Early termination:** If `prod > 2520 * lcm * gcd`, break (impossible to satisfy condition)
5. **Check condition:** If `prod == lcm * gcd`, update maximum length

### Why This Works

1. **Completeness:** We check all possible subarrays
2. **Efficiency:** 
   - Incremental computation avoids recalculating from scratch
   - Early termination prevents checking impossible cases
   - O(n²) is acceptable given constraints
3. **Correctness:** Mathematical properties ensure we don't miss valid subarrays

### Example Walkthrough

For `nums = [1,2,1,2,1,1,1]`:

Starting at i=0:
- `[1]`: prod=1, lcm=1, gcd=1 → 1 == 1*1 ✓ (len=1)
- `[1,2]`: prod=2, lcm=2, gcd=1 → 2 == 2*1 ✓ (len=2)
- `[1,2,1]`: prod=2, lcm=2, gcd=1 → 2 == 2*1 ✓ (len=3)
- `[1,2,1,2]`: prod=4, lcm=2, gcd=1 → 4 ≠ 2*1 ✗
- `[1,2,1,2,1]`: prod=4, lcm=2, gcd=1 → 4 ≠ 2*1 ✗
- `[1,2,1,2,1,1]`: prod=4, lcm=2, gcd=1 → 4 ≠ 2*1 ✗
- `[1,2,1,2,1,1,1]`: prod=4, lcm=2, gcd=1 → 4 ≠ 2*1 ✗

Starting at i=2:
- `[1,2,1,1,1]`: prod=2, lcm=2, gcd=1 → 2 == 2*1 ✓ (len=5) ← Maximum!

### Complexity Analysis

- **Time Complexity:** O(n² * log(max_num))
  - O(n²) for nested loops
  - O(log(max_num)) for GCD/LCM computation
  - Early termination reduces practical runtime
  
- **Space Complexity:** O(1)
  - Only storing scalar values (prod, lcm, gcd, res)

# Tags

Array, Math, Brute Force, GCD, LCM, Number Theory, Subarray

