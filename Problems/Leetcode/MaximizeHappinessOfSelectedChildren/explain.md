## Problem

https://leetcode.com/problems/maximize-happiness-of-selected-children/description/

You are given an array `happiness` of length `n`, and a positive integer `k`.

There are `n` children standing in a queue, where the `ith` child has happiness value `happiness[i]`. You want to select `k` children from these `n` children in `k` turns.

In each turn, when you select a child, the happiness value of all the children that have not been selected till now decreases by 1. Note that the happiness value cannot become negative and gets decremented only if it is positive.

Return the maximum sum of the happiness values of the selected children you can achieve by selecting `k` children.

**Example 1:**
- Input: `happiness = [1,2,3], k = 2`
- Output: `4`
- Explanation: Pick child with happiness 3 (remaining: [0,1]), then pick child with happiness 1 (remaining: [0]). Sum = 3 + 1 = 4.

**Example 2:**
- Input: `happiness = [1,1,1,1], k = 2`
- Output: `1`
- Explanation: Pick any child with happiness 1 (remaining: [0,0,0]), then pick child with happiness 0. Sum = 1 + 0 = 1.

**Example 3:**
- Input: `happiness = [2,3,4,5], k = 1`
- Output: `5`
- Explanation: Pick child with happiness 5. Sum = 5.

**Constraints:**
- `1 <= n == happiness.length <= 2 * 10^5`
- `1 <= happiness[i] <= 10^8`
- `1 <= k <= n`

## Observations

1. **Greedy Approach**: To maximize the sum, we should always pick the child with the highest remaining happiness value in each turn.

2. **Decreasing Happiness**: Each time we select a child, all unselected children's happiness decreases by 1. This means:
   - When we pick the 1st child (index 0), their happiness decreases by 0
   - When we pick the 2nd child (index 1), their happiness decreases by 1
   - When we pick the 3rd child (index 2), their happiness decreases by 2
   - And so on...

3. **Pattern Recognition**: If we sort the happiness values in descending order and pick the top `k` children:
   - The child picked at turn `i` (0-indexed) will have their original happiness reduced by `i`
   - The contribution is `max(0, happiness[i] - i)`

4. **Why Sorting Works**: By sorting in descending order, we ensure that children with higher happiness values are picked earlier, minimizing the effect of the decrement.

## Solution

```python
class Solution:
    def maximumHappinessSum(self, nums: List[int], k: int) -> int:
        res = 0
        nums.sort(reverse=True)  # Sort in descending order
        for i in range(k):
            if nums[i] > i:
                res += nums[i] - i  # Add happiness minus decrement
        return res
```

**Algorithm Explanation:**

1. **Sort Descending**: Sort the happiness array in descending order to prioritize children with higher happiness values.

2. **Iterate k Times**: For each of the `k` selections:
   - At turn `i` (0-indexed), we've already made `i` selections
   - The current child's happiness has decreased by `i` from their original value
   - Add `nums[i] - i` to the result (only if positive)

3. **Return Sum**: Return the total accumulated happiness.

**Time Complexity**: $O(n \log n)$ due to sorting, where $n$ is the length of the happiness array.

**Space Complexity**: $O(1)$ if we don't count the space used by the sorting algorithm (or $O(n)$ if counting the sort space).

**Example Walkthrough** (`happiness = [1,2,3], k = 2`):
1. After sorting: `[3, 2, 1]`
2. Turn 0 (i=0): Pick child with happiness 3, contribution = 3 - 0 = 3
3. Turn 1 (i=1): Pick child with happiness 2, contribution = 2 - 1 = 1
4. Total = 3 + 1 = 4

# Tags

`Greedy` `Sorting` `Array`

