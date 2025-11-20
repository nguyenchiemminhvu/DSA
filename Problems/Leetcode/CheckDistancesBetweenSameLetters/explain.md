## Problem

https://leetcode.com/problems/check-distances-between-same-letters/description/

```
You are given a 0-indexed string s consisting of only lowercase English letters, where each letter in s appears exactly twice. You are also given a 0-indexed integer array distance of length 26.

Each letter in the alphabet is numbered from 0 to 25 (i.e. 'a' -> 0, 'b' -> 1, 'c' -> 2, ... , 'z' -> 25).

In a well-spaced string, the number of letters between the two occurrences of the ith letter is distance[i]. If the ith letter does not appear in s, then distance[i] can be ignored.

Return true if s is a well-spaced string, otherwise return false.

Example 1:

Input: s = "abaccb", distance = [1,3,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
Output: true
Explanation:
- 'a' appears at indices 0 and 2 so it satisfies distance[0] = 1.
- 'b' appears at indices 1 and 5 so it satisfies distance[1] = 3.
- 'c' appears at indices 3 and 4 so it satisfies distance[2] = 0.
Note that distance[3] = 5, but since 'd' does not appear in s, it can be ignored.
Return true because s is a well-spaced string.

Example 2:

Input: s = "aa", distance = [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
Output: false
Explanation:
- 'a' appears at indices 0 and 1 so there are zero letters between them.
Because distance[0] = 1, s is not a well-spaced string.

Constraints:

2 <= s.length <= 52
s consists only of lowercase English letters.
Each letter appears in s exactly twice.
distance.length == 26
0 <= distance[i] <= 50
```

## Observations

1. **Problem Understanding**: We need to check if each letter in the string has the correct distance between its two occurrences according to the `distance` array.

2. **Key Insights**:
   - Each letter appears exactly twice in the string
   - Distance is measured as the number of letters **between** the two occurrences (not including the letters themselves)
   - If a letter doesn't appear in the string, its distance requirement can be ignored

3. **Algorithm Analysis**:
   - We need to map each letter (a-z) to its required distance from the `distance` array
   - For each letter in the string, we need to calculate the actual distance between its two occurrences
   - Compare actual distances with required distances

4. **Edge Cases**:
   - Letters that appear at adjacent positions (distance = 0)
   - Letters that appear far apart
   - Only letters present in the string need to be validated

## Solution

**Approach: Hash Map Tracking**

The solution uses two hash maps:

1. **`fd` (frequency/distance mapping)**: Maps each letter ('a' to 'z') to its required distance from the `distance` array
   ```python
   fd[chr(ord('a') + i)] = dist  # Maps 'a' -> distance[0], 'b' -> distance[1], etc.
   ```

2. **`fs` (string tracking)**: Tracks the actual distance for each letter in the string
   - On first occurrence: stores the index
   - On second occurrence: calculates and stores the distance between occurrences

**Step-by-step execution**:

1. **Build required distance mapping**:
   ```python
   fd = {'a': distance[0], 'b': distance[1], ..., 'z': distance[25]}
   ```

2. **Calculate actual distances**:
   - For each character at index `i`:
     - First occurrence: `fs[c] = i` (store position)
     - Second occurrence: `fs[c] = i - fs[c] - 1` (calculate distance)
   
   The formula `i - fs[c] - 1` works because:
   - `i` is current position
   - `fs[c]` is first occurrence position  
   - `-1` excludes both occurrence positions from the count

3. **Validation**:
   - Compare each letter's actual distance (`fs[k]`) with required distance (`fd[k]`)
   - Return `False` if any mismatch found

**Example walkthrough** with `s = "abaccb"`, `distance = [1,3,0,...]`:

```
fd = {'a': 1, 'b': 3, 'c': 0, ...}

Processing string:
- i=0, c='a': fs = {'a': 0}
- i=1, c='b': fs = {'a': 0, 'b': 1}  
- i=2, c='a': fs = {'a': 1, 'b': 1}  # 2-0-1=1 letters between 'a's
- i=3, c='c': fs = {'a': 1, 'b': 1, 'c': 3}
- i=4, c='c': fs = {'a': 1, 'b': 1, 'c': 0}  # 4-3-1=0 letters between 'c's  
- i=5, c='b': fs = {'a': 1, 'b': 3, 'c': 0}  # 5-1-1=3 letters between 'b's

Validation: fs['a']=1 == fd['a']=1 ✓, fs['b']=3 == fd['b']=3 ✓, fs['c']=0 == fd['c']=0 ✓
```

**Time Complexity**: O(n) where n is the length of string  
**Space Complexity**: O(1) since we have at most 26 letters

# Tags

Hash Table, String, Array

