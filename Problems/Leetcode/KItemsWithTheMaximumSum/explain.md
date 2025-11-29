## Problem

https://leetcode.com/problems/k-items-with-the-maximum-sum/description/

```
There is a bag that consists of items, each item has a number 1, 0, or -1 written on it.

You are given four non-negative integers numOnes, numZeros, numNegOnes, and k.

The bag initially contains:
- numOnes items with 1s written on them.
- numZeroes items with 0s written on them.
- numNegOnes items with -1s written on them.

We want to pick exactly k items among the available items. Return the maximum possible sum of numbers written on the items.

Example 1:
Input: numOnes = 3, numZeros = 2, numNegOnes = 0, k = 2
Output: 2
Explanation: We have a bag of items with numbers written on them {1, 1, 1, 0, 0}. We take 2 items with 1 written on them and get a sum in a total of 2.

Example 2:
Input: numOnes = 3, numZeros = 2, numNegOnes = 0, k = 4
Output: 3
Explanation: We have a bag of items with numbers written on them {1, 1, 1, 0, 0}. We take 3 items with 1 written on them, and 1 item with 0 written on it, and get a sum in a total of 3.

Constraints:
- 0 <= numOnes, numZeros, numNegOnes <= 50
- 0 <= k <= numOnes + numZeros + numNegOnes
```

## Observations

1. **Greedy Strategy**: To maximize the sum, we should pick items in order of their value:
   - First, pick all items with value `1` (they contribute positively)
   - Second, pick items with value `0` (they don't affect the sum)
   - Finally, only if necessary, pick items with value `-1` (they decrease the sum)

2. **Three Scenarios**:
   - If `k <= numOnes`: We can pick only 1s, so the sum is simply `k`
   - If `numOnes < k <= numOnes + numZeros`: We pick all 1s and fill the rest with 0s, so the sum is `numOnes`
   - If `k > numOnes + numZeros`: We pick all 1s, all 0s, and some -1s, so the sum is `numOnes - (number of -1s picked)`

3. **Sequential Consumption**: We can process the items in three phases, consuming from each group as needed.

## Solution

1. **Phase 1 - Pick 1s**: 
   - If `k <= a`, we can pick `k` items with value 1, giving us a sum of `k`
   - Otherwise, we pick all `a` items with value 1 and reduce `k` by `a`

2. **Phase 2 - Pick 0s**:
   - If the remaining `k <= b`, we pick `k` items with value 0, which doesn't change our sum of `a`
   - Otherwise, we pick all `b` items with value 0 and reduce `k` by `b`

3. **Phase 3 - Pick -1s**:
   - We must pick the remaining `k` items from the -1s
   - We pick `min(k, c)` items (in case `k > c`, though constraints guarantee this won't happen)
   - Each -1 decreases our sum, so final sum = `a - min(k, c)`

**Time Complexity**: O(1) - constant time operations  
**Space Complexity**: O(1) - no extra space used

# Tags
`greedy` `math` `easy`

