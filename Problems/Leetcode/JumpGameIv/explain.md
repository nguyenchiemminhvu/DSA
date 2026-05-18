## Problem

https://leetcode.com/problems/jump-game-iv/description

### Problem Statement

Given an array of integers `arr`, you are initially positioned at the first index of the array.

In one step you can jump from index `i` to index:
- `i + 1` where `i + 1 < arr.length`
- `i - 1` where `i - 1 >= 0`
- `j` where `arr[i] == arr[j]` and `i != j`

Return the minimum number of steps to reach the last index of the array.

**Note:** You cannot jump outside of the array at any time.

### Examples

**Example 1:**
- Input: `arr = [100,-23,-23,404,100,23,23,23,3,404]`
- Output: `3`
- Explanation: You need three jumps: `0 --> 4 --> 3 --> 9`. Index 9 is the last index.

**Example 2:**
- Input: `arr = [7]`
- Output: `0`
- Explanation: Start index is the last index. No jumps needed.

**Example 3:**
- Input: `arr = [7,6,9,6,9,6,9,7]`
- Output: `1`
- Explanation: Jump directly from index 0 to index 7 (last index).

### Constraints

- `1 <= arr.length <= 5 * 10^4`
- `-10^8 <= arr[i] <= 10^8`

## Observations

1. **Shortest Path Problem**: This is a classic shortest path problem that can be solved using BFS (Breadth-First Search). We need to find the minimum steps, which is naturally solved by BFS since it explores nodes level by level.

2. **Three Types of Jumps**: From each index, we have three possible jumps:
   - Adjacent left (`i - 1`)
   - Adjacent right (`i + 1`)
   - Any index with the same value (`arr[i] == arr[j]`)

3. **Graph Construction**: We can think of the problem as a graph where:
   - Each index is a node
   - Edges exist between indices based on the three jump rules above
   - We need to find the shortest path from index 0 to index `n - 1`

4. **Value-to-Indices Mapping**: To efficiently find all indices with the same value, we should precompute a mapping from each value to all its indices. This avoids repeatedly searching the entire array.

5. **Preventing Redundant Exploration**: For indices with the same value, once we've visited them all in one step, we should clear the list to prevent revisiting the same group of indices in future BFS iterations. This optimization prevents O(n²) complexity in worst cases.

6. **Early Termination**: We can return immediately when we reach the last index during BFS, rather than waiting for the queue to empty.

## Solution

### Algorithm: Breadth-First Search (BFS)

The solution uses BFS to find the shortest path in an unweighted graph:

```python
class Solution:
    def minJumps(self, arr: List[int]) -> int:
        n = len(arr)
        if n == 1:
            return 0
        
        # Map each value to all indices where it appears
        val_idx = defaultdict(list)
        for i in range(n):
            val_idx[arr[i]].append(i)
        
        def bfs():
            q = deque([0])
            visited = set()
            visited.add(0)
            steps = 0
            
            while q:
                size = len(q)
                # Process all nodes at the current level
                for _ in range(size):
                    cur = q.popleft()
                    
                    # Check if we reached the destination
                    if cur == n - 1:
                        return steps
                    
                    # Jump to index - 1
                    if cur - 1 >= 0 and cur - 1 not in visited:
                        visited.add(cur - 1)
                        q.append(cur - 1)
                    
                    # Jump to index + 1
                    if cur + 1 < n and cur + 1 not in visited:
                        visited.add(cur + 1)
                        q.append(cur + 1)
                    
                    # Jump to all indices with the same value
                    for idx in val_idx[arr[cur]]:
                        if idx not in visited:
                            visited.add(idx)
                            q.append(idx)
                    
                    # Clear the list to avoid processing the same indices again
                    val_idx[arr[cur]].clear()
                
                steps += 1
            
            return -1
        
        return bfs()
```

### Step-by-Step Explanation

1. **Edge Case**: If the array has only one element, we're already at the last index, so return 0.

2. **Precomputation**: Create a dictionary `val_idx` that maps each value to a list of all indices where that value appears. This allows O(1) lookup of indices with the same value.

3. **BFS Initialization**:
   - Queue `q` starts with index 0 (starting position)
   - `visited` set tracks all visited indices to avoid revisiting
   - `steps` counter tracks the number of jumps

4. **BFS Loop**:
   - Process all nodes at the current level (determined by `size = len(q)`)
   - For each node, add all unvisited neighbors to the queue:
     - Left neighbor (`cur - 1`)
     - Right neighbor (`cur + 1`)
     - All indices with the same value
   - Increment `steps` after processing all nodes at the current level
   - Return `steps` immediately when reaching index `n - 1`

5. **Optimization**: After processing all indices with a specific value from the current node, we clear `val_idx[arr[cur]]`. This prevents redundant processing:
   - Prevents the same group of indices from being added multiple times across iterations
   - Reduces time complexity from potentially O(n²) to O(n)

### Complexity Analysis

- **Time Complexity**: O(n)
  - Each index is visited at most once (added to queue once)
  - The value-to-index mapping is built in O(n)
  - Total: O(n)

- **Space Complexity**: O(n)
  - The `val_idx` dictionary stores all n indices
  - The `visited` set stores at most n entries
  - The queue stores at most n entries
  - Total: O(n)

### Example Walkthrough

Given `arr = [100,-23,-23,404,100,23,23,23,3,404]`:

```
Index:  0    1    2    3   4    5    6    7  8    9
Value: 100  -23  -23  404 100  23   23   23  3   404

Step 0: Start at index 0
Step 1: From 0, can jump to:
        - Index 1 (adjacent)
        - Index 4 (same value: 100)
Step 2: From 1, can jump to:
        - Index 2 (adjacent, same value: -23)
        From 4, can jump to:
        - Index 3 (adjacent)
        - Index 5 (adjacent)
        - Index 9 (same value: 404)
Step 3: From 3, we've reached index 3. Continue to find shortest...
        From 5, can jump to indices with value 23
        ...ultimately reaching index 9 in 3 steps: 0 → 4 → 3 → 9
```

# Tags

- Breadth-First Search (BFS)
- Graph
- Shortest Path
- Level Order Traversal
- Hash Table (Value-to-Index Mapping)

