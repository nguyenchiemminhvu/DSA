## Problem

https://leetcode.com/problems/next-greater-numerically-balanced-number/description/

```
An integer x is numerically balanced if for every digit d in the number x, 
there are exactly d occurrences of that digit in x.

Given an integer n, return the smallest numerically balanced number strictly greater than n.

Example 1:
Input: n = 1
Output: 22
Explanation: 22 is numerically balanced since the digit 2 occurs 2 times.

Example 2:
Input: n = 1000
Output: 1333
Explanation: 1333 is numerically balanced since:
- The digit 1 occurs 1 time.
- The digit 3 occurs 3 times.
Note that 1022 cannot be the answer because 0 appeared more than 0 times.

Example 3:
Input: n = 3000
Output: 3133

Constraints: 0 <= n <= 10^6
```

## Observations

1. **Digit 0 cannot appear**: If digit 0 appears in a numerically balanced number, it must appear exactly 0 times, which is a contradiction. Therefore, 0 never appears in valid numbers.

2. **Maximum digit is 7**: Given the constraint n ≤ 10^6 (7 digits max), and each digit d must appear d times, the maximum digit is 7 (appearing 7 times in 7777777).

3. **Limited valid patterns**: The base patterns (multisets of digits) are limited:
   - 1-digit: {1}
   - 2-digit: {2,2}
   - 3-digit: {1,2,2}
   - 4-digit: {3,3,3}
   - 5-digit: {1,3,3,3}
   - 6-digit: {4,4,4,4}, {2,2,3,3,3}, {1,2,2,3,3,3}
   - 7-digit: {5,5,5,5,5}, {1,5,5,5,5,5}, {2,2,4,4,4,4}, {1,2,2,4,4,4,4}, {6,6,6,6,6,6}
   - 8-digit: {1,6,6,6,6,6,6}, {7,7,7,7,7,7,7}

4. **Finite search space**: Since there are only ~16 base patterns within the constraint, and each generates at most a few thousand permutations, we can precompute all valid numerically balanced numbers up to 10^6.

5. **Monotonic property**: We need the next greater number, which is perfect for binary search on a sorted list.

## Solution

### Approach 1: Precomputation + Permutation + Binary Search

**Algorithm:**
1. **Define base patterns**: List all minimal digit multisets that are numerically balanced (e.g., "122" means one 1 and two 2s)
2. **Generate all permutations**: For each base pattern, generate all permutations to get all possible arrangements
3. **Convert to integers**: Convert string permutations to integer values
4. **Sort and deduplicate**: Create a sorted list of unique numerically balanced numbers
5. **Binary search**: Use upper_bound to find the smallest number > n

**Time Complexity:** O(log k) where k is the number of valid numerically balanced numbers (~2000)
**Space Complexity:** O(k) for storing all valid numbers

**Code:**
```python
from itertools import permutations
from typing import List

class Solution:
    def nextBeautifulNumber(self, n: int) -> int:
        def upper_bound(arr: List[int], target: int) -> int:
            n = len(arr)
            left, right, found = 0, n - 1, n
            while left <= right:
                mid = left + (right - left) // 2
                if arr[mid] > target:
                    found = mid
                    right = mid - 1
                else:
                    left = mid + 1
            return found

        # Base patterns: minimal representations of balanced numbers
        base = ['1', '22', '122', '333', '1333', '4444', '22333', 
                '14444', '55555', '155555', '224444', '122333', 
                '666666', '1224444', '1666666', '7777777']
        
        arr = []
        for s in base:
            arr.extend(list(permutations(s)))
        
        # Convert tuples to integers
        for i in range(len(arr)):
            sub = arr[i]
            val = 0
            for c in sub:
                val = val * 10 + int(c)
            arr[i] = val
        
        arr = sorted(set(arr))  # Remove duplicates and sort
        upper = upper_bound(arr, n)
        return arr[upper]
```

### Approach 2: Brute Force with Validation

**Algorithm:**
1. Start from n+1 and check each number
2. For each number, count digit frequencies
3. Verify if each digit d appears exactly d times
4. Return the first valid number found

**Time Complexity:** O(m × d) where m is the distance to next balanced number (worst ~130) and d is digit count (~7)
**Space Complexity:** O(1)

**Code:**
```python
class Solution:
    def nextBeautifulNumber(self, n: int) -> int:
        def is_balanced(num: int) -> bool:
            s = str(num)
            freq = [0] * 10
            for c in s:
                freq[int(c)] += 1
            
            for digit in range(10):
                if freq[digit] != 0 and freq[digit] != digit:
                    return False
            return True
        
        num = n + 1
        while num <= 10**7:  # Safety bound
            if is_balanced(num):
                return num
            num += 1
        return -1
```

### Approach 3: BFS/DFS Generation

**Algorithm:**
1. Use backtracking to generate numerically balanced numbers
2. Build numbers digit by digit, tracking digit usage
3. Prune invalid branches early
4. Return first valid number > n

**Time Complexity:** O(k) where k is numbers generated before finding answer
**Space Complexity:** O(d) for recursion depth

**Code:**
```python
class Solution:
    def nextBeautifulNumber(self, n: int) -> int:
        results = []
        
        def backtrack(num: int, remaining: List[int]):
            if all(r == 0 for r in remaining):
                results.append(num)
                return
            
            for digit in range(1, 8):
                if remaining[digit] > 0:
                    remaining[digit] -= 1
                    backtrack(num * 10 + digit, remaining)
                    remaining[digit] += 1
        
        # Generate all patterns up to 7 digits
        patterns = [
            [0,1,0,0,0,0,0,0],  # 1
            [0,0,2,0,0,0,0,0],  # 22
            [0,1,2,0,0,0,0,0],  # 122
            [0,0,0,3,0,0,0,0],  # 333
            # ... add more patterns
        ]
        
        for pattern in patterns:
            backtrack(0, pattern)
        
        results.sort()
        for num in results:
            if num > n:
                return num
```

## Comparison of Approaches

| Approach | Time | Space | Best For |
|----------|------|-------|----------|
| Precomputation | O(log k) | O(k) | Multiple queries |
| Brute Force | O(m × d) | O(1) | Single query, simple |
| BFS/DFS | O(k) | O(d) | Dynamic generation |

**Recommended:** Approach 1 (given solution) is optimal for the constraint range since the search space is small and precomputation is feasible.

# Tags
#math #enumeration #binary-search #permutation #brute-force #precomputation

