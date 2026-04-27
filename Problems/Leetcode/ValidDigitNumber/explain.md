## Problem

https://leetcode.com/problems/valid-digit-number/description/

You are given an integer `n` and a digit `x`.

A number is considered **valid** if:
1. It contains at least one occurrence of digit `x`
2. It does not start with digit `x`

Return `true` if `n` is valid, otherwise return `false`.

**Constraints:**
- $0 \leq n \leq 10^5$
- $0 \leq x \leq 9$

**Examples:**

| Input | Output | Explanation |
|-------|--------|-------------|
| n = 101, x = 0 | true | Contains digit 0 at index 1. Doesn't start with 0. |
| n = 232, x = 2 | false | Starts with 2, which violates the condition. |
| n = 5, x = 1 | false | Does not contain digit 1. |

## Observations

1. **Two independent conditions:** The problem requires BOTH conditions to be true simultaneously:
   - Digit `x` must appear somewhere in `n`
   - The first digit of `n` must NOT be `x`

2. **Digit extraction:** To check individual digits, we need to extract them from the number. Two common approaches:
   - Convert to string and iterate through characters
   - Use modulo arithmetic to extract digits from right to left

3. **Array of digits:** Building an array of digits allows us to:
   - Easily check if digit `x` exists using `in` operator
   - Access the last element (index `-1`) which is the first digit after extraction

4. **Digit order matters:** When extracting digits via modulo, we get them in reverse order (least significant to most significant). The last element in our array corresponds to the first digit of the original number.

## Solution

```python
class Solution:
    def validDigit(self, n: int, x: int) -> bool:
        arr = []
        while n:
            arr.append(n % 10)
            n //= 10
        return x in arr and arr[-1] != x
```

### Approach: Digit Extraction with Modulo

**Algorithm:**
1. Extract all digits from `n` into an array using modulo operation
2. Check if `x` exists in the array AND the last element (first digit) is not `x`

**Step-by-step walkthrough with Example 1** (n = 101, x = 0):

| Step | Operation | Result |
|------|-----------|--------|
| Initial | n = 101 | arr = [] |
| Iteration 1 | 101 % 10 = 1, n = 10 | arr = [1] |
| Iteration 2 | 10 % 10 = 0, n = 1 | arr = [1, 0] |
| Iteration 3 | 1 % 10 = 1, n = 0 | arr = [1, 0, 1] |
| Check 1 | `0 in [1, 0, 1]` | true ✓ |
| Check 2 | `arr[-1] = 1 ≠ 0` | true ✓ |
| Result | true AND true | **true** |

**Why `arr[-1]` is the first digit:**
- When extracting digits via modulo, we get: least significant digit first, most significant digit last
- For 101: we get [1, 0, 1] where 1 (first digit of "101") is at the end
- Python's negative indexing: `arr[-1]` accesses the last element

**Time Complexity:** $O(d)$ where $d$ is the number of digits in $n$ (at most $\log_{10}(n)$ or 5 digits given constraint)

**Space Complexity:** $O(d)$ for storing the digit array

**Alternative approaches:**
- **String conversion:** `return x in str(n) and str(n)[0] != str(x)`
- **Direct checks without array:** Extract while checking conditions (saves space)

# Tags

- String/Number Manipulation
- Digit Extraction
- Conditional Logic

