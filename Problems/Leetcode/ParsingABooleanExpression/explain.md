## Problem

https://leetcode.com/problems/parsing-a-boolean-expression/description/

```
A boolean expression is an expression that evaluates to either true or false. It can be in one of the following shapes:

't' that evaluates to true.
'f' that evaluates to false.
'!(subExpr)' that evaluates to the logical NOT of the inner expression subExpr.
'&(subExpr1, subExpr2, ..., subExprn)' that evaluates to the logical AND of the inner expressions subExpr1, subExpr2, ..., subExprn where n >= 1.
'|(subExpr1, subExpr2, ..., subExprn)' that evaluates to the logical OR of the inner expressions subExpr1, subExpr2, ..., subExprn where n >= 1.

Given a string expression that represents a boolean expression, return the evaluation of that expression.

It is guaranteed that the given expression is valid and follows the given rules.

Example 1:

Input: expression = "&(|(f))"
Output: false
Explanation:
First, evaluate |(f) --> f. The expression is now "&(f)".
Then, evaluate &(f) --> f. The expression is now "f".
Finally, return false.

Example 2:

Input: expression = "|(f,f,f,t)"
Output: true
Explanation: The evaluation of (false OR false OR false OR true) is true.

Example 3:

Input: expression = "!(&(f,t))"
Output: true
Explanation:
First, evaluate &(f,t) --> (false AND true) --> false --> f. The expression is now "!(f)".
Then, evaluate !(f) --> NOT false --> true. We return true.

Constraints:

1 <= expression.length <= 2 * 10^4
expression[i] is one of the following characters: '(', ')', '&', '|', '!', 't', 'f', and ','.
```

## Observations

1. **Nested Structure**: The expression is recursively nested — inner sub-expressions must be evaluated before outer ones. This naturally suggests either a **stack-based** or **recursive** approach.

2. **Operator Precedence via Parentheses**: Every operator (`!`, `&`, `|`) is immediately followed by `(...)`, so parentheses fully determine evaluation order. There is no ambiguity.

3. **Comma is a Separator Only**: Commas `,` separate sub-expressions but carry no value. They can be safely ignored during parsing.

4. **Stack-Based Evaluation**:
   - Push operators and `(` onto the stack as we scan left to right.
   - When we encounter `)`, collect all `'t'/'f'` values back to the nearest `(`, pop `(`, pop the operator, apply the operation, and push the result back.
   - This mimics how a call stack evaluates nested sub-expressions from the inside out.

5. **Recursive Descent**: Alternatively, we can write a recursive parser that consumes characters via an index pointer:
   - If the current character is `'t'` or `'f'`, return its boolean value immediately.
   - If it is `!`, `&`, or `|`, consume the operator, then recursively parse the comma-separated sub-expressions inside `(...)`.

6. **Result Mapping**: Throughout the algorithm, keep values on the stack as `'t'` / `'f'` strings (or booleans), and only convert to a Python `bool` at the very end.

## Solution

### Approach: Stack-Based Parsing

Process the expression character by character. Use a stack to defer evaluation until a closing `)` is seen.

#### Algorithm Steps:

1. **Scan each character**:
   - `'t'` or `'f'` → push onto stack.
   - `'!'`, `'&'`, `'|'`, `'('` → push onto stack.
   - `','` → skip (just a separator).
   - `')'` → trigger evaluation:
     1. Pop values from the stack until `'('` is found; collect them into a list.
     2. Pop `'('`.
     3. Pop the operator (`'!'`, `'&'`, or `'|'`).
     4. Apply the operator to the collected values.
     5. Push `'t'` or `'f'` (the result) back onto the stack.

2. **Final answer**: The single remaining element on the stack is `'t'` or `'f'` — return `True` or `False` accordingly.

#### Operator Logic:

| Operator | Logic |
|----------|-------|
| `!`      | NOT the single sub-expression: `'f' → True`, `'t' → False` |
| `&`      | AND all sub-expressions: `True` only if **all** are `'t'` |
| `\|`     | OR all sub-expressions: `True` if **any** is `'t'` |

#### Example Walkthrough — `"!(&(f,t))"`:

| Step | Character | Stack |
|------|-----------|-------|
| 1    | `!`       | `['!']` |
| 2    | `(`       | `['!', '(']` |
| 3    | `&`       | `['!', '(', '&']` |
| 4    | `(`       | `['!', '(', '&', '(']` |
| 5    | `f`       | `['!', '(', '&', '(', 'f']` |
| 6    | `,`       | *(skip)* |
| 7    | `t`       | `['!', '(', '&', '(', 'f', 't']` |
| 8    | `)`       | collect `['f','t']`, op=`&` → `False` → push `'f'` → `['!', '(', 'f']` |
| 9    | `)`       | collect `['f']`, op=`!` → `True` → push `'t'` → `['t']` |
| End  |           | return `True` |

#### Complexity:
- **Time**: $O(n)$ — each character is pushed and popped at most once.
- **Space**: $O(n)$ — stack depth proportional to expression length.

## Tags

string, stack, recursion, parsing
