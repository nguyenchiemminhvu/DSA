## Problem

https://leetcode.com/problems/clumsy-factorial/description/

```
The factorial of a positive integer n is the product of all positive integers less than or equal to n.

For example, factorial(10) = 10 * 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1.

We make a clumsy factorial using the integers in decreasing order by swapping out the multiply 
operations for a fixed rotation of operations with multiply '*', divide '/', add '+', and subtract '-' 
in this order.

For example, clumsy(10) = 10 * 9 / 8 + 7 - 6 * 5 / 4 + 3 - 2 * 1.

However, these operations are still applied using the usual order of operations of arithmetic. 
We do all multiplication and division steps before any addition or subtraction steps, and 
multiplication and division steps are processed left to right.

Additionally, the division that we use is floor division such that 10 * 9 / 8 = 90 / 8 = 11.

Given an integer n, return the clumsy factorial of n.

Example 1:
Input: n = 4
Output: 7
Explanation: 7 = 4 * 3 / 2 + 1

Example 2:
Input: n = 10
Output: 12
Explanation: 12 = 10 * 9 / 8 + 7 - 6 * 5 / 4 + 3 - 2 * 1

Constraints:
1 <= n <= 10^4
```

## Observations

1. **Operation Pattern**: The operations cycle through `['*', '/', '+', '-']` repeatedly for consecutive descending integers from n to 1.

2. **Order of Operations**: Following standard arithmetic rules:
   - Multiplication and division are evaluated first (left to right)
   - Addition and subtraction are evaluated after (left to right)

3. **Grouping Pattern**: Due to operator precedence, the expression naturally groups into chunks:
   - First chunk: `n * (n-1) / (n-2) + (n-3)`
   - Subsequent chunks: `- [num * (num-1) / (num-2)] + (num-3)`
   
4. **Key Insight**: After the first group, each subsequent 4-number group starts with subtraction, which means we're subtracting a product and then adding a number. This can be represented as: `result - (a * b / c) + d = result - (a * b / c - d)`

5. **Stack-Based Approach**: We can use a stack to handle the operations:
   - For `*` and `/`: directly modify the top of stack
   - For `+`: push the number to stack (will be added later)
   - For `-`: push the negative number to stack (subtraction = adding negative)
   - Final result is the sum of all stack elements

## Solution

### Approach: Stack-Based Evaluation

The solution uses a stack to manage intermediate results while respecting operator precedence:

**Algorithm:**
1. Initialize stack with `n` as the first value
2. Iterate through numbers from `n-1` down to 1
3. Based on the operation index (cycling through 0, 1, 2, 3):
   - **Op 0 (multiply)**: Multiply the top of stack with current number
   - **Op 1 (divide)**: Integer divide the top of stack by current number
   - **Op 2 (add)**: Push current number to stack (deferred addition)
   - **Op 3 (subtract)**: Push negative of current number to stack
4. Return the sum of all stack elements

**Why this works:**
- Multiplication and division are applied immediately to the stack top, maintaining correct precedence
- Addition and subtraction are handled by pushing values to the stack
- Pushing negative values for subtraction converts `a - b` into `a + (-b)`
- Final sum of stack gives the correct result

**Example Walkthrough (n = 10):**
```
Expression: 10 * 9 / 8 + 7 - 6 * 5 / 4 + 3 - 2 * 1

Step-by-step:
n=10: stack = [10]
n=9, op=0(*): stack = [10*9] = [90]
n=8, op=1(/): stack = [90/8] = [11]
n=7, op=2(+): stack = [11, 7]
n=6, op=3(-): stack = [11, 7, -6]
n=5, op=0(*): stack = [11, 7, -6*5] = [11, 7, -30]
n=4, op=1(/): stack = [11, 7, -30/4] = [11, 7, -7]
n=3, op=2(+): stack = [11, 7, -7, 3]
n=2, op=3(-): stack = [11, 7, -7, 3, -2]
n=1, op=0(*): stack = [11, 7, -7, 3, -2*1] = [11, 7, -7, 3, -2]

Sum = 11 + 7 - 7 + 3 - 2 = 12
```

**Complexity Analysis:**
- **Time Complexity**: O(n) - single pass through n-1 numbers
- **Space Complexity**: O(n) - stack can contain up to n/4 + 1 elements (approximately O(n))

**Alternative Approach (commented out):**
The commented code uses Python's `eval()` function by building a string expression. While clever and concise, it's less efficient and not recommended for production code due to:
- Security concerns with `eval()`
- String concatenation overhead
- Less control over the evaluation process

# Tags

#stack #math #simulation #operator-precedence #leetcode-medium

