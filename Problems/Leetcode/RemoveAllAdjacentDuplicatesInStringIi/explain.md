## Problem

https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string-ii/description/

You are given a string `s` and an integer `k`. A **k duplicate removal** consists of choosing `k` adjacent and equal letters from `s` and removing them, causing the left and right side of the deleted substring to concatenate together.

We repeatedly make k duplicate removals on `s` until we no longer can.

Return the final string after all such duplicate removals have been made. It is guaranteed that the answer is unique.

### Examples

**Example 1:**
```
Input: s = "abcd", k = 2
Output: "abcd"
Explanation: There's nothing to delete.
```

**Example 2:**
```
Input: s = "deeedbbcccbdaa", k = 3
Output: "aa"
Explanation: 
First delete "eee" and "ccc", get "ddbbbdaa"
Then delete "bbb", get "dddaa"
Finally delete "ddd", get "aa"
```

**Example 3:**
```
Input: s = "pbbcggttciiippooaais", k = 2
Output: "ps"
```

### Constraints

- `1 <= s.length <= 10^5`
- `2 <= k <= 10^4`
- `s` only contains lowercase English letters

## Observations

1. **Stack-based approach**: This problem naturally fits a stack data structure since we need to track adjacent characters and potentially remove them.

2. **Count tracking**: We need to keep track of consecutive character counts. When a count reaches `k`, we remove those characters.

3. **Cascading deletions**: After removing k duplicates, new adjacent characters might form new k-duplicates that also need to be removed (chain reaction).

4. **Sequential processing**: We process the string left-to-right, maintaining state as we go.

5. **Efficient removal**: Instead of actually removing characters from a string (which is O(n) per removal), we use a stack/array with an index pointer for O(1) operations.

6. **Sentinel character**: Using a sentinel `'#'` at the beginning simplifies boundary checks.

## Solution

### Approach: Stack with Count Array

The solution uses two parallel data structures:
- **Stack (`st`)**: Stores the characters as we process them
- **Count array (`count`)**: Stores the count of consecutive occurrences for each character group
- **Index pointer (`ist`)**: Points to the current position in the stack (acts as stack top)

### Algorithm Explanation:

1. **Initialize**:
   ```python
   st = ['#']      # Stack with a sentinel character
   ist = 1         # Index pointer (current position in stack)
   count = [0]     # Count array with initial value for sentinel
   prev = '#'      # Previous character tracker
   ```

2. **Process each character**:
   - Add character to stack at current position (reuse space when available)
   - If the character equals the previous one: increment the count
   - If the character is different: start a new count group with count 1

3. **Handle k-duplicate removal**:
   - When `count[-1] == k`, we have k adjacent duplicates
   - Move index pointer back by k positions: `ist -= k`
   - Remove the count entry: `count.pop()`
   - Update previous character: `prev = st[ist-1]`
   - Use a **while loop** to handle cascading deletions

4. **Return result**: 
   - Join characters from index 1 to `ist` (skip sentinel)

### Why This Works:

- **Space efficiency**: Reuses the stack array instead of constantly appending/removing
- **Time efficiency**: O(n) time - each character is pushed and popped at most once
- **Cascading handled**: The while loop automatically processes chain reactions of deletions
- **No string reconstruction overhead**: Only join at the very end

### Example Walkthrough:

For `s = "deeedbbcccbdaa"`, `k = 3`:

```
'd': st=['#','d'], ist=2, count=[0,1], prev='d'
'e': st=['#','d','e'], ist=3, count=[0,1,1], prev='e'
'e': st=['#','d','e','e'], ist=4, count=[0,1,2], prev='e'
'e': st=['#','d','e','e','e'], ist=5, count=[0,1,3], prev='e'
     → count[-1]==3, remove! ist=2, count=[0,1], prev='d'
     
'd': st=['#','d','d'], ist=3, count=[0,2], prev='d'
'b': st=['#','d','d','b'], ist=4, count=[0,2,1], prev='b'
'b': st=['#','d','d','b','b'], ist=5, count=[0,2,2], prev='b'
'b': st=['#','d','d','b','b','b'], ist=6, count=[0,2,3], prev='b'
     → count[-1]==3, remove! ist=3, count=[0,2], prev='d'
     
'c': st=['#','d','d','c'], ist=4, count=[0,2,1], prev='c'
'c': st=['#','d','d','c','c'], ist=5, count=[0,2,2], prev='c'
'c': st=['#','d','d','c','c','c'], ist=6, count=[0,2,3], prev='c'
     → count[-1]==3, remove! ist=3, count=[0,2], prev='d'
     
'd': st=['#','d','d','d'], ist=4, count=[0,3], prev='d'
     → count[-1]==3, remove! ist=1, count=[0], prev='#'
     
'b': st=['#','b'], ist=2, count=[0,1], prev='b'
'a': st=['#','b','a'], ist=3, count=[0,1,1], prev='a'
'a': st=['#','b','a','a'], ist=4, count=[0,1,2], prev='a'

Result: "aa"
```

### Complexity Analysis:

- **Time Complexity**: **O(n)**, where n is the length of string s
  - Each character is visited once in the main loop
  - Each character is pushed at most once and popped at most once
  - The while loop doesn't increase complexity as deletions are bounded by insertions
  
- **Space Complexity**: **O(n)**
  - Stack can grow up to size n in worst case (when no deletions occur)
  - Count array can grow up to size n in worst case

### Implementation

```python
class Solution:
    def removeDuplicates(self, s: str, k: int) -> str:
        st = ['#']           # Stack with sentinel
        ist = 1              # Current index in stack
        count = [0]          # Count of consecutive chars
        prev = '#'           # Previous character
        
        for c in s:
            # Place character at current position
            if ist == len(st):
                st.append(c)
            else:
                st[ist] = c
            ist += 1
            
            if c == prev:
                # Same as previous, increment count
                count[-1] += 1
                # Check for k-duplicates (handle cascading)
                while count and count[-1] == k:
                    ist -= k
                    count.pop()
                    prev = st[ist - 1]
            else:
                # New character group
                count.append(1)
                prev = c
        
        return "".join(st[1:ist])
```

# Tags

`Stack`, `String`, `Array`, `Greedy`

