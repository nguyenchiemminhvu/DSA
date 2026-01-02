# Resulting String After Adjacent Removals

## Problem

https://leetcode.com/problems/resulting-string-after-adjacent-removals/description/

You are given a string `s` consisting of lowercase English letters.

You must repeatedly perform the following operation while the string `s` has at least two consecutive characters:

1. Remove the leftmost pair of adjacent characters in the string that are consecutive in the alphabet, in either order (e.g., 'a' and 'b', or 'b' and 'a').
2. Shift the remaining characters to the left to fill the gap.

Return the resulting string after no more operations can be performed.

**Note:** Consider the alphabet as circular, thus 'a' and 'z' are consecutive.

### Examples

**Example 1:**
```
Input: s = "abc"
Output: "c"
Explanation:
- Remove "ab" from the string, leaving "c" as the remaining string.
- No further operations are possible. Thus, the resulting string is "c".
```

**Example 2:**
```
Input: s = "adcb"
Output: ""
Explanation:
- Remove "dc" from the string, leaving "ab" as the remaining string.
- Remove "ab" from the string, leaving "" as the remaining string.
- No further operations are possible. Thus, the resulting string is "".
```

**Example 3:**
```
Input: s = "zadb"
Output: "db"
Explanation:
- Remove "za" from the string, leaving "db" as the remaining string.
- No further operations are possible. Thus, the resulting string is "db".
```

### Constraints

- `1 <= s.length <= 10^5`
- `s` consists only of lowercase English letters.

---

## Observations

1. **Consecutive Characters**: Two characters are consecutive if their alphabetical distance is 1 (e.g., 'a' and 'b', 'x' and 'y'). The order doesn't matter ('ab' or 'ba' both count).

2. **Circular Alphabet**: The alphabet wraps around, so 'z' and 'a' are also consecutive.

3. **Leftmost Pair**: We always remove the leftmost consecutive pair first. However, after removal, new pairs might form from previously non-adjacent characters.

4. **Stack Pattern**: This problem exhibits a classic stack pattern - when we add a new character, we need to check if it forms a consecutive pair with the most recently added character. If yes, we remove the previous character instead of adding the new one.

5. **Cascading Removals**: After removing a pair, previously non-adjacent characters become adjacent and might form new consecutive pairs. The stack naturally handles this cascading effect.

6. **ASCII Arithmetic**: We can convert characters to numbers (0-25) to simplify the consecutive check:
   - Character 'a' → 0, 'b' → 1, ..., 'z' → 25
   - Two characters are consecutive if their difference is ±1 (mod 26)

---

## Solution

### Algorithm: Stack-Based Greedy Approach

The key insight is that we don't need to repeatedly scan the string from left to right. Instead, we can use a **stack** to process characters one by one:

1. **Convert to Numbers**: Transform each character to a number (0-25) for easier arithmetic.

2. **Process Each Character**:
   - If the stack is empty, push the current character.
   - If the stack is not empty, check if the top of the stack and current character are consecutive:
     - Check if `(current - 1 + 26) % 26 == stack_top` (current is one more than top)
     - Check if `(current + 1) % 26 == stack_top` (current is one less than top)
   - If consecutive, **pop** the stack (remove the pair).
   - Otherwise, **push** the current character.

3. **Build Result**: Convert the remaining numbers in the stack back to characters.

### Why This Works

- **Greedy Property**: Removing the leftmost consecutive pair is always optimal because:
  - We process left to right, so we naturally handle leftmost pairs first.
  - The stack ensures that when we add a character, we immediately check if it can be removed with the previous character.
  
- **Cascading Effect**: When we remove a pair by popping from the stack, the next character we process will be compared with the new top of the stack, automatically handling cascading removals.

- **Circular Alphabet**: The modulo arithmetic `(val + 1) % 26` and `(val - 1 + 26) % 26` handles the wrap-around from 'z' to 'a'.

### Complexity Analysis

- **Time Complexity**: O(n) where n is the length of the string. Each character is pushed and popped at most once.
- **Space Complexity**: O(n) for the stack in the worst case (when no characters can be removed).

### Code Implementation

```python
class Solution:
    def resultingString(self, s: str) -> str:
        # Convert characters to numbers (0-25)
        s = [ord(c) - ord('a') for c in s]
        
        st = []  # Stack to store remaining characters
        
        for val in s:
            # Check if current character forms a consecutive pair with stack top
            if st and ((((val - 1) + 26) % 26) == st[-1] or ((val + 1) % 26) == st[-1]):
                # Consecutive pair found, remove the previous character
                st.pop()
            else:
                # No consecutive pair, add current character
                st.append(val)
        
        # Convert numbers back to characters
        return "".join([chr(ord('a') + val) for val in st])
```

### Line-by-Line Breakdown

1. **`s = [ord(c) - ord('a') for c in s]`**
   - Convert each character to a number: 'a' → 0, 'b' → 1, ..., 'z' → 25

2. **`st = []`**
   - Initialize an empty stack

3. **`for val in s:`**
   - Iterate through each character (as a number)

4. **`if st and ((((val - 1) + 26) % 26) == st[-1] or ((val + 1) % 26) == st[-1]):`**
   - Check two conditions:
     - Stack is not empty
     - Current character is consecutive with the top of the stack:
       - `((val - 1) + 26) % 26 == st[-1]`: top is one less than current (e.g., 'a' and 'b')
       - `((val + 1) % 26) == st[-1]`: top is one more than current (e.g., 'b' and 'a')
   - The `+ 26` in the first check handles negative numbers when val is 0

5. **`st.pop()`**
   - Remove the consecutive pair by popping the top

6. **`st.append(val)`**
   - If no consecutive pair, add the current character

7. **`return "".join([chr(ord('a') + val) for val in st])`**
   - Convert remaining numbers back to characters and join into a string

### Example Walkthrough

**Example: s = "adcb"**

1. Initial: `s = [0, 3, 2, 1]` (a=0, d=3, c=2, b=1)
2. Process 0 (a): stack = `[0]`
3. Process 3 (d): not consecutive with 0, stack = `[0, 3]`
4. Process 2 (c): consecutive with 3 (3-1=2), **pop 3**, stack = `[0]`
5. Process 1 (b): consecutive with 0 (0+1=1), **pop 0**, stack = `[]`
6. Result: `""` (empty string)

**Example: s = "zadb"**

1. Initial: `s = [25, 0, 3, 1]` (z=25, a=0, d=3, b=1)
2. Process 25 (z): stack = `[25]`
3. Process 0 (a): consecutive with 25 ((0-1+26)%26=25), **pop 25**, stack = `[]`
4. Process 3 (d): stack = `[3]`
5. Process 1 (b): not consecutive with 3, stack = `[3, 1]`
6. Result: `"db"`

---

## Key Takeaways

1. **Stack Pattern Recognition**: This is a classic "match and remove" problem that naturally fits the stack data structure.

2. **Modular Arithmetic**: Handling circular conditions (like the circular alphabet) can be elegantly solved with modulo operations.

3. **Greedy Approach**: Processing characters left-to-right with immediate removal when conditions are met is sufficient; no need for complex backtracking.

4. **Single Pass**: The solution requires only one pass through the string, making it very efficient.

# Tags

`Stack` `String` `Greedy` `Modular Arithmetic`

