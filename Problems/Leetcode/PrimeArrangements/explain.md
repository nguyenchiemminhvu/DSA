## Problem

https://leetcode.com/problems/prime-arrangements/description/

```
Return the number of permutations of 1 to n so that prime numbers are at prime indices (1-indexed.)

(Recall that an integer is prime if and only if it is greater than 1, and cannot be written as a product of two positive integers both smaller than it.)

Since the answer may be large, return the answer modulo 10^9 + 7.

Example 1:

Input: n = 5
Output: 12
Explanation: For example [1,2,5,4,3] is a valid permutation, but [5,2,3,4,1] is not because the prime number 5 is at index 1.

Example 2:

Input: n = 100
Output: 682289015

Constraints:

1 <= n <= 100
```

## Observations

1. **Problem Understanding**: We need to arrange numbers 1 to n such that prime numbers occupy prime indices (1-indexed).

2. **Key Insight**: The problem can be broken down into two independent subproblems:
   - Arrange all prime numbers among themselves in prime positions
   - Arrange all non-prime numbers among themselves in non-prime positions

3. **Independence**: Since prime numbers can only go in prime positions and non-prime numbers can only go in non-prime positions, these arrangements are independent of each other.

4. **Mathematical Approach**: 
   - Count how many prime numbers exist from 1 to n
   - Count how many prime positions exist from 1 to n (which is the same count)
   - The answer is: `factorial(prime_count) × factorial(non_prime_count)`

5. **Edge Cases**: 
   - When n < 2, there are no prime numbers
   - Need to handle modulo operations carefully to avoid overflow

## Solution

The solution uses a two-step approach:

### Step 1: Count Prime Numbers (Sieve of Eratosthenes)
```python
def count_primes_up_to_n(n):
    if n < 2:
        return 0
    is_prime = [True] * (n + 1)
    is_prime[0] = is_prime[1] = False
    for p in range(2, int(n**0.5) + 1):
        if is_prime[p]:
            for multiple in range(p * p, n + 1, p):
                is_prime[multiple] = False
    count = 0
    for i in range(2, n + 1):
        if is_prime[i]:
            count += 1
    return count
```

- Uses Sieve of Eratosthenes algorithm for efficient prime detection
- Time complexity: O(n log log n)
- Space complexity: O(n)
- Marks multiples of each prime starting from p² (optimization)

### Step 2: Calculate Arrangements
```python
primes = count_primes_up_to_n(n)
primes_permu = math.factorial(primes) % int(1e9 + 7)
normal = n - primes
normal_permu = math.factorial(normal) % int(1e9 + 7)
return (primes_permu * normal_permu) % int(1e9 + 7)
```

- Calculate factorial of prime count (ways to arrange primes in prime positions)
- Calculate factorial of non-prime count (ways to arrange non-primes in non-prime positions)
- Multiply both results (multiplication principle)
- Apply modulo at each step to prevent overflow

### Why This Works:
- Prime positions (1-indexed): 2, 3, 5, 7, 11, ...
- Prime numbers from 1 to n: 2, 3, 5, 7, 11, ... (up to n)
- The count of prime positions equals the count of prime numbers ≤ n
- Each group can be arranged independently within their designated positions

### Example (n = 5):
- Numbers: [1, 2, 3, 4, 5]
- Positions: [1, 2, 3, 4, 5]
- Prime positions: [2, 3, 5] (3 positions)
- Prime numbers: [2, 3, 5] (3 numbers)
- Non-prime positions: [1, 4] (2 positions)  
- Non-prime numbers: [1, 4] (2 numbers)
- Answer: 3! × 2! = 6 × 2 = 12

**Time Complexity**: O(n log log n) for sieve + O(1) for factorial calculation
**Space Complexity**: O(n) for the sieve array

# Tags

- Math
- Number Theory
- Prime Numbers
- Permutation
- Sieve of Eratosthenes
- Combinatorics

