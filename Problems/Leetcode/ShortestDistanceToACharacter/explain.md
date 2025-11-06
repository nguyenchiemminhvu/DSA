## Problem

https://leetcode.com/problems/shortest-distance-to-a-character/

```
Given a string s and a character c that occurs in s, return an array of integers answer where answer.length == s.length and answer[i] is the distance from index i to the closest occurrence of character c in s.

The distance between two indices i and j is abs(i - j), where abs is the absolute value function.

Example 1:

Input: s = "loveleetcode", c = "e"
Output: [3,2,1,0,1,0,0,1,2,2,1,0]
Explanation: The character 'e' appears at indices 3, 5, 6, and 11 (0-indexed).
The closest occurrence of 'e' for index 0 is at index 3, so the distance is abs(0 - 3) = 3.
The closest occurrence of 'e' for index 1 is at index 3, so the distance is abs(1 - 3) = 2.
For index 4, there is a tie between the 'e' at index 3 and the 'e' at index 5, but the distance is still the same: abs(4 - 3) == abs(4 - 5) = 1.
The closest occurrence of 'e' for index 8 is at index 6, so the distance is abs(8 - 6) = 2.

Example 2:

Input: s = "aaab", c = "b"
Output: [3,2,1,0]

Constraints:

1 <= s.length <= 104
s[i] and c are lowercase English letters.
It is guaranteed that c occurs at least once in s.
```

## Observations

1. **Problem Understanding**: For each position in the string, we need to find the minimum distance to the nearest occurrence of character `c`.

2. **Key Insight**: Since we need to find the closest occurrence, for any position `i`, we only need to consider:
   - The nearest occurrence of `c` to the left of `i`
   - The nearest occurrence of `c` to the right of `i`
   - The minimum distance between these two

3. **Binary Search Approach**: The solution uses binary search (lower_bound) to efficiently find the position of the nearest occurrence of `c` that is greater than or equal to the current index.

4. **Edge Cases to Handle**:
   - When current index is before all occurrences of `c` (only consider the first occurrence)
   - When current index is after all occurrences of `c` (only consider the last occurrence)
   - When current index is between two occurrences (consider both and take minimum)

## Solution

The solution follows these steps:

1. **Preprocessing**: Collect all indices where character `c` occurs in the string and store them in array `arr`.

2. **Binary Search Implementation**: 
   - The `lower_bound` function finds the first position in `arr` that is greater than or equal to the target index
   - This efficiently locates the nearest occurrence of `c` at or after the current position

3. **Distance Calculation**: For each position `i` in the string:
   - Use binary search to find the position of the first occurrence of `c` at index `>= i`
   - Handle three cases:
     - **Case 1**: `found == len(arr)` - Current position is after all occurrences of `c`
       - Distance = `abs(i - arr[found - 1])` (distance to last occurrence)
     - **Case 2**: `found == 0` - Current position is before all occurrences of `c`
       - Distance = `abs(i - arr[found])` (distance to first occurrence)
     - **Case 3**: `0 < found < len(arr)` - Current position is between occurrences
       - Distance = `min(abs(i - arr[found]), abs(i - arr[found - 1]))` (minimum of distances to adjacent occurrences)

**Time Complexity**: O(n log k) where n is the length of string and k is the number of occurrences of character `c`
**Space Complexity**: O(k) for storing the indices of character `c`

**Example Walkthrough** with `s = "loveleetcode"`, `c = "e"`:
- Occurrences of 'e': [3, 5, 6, 11]
- For index 0: found = 0, distance = abs(0 - 3) = 3
- For index 4: found = 1, distance = min(abs(4 - 5), abs(4 - 3)) = min(1, 1) = 1
- For index 8: found = 3, distance = min(abs(8 - 11), abs(8 - 6)) = min(3, 2) = 2

# Tags

- Binary Search
- Array
- String Processing
- Two Pointers (conceptually)

