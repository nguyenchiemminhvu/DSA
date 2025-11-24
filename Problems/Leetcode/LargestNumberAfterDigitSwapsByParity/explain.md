## Problem

https://leetcode.com/problems/largest-number-after-digit-swaps-by-parity/description/

```
You are given a positive integer num. You may swap any two digits of num that have the same parity (i.e. both odd digits or both even digits).

Return the largest possible value of num after any number of swaps.

Example 1:

Input: num = 1234
Output: 3412
Explanation: Swap the digit 3 with the digit 1, this results in the number 3214.
Swap the digit 2 with the digit 4, this results in the number 3412.
Note that there may be other sequences of swaps but it can be shown that 3412 is the largest possible number.
Also note that we may not swap the digit 4 with the digit 1 since they are of different parities.

Example 2:

Input: num = 65875
Output: 87655
Explanation: Swap the digit 8 with the digit 6, this results in the number 85675.
Swap the first digit 5 with the digit 7, this results in the number 87655.
Note that there may be other sequences of swaps but it can be shown that 87655 is the largest possible number.

Constraints:

1 <= num <= 109
```

## Observations

1. **Parity constraint**: We can only swap digits that have the same parity (both odd or both even)
2. **Maximization strategy**: To get the largest number, we want larger digits in more significant positions
3. **Independent optimization**: Since odd and even digits can't be swapped with each other, we can optimize their positions independently
4. **Greedy approach**: For each parity group, we should arrange digits in descending order at their original positions

Key insights:
- Extract all digit positions and separate them by parity
- Sort odd digits in descending order and place them back at odd positions
- Sort even digits in descending order and place them back at even positions
- This ensures maximum value while respecting parity constraints

## Solution

1. **Extract digits**: Convert integer to array of individual digits
2. **Classify positions**: Identify indices of odd and even digits
3. **Sort by parity**: Sort odd digits and even digits separately in descending order
4. **Rearrange**: Place sorted digits back at their respective parity positions
5. **Reconstruct**: Convert digit array back to integer

**Time Complexity:** O(n log n) where n is the number of digits (due to sorting)
**Space Complexity:** O(n) for storing digits and indices

**Example walkthrough (num = 1234):**
- Digits: [1, 2, 3, 4]
- Odd positions: [0, 2] with values [1, 3] → sorted: [3, 1]
- Even positions: [1, 3] with values [2, 4] → sorted: [4, 2]
- Result: [3, 4, 1, 2] → 3412

# Tags

array