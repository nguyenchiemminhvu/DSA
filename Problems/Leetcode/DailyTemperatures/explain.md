## Problem

https://leetcode.com/problems/daily-temperatures/description/

```
Given an array of integers temperatures represents the daily temperatures, return an array answer such that answer[i] is the number of days you have to wait after the ith day to get a warmer temperature. If there is no future day for which this is possible, keep answer[i] == 0 instead.

Example 1:

Input: temperatures = [73,74,75,71,69,72,76,73]
Output: [1,1,4,2,1,1,0,0]

Example 2:

Input: temperatures = [30,40,50,60]
Output: [1,1,1,0]

Example 3:

Input: temperatures = [30,60,90]
Output: [1,1,0]

Constraints:

1 <= temperatures.length <= 105
30 <= temperatures[i] <= 100
```

## Observations

1. **Next Greater Element Pattern**: This problem is a classic "next greater element" variant where we need to find the next warmer temperature for each day.

2. **Monotonic Stack Approach**: We can use a stack to maintain temperatures in decreasing order. When we encounter a warmer temperature, it will be the answer for all cooler temperatures in the stack.

3. **Reverse Iteration**: Processing the array from right to left allows us to build up the stack of "future" temperatures as we go, making it easier to find the next warmer day.

4. **Time-Space Trade-off**: Using a stack gives us O(n) time complexity instead of the naive O(n²) approach, at the cost of O(n) extra space.

5. **Index Distance**: The answer is not the temperature value itself, but the number of days (index difference) until a warmer temperature occurs.

## Solution

The solution uses a **monotonic decreasing stack** with reverse iteration:

1. **Initialize**: 
   - `res[0] * n` - result array initialized to 0 (default for no warmer day)
   - `st` - stack storing tuples of (temperature, index)
   - Start with the last element in the stack

2. **Reverse Iteration** (from second-to-last to first element):
   - For each temperature at index `i`, we process from right to left

3. **Stack Maintenance**:
   - **Pop elements**: Remove all temperatures from stack that are ≤ current temperature
   - These can never be the "next warmer" for any future elements we'll process
   - This maintains the decreasing property of our stack

4. **Find Next Warmer Day**:
   - If stack is not empty after popping, the top element is the next warmer temperature
   - Calculate days to wait: `st[-1][1] - i` (difference in indices)
   - If stack is empty, no warmer day exists (res[i] remains 0)

5. **Update Stack**: Add current temperature and index to stack for future iterations

**Example Walkthrough** with `[73,74,75,71,69,72,76,73]`:

```
i=6 (temp=76): st=[(73,7)] → pop nothing → res[6]=0 → st=[(73,7),(76,6)]
i=5 (temp=72): st=[(73,7),(76,6)] → pop (73,7) → res[5]=6-5=1 → st=[(76,6),(72,5)]
i=4 (temp=69): st=[(76,6),(72,5)] → pop nothing → res[4]=5-4=1 → st=[(76,6),(72,5),(69,4)]
i=3 (temp=71): st=[(76,6),(72,5),(69,4)] → pop (69,4) → res[3]=5-3=2 → st=[(76,6),(72,5),(71,3)]
i=2 (temp=75): st=[(76,6),(72,5),(71,3)] → pop (72,5),(71,3) → res[2]=6-2=4 → st=[(76,6),(75,2)]
i=1 (temp=74): st=[(76,6),(75,2)] → pop nothing → res[1]=2-1=1 → st=[(76,6),(75,2),(74,1)]
i=0 (temp=73): st=[(76,6),(75,2),(74,1)] → pop nothing → res[0]=1-0=1 → final
```

**Time Complexity**: O(n) - Each element is pushed and popped at most once
**Space Complexity**: O(n) - Stack can hold up to n elements in worst case

## Tags

array, stack, greedy