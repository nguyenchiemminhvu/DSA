## Problem

https://leetcode.com/problems/minimum-cost-to-reach-every-position/

```
You are given an integer array cost of size n. You are currently at position n (at the end of the line) in a line of n + 1 people (numbered from 0 to n).

You wish to move forward in the line, but each person in front of you charges a specific amount to swap places. The cost to swap with person i is given by cost[i].

You are allowed to swap places with people as follows:

If they are in front of you, you must pay them cost[i] to swap with them.
If they are behind you, they can swap with you for free.
Return an array answer of size n, where answer[i] is the minimum total cost to reach each position i in the line.

Example 1:

Input: cost = [5,3,4,1,3,2]

Output: [5,3,3,1,1,1]

Explanation:

We can get to each position in the following way:

i = 0. We can swap with person 0 for a cost of 5.
i = 1. We can swap with person 1 for a cost of 3.
i = 2. We can swap with person 1 for a cost of 3, then swap with person 2 for free.
i = 3. We can swap with person 3 for a cost of 1.
i = 4. We can swap with person 3 for a cost of 1, then swap with person 4 for free.
i = 5. We can swap with person 3 for a cost of 1, then swap with person 5 for free.

Example 2:

Input: cost = [1,2,4,6,7]

Output: [1,1,1,1,1]

Explanation:

We can swap with person 0 for a cost of 1, then we will be able to reach any position i for free.

Constraints:

1 <= n == cost.length <= 100
1 <= cost[i] <= 100
```

## Observations

1. **Starting Position**: We start at position `n` (the end of the line with `n+1` people numbered 0 to n).

2. **Movement Rules**:
   - To swap with someone in front of us: we pay `cost[i]`
   - To swap with someone behind us: it's free

3. **Key Insight**: Once we reach a position, we can move to any position behind it for free. This means we only need to pay to move forward to a new "minimum position".

4. **Greedy Strategy**: To reach position `i`, we need to find the cheapest way to get to position `i` or any position before it (since we can move backward for free).

5. **Pattern Recognition**: The minimum cost to reach position `i` is the minimum of all costs from position 0 to position `i`, because:
   - We can pay the minimum cost among `cost[0]` to `cost[i]` to reach that cheapest position
   - From there, we can move backward to position `i` for free

## Solution

1. **Initialize**: Start with `cur_min = cost[0]` (the cost to reach position 0).

2. **Iterate**: For each position `i` from 0 to n-1:
   - Update `cur_min` to be the minimum cost seen so far
   - This represents the cheapest way to reach any position from 0 to i
   - Add `cur_min` to the result

3. **Why this works**:
   - To reach position `i`, we need to first reach some position `j ≤ i`
   - The optimal strategy is to reach the position with minimum cost among positions 0 to i
   - Once we're at that position, we can move backward to position `i` for free
   - Therefore, `answer[i] = min(cost[0], cost[1], ..., cost[i])`

**Time Complexity**: O(n) - single pass through the array
**Space Complexity**: O(1) - excluding the output array

**Example Walkthrough** with `cost = [5,3,4,1,3,2]`:
- Position 0: min(5) = 5
- Position 1: min(5,3) = 3  
- Position 2: min(5,3,4) = 3
- Position 3: min(5,3,4,1) = 1
- Position 4: min(5,3,4,1,3) = 1
- Position 5: min(5,3,4,1,3,2) = 1

Result: `[5,3,3,1,1,1]`

# Tags

- Array
- Greedy
- Prefix Minimum
- Dynamic Programming (implicit)

