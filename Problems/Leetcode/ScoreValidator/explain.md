## Problem

https://leetcode.com/problems/score-validator/description/

You are given a string array `events`. Initially, `score = 0` and `counter = 0`. Each element in `events` is one of the following:

- `"0"`, `"1"`, `"2"`, `"3"`, `"4"`, `"6"`: Add that value to the total score.
- `"W"`: Increase the counter by 1. No score is added.
- `"WD"`: Add 1 to the total score.
- `"NB"`: Add 1 to the total score.

Process the array from left to right. Stop processing when either:
- All elements in `events` have been processed, or
- The counter becomes 10.

Return an integer array `[score, counter]`, where `score` is the final total score and `counter` is the final counter value.

**Constraints:**
- `1 <= events.length <= 1000`
- `events[i]` is one of `"0"`, `"1"`, `"2"`, `"3"`, `"4"`, `"6"`, `"W"`, `"WD"`, or `"NB"`.

## Observations

- There are only three distinct behaviors: add a numeric value, increment the counter, or add 1 to the score (`"WD"` and `"NB"` are equivalent here).
- A digit string can be detected with `str.isdigit()`, which cleanly separates it from `"W"`, `"WD"`, and `"NB"` without needing to enumerate all digit cases.
- Since `"WD"` and `"NB"` both just add 1 to the score, they fall into a single `else` branch — no individual handling needed.
- The only termination condition beyond exhausting the list is `counter == 10`, so a single check after each event update is sufficient.
- The problem note says the valid digit values are `"0"`, `"1"`, `"2"`, `"3"`, `"4"`, `"6"` — `"5"` is intentionally absent, but `isdigit()` still works because the constraints guarantee only valid inputs will appear.

## Solution

```python
class Solution:
    def scoreValidator(self, events: list[str]) -> list[int]:
        s, c = 0, 0
        for e in events:
            if e.isdigit():
                s += int(e)
            elif e == 'W':
                c += 1
            else:
                s += 1
            
            if c == 10:
                break
        return [s, c]
```

**Walk-through:**
1. Iterate through each event left to right.
2. If the event is a single digit string, convert and add it to `s`.
3. If it is `"W"`, increment `c`.
4. Otherwise (`"WD"` or `"NB"`), add 1 to `s`.
5. After each update, check if `c` has reached 10 and break early if so.
6. Return `[s, c]`.

**Complexity:**
- Time: $O(n)$ — single pass through the events array.
- Space: $O(1)$ — only two integer variables maintained.

# Tags

`simulation` `string`

