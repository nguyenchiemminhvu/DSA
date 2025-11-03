## Problem

https://leetcode.com/problems/minimum-time-to-make-rope-colorful/description/

```
Alice has n balloons arranged on a rope. You are given a 0-indexed string colors where colors[i] is the color of the ith balloon.

Alice wants the rope to be colorful. She does not want two consecutive balloons to be of the same color, so she asks Bob for help. Bob can remove some balloons from the rope to make it colorful. You are given a 0-indexed integer array neededTime where neededTime[i] is the time (in seconds) that Bob needs to remove the ith balloon from the rope.

Return the minimum time Bob needs to make the rope colorful.

Example 1:

Input: colors = "abaac", neededTime = [1,2,3,4,5]
Output: 3
Explanation: In the above image, 'a' is blue, 'b' is red, and 'c' is green.
Bob can remove the blue balloon at index 2. This takes 3 seconds.
There are no longer two consecutive balloons of the same color. Total time = 3.

Example 2:

Input: colors = "abc", neededTime = [1,2,3]
Output: 0
Explanation: The rope is already colorful. Bob does not need to remove any balloons from the rope.

Example 3:

Input: colors = "aabaa", neededTime = [1,2,3,4,1]
Output: 2
Explanation: Bob will remove the balloons at indices 0 and 4. Each balloons takes 1 second to remove.
There are no longer two consecutive balloons of the same color. Total time = 1 + 1 = 2.

Constraints:

n == colors.length == neededTime.length
1 <= n <= 105
1 <= neededTime[i] <= 104
colors contains only lowercase English letters.
```

## Observations

1. **Problem Goal**: Remove minimum time worth of balloons to ensure no two consecutive balloons have the same color.

2. **Key Insight**: When we have a group of consecutive balloons with the same color, we need to remove all but one balloon from that group. To minimize time, we should keep the balloon that takes the maximum time to remove and remove all others.

3. **Greedy Strategy**: For each group of consecutive same-colored balloons:
   - Keep the balloon with maximum removal time
   - Remove all other balloons in the group
   - Add the sum of removal times of removed balloons to total cost

4. **Example Analysis**:
   - `colors = "abaac"`, `neededTime = [1,2,3,4,5]`
   - Groups: "a" at index 0, "b" at index 1, "aa" at indices 2,3, "c" at index 4
   - For group "aa" with times [3,4]: keep balloon with time 4, remove balloon with time 3
   - Total cost = 3

## Solution

1. **Two Pointer Approach**: Use `i` to mark the start of each group and `j` to find the end of consecutive same-colored balloons.

2. **Group Processing**: For each group of consecutive same-colored balloons:
   - Track `cur_max`: maximum removal time in the group (balloon to keep)
   - Track `cur_sum`: total removal time of all balloons in the group
   - Cost to remove group = `cur_sum - cur_max` (remove all except the most expensive)

3. **Edge Cases**: 
   - Single balloons (no consecutive duplicates) contribute 0 to the cost
   - Groups of size 2+ contribute `(sum of all times) - (max time)` to the cost

4. **Time Complexity**: O(n) - single pass through the array
5. **Space Complexity**: O(1) - only using constant extra space

**Step-by-step trace for "abaac" example**:
- i=0: colors[0]='a', no consecutive duplicate, i moves to 1
- i=1: colors[1]='b', no consecutive duplicate, i moves to 2  
- i=2: colors[2]='a', colors[3]='a' (consecutive duplicate found)
  - cur_max = max(3,4) = 4, cur_sum = 3+4 = 7
  - res += 7-4 = 3, i moves to 4
- i=4: colors[4]='c', no consecutive duplicate, done
- Result: 3

## Tags

- Array
- Greedy
- Two Pointers
- String Processing

