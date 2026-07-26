## Problem

https://leetcode.com/problems/digit-operations-to-make-two-integers-equal/description/

Given two integers `n` and `m` with the same number of digits, transform `n` into `m` by repeatedly incrementing or decrementing any single digit of `n` by 1. At every step (including the start), `n` must **not** be prime. The **cost** is the sum of all values `n` takes throughout the process (including the initial `n` and the final `m`). Return the minimum cost, or `-1` if impossible.

**Constraints:**
- `1 <= n, m < 10^4`
- `n` and `m` have the same number of digits
- A digit cannot go below `0` or above `9`
- The leading digit cannot become `0` (would reduce digit count)

---

## Ideas

### Key Observations

1. **Graph problem**: Each non-prime number is a node. Two nodes are connected if they differ by exactly 1 in exactly one digit position.
2. **Cost model**: Every time we "visit" a value of `n`, we add it to the total cost. So the cost of a path `v0 → v1 → ... → vk` is `v0 + v1 + ... + vk`.
3. **Constraint**: We can never pass through a prime number.
4. **Digit bounds**:
   - Any digit: cannot go below `0` or above `9`.
   - Leading digit: cannot go below `1` (otherwise the number loses a digit).

### Approach — Dijkstra's Algorithm

Model this as a **weighted shortest path** problem:

- **Nodes**: all non-prime integers in the range `[10^(d-1), 10^d - 1]` where `d` is the number of digits in `n` (for `d = 1`, range is `[1, 9]`).
- **Edges**: between numbers that differ by ±1 in exactly one digit (respecting digit bounds).
- **Edge weight**: the value of the destination node (since we pay the destination's value upon arrival).
- **Source**: `n` with initial cost `n`.
- **Answer**: `dist[m]`, where `dist[v]` = minimum cumulative sum to reach `v` from `n`.

**Dijkstra recurrence:**

$$\text{dist}[v] = \min(\text{dist}[v],\ \text{dist}[u] + v) \quad \text{for each neighbor } v \text{ of } u$$

**Early exits:**
- If `n` is prime → return `-1`
- If `m` is prime → return `-1`

### Complexity

- **Nodes**: at most `9000` numbers (for 4-digit: 1000–9999).
- **Edges per node**: at most `2 * d` (increment/decrement each digit), so `O(1)` per node for `d ≤ 4`.
- **Time**: $O(N \log N)$ where $N < 10^4$.
- **Space**: $O(N)$.

### Example Walkthrough (n = 10, m = 12)

Path: `10 → 20 → 21 → 22 → 12`

| Step | Value | Running Cost |
|------|-------|-------------|
| Start | 10 | 10 |
| +1 to tens digit | 20 | 30 |
| +1 to units digit | 21 | 51 |
| +1 to units digit | 22 | 73 |
| -1 to tens digit | 12 | 85 |

All intermediate values are non-prime. Total cost = **85**.
