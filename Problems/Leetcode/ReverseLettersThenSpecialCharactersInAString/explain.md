# Reverse Letters Then Special Characters In A String

## Problem

https://leetcode.com/problems/reverse-letters-then-special-characters-in-a-string/description/

You are given a string `s` consisting of lowercase English letters and special characters.

Your task is to perform these in order:

1. **Reverse the lowercase letters** and place them back into the positions originally occupied by letters.
2. **Reverse the special characters** and place them back into the positions originally occupied by special characters.

Return the resulting string after performing the reversals.

### Examples

**Example 1:**
```
Input: s = ")ebc#da@f("
Output: "(fad@cb#e)"

Explanation:
- The letters in the string are ['e', 'b', 'c', 'd', 'a', 'f']
  Reversing them gives ['f', 'a', 'd', 'c', 'b', 'e']
  s becomes ")fad#cb@e("
  
- The special characters in the string are [')', '#', '@', '(']
  Reversing them gives ['(', '@', '#', ')']
  s becomes "(fad@cb#e)"
```

**Example 2:**
```
Input: s = "z"
Output: "z"

Explanation:
The string contains only one letter, and reversing it does not change the string.
There are no special characters.
```

**Example 3:**
```
Input: s = "!@#$%^&*()"
Output: ")(*&^%$#@!"

Explanation:
The string contains no letters. The string contains all special characters,
so reversing the special characters reverses the whole string.
```

### Constraints

- `1 <= s.length <= 100`
- `s` consists only of lowercase English letters and the special characters in `"!@#$%^&*()"`

---

## Observations

1. **Two Independent Reversals**: The problem requires us to reverse two groups independently:
   - All lowercase letters (keeping their relative positions among letters)
   - All special characters (keeping their relative positions among special characters)

2. **Position Preservation**: The key insight is that letters stay in letter positions and special characters stay in special character positions. We're not mixing them.

3. **Two-Pass Approach**: 
   - First pass: Extract letters and special characters into separate lists
   - Second pass: Rebuild the string by consuming from the reversed lists

4. **Stack-like Behavior**: Using `pop()` on lists naturally gives us the reversed order without explicitly reversing the lists.

5. **Character Classification**: We can use `str.islower()` to identify lowercase letters, and treat everything else as special characters.

---

## Solution

### Approach: Two-Pass with Separate Lists

The solution uses a clever two-pass algorithm:

**Pass 1: Extraction**
- Iterate through the string once
- Separate characters into two lists:
  - `letters`: contains all lowercase letters in original order
  - `others`: contains all special characters in original order

**Pass 2: Reconstruction**
- Iterate through the original string again
- For each position:
  - If original character was a letter → take from end of `letters` list (using `pop()`)
  - If original character was special → take from end of `others` list (using `pop()`)

### Why This Works

- `list.pop()` removes and returns the **last** element
- Since we filled the lists in forward order, popping gives us reversed order
- By checking the original character type, we ensure letters go back to letter positions and special characters go back to special positions

### Code Implementation

```python
class Solution:
    def reverseByType(self, s: str) -> str:
        # Step 1: Extract letters and special characters
        letters = []
        others = []
        for c in s:
            if c.islower():  # Check if lowercase letter
                letters.append(c)
            else:
                others.append(c)
        
        # Step 2: Rebuild string with reversed order
        out = []
        for c in s:
            if c.islower():
                out.append(letters.pop())  # Take from end => reversed
            else:
                out.append(others.pop())
        
        return "".join(out)
```

### Example Trace

For `s = ")ebc#da@f("`:

**After Pass 1:**
- `letters = ['e', 'b', 'c', 'd', 'a', 'f']`
- `others = [')', '#', '@', '(']`

**During Pass 2:**
```
Position 0: ')' is special → pop from others → '(' → out = ['(']
Position 1: 'e' is letter → pop from letters → 'f' → out = ['(', 'f']
Position 2: 'b' is letter → pop from letters → 'a' → out = ['(', 'f', 'a']
Position 3: 'c' is letter → pop from letters → 'd' → out = ['(', 'f', 'a', 'd']
Position 4: '#' is special → pop from others → '@' → out = ['(', 'f', 'a', 'd', '@']
Position 5: 'd' is letter → pop from letters → 'c' → out = ['(', 'f', 'a', 'd', '@', 'c']
Position 6: 'a' is letter → pop from letters → 'b' → out = ['(', 'f', 'a', 'd', '@', 'c', 'b']
Position 7: '@' is special → pop from others → '#' → out = ['(', 'f', 'a', 'd', '@', 'c', 'b', '#']
Position 8: 'f' is letter → pop from letters → 'e' → out = ['(', 'f', 'a', 'd', '@', 'c', 'b', '#', 'e']
Position 9: '(' is special → pop from others → ')' → out = ['(', 'f', 'a', 'd', '@', 'c', 'b', '#', 'e', ')']
```

**Result:** `"(fad@cb#e)"`

### Complexity Analysis

**Time Complexity: O(n)**
- First pass: O(n) to extract letters and special characters
- Second pass: O(n) to rebuild the string
- Total: O(n) + O(n) = O(n)

**Space Complexity: O(n)**
- `letters` list: O(k) where k = number of letters
- `others` list: O(m) where m = number of special characters
- `out` list: O(n)
- Total: O(n) where n = length of input string

### Alternative Approaches

**1. Explicit Reversal**
Instead of using `pop()`, explicitly reverse the lists:

```python
def reverseByType(self, s: str) -> str:
    letters = [c for c in s if c.islower()]
    others = [c for c in s if not c.islower()]
    
    letters.reverse()
    others.reverse()
    
    li = oi = 0
    out = []
    for c in s:
        if c.islower():
            out.append(letters[li])
            li += 1
        else:
            out.append(others[oi])
            oi += 1
    
    return "".join(out)
```

**2. Two-Pointer In-Place (if using list)**
Convert to list, use two pointers to swap letters and special characters separately:

```python
def reverseByType(self, s: str) -> str:
    arr = list(s)
    n = len(arr)
    
    # Reverse letters
    left = 0
    right = n - 1
    while left < right:
        while left < right and not arr[left].islower():
            left += 1
        while left < right and not arr[right].islower():
            right -= 1
        if left < right:
            arr[left], arr[right] = arr[right], arr[left]
            left += 1
            right -= 1
    
    # Reverse special characters
    left = 0
    right = n - 1
    while left < right:
        while left < right and arr[left].islower():
            left += 1
        while left < right and arr[right].islower():
            right -= 1
        if left < right:
            arr[left], arr[right] = arr[right], arr[left]
            left += 1
            right -= 1
    
    return "".join(arr)
```

### Key Takeaways

1. **Problem Decomposition**: Break the problem into two independent sub-problems (reverse letters, reverse special characters)
2. **Stack Properties**: Using `pop()` on a list naturally reverses order
3. **Position Tracking**: Preserve original positions by checking character types in the original string
4. **Clean and Readable**: The solution is straightforward and easy to understand
5. **Efficient**: Linear time and space complexity, which is optimal for this problem

# Tags

`string` `two-pointers` `array` `simulation`

