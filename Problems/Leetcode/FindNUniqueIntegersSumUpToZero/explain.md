## Problem

https://leetcode.com/problems/find-n-unique-integers-sum-up-to-zero/description/

```
Given an integer n, return any array containing n unique integers such that they add up to 0.

Example 1:

Input: n = 5
Output: [-7,-1,1,3,4]
Explanation: These arrays also are accepted [-5,-1,1,2,3] , [-3,-1,2,-2,4].

Example 2:

Input: n = 3
Output: [-1,0,1]

Example 3:

Input: n = 1
Output: [0]

Constraints:

1 <= n <= 1000
```

## Observations

1. **Problem Goal**: We need to find `n` unique integers that sum to 0.

2. **Key Insight**: We can use pairs of positive and negative numbers to cancel each other out:
   - For even `n`: Create `n/2` pairs like `(1, -1), (2, -2), ...`
   - For odd `n`: Create `(n-1)/2` pairs and add a `0`

3. **Alternative Approach**: The given solution uses a different strategy:
   - Generate negative numbers: `-1, -2, -3, ..., -(n-1)`
   - Calculate what positive number is needed to balance the sum

4. **Sum Formula**: The sum of first `k` natural numbers is `k(k+1)/2`
   - Sum of `1, 2, 3, ..., (n-1)` = `(n-1)×n/2`
   - So we need `+(n-1)×n/2` to balance the negative sum `-(n-1)×n/2`

## Solution

The solution works as follows:

1. **Base Case**: If `n = 1`, return `[0]` since it's the only way to get one unique integer that sums to 0.

2. **General Case**: 
   - Create negative numbers: `[-1, -2, -3, ..., -(n-1)]`
   - Their sum is: `-(1 + 2 + 3 + ... + (n-1)) = -((n-1)×n/2)`
   - To make total sum = 0, add the positive counterpart: `+((n-1)×n/2)`

3. **Example with n = 5**:
   - Negative numbers: `[-1, -2, -3, -4]`
   - Their sum: `-(1+2+3+4) = -10`
   - Positive number needed: `+10`
   - Final array: `[-1, -2, -3, -4, 10]`
   - Verification: `-1 + (-2) + (-3) + (-4) + 10 = 0` ✓

4. **Time Complexity**: O(n) - we generate n-1 negative numbers
5. **Space Complexity**: O(n) - for the output array

**Alternative simpler approach** (not used here but worth noting):
```python
def sumZero(self, n: int) -> List[int]:
    result = []
    for i in range(1, n//2 + 1):
        result.extend([i, -i])
    if n % 2 == 1:
        result.append(0)
    return result
```

# Tags

- **Array**
- **Math**
- **Greedy**

