## Problem

https://leetcode.com/problems/maximize-sum-of-squares-of-digits/description/

You are given two **positive** integers `num` and `sum`.

A positive integer `n` is **good** if:

- The number of digits in `n` is **exactly** `num`.
- The sum of digits in `n` is **exactly** `sum`.

The **score** of a **good** integer `n` is the sum of the squares of its digits.

Return a **string** denoting the **good** integer `n` that achieves the **maximum** score. If there are multiple such integers, return the **maximum** one. If no such integer exists, return an empty string.

**Example 1:**

- **Input:** `num = 2`, `sum = 3`
- **Output:** `"30"`
- **Explanation:** Good integers are 12, 21, 30 with scores 5, 5, 9. Max score is 9 (30).

**Example 2:**

- **Input:** `num = 2`, `sum = 17`
- **Output:** `"98"`
- **Explanation:** Good integers are 89, 98 with score 145 each. Max is 98.

**Example 3:**

- **Input:** `num = 1`, `sum = 10`
- **Output:** `""`
- **Explanation:** No 1-digit integer has digit sum 10.

**Constraints:**

- $1 \le num \le 2 \cdot 10^5$
- $1 \le sum \le 2 \cdot 10^6$

## Ideas

**Key observation:** the score depends only on the multiset of digits, and the number itself is largest when its digits are sorted in descending order.

**Maximizing the score:** the function $f(x) = x^2$ is strictly convex, so over digits $x_i \in [0, 9]$ with $\sum x_i = sum$, the maximum is reached at a vertex of that polytope. Every vertex has all digits in $\{0, 9\}$ except at most one. So the optimal multiset is unique:

$$sum = 9k + r, \quad 0 \le r \le 8$$

Digits: $k$ nines, one digit $r$ (if $r > 0$), and the remaining digits are $0$.

**Algorithm (greedy):**

1. If $sum > 9 \cdot num$, no answer exists, return `""`.
2. Take as many `9`s as possible, then the remainder digit, then pad with `0`s to length `num`.
3. The result is already in descending order, so it is the maximum integer among those with the same score.

Since the digit multiset is unique, no other arrangement needs checking.

**Complexity:** $O(num)$ time and $O(num)$ space for the output string.

**Check against the given code:** the loop takes `min(9, sum)` each iteration, which gives `9`s first, then the remainder, then `0`s. `times > num` returns `""` when the digits don't fit. Note that `sum` shadows the built-in name.
