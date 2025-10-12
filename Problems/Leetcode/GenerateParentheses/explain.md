## Problem

https://leetcode.com/problems/generate-parentheses/description/

```
Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

Example 1:

Input: n = 3
Output: ["((()))","(()())","(())()","()(())","()()()"]

Example 2:

Input: n = 1
Output: ["()"]

Constraints:

1 <= n <= 8
```

## Observations

1. **Valid Parentheses Rules:**
   - Every opening parenthesis `(` must have a corresponding closing parenthesis `)`
   - At any point in the string, the number of closing parentheses cannot exceed the number of opening parentheses
   - We need exactly `n` opening and `n` closing parentheses

2. **Backtracking Approach:**
   - We can build valid combinations by making choices at each step
   - At each position, we can either add an opening `(` or closing `)` parenthesis
   - We need to backtrack when we've explored all possibilities from a given state

3. **State Tracking:**
   - Track count of opening parentheses used (`open`)
   - Track count of closing parentheses used (`close`)
   - Build the current combination incrementally

## Solution

The solution uses a **depth-first search (DFS) backtracking** approach:

### Algorithm Breakdown:

1. **Base Case:** When `open == n` and `close == n`, we've used all `n` pairs - convert the current combination to string and add to results

2. **Recursive Cases:**
   - **Add Opening Parenthesis:** If `open < n`, we can still add more `(`
   - **Add Closing Parenthesis:** If `close < open`, we can add `)` (ensures validity)

3. **Backtracking:** After exploring each choice, remove it (`temp.pop()`) to try other possibilities

### Example Trace (n=2):
```
Start: open=0, close=0, temp=[]
├── Add '(': open=1, close=0, temp=[0]
│   ├── Add '(': open=2, close=0, temp=[0,0]
│   │   └── Add ')': open=2, close=1, temp=[0,0,1]
│   │       └── Add ')': open=2, close=2, temp=[0,0,1,1] → "(())"
│   └── Add ')': open=1, close=1, temp=[0,1]
│       └── Add '(': open=2, close=1, temp=[0,1,0]
│           └── Add ')': open=2, close=2, temp=[0,1,0,1] → "()()"
```

### Time & Space Complexity:
- **Time:** O(4ⁿ/√n) - This is the nth Catalan number
- **Space:** O(n) for recursion depth and temporary array

### Key Insights:
- The constraint `close < open` ensures we never have more closing than opening parentheses
- Using `0` for `(` and `1` for `)` in the temp array is a clever encoding
- The backtracking ensures all valid combinations are explored exactly once

## Tags

array, string, backtracking