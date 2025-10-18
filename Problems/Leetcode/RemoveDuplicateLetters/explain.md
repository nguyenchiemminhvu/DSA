## Problem

https://leetcode.com/problems/remove-duplicate-letters/description/

```
Given a string s, remove duplicate letters so that every letter appears once and only once. You must make sure your result is the smallest in lexicographical order among all possible results.

Example 1:

Input: s = "bcabc"
Output: "abc"

Example 2:

Input: s = "cbacdcbc"
Output: "acdb"

Constraints:

1 <= s.length <= 104
s consists of lowercase English letters.

Note: This question is the same as 1081: https://leetcode.com/problems/smallest-subsequence-of-distinct-characters/
```

## Observations

1. **Unique Characters**: Each letter must appear exactly once in the final result.

2. **Lexicographical Order**: Among all valid results, we need the lexicographically smallest one.

3. **Key Insight**: We can use a greedy approach with a stack. When processing each character:
   - If we encounter a character that's already in our result, skip it
   - If we encounter a character that's smaller than the last character in our result, and we know the last character will appear later in the string, we can remove the last character and use it later

4. **Stack-based Strategy**:
   - Use a stack to build the result
   - Use a set to track which characters are already in the stack
   - Use a counter to track remaining occurrences of each character

5. **Decision Making**: For each character, we decide whether to:
   - Skip it (if already used)
   - Add it directly (if stack is empty or maintains order)
   - Remove previous characters first (if they're larger and will appear later)

## Solution

The solution uses a **greedy stack-based approach**:

### Algorithm Steps:

1. **Preprocessing**:
   - Count frequency of each character in the input string
   - Initialize an empty stack and a set to track characters in the stack

2. **Main Processing**:
   - For each character in the string:
     - Decrement its remaining count
     - If already in stack, skip it
     - While the stack top is lexicographically larger than current character AND the stack top will appear later (count > 0):
       - Remove the stack top and remove it from the set
     - Add current character to stack and set

3. **Result**: Join the stack to form the final string

### Example Walkthrough (`s = "cbacdcbc"`):

```
s = "cbacdcbc"
After first pass: counter = {a:1, b:2, c:4, d:1}

Processing each character:

i=0, ch='c': counter[c]-- = 3, 'c' not in in_stack
             stack=[], add 'c': stack=['c'], in_stack={'c'}

i=1, ch='b': counter[b]-- = 1, 'b' not in in_stack  
             stack=['c'], 'c' > 'b' and counter['c']=3 > 0
             Remove 'c': stack=[], in_stack={}
             Add 'b': stack=['b'], in_stack={'b'}

i=2, ch='a': counter[a]-- = 0, 'a' not in in_stack
             stack=['b'], 'b' > 'a' and counter['b']=1 > 0  
             Remove 'b': stack=[], in_stack={}
             Add 'a': stack=['a'], in_stack={'a'}

i=3, ch='c': counter[c]-- = 2, 'c' not in in_stack
             stack=['a'], 'a' < 'c', no removal needed
             Add 'c': stack=['a','c'], in_stack={'a','c'}

i=4, ch='d': counter[d]-- = 0, 'd' not in in_stack
             stack=['a','c'], 'c' < 'd', no removal needed  
             Add 'd': stack=['a','c','d'], in_stack={'a','c','d'}

i=5, ch='c': counter[c]-- = 1, 'c' in in_stack → skip

i=6, ch='b': counter[b]-- = 0, 'b' not in in_stack
             stack=['a','c','d'], 'd' > 'b' but counter['d']=0
             Can't remove 'd' (no more d's coming)
             Add 'b': stack=['a','c','d','b'], in_stack={'a','c','d','b'}

i=7, ch='c': counter[c]-- = 0, 'c' in in_stack → skip

Final result: "acdb" ✓
```

### Key Insights:

1. **Greedy Choice**: We remove larger characters only if we know they'll appear later
2. **Stack Property**: Maintains the lexicographically smallest valid sequence  
3. **One Pass**: Each character is processed exactly once
4. **Optimal Substructure**: Local optimal choices lead to global optimum

### Complexity Analysis:

- **Time Complexity**: O(n) where n is the length of string
  - Each character is pushed and popped at most once
  - The inner while loop operations are amortized O(1)
  
- **Space Complexity**: O(1) for lowercase English letters  
  - Counter array: O(128) = O(1)
  - Stack and set: at most 26 unique characters = O(1)
  - For general ASCII: O(128) = O(1)

## Tags

array, string, greedy, stack