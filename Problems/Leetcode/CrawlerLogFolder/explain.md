## Problem

https://leetcode.com/problems/crawler-log-folder/

```
The Leetcode file system keeps a log each time some user performs a change folder operation.

The operations are described below:

"../" : Move to the parent folder of the current folder. (If you are already in the main folder, remain in the same folder).
"./" : Remain in the same folder.
"x/" : Move to the child folder named x (This folder is guaranteed to always exist).
You are given a list of strings logs where logs[i] is the operation performed by the user at the ith step.

The file system starts in the main folder, then the operations in logs are performed.

Return the minimum number of operations needed to go back to the main folder after the change folder operations.

Example 1:

Input: logs = ["d1/","d2/","../","d21/","./"]
Output: 2
Explanation: Use this change folder operation "../" 2 times and go back to the main folder.

Example 2:

Input: logs = ["d1/","d2/","./","d3/","../","d31/"]
Output: 3

Example 3:

Input: logs = ["d1/","../","../","../"]
Output: 0

Constraints:

1 <= logs.length <= 103
2 <= logs[i].length <= 10
logs[i] contains lowercase English letters, digits, '.', and '/'.
logs[i] follows the format described in the statement.
Folder names consist of lowercase English letters and digits.
```

## Observations

1. **Problem Type**: This is a file system navigation simulation problem that can be solved using a stack data structure.

2. **Key Operations**:
   - `"../"`: Move to parent folder (go back one level)
   - `"./"`: Stay in current folder (no change)
   - `"x/"`: Move into child folder named x (go deeper one level)

3. **Stack Behavior**:
   - Each folder we enter represents going deeper into the directory tree
   - Going back (`../`) means popping from the stack (if possible)
   - Staying (`.`) means no stack operation
   - The final stack size represents how deep we are from the main folder

4. **Edge Cases**:
   - If we're already at main folder and try to go back (`../`), we stay at main folder
   - Multiple consecutive `../` operations should be handled correctly
   - The solution needs to count minimum operations to return to main folder

5. **Pattern Recognition**: The depth from main folder = number of folders we've entered - number of times we've gone back

## Solution

1. **Initialize**: Create an empty stack to track our current path depth
2. **Process Each Log**:
   - Extract folder name by removing the trailing '/'
   - If folder is `'.'`: Do nothing (stay in current folder)
   - If folder is `'..'`: Pop from stack if not empty (go back to parent)
   - Otherwise: Push folder to stack (enter the folder)
3. **Return**: The stack size represents how many levels deep we are from main folder

**Time Complexity**: O(n) where n is the length of logs array
**Space Complexity**: O(n) in worst case when all operations are entering new folders

**Key Insights**:
- We don't need to store actual folder names, just count the depth
- The stack simulates the directory traversal perfectly
- Final stack size = minimum operations needed to return to main folder

# Tags

- Stack
- Simulation
- String Processing
- File System

