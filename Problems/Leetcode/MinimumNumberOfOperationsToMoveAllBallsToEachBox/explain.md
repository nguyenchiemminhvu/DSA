## Problem Description

https://leetcode.com/problems/minimum-number-of-operations-to-move-all-balls-to-each-box/

```
You have n boxes. You are given a binary string boxes of length n, where boxes[i] is '0' if the ith box is empty, and '1' if it contains one ball.

In one operation, you can move one ball from a box to an adjacent box. Box i is adjacent to box j if abs(i - j) == 1. Note that after doing so, there may be more than one ball in some boxes.

Return an array answer of size n, where answer[i] is the minimum number of operations needed to move all the balls to the ith box.

Each answer[i] is calculated considering the initial state of the boxes.

Example 1:

Input: boxes = "110"
Output: [1,1,3]
Explanation: The answer for each box is as follows:
1) First box: you will have to move one ball from the second box to the first box in one operation.
2) Second box: you will have to move one ball from the first box to the second box in one operation.
3) Third box: you will have to move one ball from the first box to the third box in two operations, and move one ball from the second box to the third box in one operation.
Example 2:

Input: boxes = "001011"
Output: [11,8,5,4,3,4]

Constraints:

n == boxes.length
1 <= n <= 2000
boxes[i] is either '0' or '1'.
```

## Problem Restatement

We are given a binary string boxes of length n. Each character represents whether the box contains a ball ```('1')``` or is empty ```('0')```.

We want to compute, for each index ```i```, the minimum number of operations required to move all balls into box ```i```.

Moving a ball from one box to an adjacent one counts as ```1``` operation.

We return an array ```answer``` of size ```n```, where ```answer[i]``` is the total number of operations needed to gather all balls at index ```i```.

## Observations

The cost of moving a ball from index ```j``` to index ```i``` is simply ```|i - j|``` (the distance between them).

A brute-force approach would be: for each index ```i```, sum up distances from all ```j``` where ```boxes[j] == '1'```.

Time complexity: ```O(n²)``` (since for each of ```n``` indices we scan all other indices).

This would be too slow for ```n = 2000``` (worst case ```~4``` million operations).

We need a more efficient approach by avoiding recalculating distances from scratch for each ```i```.

Notice the problem has a prefix/suffix cumulative nature: the number of operations from the left side and from the right side can be accumulated progressively.

## Examples

### Example 1

**Input**:

```boxes = "110"```

Left pass (scan left → right) — formula: ```left[i] = left[i-1] + count```, where count is number of ```'1'``` seen so far.

```
i = 0: left[0] = 0. boxes[0] = '1' → count = 1.

i = 1: left[1] = left[0] + count = 0 + 1 = 1. boxes[1] = '1' → count = 2.

i = 2: left[2] = left[1] + count = 1 + 2 = 3. boxes[2] = '0' → count = 2 (unchanged).

left = [0, 1, 3]
```

Right pass (scan right → left) — formula: ```right[i] = right[i+1] + count```, where count is number of ```'1'``` seen so far from the right.

```
i = 2: right[2] = 0. boxes[2] = '0' → count = 0.

i = 1: right[1] = right[2] + count = 0 + 0 = 0. boxes[1] = '1' → count = 1.

i = 0: right[0] = right[1] + count = 0 + 1 = 1. boxes[0] = '1' → count = 2.

right = [1, 0, 0]
```

Combine: ```answer[i] = left[i] + right[i]```

```answer = [0+1, 1+0, 3+0] = [1, 1, 3]```

### Example 2

**Input**:

```boxes = "001011"```

Left pass (scan left → right):

```
i = 0: left[0] = 0. boxes[0] = '0' → count = 0.

i = 1: left[1] = 0. boxes[1] = '0' → count = 0.

i = 2: left[2] = 0. boxes[2] = '1' → count = 1.

i = 3: left[3] = left[2] + 1 = 0 + 1 = 1. boxes[3] = '0' → count = 1.

i = 4: left[4] = left[3] + 1 = 1 + 1 = 2. boxes[4] = '1' → count = 2.

i = 5: left[5] = left[4] + 2 = 2 + 2 = 4. boxes[5] = '1' → count = 3.

left = [0, 0, 0, 1, 2, 4]
```

Right pass (scan right → left):

```
i = 5: right[5] = 0. boxes[5] = '1' → count = 1.

i = 4: right[4] = right[5] + 1 = 0 + 1 = 1. boxes[4] = '1' → count = 2.

i = 3: right[3] = right[4] + 2 = 1 + 2 = 3. boxes[3] = '0' → count = 2.

i = 2: right[2] = right[3] + 2 = 3 + 2 = 5. boxes[2] = '1' → count = 3.

i = 1: right[1] = right[2] + 3 = 5 + 3 = 8. boxes[1] = '0' → count = 3.

i = 0: right[0] = right[1] + 3 = 8 + 3 = 11. boxes[0] = '0' → count = 3.

right = [11, 8, 5, 3, 1, 0]
```

Combine: add left + right index-wise

```answer = [0+11, 0+8, 0+5, 1+3, 2+1, 4+0] = [11, 8, 5, 4, 3, 4]```

## Complexity

- **Time Complexity:**  
  - Left pass: O(n)  
  - Right pass: O(n)  
  - Final merge: O(n)  
  → **Overall: O(n)**

- **Space Complexity:**  
  - `left[]` + `right[]` arrays: O(n)  
  → **O(n)** extra space.  
  - Could be optimized to O(1) if we directly compute in a single array.

## Tags

array, prefix sum