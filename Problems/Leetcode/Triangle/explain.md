## Problem Description

https://leetcode.com/problems/triangle/description/

```
Given a triangle array, return the minimum path sum from top to bottom.

For each step, you may move to an adjacent number of the row below. More formally, if you are on index i on the current row, you may move to either index i or index i + 1 on the next row.

Example 1:

Input: triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
Output: 11
Explanation: The triangle looks like:
   2
  3 4
 6 5 7
4 1 8 3
The minimum path sum from top to bottom is 2 + 3 + 5 + 1 = 11 (underlined above).

Example 2:

Input: triangle = [[-10]]
Output: -10

Constraints:

1 <= triangle.length <= 200
triangle[0].length == 1
triangle[i].length == triangle[i - 1].length + 1
-104 <= triangle[i][j] <= 104
```

## Observations

The simple and direct way is to explore all possible paths from top to bottom and pick the smallest sum.

At position ```(i, j)``` in the triangle, can move to:

```(i+1, j) (down-left)```

Or

```(i+1, j+1) (down-right)```

So the recurrence looks like:

```minPath(i, j) = triangle[i][j] + min(minPath(i+1, j), minPath(i+1, j+1))```

Problems with this:

- Many overlapping subproblems.
- Exponential time complexity O(2^n) for height n.

**Improve with dynamic programming:**

We want the minimum path sum from top to bottom of the triangle.

To reach the bottom row with an optimal result, we must ensure that each row above has already been computed optimally.

At the beginning, the only known value is the top element of the triangle.

For each next row, we must update the minimum path sums for its elements with 2 possible paths: From above-left or from above-straight.

But at index 0, no above-left index.

We don’t need to keep the entire triangle or a full ```n x n``` DP table. At any moment, we only need:

The current row (```cur_row```)

The previous row (```dp```)

So memory is reduced to ```O(n)``` instead of ```O(n²)```.

## Examples

```triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]```

Setup:

```
n = 4

MAX = 10001 (int(1e4 + 1))

initial dp = [MAX]*n then dp[0] = triangle[0][0]

dp = [2, 10001, 10001, 10001]
```

Row i = 1 (row = [3, 4])

```
before pad: cur_row = [3, 4]

pad with MAX (n - i = 3):
cur_row = [3, 4, 10001, 10001, 10001]

add dp[0] to first element:
cur_row[0] = 3 + dp[0] = 3 + 2 = 5 →
cur_row = [5, 4, 10001, 10001, 10001]
```

Now update middle elements (for j in range(1, n) i.e. j = 1,2,3):

```
j = 1: cur_row[1] = min(4 + dp[0], 4 + dp[1]) = min(4+2, 4+10001) = min(6, 10005) = 6

j = 2: cur_row[2] = min(10001 + dp[1], 10001 + dp[2]) = min(10001+10001, 10001+10001) = 20002

j = 3: cur_row[3] = min(10001 + dp[2], 10001 + dp[3]) = 20002
```

After updates:

```
cur_row (new dp) = [5, 6, 20002, 20002, 10001]
dp = cur_row
```

Row i = 2 (row = [6, 5, 7])

```
before pad: [6, 5, 7]

pad (n - i = 2): [6, 5, 7, 10001, 10001]

first element add dp[0]: 6 + 5 = 11 → [11, 5, 7, 10001, 10001]
```

Update j = 1,2,3:

```
j = 1: min(5 + dp[0], 5 + dp[1]) = min(5+5, 5+6) = min(10, 11) = 10

j = 2: min(7 + dp[1], 7 + dp[2]) = min(7+6, 7+20002) = min(13, 20009) = 13

j = 3: min(10001 + dp[2], 10001 + dp[3]) = min(10001+20002, 10001+20002) = 30003
```

After updates:

```
dp = [11, 10, 13, 30003, 10001]
```

Row i = 3 (row = [4, 1, 8, 3])

```
before pad: [4, 1, 8, 3]

pad (n - i = 1): [4, 1, 8, 3, 10001]

first element add dp[0]: 4 + 11 = 15 → [15, 1, 8, 3, 10001]
```

Update j = 1,2,3:

```
j = 1: min(1 + dp[0], 1 + dp[1]) = min(1+11, 1+10) = min(12, 11) = 11

j = 2: min(8 + dp[1], 8 + dp[2]) = min(8+10, 8+13) = min(18, 21) = 18

j = 3: min(3 + dp[2], 3 + dp[3]) = min(3+13, 3+30003) = min(16, 30006) = 16
```

Final dp after last row:

```
dp = [15, 11, 18, 16, 10001]
```

Answer is min(dp) = 11.

## Comlexity

**Time:** O(n)

**Space:** S(n)

## Tags

array, dynamic programming