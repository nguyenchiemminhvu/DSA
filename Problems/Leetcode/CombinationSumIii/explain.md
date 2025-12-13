## Problem

https://leetcode.com/problems/combination-sum-iii/description/

```
Find all valid combinations of k numbers that sum up to n such that the following conditions are true:
- Only numbers 1 through 9 are used.
- Each number is used at most once.

Return a list of all possible valid combinations. The list must not contain the same combination twice, 
and the combinations may be returned in any order.

Example 1:
Input: k = 3, n = 7
Output: [[1,2,4]]
Explanation:
1 + 2 + 4 = 7
There are no other valid combinations.

Example 2:
Input: k = 3, n = 9
Output: [[1,2,6],[1,3,5],[2,3,4]]
Explanation:
1 + 2 + 6 = 9
1 + 3 + 5 = 9
2 + 3 + 4 = 9
There are no other valid combinations.

Example 3:
Input: k = 4, n = 1
Output: []
Explanation: There are no valid combinations.
Using 4 different numbers in the range [1,9], the smallest sum we can get is 1+2+3+4 = 10 
and since 10 > 1, there are no valid combination.

Constraints:
- 2 <= k <= 9
- 1 <= n <= 60
```

## Observations

1. **Fixed candidate set**: We can only use numbers from 1 to 9, which is a small fixed set of 9 numbers.

2. **Subset generation problem**: We need to find all subsets of [1,2,3,4,5,6,7,8,9] that:
   - Have exactly k elements
   - Sum to target n
   - Each number is used at most once (no duplicates)

3. **Small input space**: Since we only have 9 numbers, there are at most 2^9 = 512 possible subsets. This makes brute force enumeration feasible.

4. **Early termination opportunities**:
   - Minimum possible sum with k numbers: 1+2+3+...+k = k(k+1)/2
   - Maximum possible sum with k numbers: (10-k)+(11-k)+...+9 = 9k - k(k-1)/2
   - If target is outside this range, return empty list immediately

5. **No duplicate combinations needed**: Since all numbers 1-9 are distinct, we naturally avoid duplicates in our combinations.

## Solution

### Approach: Bit Manipulation (Subset Enumeration)

The solution uses bit manipulation to generate all possible subsets of numbers [1,2,3,4,5,6,7,8,9].

**Key Idea**: 
- Each subset can be represented as a binary number (bitmask) where bit i indicates whether number (i+1) is included
- For 9 numbers, we need to check all masks from 0 to 2^9 - 1 (0 to 511)
- For each mask, we extract the subset and check if it meets our criteria

**Algorithm**:

1. **Initialize**: 
   - Create array `arr = [1, 2, 3, 4, 5, 6, 7, 8, 9]`
   - Result list `res = []`
   - Total subsets to check: `nn = 2^9 = 512`

2. **Enumerate all subsets**:
   - For each mask from 1 to 511 (skip 0 as it's empty set):
     - Build subset by checking each bit position
     - If bit i is set in mask, include `arr[i]` in subset

3. **Filter valid combinations**:
   - Check if subset has exactly k elements: `len(tmp) == k`
   - Check if subset sums to target: `sum(tmp) == target`
   - If both conditions met, add to result

**Bit manipulation details**:
- `(1 << i)` creates a number with only bit i set
- `(1 << i) & mask` checks if bit i is set in mask
- `(1 << n)` computes 2^n efficiently

**Time Complexity**: O(2^9 * 9) = O(512 * 9) = O(4608) = O(1)
- We iterate through 512 possible subsets
- For each subset, we check up to 9 bits and compute sum
- Since 9 is constant, this is effectively O(1)

**Space Complexity**: O(k)
- Temporary array `tmp` stores at most k elements
- Result list not counted as output space
- Array `arr` is O(9) = O(1)

```python
class Solution:
    def combinationSum3(self, k: int, target: int) -> List[List[int]]:
        res = []
        arr = [val for val in range(1, 10)]  # [1, 2, 3, 4, 5, 6, 7, 8, 9]
        n = len(arr)  # 9
        nn = (1 << n)  # 2^9 = 512
        
        # Try all possible subsets (bitmasks from 1 to 511)
        for mask in range(1, nn):
            tmp = []
            # Build subset based on current mask
            for i in range(n):
                if (1 << i) & mask:  # Check if bit i is set
                    tmp.append(arr[i])
            
            # Check if this subset meets our criteria
            if len(tmp) == k and sum(tmp) == target:
                res.append(tmp[:])  # Add copy to result
        
        return res
```

**Example walkthrough** (k=3, n=9):

- mask = 42 (binary: 000101010):
  - Bits set: 1, 3, 5 → subset: [2, 4, 6]
  - len=3 ✓, sum=12 ✗ → not added

- mask = 44 (binary: 000101100):
  - Bits set: 2, 3, 5 → subset: [3, 4, 6]
  - len=3 ✓, sum=13 ✗ → not added

- mask = 35 (binary: 000100011):
  - Bits set: 0, 1, 5 → subset: [1, 2, 6]
  - len=3 ✓, sum=9 ✓ → added to result!

**Alternative Approaches**:
1. **Backtracking** (more elegant for larger k): O(2^9)
2. **DFS with pruning**: Can terminate early when sum exceeds target

# Tags

`Backtracking` `Bit Manipulation` `Array` `Combinations` `Subset Generation`

