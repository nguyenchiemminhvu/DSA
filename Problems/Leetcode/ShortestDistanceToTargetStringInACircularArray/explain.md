## Problem

https://leetcode.com/problems/shortest-distance-to-target-string-in-a-circular-array/description/

```
You are given a 0-indexed circular string array words and a string target. A circular array means that the array's end connects to the array's beginning.

Formally, the next element of words[i] is words[(i + 1) % n] and the previous element of words[i] is words[(i - 1 + n) % n], where n is the length of words.
Starting from startIndex, you can move to either the next word or the previous word with 1 step at a time.

Return the shortest distance needed to reach the string target. If the string target does not exist in words, return -1.

Example 1:

Input: words = ["hello","i","am","leetcode","hello"], target = "hello", startIndex = 1
Output: 1
Explanation: We start from index 1 and can reach "hello" by
- moving 3 units to the right to reach index 4.
- moving 2 units to the left to reach index 4.
- moving 4 units to the right to reach index 0.
- moving 1 unit to the left to reach index 0.
The shortest distance to reach "hello" is 1.

Example 2:

Input: words = ["a","b","leetcode"], target = "leetcode", startIndex = 0
Output: 1
Explanation: We start from index 0 and can reach "leetcode" by
- moving 2 units to the right to reach index 3.
- moving 1 unit to the left to reach index 3.
The shortest distance to reach "leetcode" is 1.

Example 3:

Input: words = ["i","eat","leetcode"], target = "ate", startIndex = 0
Output: -1
Explanation: Since "ate" does not exist in words, we return -1.

Constraints:

1 <= words.length <= 100
1 <= words[i].length <= 100
words[i] and target consist of only lowercase English letters.
0 <= startIndex < words.length
```

## Observations

This problem requires finding the shortest distance to a target string in a circular array. Key insights:

1. **Circular Array Property**: In a circular array, there are only two possible paths between any two points:
   - Clockwise direction: `(target_index - start_index + n) % n`
   - Counterclockwise direction: `(start_index - target_index + n) % n`

2. **Multiple Targets**: The target string might appear multiple times. We need to find the closest occurrence.

3. **Optimization with Binary Search**: Instead of checking all target occurrences, we can use binary search to efficiently find the two closest positions (one on each side of startIndex).

4. **Edge Cases**: 
   - Target doesn't exist → return -1
   - startIndex is before/after all targets → consider wrap-around distances

## Solution

The solution uses a binary search approach for optimization:

### Algorithm Steps:

1. **Find All Target Positions**: 
   - Scan the array and collect indices where `words[i] == target`
   - If no matches found, return -1

2. **Binary Search for Closest Positions**:
   - Use `upper_bound` to find the first target position ≥ startIndex
   - This efficiently identifies the two closest target positions

3. **Calculate Minimum Distance**:
   - **Case 1**: `upper == len(found)` (startIndex > all targets)
     - Distance = min(direct to last, wrap-around to first)
   - **Case 2**: `upper == 0` (startIndex < all targets)  
     - Distance = min(direct to first, wrap-around to last)
   - **Case 3**: Between two targets
     - Distance = min(forward to next, backward to previous)

### Key Functions:

- **upper_bound**: Binary search to find insertion point
- **Distance Formulas**:
  - Forward: `target_pos - start_pos`
  - Backward: `start_pos - target_pos` 
  - Wrap-around: `n - |pos1 - pos2|`

### Time Complexity: O(n + k log k) where k is number of target occurrences
### Space Complexity: O(k) for storing target positions

# Tags

array, string, binary search