## Problem

https://leetcode.com/problems/simplify-path/description/

```
Given an absolute path for a Unix-style file system, which always begins with a slash '/'. 
Transform this absolute path into its simplified canonical path.

Rules:
- A single period '.' represents the current directory.
- A double period '..' represents the previous/parent directory.
- Multiple consecutive slashes '//' are treated as a single slash '/'.
- Any sequence of periods that doesn't match above rules is a valid directory/file name (e.g., '...', '....').

The simplified canonical path should:
- Start with a single slash '/'.
- Directories separated by exactly one slash '/'.
- Not end with a slash '/', unless it is the root directory.
- Not have any single or double periods ('.' and '..') used to denote current or parent directories.

Examples:
- "/home/" -> "/home"
- "/home//foo/" -> "/home/foo"
- "/home/user/Documents/../Pictures" -> "/home/user/Pictures"
- "/../" -> "/"
- "/.../a/../b/c/../d/./" -> "/.../b/d"

Constraints:
- 1 <= path.length <= 3000
- path consists of English letters, digits, period '.', slash '/' or '_'.
- path is a valid absolute Unix path.
```

## Observations

1. **Stack-based approach**: Use a stack to track the valid directory names as we traverse the path.

2. **Split by '/'**: Splitting the path by '/' helps us process each component individually:
   - Empty strings (from consecutive slashes) can be ignored
   - Single dots '.' can be ignored (current directory)
   - Double dots '..' mean we go back one level (pop from stack if possible)
   - Everything else is a valid directory/file name (push to stack)

3. **Edge cases**:
   - Going up from root directory (e.g., "/../") should remain at root
   - Multiple consecutive slashes should be treated as one
   - Trailing slashes should be removed (except for root)
   - Sequences like "...", "...." are valid directory names

4. **Building result**: Join the stack elements with '/' and prepend a '/' to form the canonical path.

## Solution

```python
class Solution:
    def simplifyPath(self, path: str) -> str:
        st = []
        arr = path.split('/')
        
        for sub in arr:
            # Skip empty strings (from consecutive slashes)
            if not sub:
                continue
            
            # Skip current directory marker
            if sub == '.':
                continue
            
            # Go up one level if possible
            elif sub == '..':
                if st:
                    st.pop()
            
            # Valid directory/file name, add to stack
            else:
                st.append(sub)
        
        # Build canonical path
        return "/" + "/".join(st)
```

**Algorithm Steps:**

1. Initialize an empty stack `st` to store valid directory names
2. Split the input path by '/' delimiter into components
3. For each component:
   - If empty string: skip (handles consecutive slashes)
   - If '.': skip (current directory, no change)
   - If '..': pop from stack if not empty (go to parent directory)
   - Otherwise: push to stack (valid directory name)
4. Join all elements in stack with '/' and prepend '/' to create the result

**Time Complexity**: O(n) where n is the length of the path
- Split operation: O(n)
- Iterating through components: O(n)
- Join operation: O(n)

**Space Complexity**: O(n)
- Stack can hold at most n/2 directory names (in case of all valid names)
- Split array also takes O(n) space

**Key Insights:**
- Stack naturally handles the hierarchical nature of directory navigation
- Split by delimiter simplifies handling of multiple consecutive slashes
- The '..' operation is safe even at root level due to the `if st` check

# Tags
#stack #string #file-system #path-manipulation #simulation

