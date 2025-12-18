## Problem

https://leetcode.com/problems/maximum-split-of-positive-even-integers/

```
You are given an integer finalSum. Split it into a sum of a maximum number of unique positive even integers.

For example, given finalSum = 12, the following splits are valid (unique positive even integers summing up to finalSum): (12), (2 + 10), (2 + 4 + 6), and (4 + 8). Among them, (2 + 4 + 6) contains the maximum number of integers. Note that finalSum cannot be split into (2 + 2 + 4 + 4) as all the numbers should be unique.

Return a list of integers that represent a valid split containing a maximum number of integers. If no valid split exists for finalSum, return an empty list. You may return the integers in any order.

Example 1:
Input: finalSum = 12
Output: [2,4,6]
Explanation: The following are valid splits: (12), (2 + 10), (2 + 4 + 6), and (4 + 8).
(2 + 4 + 6) has the maximum number of integers, which is 3. Thus, we return [2,4,6].

Example 2:
Input: finalSum = 7
Output: []
Explanation: There are no valid splits for the given finalSum.

Example 3:
Input: finalSum = 28
Output: [6,8,2,12]
Explanation: The following are valid splits: (2 + 26), (6 + 8 + 2 + 12), and (4 + 24). 
(6 + 8 + 2 + 12) has the maximum number of integers, which is 4.

Constraints:
1 <= finalSum <= 10^10
```

## Observations

1. **Odd numbers impossible**: If finalSum is odd, it's impossible to split it into a sum of even integers (since sum of evens is always even). Return empty list immediately.

2. **Greedy approach**: To maximize the number of integers in the split, we should use the smallest possible even integers first: 2, 4, 6, 8, 10, ...

3. **Uniqueness constraint**: Each even integer can only be used once. This means we need consecutive even numbers starting from 2.

4. **Handling remainder**: After greedily adding consecutive even numbers (2, 4, 6, ..., n), we might have a remainder. Since the remainder is also even, we need to incorporate it:
   - If the remainder equals an already used number, we can't add it directly (violates uniqueness)
   - Instead, add the remainder to the last number in our list to maintain uniqueness

5. **Why last number adjustment works**: If remainder exists in the list, adding it to the last element creates a new unique number that still maintains the sum while keeping all numbers unique.

## Solution

**Algorithm:**

1. **Check for odd input**: If `val` is odd (check using `val & 1`), return empty list.

2. **Greedy construction**: 
   - Start with `cur = 2` (smallest even number)
   - Keep adding consecutive even numbers to result list while `sum + cur <= val`
   - Increment `cur` by 2 each iteration

3. **Handle remainder**:
   - If `sum < val`, there's a remainder: `remain = val - sum`
   - If `remain` already exists in the list, add it to the last element: `tmp[-1] += remain`
   - Otherwise, append it as a new element: `tmp.append(remain)`

**Time Complexity**: O(√n) where n is finalSum. We add approximately √(2n) even numbers before the sum exceeds finalSum.

**Space Complexity**: O(√n) for storing the result list.

**Example walkthrough** (finalSum = 12):
- Start: cur = 2, sum = 0, tmp = []
- Add 2: sum = 2, tmp = [2], cur = 4
- Add 4: sum = 6, tmp = [2, 4], cur = 6
- Add 6: sum = 12, tmp = [2, 4, 6], cur = 8
- Stop (sum + 8 > 12)
- sum = 12 = finalSum, no remainder needed
- Return [2, 4, 6]

**Example with remainder** (finalSum = 28):
- Greedy phase: [2, 4, 6, 8] with sum = 20
- Next cur = 10, but 20 + 10 = 30 > 28
- Remainder: 28 - 20 = 8
- 8 exists in list, so add to last: [2, 4, 6, 8+8] = [2, 4, 6, 16]

# Tags
#greedy #array #math

