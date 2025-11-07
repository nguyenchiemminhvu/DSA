## Problem

https://leetcode.com/problems/number-of-equivalent-domino-pairs/description/

```
Given a list of dominoes, dominoes[i] = [a, b] is equivalent to dominoes[j] = [c, d] if and only if either (a == c and b == d), or (a == d and b == c) - that is, one domino can be rotated to be equal to another domino.

Return the number of pairs (i, j) for which 0 <= i < j < dominoes.length, and dominoes[i] is equivalent to dominoes[j].

Example 1:

Input: dominoes = [[1,2],[2,1],[3,4],[5,6]]
Output: 1

Example 2:

Input: dominoes = [[1,2],[1,2],[1,1],[1,2],[2,2]]
Output: 3

Constraints:

1 <= dominoes.length <= 4 * 104
dominoes[i].length == 2
1 <= dominoes[i][j] <= 9
```

## Observations

1. **Equivalent Dominoes**: Two dominoes are equivalent if they are the same when one can be rotated. For example, `[1,2]` is equivalent to `[2,1]`.

2. **Normalization Strategy**: To handle rotations, we can normalize each domino by ensuring the smaller value comes first. This way, `[1,2]` and `[2,1]` both become `[1,2]`.

3. **Counting Problem**: We need to count pairs (i,j) where i < j and dominoes are equivalent. This is a classic combinatorics problem - if we have `n` identical items, the number of ways to choose 2 is `n * (n-1) / 2`.

4. **Hash Map Approach**: Use a frequency map to count occurrences of each normalized domino, then calculate pairs for each group.

5. **Time Complexity**: O(n) where n is the number of dominoes - we iterate through once to count, once to calculate pairs.

6. **Space Complexity**: O(n) in worst case when all dominoes are unique.

## Solution

**Algorithm Steps:**

1. **Normalize Each Domino**: For each domino `[a, b]`, create a normalized form `(min(a,b), max(a,b))` to handle rotations.

2. **Count Frequencies**: Use a hash map (defaultdict) to count how many times each normalized domino appears.

3. **Calculate Pairs**: For each group of identical dominoes with count `v`, the number of pairs is `v * (v-1) / 2` (combination formula C(v,2)).

**Key Insights:**
- Normalization eliminates the rotation concern by always putting smaller value first
- The combination formula `C(n,2) = n * (n-1) / 2` gives us pairs from n identical items
- Using defaultdict simplifies counting logic

**Example Walkthrough:**
```
dominoes = [[1,2],[2,1],[3,4],[5,6]]

After normalization:
- [1,2] → (1,2)
- [2,1] → (1,2) 
- [3,4] → (3,4)
- [5,6] → (5,6)

Frequency map: {(1,2): 2, (3,4): 1, (5,6): 1}

Pairs calculation:
- (1,2): 2 * (2-1) / 2 = 1 pair
- (3,4): 1 * (1-1) / 2 = 0 pairs  
- (5,6): 1 * (1-1) / 2 = 0 pairs

Total: 1 pair
```

# Tags

Hash Table, Combinatorics, Array Processing

