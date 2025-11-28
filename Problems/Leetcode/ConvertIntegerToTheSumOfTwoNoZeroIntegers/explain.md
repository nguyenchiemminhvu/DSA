## Problem

https://leetcode.com/problems/convert-integer-to-the-sum-of-two-no-zero-integers/description/

A **No-Zero integer** is a positive integer that does not contain any 0 in its decimal representation.

Given an integer $n$, return a list of two integers $[a, b]$ where:
- $a$ and $b$ are No-Zero integers.
- $a + b = n$

The test cases guarantee at least one valid solution. If there are multiple valid solutions, any can be returned.

**Constraints:**  
$2 \leq n \leq 10^4$

**Examples:**

- Input: `n = 2`  
  Output: `[1, 1]`  
  Explanation: Both 1 and 1 are no-zero integers, and $1 + 1 = 2$.

- Input: `n = 11`  
  Output: `[2, 9]`  
  Explanation: Both 2 and 9 are no-zero integers, and $2 + 9 = 11$.  
  Note: Other valid answers like `[8, 3]` can also be accepted.

## Observations

1. Every integer $n \geq 2$ can be split into two positive integers $a$ and $b$ such that $a + b = n$.
2. The only restriction is that neither $a$ nor $b$ can contain the digit 0 in their decimal representation.
3. Since $n$ is small ($\leq 10^4$), a brute-force search is feasible and efficient.
4. For any value $l$ from $1$ to $n-1$, we can calculate $r = n - l$ and check if both are No-Zero integers.
5. The problem guarantees at least one valid solution exists for all test cases.

## Solution

The solution uses a **two-pointer approach** with a brute-force search:

1. Start with $l = 1$ and $r = n - 1$ (ensuring $l + r = n$).
2. For each pair $(l, r)$:
   - Check if both $l$ and $r$ are No-Zero integers.
   - If yes, return $[l, r]$.
   - Otherwise, increment $l$ and decrement $r$.
3. Continue until a valid pair is found.

**Helper Function:**  
`found_0(val)` checks if a number contains the digit 0:
- Extract each digit using modulo operation (`val % 10`).
- If any digit is 0, return `True`.
- Otherwise, divide by 10 and continue.
- Return `False` if no 0 is found.

**Time Complexity:** $O(n \cdot d)$
- We iterate through at most $n$ pairs.
- For each pair, we check if they contain 0, which takes $O(d)$ time where $d$ is the number of digits.
- Since $n \leq 10^4$, $d \leq 5$, making this very efficient.

**Space Complexity:** $O(1)$
- Only using a constant amount of extra space for variables.

### Example Walkthrough

**Example 1:** `n = 2`
- $l = 1, r = 1$
- Check: `found_0(1)` = False, `found_0(1)` = False
- Both are No-Zero integers, return `[1, 1]`

**Example 2:** `n = 11`
- $l = 1, r = 10$
- Check: `found_0(1)` = False, `found_0(10)` = True (contains 0)
- $l = 2, r = 9$
- Check: `found_0(2)` = False, `found_0(9)` = False
- Both are No-Zero integers, return `[2, 9]`

**Example 3:** `n = 100`
- $l = 1, r = 99$
- Check: `found_0(1)` = False, `found_0(99)` = False
- Both are No-Zero integers, return `[1, 99]`

# Tags

`Math` `Brute Force` `Two Pointers`

