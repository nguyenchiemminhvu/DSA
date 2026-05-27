## Problem

https://leetcode.com/problems/different-ways-to-add-parentheses/description

Given a string `expression` of numbers and operators (`+`, `-`, `*`), return all possible results from computing all different ways to group numbers and operators with parentheses.

**Constraints:**
- `1 <= expression.length <= 20`
- `expression` consists of digits (`0-9`) and operators (`+`, `-`, `*`)
- All integer values are in range `[0, 99]` (no leading sign)
- Output values fit in a 32-bit integer
- Number of different results ≤ 10^4

**Examples:**

Example 1: `"2-1-1"`
```
Parenthesizations:
((2-1)-1) = 0
(2-(1-1)) = 2
Output: [0, 2]
```

Example 2: `"2*3-4*5"`
```
Parenthesizations:
(2*(3-(4*5))) = 2*(3-20) = 2*(-17) = -34
((2*3)-(4*5)) = 6-20 = -14
((2*(3-4))*5) = (2*(-1))*5 = -2*5 = -10
(2*((3-4)*5)) = 2*((-1)*5) = 2*(-5) = -10
(((2*3)-4)*5) = (6-4)*5 = 2*5 = 10
Output: [-34, -14, -10, -10, 10]
```

## Observations

1. **Divide-and-Conquer Structure**: The problem naturally decomposes by operators. For each operator, we can split the expression into left and right parts, solve each independently, then combine results.

2. **Operator as Split Point**: Every operator acts as a potential "last operation" to perform. By choosing different operators to evaluate last, we get different parenthesizations.

3. **Key Insight**: At each operator position, we:
   - Recursively get all possible results from the left sub-expression
   - Recursively get all possible results from the right sub-expression  
   - Combine each left result with each right result using the current operator

4. **Base Case**: When no operators exist, the string is a single number.

5. **Exponential Growth**: The number of ways grows exponentially with expression length. For an expression with `n` operators, there are Catalan number C(n) = (2n)!/(n!(n+1)!) different parenthesizations.

6. **Duplicate Results**: The same numerical result can appear multiple times from different parenthesizations (see Example 2 with -10 appearing twice).

## Solution

### Approach: Recursive Divide-and-Conquer

The algorithm works by:

1. **Scan** the expression from left to right
2. **Whenever an operator is found**:
   - Split at that operator position
   - Recursively compute all results for the left part
   - Recursively compute all results for the right part
   - Combine each left result with each right result using the operator
3. **If no operators found**, the expression is a single number - return it as the base case

### Why This Works

By treating each operator as the "last operation to compute," we explore all possible parenthesizations. For example:
- `2-1-1` can be computed as:
  - `(2) - (1-1)` ← treating second `-` as last operation
  - `(2-1) - (1)` ← treating first `-` as last operation

### Complexity Analysis

**Time Complexity**: O(4^n) worst case, where n is the number of operators. This corresponds to the Catalan number growth. For n operators, we have C(n) = (2n)!/(n!(n+1)!)) different ways to parenthesize.

**Space Complexity**: O(4^n) for storing results and recursion stack depth of O(n).

### Code Walkthrough

```python
def diffWaysToCompute(self, s: str) -> List[int]:
    def F(exp: str) -> List[int]:
        res = []
        # Scan through the expression
        for i, c in enumerate(exp):
            # Find each operator
            if c in '+-*':
                # Split at the operator
                left_exp = exp[:i]      # Everything before operator
                right_exp = exp[i + 1:] # Everything after operator
                
                # Recursively get all results from both sides
                left_arr = F(left_exp)
                right_arr = F(right_exp)
                
                # Combine every left result with every right result
                for val1 in left_arr:
                    for val2 in right_arr:
                        if c == '+':
                            res.append(val1 + val2)
                        elif c == '-':
                            res.append(val1 - val2)
                        else:  # c == '*'
                            res.append(val1 * val2)
        
        # Base case: if no operators found, it's a single number
        if not res:
            res.append(int(exp))
        
        return res
    
    return F(s)
```

### Trace Example: `"2-1-1"`

```
F("2-1-1")
├─ i=1, c='-':
│  ├─ left_exp="2", right_exp="1-1"
│  ├─ F("2") → [2]
│  ├─ F("1-1")
│  │  ├─ i=1, c='-':
│  │  │  ├─ F("1") → [1]
│  │  │  ├─ F("1") → [1]
│  │  │  └─ res=[1-1] = [0]
│  │  └─ return [0]
│  └─ res.append(2-0) = [2]
│
└─ i=3, c='-':
   ├─ left_exp="2-1", right_exp="1"
   ├─ F("2-1")
   │  ├─ i=1, c='-':
   │  │  ├─ F("2") → [2]
   │  │  ├─ F("1") → [1]
   │  │  └─ res=[2-1] = [1]
   │  └─ return [1]
   ├─ F("1") → [1]
   └─ res.append(1-1) = [2, 0]

Final: [2, 0]
```

### Optimization: Memoization

The solution can be optimized with memoization since the same sub-expression can be computed multiple times:

```python
def diffWaysToCompute(self, s: str) -> List[int]:
    memo = {}
    
    def F(exp: str) -> List[int]:
        if exp in memo:
            return memo[exp]
        
        res = []
        for i, c in enumerate(exp):
            if c in '+-*':
                left_arr = F(exp[:i])
                right_arr = F(exp[i + 1:])
                
                for val1 in left_arr:
                    for val2 in right_arr:
                        if c == '+':
                            res.append(val1 + val2)
                        elif c == '-':
                            res.append(val1 - val2)
                        else:
                            res.append(val1 * val2)
        
        if not res:
            res.append(int(exp))
        
        memo[exp] = res
        return res
    
    return F(s)
```

# Tags
#divide-and-conquer #recursion #dynamic-programming #catalan-numbers

