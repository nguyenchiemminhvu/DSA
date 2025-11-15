## Problem

https://leetcode.com/problems/divide-a-string-into-groups-of-size-k/description/

```
A string s can be partitioned into groups of size k using the following procedure:

The first group consists of the first k characters of the string, the second group consists of the next k characters of the string, and so on. Each element can be a part of exactly one group.
For the last group, if the string does not have k characters remaining, a character fill is used to complete the group.
Note that the partition is done so that after removing the fill character from the last group (if it exists) and concatenating all the groups in order, the resultant string should be s.

Given the string s, the size of each group k and the character fill, return a string array denoting the composition of every group s has been divided into, using the above procedure.

Example 1:

Input: s = "abcdefghi", k = 3, fill = "x"
Output: ["abc","def","ghi"]
Explanation:
The first 3 characters "abc" form the first group.
The next 3 characters "def" form the second group.
The last 3 characters "ghi" form the third group.
Since all groups can be completely filled by characters from the string, we do not need to use fill.
Thus, the groups formed are "abc", "def", and "ghi".

Example 2:

Input: s = "abcdefghij", k = 3, fill = "x"
Output: ["abc","def","ghi","jxx"]
Explanation:
Similar to the previous example, we are forming the first three groups "abc", "def", and "ghi".
For the last group, we can only use the character 'j' from the string. To complete this group, we add 'x' twice.
Thus, the 4 groups formed are "abc", "def", "ghi", and "jxx".

Constraints:

1 <= s.length <= 100
s consists of lowercase English letters only.
1 <= k <= 100
fill is a lowercase English letter.
```

## Observations

1. **Linear Processing**: We need to process the string from left to right in chunks of size `k`, making this a straightforward iteration problem.

2. **Padding Strategy**: Only the last group might need padding with the fill character if the remaining characters are fewer than `k`.

3. **Simple Iteration Pattern**: We can use `range(0, n, k)` to iterate through starting positions of each group, automatically handling the step size.

4. **Boundary Handling**: For extracting substrings, we need `s[i:min(i+k, n)]` to safely handle the last group without going out of bounds.

5. **Fill Calculation**: The number of fill characters needed is always `k - len(current_substring)`, which is 0 for complete groups and positive for the incomplete last group.

6. **Edge Cases**: 
   - If string length is exactly divisible by `k`, no padding needed
   - If `k = 1`, each character becomes its own group
   - The fill character is only used for the last group if needed

## Solution

**Approach: Sequential Grouping with Padding**

The solution uses a straightforward approach: iterate through the string in steps of `k`, extract each substring, and pad the last group if necessary.

**Algorithm:**
1. **Initialize**: Get string length `n` and create empty result list
2. **Iterate through groups**: Use `range(0, n, k)` to get starting position of each group  
3. **Extract substring**: Use `s[i:min(i + k, n)]` to safely extract up to `k` characters
4. **Add padding**: Append `fill * (k - len(sub))` fill characters to make group exactly `k` characters
5. **Store result**: Add the completed group to result list

**Implementation Details:**
```python
def divideString(self, s: str, k: int, fill: str) -> List[str]:
    n = len(s)
    res = []
    for i in range(0, n, k):                    # Iterate by steps of k
        sub = s[i:min(i + k, n)]                # Extract substring safely
        sub += fill * (k - len(sub))            # Add padding if needed
        res.append(sub)                         # Store complete group
    return res
```

**Example Walkthrough:**

For `s = "abcdefghij", k = 3, fill = "x"`:
- i=0: sub="abc", len=3, padding=0 → "abc"
- i=3: sub="def", len=3, padding=0 → "def"  
- i=6: sub="ghi", len=3, padding=0 → "ghi"
- i=9: sub="j", len=1, padding=2 → "jxx"

Result: `["abc","def","ghi","jxx"]`

**Time Complexity:** O(n) - single pass through the string
**Space Complexity:** O(n) - storing the result groups (excluding input)

**Why This Works:**
- `min(i + k, n)` prevents index out of bounds for the last group
- `fill * (k - len(sub))` automatically calculates correct padding:
  - Complete groups: `len(sub) = k`, so `k - k = 0` fill characters
  - Incomplete last group: `len(sub) < k`, so `k - len(sub) > 0` fill characters
- The approach handles all edge cases naturally without special conditions

# Tags
String Manipulation, Array, Iteration

