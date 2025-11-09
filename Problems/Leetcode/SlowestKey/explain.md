## Problem

https://leetcode.com/problems/slowest-key/

```
A newly designed keypad was tested, where a tester pressed a sequence of n keys, one at a time.

You are given a string keysPressed of length n, where keysPressed[i] was the ith key pressed in the testing sequence, and a sorted list releaseTimes, where releaseTimes[i] was the time the ith key was released. Both arrays are 0-indexed. The 0th key was pressed at the time 0, and every subsequent key was pressed at the exact time the previous key was released.

The tester wants to know the key of the keypress that had the longest duration. The ith keypress had a duration of releaseTimes[i] - releaseTimes[i - 1], and the 0th keypress had a duration of releaseTimes[0].

Note that the same key could have been pressed multiple times during the test, and these multiple presses of the same key may not have had the same duration.

Return the key of the keypress that had the longest duration. If there are multiple such keypresses, return the lexicographically largest key of the keypresses.

Example 1:

Input: releaseTimes = [9,29,49,50], keysPressed = "cbcd"
Output: "c"
Explanation: The keypresses were as follows:
Keypress for 'c' had a duration of 9 (pressed at time 0 and released at time 9).
Keypress for 'b' had a duration of 29 - 9 = 20 (pressed at time 9 right after the release of the previous character and released at time 29).
Keypress for 'c' had a duration of 49 - 29 = 20 (pressed at time 29 right after the release of the previous character and released at time 49).
Keypress for 'd' had a duration of 50 - 49 = 1 (pressed at time 49 right after the release of the previous character and released at time 50).
The longest of these was the keypress for 'b' and the second keypress for 'c', both with duration 20.
'c' is lexicographically larger than 'b', so the answer is 'c'.

Example 2:

Input: releaseTimes = [12,23,36,46,62], keysPressed = "spuda"
Output: "a"
Explanation: The keypresses were as follows:
Keypress for 's' had a duration of 12.
Keypress for 'p' had a duration of 23 - 12 = 11.
Keypress for 'u' had a duration of 36 - 23 = 13.
Keypress for 'd' had a duration of 46 - 36 = 10.
Keypress for 'a' had a duration of 62 - 46 = 16.
The longest of these was the keypress for 'a' with duration 16.

Constraints:

releaseTimes.length == n
keysPressed.length == n
2 <= n <= 1000
1 <= releaseTimes[i] <= 109
releaseTimes[i] < releaseTimes[i+1]
keysPressed contains only lowercase English letters.
```

## Observations

1. **Problem Understanding**:
   - We need to find the key with the longest press duration
   - If multiple keys have the same longest duration, return the lexicographically largest one
   - Key press durations are calculated as the difference between consecutive release times
   - The first key's duration is simply `releaseTimes[0]` (pressed at time 0)

2. **Key Insights**:
   - **Duration Calculation**: For each key at position `i`:
     - If `i == 0`: duration = `releaseTimes[0] - 0 = releaseTimes[0]`
     - If `i > 0`: duration = `releaseTimes[i] - releaseTimes[i-1]`
   - **Maximum Tracking**: For each character, we need to track its maximum duration across all presses
   - **Lexicographic Ordering**: When durations are equal, choose the lexicographically larger character

3. **Edge Cases**:
   - Same character pressed multiple times with different durations
   - Multiple characters having the same maximum duration
   - Single character input

4. **Algorithm Strategy**:
   - Use a dictionary to track maximum duration for each character
   - Iterate through all keys in lexicographic order to ensure correct tie-breaking
   - Use `string.ascii_lowercase` to iterate in alphabetical order

## Solution

1. **Initialize tracking**:
   - `d = defaultdict(int)`: Track maximum duration for each character
   - `prev_time = 0`: Track previous release time for duration calculation

2. **Calculate durations**:
   - For each keypress: `duration = releaseTimes[i] - prev_time`
   - Update maximum duration: `d[k] = max(d[k], duration)`
   - Update previous time: `prev_time = releaseTimes[i]`

3. **Find result with lexicographic ordering**:
   - Iterate through alphabet in order: `string.ascii_lowercase`
   - Use `<=` comparison to prefer lexicographically larger characters
   - When `max_duration <= d[c]`, update both `max_duration` and `res`

**Example walkthrough** (releaseTimes = [9,29,49,50], keysPressed = "cbcd"):

| i | Key | Duration Calculation | Duration | d after update |
|---|-----|---------------------|----------|----------------|
| 0 | 'c' | 9 - 0 = 9          | 9        | {'c': 9}       |
| 1 | 'b' | 29 - 9 = 20        | 20       | {'c': 9, 'b': 20} |
| 2 | 'c' | 49 - 29 = 20       | 20       | {'c': 20, 'b': 20} |
| 3 | 'd' | 50 - 49 = 1        | 1        | {'c': 20, 'b': 20, 'd': 1} |

Final iteration through alphabet:
- 'b': max_duration = 20, res = 'b'
- 'c': 20 <= 20 (true), so max_duration = 20, res = 'c'
- 'd': 20 > 1, no update

Result: 'c' (lexicographically largest among keys with duration 20)

**Time Complexity**: O(n + 26) = O(n) where n is the number of keys
- O(n) to calculate durations for all keys
- O(26) to iterate through alphabet

**Space Complexity**: O(26) = O(1) for the dictionary storing at most 26 characters

**Key Design Decisions**:
- Using `defaultdict(int)` eliminates need for key existence checks
- Iterating through `string.ascii_lowercase` ensures lexicographic ordering
- Using `<=` in comparison ensures we pick the lexicographically largest character when durations are equal

# Tags
- Hash Table
- String
- Array
- Greedy

