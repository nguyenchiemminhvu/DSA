## Problem Description

https://leetcode.com/problems/isomorphic-strings/

```
Given two strings s and t, determine if they are isomorphic.

Two strings s and t are isomorphic if the characters in s can be replaced to get t.

All occurrences of a character must be replaced with another character while preserving the order of characters. No two characters may map to the same character, but a character may map to itself.

Example 1:

Input: s = "egg", t = "add"

Output: true

Explanation:

The strings s and t can be made identical by:

Mapping 'e' to 'a'.
Mapping 'g' to 'd'.

Example 2:

Input: s = "foo", t = "bar"

Output: false

Explanation:

The strings s and t can not be made identical as 'o' needs to be mapped to both 'a' and 'r'.

Example 3:

Input: s = "paper", t = "title"

Output: true

Constraints:

1 <= s.length <= 5 * 104
t.length == s.length
s and t consist of any valid ascii character.
```

## Observations

To determine if two strings are isomorphic, we need to understand what "isomorphic" means:

1. **One-to-One Mapping**: Each character in string `s` must map to exactly one character in string `t`
2. **Consistency**: If character 'a' maps to character 'x', then ALL occurrences of 'a' must map to 'x'
3. **Uniqueness**: No two different characters in `s` can map to the same character in `t`

### Key Insights:

- **Bidirectional Mapping**: We need to check mapping in both directions (s→t and t→s)
- **Why Both Directions?**: Consider `s = "ab"`, `t = "aa"`:
  - Forward mapping: 'a'→'a', 'b'→'a' (seems okay)
  - Reverse mapping: 'a'→'a', 'a'→'b' (conflict! Same char mapping to different chars)

### Example Walkthrough:

**Example 1**: `s = "egg"`, `t = "add"`
- 'e' → 'a' (position 0)
- 'g' → 'd' (position 1 and 2)
- ✅ Valid: Each character has consistent, unique mapping

**Example 2**: `s = "foo"`, `t = "bar"`
- 'f' → 'b' (position 0)
- 'o' → 'a' (position 1)
- 'o' → 'r' (position 2) ❌ Conflict! 'o' trying to map to both 'a' and 'r'

## Solution

### Approach: Two Hash Maps (Dictionaries)

We use two dictionaries to track mappings in both directions:
- `sd` (s dictionary): Maps characters from `s` to `t`
- `td` (t dictionary): Maps characters from `t` to `s`

```python
from typing import Dict

class Solution:
    def isIsomorphic(self, s: str, t: str) -> bool:
        sd : Dict[str, str] = {}  # s -> t mapping
        td : Dict[str, str] = {}  # t -> s mapping
        
        for i in range(len(s)):
            # Check if current character in s already has a mapping
            if s[i] in sd and sd[s[i]] != t[i]:
                return False
            
            # Check if current character in t already has a mapping
            if t[i] in td and td[t[i]] != s[i]:
                return False
            
            # Create/update the bidirectional mapping
            sd[s[i]] = t[i]
            td[t[i]] = s[i]
        
        return True
```

### Step-by-Step Breakdown:

#### Step 1: Initialize Two Dictionaries
```python
sd : Dict[str, str] = {}  # Maps s[i] -> t[i]
td : Dict[str, str] = {}  # Maps t[i] -> s[i]
```

#### Step 2: Iterate Through Both Strings Simultaneously
```python
for i in range(len(s)):
    # Process s[i] and t[i] at the same position
```

#### Step 3: Check Forward Mapping (s → t)
```python
if s[i] in sd and sd[s[i]] != t[i]:
    return False
```
**What this checks**: If we've seen `s[i]` before, does it map to the same character in `t`?

#### Step 4: Check Reverse Mapping (t → s)
```python
if t[i] in td and td[t[i]] != s[i]:
    return False
```
**What this checks**: If we've seen `t[i]` before, does it map to the same character in `s`?

#### Step 5: Update Both Mappings
```python
sd[s[i]] = t[i]  # Record s[i] -> t[i]
td[t[i]] = s[i]  # Record t[i] -> s[i]
```

### Detailed Example Trace:

**Input**: `s = "egg"`, `t = "add"`

| i | s[i] | t[i] | sd before | td before | Check sd | Check td | sd after | td after | Result |
|---|------|------|-----------|-----------|----------|----------|----------|----------|---------|
| 0 | 'e'  | 'a'  | {}        | {}        | ✅ Pass   | ✅ Pass   | {'e':'a'} | {'a':'e'} | Continue |
| 1 | 'g'  | 'd'  | {'e':'a'} | {'a':'e'} | ✅ Pass   | ✅ Pass   | {'e':'a', 'g':'d'} | {'a':'e', 'd':'g'} | Continue |
| 2 | 'g'  | 'd'  | {'e':'a', 'g':'d'} | {'a':'e', 'd':'g'} | ✅ 'g' maps to 'd' (consistent) | ✅ 'd' maps to 'g' (consistent) | No change | No change | Continue |

**Result**: `True` ✅

**Counter-example**: `s = "foo"`, `t = "bar"`

| i | s[i] | t[i] | sd before | td before | Check sd | Check td | Result |
|---|------|------|-----------|-----------|----------|----------|---------|
| 0 | 'f'  | 'b'  | {}        | {}        | ✅ Pass   | ✅ Pass   | Continue |
| 1 | 'o'  | 'a'  | {'f':'b'} | {'b':'f'} | ✅ Pass   | ✅ Pass   | Continue |
| 2 | 'o'  | 'r'  | {'f':'b', 'o':'a'} | {'b':'f', 'a':'o'} | ❌ 'o' exists and maps to 'a', but t[2]='r' | - | Return False |

**Result**: `False` ❌

### Complexity Analysis:

- **Time Complexity**: O(n) where n is the length of the strings
  - We iterate through each character once
  - Dictionary operations (lookup, insert) are O(1) on average

- **Space Complexity**: O(k) where k is the number of unique characters
  - In worst case, O(n) if all characters are unique
  - We store at most n entries in each dictionary

### Why This Solution Works:

1. **Handles One-to-One Mapping**: The forward check ensures each character in `s` maps to exactly one character in `t`
2. **Handles Many-to-One Prevention**: The reverse check ensures no two characters in `s` map to the same character in `t`
3. **Efficient**: Single pass through the strings with constant-time dictionary operations



## Tags

array, string, hash table