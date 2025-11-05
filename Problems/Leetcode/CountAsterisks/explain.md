## Problem

https://leetcode.com/problems/count-asterisks/description/

```
You are given a string s, where every two consecutive vertical bars '|' are grouped into a pair. In other words, the 1st and 2nd '|' make a pair, the 3rd and 4th '|' make a pair, and so forth.

Return the number of '*' in s, excluding the '*' between each pair of '|'.

Note that each '|' will belong to exactly one pair.

Example 1:

Input: s = "l|*e*et|c**o|*de|"
Output: 2
Explanation: The considered characters are underlined: "l|*e*et|c**o|*de|".
The characters between the first and second '|' are excluded from the answer.
Also, the characters between the third and fourth '|' are excluded from the answer.
There are 2 asterisks considered. Therefore, we return 2.

Example 2:

Input: s = "iamprogrammer"
Output: 0
Explanation: In this example, there are no asterisks in s. Therefore, we return 0.

Example 3:

Input: s = "yo|uar|e**|b|e***au|tifu|l"
Output: 5
Explanation: The considered characters are underlined: "yo|uar|e**|b|e***au|tifu|l". There are 5 asterisks considered. Therefore, we return 5.

Constraints:

1 <= s.length <= 1000
s consists of lowercase English letters, vertical bars '|', and asterisks '*'.
s contains an even number of vertical bars '|'.
```

## Observations

1. **Problem Pattern**: We need to count asterisks (*) that are NOT between pairs of vertical bars (|)
2. **Pairing Rule**: Vertical bars are paired consecutively - 1st with 2nd, 3rd with 4th, etc.
3. **State Tracking**: We need to track whether we're currently inside a pair of vertical bars or outside
4. **Toggle Mechanism**: Each '|' character toggles our state between "inside pair" and "outside pair"
5. **Counting Rule**: Only count asterisks when we're outside of vertical bar pairs

## Solution

**Approach**: Single pass with state tracking

**Algorithm**:
1. Initialize `count = 0` (asterisk counter) and `enabled = False` (inside pair flag)
2. Iterate through each character in the string:
   - If character is '|': toggle the `enabled` flag (enter/exit pair state)
   - If character is '*' and we're NOT inside a pair (`not enabled`): increment count
3. Return the total count

**Key Insight**: The `enabled` flag starts as `False`, meaning we start outside any pair. Each '|' flips this state:
- First '|': `enabled` becomes `True` (entering pair)
- Second '|': `enabled` becomes `False` (exiting pair)
- Third '|': `enabled` becomes `True` (entering next pair)
- And so on...

**Example Trace** (`s = "l|*e*et|c**o|*de|"`):
- 'l': not '|', not '*' → continue
- '|': toggle enabled (False → True) → now inside pair
- '*': inside pair (enabled=True) → don't count
- 'e': inside pair → continue
- '*': inside pair → don't count
- 'e': inside pair → continue
- 't': inside pair → continue
- '|': toggle enabled (True → False) → now outside pair
- 'c': outside pair, not '*' → continue
- '*': outside pair (enabled=False) → count++ (count=1)
- '*': outside pair → count++ (count=2)
- 'o': outside pair, not '*' → continue
- '|': toggle enabled (False → True) → now inside pair
- '*': inside pair → don't count
- 'd': inside pair → continue
- 'e': inside pair → continue
- '|': toggle enabled (True → False) → now outside pair
- Result: count = 2

**Time Complexity**: O(n) - single pass through the string
**Space Complexity**: O(1) - only using constant extra space

# Tags

String, Simulation, State Machine

