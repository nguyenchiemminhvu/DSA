## Problem

https://leetcode.com/problems/minimum-total-cost-to-process-all-elements/description/

Given an integer array `nums` and an integer `k`:

- Start with `k` units of resources.
- Process elements left to right. Processing element `i` requires `nums[i]` resources.
- If current resources < `nums[i]`, perform one or more operations. Each operation adds `k` resources. The 1st operation costs 1, the 2nd costs 2, and so on (globally cumulative across all elements).
- After processing element `i`, resources decrease by `nums[i]`.

Return the **minimum total cost** modulo $10^9 + 7$.

**Constraints:**
- $1 \le \text{nums.length} \le 10^5$
- $1 \le \text{nums}[i] \le 10^9$
- $1 \le k \le 10^9$

---

## Ideas

### Simulation — O(n)

Track two variables through a single pass:
- `cur`: current available resources (starts at `k`)
- `t`: total number of operations performed so far

For each `nums[i]`:

1. If `cur < nums[i]`, we need more resources. The shortfall is `nums[i] - cur`, so the minimum number of new operations is:

$$ops = \left\lceil \frac{\text{nums}[i] - \text{cur}}{k} \right\rceil$$

2. These `ops` new operations are numbered `t+1, t+2, ..., t+ops`, so their total cost is:

$$\text{cost} = \sum_{j=1}^{ops}(t + j) = ops \cdot t + \frac{ops \cdot (ops+1)}{2}$$

3. Update state:
   - `cur += ops * k`
   - `t += ops`

4. After the check, consume: `cur -= nums[i]`

All arithmetic is done modulo $10^9 + 7$ for the cost accumulation, but `cur` and `t` are tracked as plain integers (they don't overflow 64-bit since values are bounded by $10^9$ and array length $10^5$).

**Complexity:** $O(n)$ time, $O(1)$ space.
