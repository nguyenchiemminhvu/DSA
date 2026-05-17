## Problem

https://leetcode.com/problems/jump-game-iii/description

### Problem Statement

Given an array of non-negative integers `arr`, you are initially positioned at the `start` index of the array. When you are at index `i`, you can jump to either:
- `i + arr[i]` (jump forward by `arr[i]` steps)
- `i - arr[i]` (jump backward by `arr[i]` steps)

**Task**: Determine if you can reach any index with value 0.

**Constraint**: You cannot jump outside the array bounds at any time.

### Examples

**Example 1:**
```
Input: arr = [4,2,3,0,3,1,2], start = 5
Output: true
Explanation: 
  index 5 -> index 4 -> index 1 -> index 3 (arr[3] = 0) ✓
  index 5 -> index 6 -> index 4 -> index 1 -> index 3 (arr[3] = 0) ✓
```

**Example 2:**
```
Input: arr = [4,2,3,0,3,1,2], start = 0
Output: true
Explanation: 
  index 0 -> index 4 -> index 1 -> index 3 (arr[3] = 0) ✓
```

**Example 3:**
```
Input: arr = [3,0,2,1,2], start = 2
Output: false
Explanation: There is no path from index 2 to any index with value 0.
```

### Constraints

- `1 <= arr.length <= 5 * 10^4`
- `0 <= arr[i] < arr.length`
- `0 <= start < arr.length`

## Observations

1. **Graph Traversal Problem**: This is a graph reachability problem where each index is a node, and edges exist to `i + arr[i]` and `i - arr[i]` (if valid).

2. **Visited State Management**: We need to track visited indices to avoid infinite loops since we can move bidirectionally. Without this, we could get stuck in cycles like `i → j → i → j → ...`

3. **Search Strategy**: Both BFS and DFS work equally well. BFS naturally explores all reachable states level by level.

4. **Early Termination**: As soon as we reach an index with value 0, we can return `true`. There's no need to explore further.

5. **Unreachable Cases**: If an index cannot be reached from the start position, it's impossible to visit it. The visited set efficiently prunes already-explored paths.

6. **Time Complexity**: O(n) where n is the array length. Each index is visited at most once.

7. **Space Complexity**: O(n) for the visited set and BFS queue in the worst case.

## Solution

### Approach: Breadth-First Search (BFS)

The solution uses BFS to explore all reachable indices from the starting position:

```python
class Solution:
    def canReach(self, arr: List[int], start: int) -> bool:
        n = len(arr)

        def bfs():
            q = deque([start])
            visited = set()
            
            while q:
                cur = q.popleft()
                
                # Check if we reached a target (index with value 0)
                if arr[cur] == 0:
                    return True
                
                # Mark as visited to avoid revisiting
                visited.add(cur)

                # Try both jump directions
                left = cur - arr[cur]   # Jump backward
                right = cur + arr[cur]  # Jump forward
                
                # Add valid, unvisited neighbors to queue
                if left >= 0 and left not in visited:
                    q.append(left)
                if right < n and right not in visited:
                    q.append(right)
            
            return False
        
        return bfs()
```

### Step-by-Step Explanation

1. **Initialization**:
   - Create a queue with the starting index
   - Create a visited set to track explored indices

2. **BFS Loop**:
   - Dequeue the current index
   - Check if `arr[cur] == 0` (success condition)
   - Mark current index as visited
   - Calculate both possible next positions: `cur - arr[cur]` and `cur + arr[cur]`

3. **Boundary & Cycle Checks**:
   - For left jump: ensure `left >= 0` (within left boundary)
   - For right jump: ensure `right < n` (within right boundary)
   - Only enqueue if the index hasn't been visited (prevents infinite loops)

4. **Return**:
   - If queue becomes empty without finding 0, return `False`
   - If we find an index with value 0, return `True`

### Example Walkthrough

For `arr = [4,2,3,0,3,1,2]`, `start = 5`:

```
Start: Queue = [5], Visited = {}

Step 1: cur = 5, arr[5] = 1
  - Not 0, mark as visited: Visited = {5}
  - left = 5 - 1 = 4 ✓ (add to queue)
  - right = 5 + 1 = 6 ✓ (add to queue)
  - Queue = [4, 6]

Step 2: cur = 4, arr[4] = 3
  - Not 0, mark as visited: Visited = {5, 4}
  - left = 4 - 3 = 1 ✓ (add to queue)
  - right = 4 + 3 = 7 ✗ (out of bounds)
  - Queue = [6, 1]

Step 3: cur = 6, arr[6] = 2
  - Not 0, mark as visited: Visited = {5, 4, 6}
  - left = 6 - 2 = 4 ✗ (already visited)
  - right = 6 + 2 = 8 ✗ (out of bounds)
  - Queue = [1]

Step 4: cur = 1, arr[1] = 2
  - Not 0, mark as visited: Visited = {5, 4, 6, 1}
  - left = 1 - 2 = -1 ✗ (out of bounds)
  - right = 1 + 2 = 3 ✓ (add to queue)
  - Queue = [3]

Step 5: cur = 3, arr[3] = 0
  - Found target! Return True ✓
```

# Tags

#graph #bfs #reachability #cycle-detection

