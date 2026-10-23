## Problem

https://leetcode.com/problems/maximum-k-to-sort-a-permutation/description

You are given an integer array `nums` of length `n`, where `nums` is a **permutation** of the numbers in the range `[0..n - 1]`.

You may swap elements at indices `i` and `j` **only if** `nums[i] AND nums[j] == k`, where `k` is a **non-negative** integer.

Return the **maximum** value of `k` such that the array can be sorted in **non-decreasing** order using any number of such swaps. If `nums` is already sorted, return 0.

**Example 1:**

- Input: `nums = [0,3,2,1]`
- Output: `1`
- Explanation: With `k = 1`, swapping `nums[1] = 3` and `nums[3] = 1` gives `[0, 1, 2, 3]`.

**Example 2:**

- Input: `nums = [0,1,3,2]`
- Output: `2`
- Explanation: With `k = 2`, swapping `nums[2] = 3` and `nums[3] = 2` gives `[0, 1, 2, 3]`.

**Example 3:**

- Input: `nums = [3,2,1,0]`
- Output: `0`
- Explanation: Only `k = 0` allows sorting.

**Constraints:**

- $1 \le n = \text{nums.length} \le 10^5$
- $0 \le \text{nums}[i] \le n - 1$
- `nums` is a permutation of integers from `0` to `n - 1`.

## Ideas

- Fixed points (`nums[i] == i`) never need to move, so only misplaced values matter.
- A misplaced value $v$ at index $i$ must be swapped at least once, and each swap requires $v \,\&\, \text{partner} = k$. So $k \subseteq v$ (submask), meaning $k$ is a submask of every misplaced value.
- Hence $k \subseteq \bigwedge_{\text{nums}[i] \ne i} \text{nums}[i]$, and that AND is an upper bound on the answer.
- Answer = that AND (0 if there are no misplaced values). Checked against the examples: misplaced `{3, 1}` gives 1, `{3, 2}` gives 2, `{3, 2, 1, 0}` gives 0.
- Open point: that the AND is actually achievable (sufficiency) is not proven here; it is only verified on the examples.
- Complexity: $O(n)$ time, $O(1)$ space.
