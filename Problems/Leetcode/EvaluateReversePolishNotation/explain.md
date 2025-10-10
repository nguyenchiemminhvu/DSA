## Problem

https://leetcode.com/problems/evaluate-reverse-polish-notation/

```
You are given an array of strings tokens that represents an arithmetic expression in a Reverse Polish Notation.

Evaluate the expression. Return an integer that represents the value of the expression.

Note that:

The valid operators are '+', '-', '*', and '/'.
Each operand may be an integer or another expression.
The division between two integers always truncates toward zero.
There will not be any division by zero.
The input represents a valid arithmetic expression in a reverse polish notation.
The answer and all the intermediate calculations can be represented in a 32-bit integer.

Example 1:

Input: tokens = ["2","1","+","3","*"]
Output: 9
Explanation: ((2 + 1) * 3) = 9

Example 2:

Input: tokens = ["4","13","5","/","+"]
Output: 6
Explanation: (4 + (13 / 5)) = 6

Example 3:

Input: tokens = ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]
Output: 22
Explanation: ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
= ((10 * (6 / (12 * -11))) + 17) + 5
= ((10 * (6 / -132)) + 17) + 5
= ((10 * 0) + 17) + 5
= (0 + 17) + 5
= 17 + 5
= 22

Constraints:

1 <= tokens.length <= 104
tokens[i] is either an operator: "+", "-", "*", or "/", or an integer in the range [-200, 200].
```

## Observations

**Reverse Polish Notation (RPN)** is a postfix notation where operators come after their operands. For example:
- Infix: `(2 + 1) * 3` becomes RPN: `["2", "1", "+", "3", "*"]`
- The key insight is that RPN can be evaluated using a **stack** in a single left-to-right pass

**Stack-based evaluation strategy:**
- When we encounter a number, push it onto the stack
- When we encounter an operator, pop the required operands (2 for binary operators), perform the operation, and push the result back
- The final result will be the only element left in the stack

**Important details:**
- For subtraction and division, **order matters**: if we pop `b` then `a`, the operation is `a - b` or `a / b` (not `b - a` or `b / a`)
- Division should truncate toward zero: `int(a / b)` in Python handles this correctly for both positive and negative results
- We can use `try-except` to distinguish between numbers and operators instead of string comparison

## Solution

The solution uses a **deque** as a stack to evaluate the RPN expression:

1. **Initialize a stack** using `deque()` for efficient append/pop operations

2. **Process each token** in the input array:
   - **Try to convert to integer**: Use `int(token)` inside a try-except block
   - **If successful** (it's a number): Push the value onto the stack
   - **If ValueError occurs** (it's an operator): Pop two operands and perform the operation

3. **Handle operators** using pattern matching:
   - Pop `b` first, then `a` (important for order in subtraction/division)
   - Perform the operation: `a + b`, `a - b`, `a * b`, or `int(a / b)`
   - Push the result back onto the stack

4. **Return the final result**: The stack will contain exactly one element - the answer

**Key implementation details:**
- Using `deque()` provides O(1) append and pop operations
- The `try-except` approach is more Pythonic than checking if the token is in `["+", "-", "*", "/"]`
- `int(a / b)` correctly handles truncation toward zero for both positive and negative divisions
- The `match-case` statement (Python 3.10+) provides clean operator handling

**Time Complexity:** `O(n)` - single pass through all tokens  
**Space Complexity:** `O(n)` - stack can hold up to `n/2` operands in worst case

## Tags

array, string, stack