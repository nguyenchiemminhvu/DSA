## Problem

https://leetcode.com/problems/rings-and-rods/description/

```
There are n rings and each ring is either red, green, or blue. The rings are distributed across ten rods labeled from 0 to 9.

You are given a string rings of length 2n that describes the n rings that are placed onto the rods. Every two characters in rings forms a color-position pair that is used to describe each ring where:

The first character of the ith pair denotes the ith ring's color ('R', 'G', 'B').
The second character of the ith pair denotes the rod that the ith ring is placed on ('0' to '9').
For example, "R3G2B1" describes n == 3 rings: a red ring placed onto the rod labeled 3, a green ring placed onto the rod labeled 2, and a blue ring placed onto the rod labeled 1.

Return the number of rods that have all three colors of rings on them.

Example 1:

Input: rings = "B0B6G0R6R0R6G9"
Output: 1
Explanation: 
- The rod labeled 0 holds 3 rings with all colors: red, green, and blue.
- The rod labeled 6 holds 3 rings, but it only has red and blue.
- The rod labeled 9 holds only a green ring.
Thus, the number of rods with all three colors is 1.

Example 2:

Input: rings = "B0R0G0R9R0B0G0"
Output: 1
Explanation: 
- The rod labeled 0 holds 6 rings with all colors: red, green, and blue.
- The rod labeled 9 holds only a red ring.
Thus, the number of rods with all three colors is 1.

Example 3:

Input: rings = "G4"
Output: 0
Explanation: 
Only one ring is given. Thus, no rods have all three colors.

Constraints:

rings.length == 2 * n
1 <= n <= 100
rings[i] where i is even is either 'R', 'G', or 'B' (0-indexed).
rings[i] where i is odd is a digit from '0' to '9' (0-indexed).
```

## Observations

1. **Input Format**: The string `rings` contains pairs of characters where:
   - Even indices (0, 2, 4, ...) contain colors: 'R', 'G', or 'B'
   - Odd indices (1, 3, 5, ...) contain rod positions: '0' to '9'

2. **Goal**: Count how many rods have all three colors (Red, Green, Blue) on them.

3. **Key Insight**: We need to track which colors are present on each rod, not how many rings of each color.

4. **Data Structure Choice**: Using a dictionary with sets is efficient because:
   - Dictionary keys represent rod positions
   - Set values automatically handle duplicates (multiple rings of same color on same rod)
   - Set size of 3 means all three colors are present

5. **Parsing Strategy**: Iterate through the string by steps of 2, treating each pair as (color, position).

## Solution

**Algorithm Explanation:**

1. **Initialize**: Create an empty dictionary `f` to store rod positions as keys and sets of colors as values.

2. **Parse Input**: 
   - Loop through odd indices (1, 3, 5, ...) to get positions
   - For each position `i`, get the color from `rings[i-1]` and position from `rings[i]`

3. **Track Colors per Rod**:
   - If rod position doesn't exist in dictionary, create a new set for it
   - Add the color to the set for that rod position

4. **Count Complete Rods**: Count how many rods have exactly 3 colors (set size == 3)

**Time Complexity**: O(n) where n is the number of rings (length of string / 2)
**Space Complexity**: O(1) since there are at most 10 rods, each storing at most 3 colors

**Example Walkthrough** (`rings = "B0B6G0R6R0R6G9"`):
- `f = {'0': {'B', 'G', 'R'}, '6': {'B', 'R'}, '9': {'G'}}`
- Only rod '0' has all 3 colors, so return 1

# Tags

- Hash Table
- String
- Simulation

