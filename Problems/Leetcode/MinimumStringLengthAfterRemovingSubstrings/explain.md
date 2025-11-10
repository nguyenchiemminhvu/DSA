## Problem

https://leetcode.com/problems/minimum-string-length-after-removing-substrings/description/

```
You are given a string s consisting only of uppercase English letters.

You can apply some operations to this string where, in one operation, you can remove any occurrence of one of the substrings "AB" or "CD" from s.

Return the minimum possible length of the resulting string that you can obtain.

Note that the string concatenates after removing the substring and could produce new "AB" or "CD" substrings.

Example 1:

Input: s = "ABFCACDB"
Output: 2
Explanation: We can do the following operations:
- Remove the substring "ABFCACDB", so s = "FCACDB".
- Remove the substring "FCACDB", so s = "FCAB".
- Remove the substring "FCAB", so s = "FC".
So the resulting length of the string is 2.
It can be shown that it is the minimum length that we can obtain.

Example 2:

Input: s = "ACBBD"
Output: 5
Explanation: We cannot do any operations on the string so the length remains the same.

Constraints:

1 <= s.length <= 100
s consists only of uppercase English letters.
```

## Observations

1. **Pattern Recognition**: We need to remove substrings "AB" and "CD" from the string until no more removals are possible.

2. **Cascading Effect**: After removing a substring, the remaining parts concatenate and might form new "AB" or "CD" patterns. For example, in "ABFCACDB", after removing "AB", we get "FCACDB", and after removing "CD", we get "FCAB", which contains another "AB" to remove.

3. **Greedy vs Stack Approach**: 
   - A naive approach would be to repeatedly search and remove "AB" and "CD" patterns, but this could be inefficient.
   - A more efficient approach uses a stack to process characters one by one.

4. **Stack Pattern**: When we encounter 'B' and the top of stack is 'A', we can immediately remove the pair. Similarly for 'D' when top is 'C'. This naturally handles the cascading removals.

5. **Order Independence**: The order in which we remove "AB" and "CD" patterns doesn't matter for the final result - we'll always get the same minimum length.

## Solution

The solution uses a **stack-based approach** to efficiently handle the removal of "AB" and "CD" substrings:

### Algorithm:
1. Initialize an empty stack
2. Iterate through each character in the string:
   - If current character is 'B' and stack top is 'A': pop the stack (removes "AB")
   - If current character is 'D' and stack top is 'C': pop the stack (removes "CD") 
   - Otherwise: push the current character to stack
3. Return the size of the stack (remaining characters)

### Why This Works:
- **Immediate Removal**: As soon as we see a completing character ('B' after 'A' or 'D' after 'C'), we remove the pair immediately
- **Automatic Cascading**: By using a stack, previously processed characters can form new pairs with upcoming characters naturally
- **Single Pass**: We only need to traverse the string once, making it O(n) time complexity

### Example Trace:
For `s = "ABFCACDB"`:
- 'A': stack = ['A']
- 'B': 'B' with 'A' on top → pop → stack = []
- 'F': stack = ['F']  
- 'C': stack = ['F', 'C']
- 'A': stack = ['F', 'C', 'A']
- 'C': stack = ['F', 'C', 'A', 'C']  
- 'D': 'D' with 'C' on top → pop → stack = ['F', 'C', 'A']
- 'B': 'B' with 'A' on top → pop → stack = ['F', 'C']

Final length: 2

### Time Complexity: O(n) - single pass through string
### Space Complexity: O(n) - worst case stack size

# Tags

- Stack
- String Manipulation
- Greedy Algorithm

