## Problem

https://leetcode.com/problems/minimum-time-to-type-word-using-special-typewriter/

```
There is a special typewriter with lowercase English letters 'a' to 'z' arranged in a circle with a pointer. A character can only be typed if the pointer is pointing to that character. The pointer is initially pointing to the character 'a'.

Each second, you may perform one of the following operations:

Move the pointer one character counterclockwise or clockwise.
Type the character the pointer is currently on.
Given a string word, return the minimum number of seconds to type out the characters in word.

Example 1:

Input: word = "abc"
Output: 5
Explanation: 
The characters are printed as follows:
- Type the character 'a' in 1 second since the pointer is initially on 'a'.
- Move the pointer clockwise to 'b' in 1 second.
- Type the character 'b' in 1 second.
- Move the pointer clockwise to 'c' in 1 second.
- Type the character 'c' in 1 second.

Example 2:

Input: word = "bza"
Output: 7
Explanation:
The characters are printed as follows:
- Move the pointer clockwise to 'b' in 1 second.
- Type the character 'b' in 1 second.
- Move the pointer counterclockwise to 'z' in 2 seconds.
- Type the character 'z' in 1 second.
- Move the pointer clockwise to 'a' in 1 second.
- Type the character 'a' in 1 second.

Example 3:

Input: word = "zjpc"
Output: 34
Explanation:
The characters are printed as follows:
- Move the pointer counterclockwise to 'z' in 1 second.
- Type the character 'z' in 1 second.
- Move the pointer clockwise to 'j' in 10 seconds.
- Type the character 'j' in 1 second.
- Move the pointer clockwise to 'p' in 6 seconds.
- Type the character 'p' in 1 second.
- Move the pointer counterclockwise to 'c' in 13 seconds.
- Type the character 'c' in 1 second.

Constraints:

1 <= word.length <= 100
word consists of lowercase English letters.
```

## Observations

1. **Circular typewriter layout**: Letters 'a' to 'z' are arranged in a circle, so we can move clockwise or counterclockwise between any two letters.

2. **Two movement paths available**: From any letter to another, we can go either:
   - Clockwise (forward in alphabet with wraparound)
   - Counterclockwise (backward in alphabet with wraparound)

3. **Optimal path choice**: We always want to choose the shorter of the two possible paths to minimize movement time.

4. **Movement cost calculation**: For any two letters at positions `i` and `j` (0-based):
   - Direct distance: `|j - i|`
   - Wraparound distance: `26 - |j - i|`
   - We take the minimum of these two values

5. **Fixed starting position**: The pointer always starts at 'a', so we need to account for the initial movement from 'a' to the first character.

6. **Typing cost**: Each character requires exactly 1 second to type, regardless of which character it is.

## Solution

**Algorithm**: Greedy approach - for each character transition, calculate the minimum movement time and add the typing time.

**Time Complexity**: O(n) where n is the length of the word
**Space Complexity**: O(1)

**Key Components**:

1. **Distance calculation function** (`min_cost`):
   ```python
   def min_cost(a: str, b: str) -> int:
       vals = [ord(a) - ord('a'), ord(b) - ord('a')]
       vals.sort()
       cost = min(vals[1] - vals[0], 26 - vals[1] + vals[0])
       return cost
   ```
   - Converts characters to 0-25 positions
   - Sorts to ensure `vals[1] >= vals[0]`
   - Calculates both clockwise (`vals[1] - vals[0]`) and counterclockwise (`26 - vals[1] + vals[0]`) distances
   - Returns the minimum distance

2. **Main logic**:
   - Start with pointer at 'a'
   - For each character in the word:
     - Calculate minimum movement cost from current position
     - Add 1 second for typing the character
     - Update current position

**Step-by-step breakdown**:
- Initialize: `res = 0`, `cur_key = 'a'`
- For each character `c` in word:
  1. Add movement cost: `res += min_cost(cur_key, c)`
  2. Add typing cost: `res += 1`
  3. Update position: `cur_key = c`

**Example walkthrough** (word = "abc"):
- Start at 'a': cost = 0
- Type 'a': movement = 0, typing = 1, total = 1
- Move to 'b': movement = 1, typing = 1, total = 3  
- Move to 'c': movement = 1, typing = 1, total = 5

## Tags

string, greedy, simulation

