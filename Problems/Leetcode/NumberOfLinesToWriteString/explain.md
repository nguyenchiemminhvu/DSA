## Problem

https://leetcode.com/problems/number-of-lines-to-write-string/

```
You are given a string s of lowercase English letters and an array widths denoting how many pixels wide each lowercase English letter is. Specifically, widths[0] is the width of 'a', widths[1] is the width of 'b', and so on.

You are trying to write s across several lines, where each line is no longer than 100 pixels. Starting at the beginning of s, write as many letters on the first line such that the total width does not exceed 100 pixels. Then, from where you stopped in s, continue writing as many letters as you can on the second line. Continue this process until you have written all of s.

Return an array result of length 2 where:

result[0] is the total number of lines.
result[1] is the width of the last line in pixels.

Example 1:

Input: widths = [10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10], s = "abcdefghijklmnopqrstuvwxyz"
Output: [3,60]
Explanation: You can write s as follows:
abcdefghij  // 100 pixels wide
klmnopqrst  // 100 pixels wide
uvwxyz      // 60 pixels wide
There are a total of 3 lines, and the last line is 60 pixels wide.

Example 2:

Input: widths = [4,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10], s = "bbbcccdddaaa"
Output: [2,4]
Explanation: You can write s as follows:
bbbcccdddaa  // 98 pixels wide
a            // 4 pixels wide
There are a total of 2 lines, and the last line is 4 pixels wide.

Constraints:

widths.length == 26
2 <= widths[i] <= 10
1 <= s.length <= 1000
s contains only lowercase English letters.
```

## Observations

1. **Width Mapping**: Each character 'a' to 'z' has a corresponding width in the `widths` array, where `widths[0]` is the width of 'a', `widths[1]` is the width of 'b', etc.

2. **Line Constraint**: Each line can contain at most 100 pixels worth of characters.

3. **Greedy Approach**: We should fit as many characters as possible on each line before moving to the next line.

4. **Character Index Calculation**: For any character `c`, its width can be found at index `ord(c) - ord('a')` in the widths array.

5. **Edge Cases**: 
   - When adding a character would exceed 100 pixels, we need to start a new line
   - The last line might not be full (less than 100 pixels)

## Solution

The solution uses a simple greedy simulation approach:

### Algorithm:
1. **Initialize Counters**: Start with `count = 1` (at least one line) and `cur = 0` (current line width)

2. **Process Each Character**: 
   - For each character in the string, find its width using `w[ord(c) - ord('a')]`
   - Check if adding this character would exceed 100 pixels

3. **Line Management**:
   - If `cur + pix > 100`: Start a new line (increment `count`, reset `cur = 0`)
   - Add the character width to current line: `cur += pix`

4. **Return Result**: `[count, cur]` where `count` is total lines and `cur` is the width of the last line

### Key Insights:
- **Greedy Strategy**: Always try to fit the current character on the current line first
- **Index Mapping**: `ord(c) - ord('a')` converts character to array index (0-25)
- **Boundary Check**: Check before adding, not after, to avoid overflow

### Time Complexity: O(n) where n is the length of string s
### Space Complexity: O(1) - only using constant extra space

### Example Walkthrough:
For `widths = [4,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10]`, `s = "bbbcccdddaaa"`:
- 'b' (width=10): cur = 10
- 'b' (width=10): cur = 20
- 'b' (width=10): cur = 30
- 'c' (width=10): cur = 40
- 'c' (width=10): cur = 50
- 'c' (width=10): cur = 60
- 'd' (width=10): cur = 70
- 'd' (width=10): cur = 80
- 'd' (width=10): cur = 90
- 'a' (width=4): cur = 94
- 'a' (width=4): 94+4 > 100, so count=2, cur=0, then cur=4
- 'a' (width=4): cur = 8

Result: [2, 4] - 2 lines total, last line is 4 pixels wide

# Tags

- String Processing
- Simulation
- Greedy Algorithm
- Array Indexing

