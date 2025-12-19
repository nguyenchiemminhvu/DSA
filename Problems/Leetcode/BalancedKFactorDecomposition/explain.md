## Problem

https://leetcode.com/problems/balanced-k-factor-decomposition/description/

Given two integers `n` and `k`, split the number `n` into exactly `k` positive integers such that the product of these integers is equal to `n`.

Return any one split in which the maximum difference between any two numbers is minimized. You may return the result in any order.

**Example 1:**
- Input: `n = 100, k = 2`
- Output: `[10,10]`
- Explanation: The split [10, 10] yields 10 * 10 = 100 and a max-min difference of 0, which is minimal.

**Example 2:**
- Input: `n = 44, k = 3`
- Output: `[2,2,11]`
- Explanation: 
  - Split [1, 1, 44] yields a difference of 43
  - Split [1, 2, 22] yields a difference of 21
  - Split [1, 4, 11] yields a difference of 10
  - Split [2, 2, 11] yields a difference of 9 (optimal)

**Constraints:**
- `4 <= n <= 10^5`
- `2 <= k <= 5`
- `k` is strictly less than the total number of positive divisors of `n`

## Observations

1. **Prime Factorization Insight**: We need to split `n` into `k` factors whose product equals `n`. This is essentially distributing the prime factors of `n` among `k` buckets.

2. **Minimize Max-Min Difference**: To minimize the difference, we want the factors to be as close to each other as possible. Ideally, all factors would be equal to `n^(1/k)`.

3. **Only Divisors Matter**: We can only use divisors of `n` in our split, since the product must equal `n`.

4. **Small k Constraint**: Since `k <= 5`, a brute force/backtracking approach is feasible. We can try all combinations of `k` divisors.

5. **Monotonicity**: Using non-decreasing sequences helps avoid duplicate combinations and makes pruning easier.

6. **Early Termination**: If at any point the product exceeds `n` or we can't reach `n` with remaining slots, we can prune that branch.

## Solution

### Approach 1: Brute Force DFS

**Algorithm:**
1. Generate all divisors of `n` using trial division up to `√n`
2. Use DFS/backtracking to try all combinations of `k` divisors
3. For each complete combination, check if product equals `n`
4. Track the split with minimum max-min difference

**Time Complexity:** O(d^k) where d is the number of divisors
**Space Complexity:** O(k) for recursion stack

```python
class Solution:
    def minDifference(self, n: int, k: int) -> List[int]:
        def all_div(val: int) -> List[int]:
            divs = []
            s = int(math.sqrt(val) + 1)
            for i in range(1, s):
                if val % i == 0:
                    divs.append(i)
                    if i * i != val:
                        divs.append(val // i)
            divs.sort()
            return divs
        
        divs = all_div(n)
        best_diff = float('inf')
        best_split = []
        tmp = []
        
        def dfs(i: int, start: int, prod: int) -> None:
            nonlocal best_diff, best_split, tmp
            # Base case: filled k slots
            if i >= k:
                if prod == n:
                    diff = max(tmp) - min(tmp)
                    if diff < best_diff:
                        best_diff = diff
                        best_split = tmp[:]
                return
            
            # Try each divisor starting from 'start' (for non-decreasing order)
            for j in range(start, len(divs)):
                if prod * divs[j] > n:  # Pruning: product too large
                    continue
                tmp.append(divs[j])
                dfs(i + 1, j, prod * divs[j])
                tmp.pop()
        
        dfs(0, 0, 1)
        return best_split
```

### Approach 2: Optimized DFS with Better Pruning

**Key Improvements:**
1. **Track Remainder Instead of Product**: Instead of tracking `prod` and checking if it equals `n`, we divide `n` by each chosen divisor and track the `remain` value. This makes pruning more natural.
2. **Only Try Valid Divisors**: At each step, only try divisors that divide the current remainder.
3. **Early Termination**: Stop immediately when remainder becomes 1 (unless we need exactly one more slot).
4. **Last Slot Validation**: When filling the last slot, ensure remainder equals 1 after division.

**Algorithm:**
1. Generate all divisors of `n`
2. Use DFS where at each step:
   - If we've filled `k` slots and remainder is 1, we found a valid split
   - Try each divisor that divides the current remainder
   - Recursively solve with `remain // divisor`
3. Track the best split with minimum difference

**Time Complexity:** O(d^k) but with much better pruning in practice
**Space Complexity:** O(k) for recursion stack

```python
class Solution:
    def minDifference(self, n: int, k: int) -> List[int]:
        def all_div(val: int) -> List[int]:
            divs = []
            s = int(math.sqrt(val) + 1)
            for i in range(1, s):
                if val % i == 0:
                    divs.append(i)
                    if i * i != val:
                        divs.append(val // i)
            divs.sort()
            return divs
        
        divs = all_div(n)
        best_diff = [float('inf')]
        best_split = []
        
        def dfs(start: int, remain: int, path: List[int]) -> None:
            nonlocal best_split
            
            # Base case: filled k slots
            if len(path) == k:
                if remain == 1:  # Valid split found
                    diff = max(path) - min(path)
                    if diff < best_diff[0]:
                        best_diff[0] = diff
                        best_split = path[:]
                return
            
            # Pruning: if remain is 1 but we need more numbers, impossible
            if remain == 1:
                return
            
            # Try each divisor
            for i in range(start, len(divs)):
                d = divs[i]
                if remain % d != 0:  # Must divide remainder
                    continue
                
                slots_left = k - len(path) - 1
                if slots_left == 0:
                    # Last slot: must use exactly remainder/d == 1
                    if remain // d == 1:
                        dfs(i, remain // d, path + [d])
                else:
                    dfs(i, remain // d, path + [d])
        
        dfs(0, n, [])
        return best_split
```

**Why This is Better:**
- Avoids trying divisors that can't possibly lead to valid splits
- Natural pruning by checking divisibility
- More intuitive: we're "dividing down" n rather than "multiplying up"
- Better constant factors in practice due to early termination

# Tags
`Backtracking` `DFS` `Number Theory` `Divisors` `Prime Factorization` `Math`

