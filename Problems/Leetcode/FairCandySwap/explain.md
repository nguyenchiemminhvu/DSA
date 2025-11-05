## Problem

https://leetcode.com/problems/fair-candy-swap/

```
Alice and Bob have a different total number of candies. You are given two integer arrays aliceSizes and bobSizes where aliceSizes[i] is the number of candies of the ith box of candy that Alice has and bobSizes[j] is the number of candies of the jth box of candy that Bob has.

Since they are friends, they would like to exchange one candy box each so that after the exchange, they both have the same total amount of candy. The total amount of candy a person has is the sum of the number of candies in each box they have.

Return an integer array answer where answer[0] is the number of candies in the box that Alice must exchange, and answer[1] is the number of candies in the box that Bob must exchange. If there are multiple answers, you may return any one of them. It is guaranteed that at least one answer exists.

Example 1:

Input: aliceSizes = [1,1], bobSizes = [2,2]
Output: [1,2]

Example 2:

Input: aliceSizes = [1,2], bobSizes = [2,3]
Output: [1,2]
Example 3:

Input: aliceSizes = [2], bobSizes = [1,3]
Output: [2,3]

Constraints:

1 <= aliceSizes.length, bobSizes.length <= 104
1 <= aliceSizes[i], bobSizes[j] <= 105
Alice and Bob have a different total number of candies.
There will be at least one valid answer for the given input.
```

## Observations

1. **Goal**: After exchanging one candy box each, both Alice and Bob should have equal total candies.

2. **Mathematical relationship**: 
   - Let Alice give candy box of size `x` and receive candy box of size `y` from Bob
   - Alice's new total: `sa - x + y`
   - Bob's new total: `sb - y + x`
   - For equality: `sa - x + y = sb - y + x`
   - Solving: `sa - sb = 2x - 2y` → `y = x + (sb - sa) / 2`

3. **Key insight**: The difference `(sb - sa) / 2` is constant, so for each candy box `x` that Alice can give, we need to find if Bob has a candy box of size `x + (sb - sa) / 2`.

4. **Optimization**: Convert Bob's array to a set for O(1) lookup time instead of O(n) search.

5. **Edge cases**: The problem guarantees at least one valid answer exists, so we don't need to handle the case where no solution is found.

## Solution

The solution uses a mathematical approach to find the fair candy swap:

1. **Calculate totals**: First, compute the sum of Alice's candies (`sa`) and Bob's candies (`sb`).

2. **Find target difference**: Calculate `target = (sb - sa) // 2`. This represents how much more Bob needs to give Alice compared to what Alice gives Bob.

3. **Set up for fast lookup**: Convert Bob's candy array to a set for O(1) lookup operations.

4. **Find the swap**: For each candy box `x` that Alice can give:
   - Calculate the required candy box size Bob must give: `y = target + x`
   - Check if Bob has a candy box of size `y`
   - If yes, return `[x, y]`

**Time Complexity**: O(n + m) where n and m are the lengths of Alice's and Bob's arrays respectively.
**Space Complexity**: O(m) for storing Bob's candies in a set.

**Example walkthrough**:
- Input: `a = [1,2]`, `b = [2,3]`
- `sa = 3`, `sb = 5`, `target = (5-3)//2 = 1`
- For `x = 1`: need `y = 1 + 1 = 2`, check if 2 is in Bob's set → Yes!
- Return `[1, 2]`

# Tags

- Array
- Hash Table
- Math
- Two Pointers

