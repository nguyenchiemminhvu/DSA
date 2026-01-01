## Problem

https://leetcode.com/problems/online-stock-span/description/

```
Design an algorithm that collects daily price quotes for some stock and returns the span of that stock's price for the current day.

The span of the stock's price in one day is the maximum number of consecutive days (starting from that day and going backward) for which the stock price was less than or equal to the price of that day.

For example:
- If prices in last 4 days: [7,2,1,2] and today's price is 2, then span = 4
- If prices in last 4 days: [7,34,1,2] and today's price is 8, then span = 3

Implement the StockSpanner class:
- StockSpanner(): Initializes the object
- int next(int price): Returns the span of the stock's price given today's price

Constraints:
- 1 <= price <= 10^5
- At most 10^4 calls will be made to next
```

## Observations

1. **Naive Approach**: For each new price, iterate backward through all previous prices counting consecutive days with price <= current price. This would be O(n) per call, leading to O(n²) total time complexity.

2. **Key Insight**: We need to efficiently find how many consecutive previous days had prices <= current price. This is a classic monotonic stack problem.

3. **Monotonic Stack Pattern**: 
   - When a new price arrives, all previous smaller prices become "irrelevant" for future calculations
   - We only need to remember prices that are greater than prices that came after them
   - This suggests maintaining a decreasing monotonic stack

4. **Stack of Indices**: Store indices (not prices) in the stack, which allows us to calculate spans as distances between indices.

5. **What the Stack Represents**: After processing each price, the stack contains indices of prices in decreasing order. These are potential "boundaries" for future span calculations.

## Solution

### Approach: Monotonic Decreasing Stack

The solution maintains:
- `arr[]`: List of all prices in order
- `st[]`: Stack storing indices of prices in decreasing order

### Algorithm

For each new price:

1. **Append price** to the array

2. **Pop smaller/equal prices**: While stack is not empty and price at stack top ≤ current price:
   - Pop from stack (these prices are now "covered" by current price)

3. **Calculate span**:
   - If stack is empty: All previous prices were ≤ current price → span = length of array
   - If stack is not empty: Span = distance from current index to index at stack top
     - Formula: `len(arr) - st[-1] - 1`

4. **Push current index** to stack

5. **Return span**

### Why This Works

- The stack maintains indices of prices that could be the "left boundary" for future span calculations
- When we pop an index, it means that price is ≤ current price, so it's included in current span
- The remaining top of stack (if any) is the first price to the left that is > current price
- The distance from that boundary to current position gives us the span

### Complexity

- **Time**: O(1) amortized per call
  - Each index is pushed once and popped at most once
  - Over n calls: O(n) total operations
- **Space**: O(n) to store prices and indices

### Example Walkthrough

```
Prices: [100, 80, 60, 70, 60, 75, 85]

100: st=[], push(0) → span=1, st=[0]
80:  st=[0], 100>80, push(1) → span=1, st=[0,1]
60:  st=[0,1], 80>60, push(2) → span=1, st=[0,1,2]
70:  st=[0,1,2], pop(2), 80>70, push(3) → span=2, st=[0,1,3]
60:  st=[0,1,3], 70>60, push(4) → span=1, st=[0,1,3,4]
75:  st=[0,1,3,4], pop(4), pop(3), 80>75, push(5) → span=4, st=[0,1,5]
85:  st=[0,1,5], pop(5), pop(1), 100>85, push(6) → span=6, st=[0,6]
```

# Tags
Stack, Monotonic Stack, Design, Array

