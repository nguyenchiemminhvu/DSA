## Problem

https://leetcode.com/problems/most-visited-sector-in-a-circular-track/description/

```
Given an integer n and an integer array rounds. We have a circular track which consists of n sectors labeled from 1 to n. A marathon will be held on this track, the marathon consists of m rounds. The ith round starts at sector rounds[i - 1] and ends at sector rounds[i]. For example, round 1 starts at sector rounds[0] and ends at sector rounds[1]

Return an array of the most visited sectors sorted in ascending order.

Notice that you circulate the track in ascending order of sector numbers in the counter-clockwise direction.

Example 1:
Input: n = 4, rounds = [1,3,1,2]
Output: [1,2]
Explanation: The marathon starts at sector 1. The order of the visited sectors is as follows:
1 --> 2 --> 3 (end of round 1) --> 4 --> 1 (end of round 2) --> 2 (end of round 3 and the marathon)
We can see that both sectors 1 and 2 are visited twice and they are the most visited sectors. Sectors 3 and 4 are visited only once.

Example 2:
Input: n = 2, rounds = [2,1,2,1,2,1,2,1,2]
Output: [2]

Example 3:
Input: n = 7, rounds = [1,3,5,7]
Output: [1,2,3,4,5,6,7]

Constraints:
- 2 <= n <= 100
- 1 <= m <= 100
- rounds.length == m + 1
- 1 <= rounds[i] <= n
- rounds[i] != rounds[i + 1] for 0 <= i < m
```

## Observations

1. **Circular Track Movement**: The track is circular with sectors 1 to n, where after sector n comes sector 1.

2. **Visit Counting**: We need to count how many times each sector is visited across all rounds.

3. **Prefix Sum Technique**: Instead of explicitly counting each sector visit, we can use a prefix sum array with range updates to efficiently track visits.

4. **Two Cases for Range Updates**:
   - **Non-wrapping case** (`cur <= target`): Direct range update from cur to target
   - **Wrapping case** (`cur > target`): The path wraps around, so we need two range updates:
     - From cur to n
     - From 1 to target

5. **Key Insight**: The problem can be solved efficiently using difference array technique rather than simulating the entire marathon step by step.

## Solution

### Approach: Prefix Sum with Difference Array

The solution uses a **difference array** technique to handle range updates efficiently:

1. **Initialize Prefix Array**: Create an array `prefix` of size `n + 2` to handle boundary cases.

2. **Process Each Round**:
   - For each round, we move from `cur` to `target = rounds[i]`
   - If `cur <= target`: Simple range update from cur to target
     - Increment `prefix[cur]` and decrement `prefix[target + 1]`
   - If `cur > target`: The path wraps around the track
     - Update range [1, target]: `prefix[1]++`, `prefix[target + 1]--`
     - Update range [cur, n]: `prefix[cur]++`, `prefix[n + 1]--`
   - Move to next starting position: `cur = target + 1`

3. **Convert to Actual Counts**: Apply prefix sum to convert the difference array to actual visit counts.

4. **Find Maximum and Collect Results**: Find the maximum visit count and collect all sectors with that count.

### Complexity Analysis

- **Time Complexity**: O(n + m) where m is the number of rounds
  - Processing rounds: O(m)
  - Prefix sum computation: O(n)
  - Finding maximum and results: O(n)

- **Space Complexity**: O(n) for the prefix array

### Alternative Insight

A simpler observation: Only the first and last sectors matter! The answer is simply the range from `rounds[0]` to `rounds[-1]`. If this wraps around (start > end), the answer is `[1...end] + [start...n]`. This is because intermediate rounds cancel out in terms of which sectors are visited most frequently.

# Tags
#array #simulation #prefix-sum #difference-array #circular-track

