## Problem

https://leetcode.com/problems/broken-calculator/

```
There is a broken calculator that has the integer startValue on its display initially. In one operation, you can:

multiply the number on display by 2, or
subtract 1 from the number on display.
Given two integers startValue and target, return the minimum number of operations needed to display target on the calculator.

Example 1:

Input: startValue = 2, target = 3
Output: 2
Explanation: Use double operation and then decrement operation {2 -> 4 -> 3}.

Example 2:

Input: startValue = 5, target = 8
Output: 2
Explanation: Use decrement and then double {5 -> 4 -> 8}.

Example 3:

Input: startValue = 3, target = 10
Output: 3
Explanation: Use double, decrement and double {3 -> 6 -> 5 -> 10}.

Constraints:

1 <= startValue, target <= 109
```

## Observations

1. **Key Insight**: Instead of thinking forward from `startValue` to `target`, we can think backward from `target` to `startValue`. This reverses the operations:
   - Forward: multiply by 2 or subtract 1
   - Backward: divide by 2 or add 1

2. **Why backward approach works better**:
   - When working forward, we have to make choices about when to multiply vs subtract
   - When working backward, the choice is often obvious: if target is even, divide by 2; if odd, add 1

3. **Greedy Strategy**:
   - If `target > startValue`: work backward from target
   - If `target` is odd: add 1 (equivalent to subtracting 1 in forward direction)
   - If `target` is even: divide by 2 (equivalent to multiplying by 2 in forward direction)
   - Continue until `target <= startValue`

4. **Final Step**: Once `target <= startValue`, we can only subtract 1 repeatedly, so we need `startValue - target` more operations.

## Solution

1. **Phase 1 - Backward from target**: While `target > startValue`:
   - If `target` is odd: increment it by 1
   - If `target` is even: divide it by 2
   - Count each operation

2. **Phase 2 - Forward to target**: Once `target <= startValue`:
   - We can only subtract 1 from `startValue`
   - Need exactly `startValue - target` operations

**Why this is optimal**:
- When `target` is odd and > `startValue`, adding 1 is always better than trying to reach it through multiplication
- When `target` is even and > `startValue`, dividing by 2 reduces the problem size most efficiently
- The greedy choice at each step leads to the global optimum

**Time Complexity**: O(log target) - we're essentially dividing target by 2 repeatedly
**Space Complexity**: O(1) - only using constant extra space

**Example Walkthrough** (startValue = 3, target = 10):
- target = 10 (even) → target = 5, count = 1
- target = 5 (odd) → target = 6, count = 2  
- target = 6 (even) → target = 3, count = 3
- Now target = startValue = 3, so return count + (3-3) = 3

## Tags

math, greedy