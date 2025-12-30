## Problem

https://leetcode.com/problems/longest-absolute-file-path/description/

Given a string representing a file system in a hierarchical format (using `\n` for new lines and `\t` for tabs indicating depth), return the length of the longest absolute path to a **file** in the system. If there is no file, return 0.

**Key Points:**
- Directories and files are represented with tab characters (`\t`) indicating their depth level
- Files have a dot (`.`) in their name (e.g., `file.ext`)
- Directories don't have a dot
- Absolute paths use `/` as separator
- We only count paths to files, not directories

**Example 1:**
```
Input: input = "dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext"
Output: 20
Explanation: "dir/subdir2/file.ext" has length 20
```

**Example 2:**
```
Input: input = "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext"
Output: 32
Explanation: 
- "dir/subdir1/file1.ext" = 21
- "dir/subdir2/subsubdir2/file2.ext" = 32 (longest)
```

**Example 3:**
```
Input: input = "a"
Output: 0
Explanation: No files, only directory "a"
```

**Constraints:**
- 1 <= input.length <= 10^4
- Input contains letters, digits, spaces, '\n', '\t', and '.'
- All names have positive length

## Observations

1. **Hierarchy Representation**: The number of `\t` characters indicates the depth/level in the file system tree
   - 0 tabs = root level
   - 1 tab = first level subdirectory
   - 2 tabs = second level subdirectory, etc.

2. **File vs Directory**: Files contain a dot (`.`) in their name, directories don't

3. **Stack-Based Approach**: We can use a stack/list to maintain the current path at each depth level
   - When we encounter an item at depth `d`, it replaces any previous item at that depth
   - All items at depths > `d` become invalid (we've moved to a different branch)

4. **Path Length Calculation**: 
   - When joining path components with `/`, we need to account for the separators
   - The tab characters in the original string don't contribute to the actual path length
   - Formula: `actual_length = len(joined_path) - number_of_tabs_in_joined_path`

5. **Tab Count Optimization**: 
   - For an item at depth `idx`, the total number of tabs when joining is: `idx * (idx + 1) / 2`
   - This is because: depth 0 has 0 tabs, depth 1 has 1 tab, depth 2 has 2 tabs, etc.
   - Sum = 0 + 1 + 2 + ... + idx = idx * (idx + 1) / 2

## Solution

### Approach: Stack/List to Track Current Path

**Algorithm:**
1. Split the input by newlines to get individual entries
2. Maintain a stack/list where `st[i]` stores the current directory/file name at depth `i`
3. For each entry:
   - Count the number of tabs to determine its depth
   - Update the stack at that depth (this implicitly removes deeper levels)
   - If it's a file (contains '.'), calculate the path length:
     - Join all stack elements up to current depth with '/'
     - Subtract the tab characters that don't count toward actual length
     - Update the maximum length found

**Time Complexity:** O(n) where n is the length of input
- We process each character once during split
- For each line, we do O(depth) work which is bounded by the number of lines

**Space Complexity:** O(d) where d is the maximum depth
- Stack stores at most one entry per depth level

**Implementation:**

```python
class Solution:
    def lengthLongestPath(self, input: str) -> int:
        arr = input.splitlines()  # Split by newlines
        res = 0
        st = []  # Stack to maintain current path at each depth
        
        for sub in arr:
            # Count tabs to determine depth level
            idx = sub.count('\t')
            
            # Update stack at current depth
            if idx >= len(st):
                st.append(sub)  # Add new depth level
            else:
                st[idx] = sub  # Replace at existing depth (moves to new branch)
            
            # Check if this is a file (contains '.')
            if sub.count('.'):
                # Build the absolute path
                path = "/".join(st[:idx + 1])
                
                # Calculate number of tab characters in the joined path
                # Tabs at depth d: d tabs per entry
                # Total tabs for depths 0 to idx: 0+1+2+...+idx = idx*(idx+1)/2
                num_tabs = idx * (idx + 1) // 2
                
                # Actual path length (excluding tab characters)
                res = max(res, len(path) - num_tabs)
        
        return res
```

**Example Walkthrough:**

For input: `"dir\n\tsubdir1\n\t\tfile1.ext\n\tsubdir2\n\t\tfile2.ext"`

| Line | Tabs | Stack After | File? | Path | Length Calc | Max |
|------|------|-------------|-------|------|-------------|-----|
| `dir` | 0 | `['dir']` | No | - | - | 0 |
| `\tsubdir1` | 1 | `['dir', '\tsubdir1']` | No | - | - | 0 |
| `\t\tfile1.ext` | 2 | `['dir', '\tsubdir1', '\t\tfile1.ext']` | Yes | `dir/\tsubdir1/\t\tfile1.ext` | len=29, tabs=3, actual=26 | 26 |
| `\tsubdir2` | 1 | `['dir', '\tsubdir2']` | No | - | - | 26 |
| `\t\tfile2.ext` | 2 | `['dir', '\tsubdir2', '\t\tfile2.ext']` | Yes | `dir/\tsubdir2/\t\tfile2.ext` | len=29, tabs=3, actual=26 | 26 |

**Key Insights:**
- The stack automatically handles branching in the tree structure
- We only calculate lengths for files, not directories
- The mathematical formula for tab count eliminates the need to count them manually

# Tags

`String` `Stack` `Depth-First-Search` `Tree-Simulation` `File-System`

