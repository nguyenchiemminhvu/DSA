## Problem

https://leetcode.com/problems/sliding-puzzle/description

# Sliding Puzzle

## Problem

https://leetcode.com/problems/sliding-puzzle/description

On a 2 x 3 board, there are five tiles labeled from 1 to 5, and an empty square represented by 0. A move consists of choosing 0 and a 4-directionally adjacent number and swapping it.

**Goal**: The state of the board is solved if and only if the board is `[[1,2,3],[4,5,0]]`.

**Task**: Given the puzzle board, return the least number of moves required so that the state of the board is solved. If it is impossible for the state of the board to be solved, return -1.

### Examples

**Example 1:**
- Input: `board = [[1,2,3],[4,0,5]]`
- Output: `1`
- Explanation: Swap the 0 and the 5 in one move.

**Example 2:**
- Input: `board = [[1,2,3],[5,4,0]]`
- Output: `-1`
- Explanation: No number of moves will make the board solved.

**Example 3:**
- Input: `board = [[4,1,2],[5,0,3]]`
- Output: `5`
- Example path:
  - After move 0: `[[4,1,2],[5,0,3]]`
  - After move 1: `[[4,1,2],[0,5,3]]`
  - After move 2: `[[0,1,2],[4,5,3]]`
  - After move 3: `[[1,0,2],[4,5,3]]`
  - After move 4: `[[1,2,0],[4,5,3]]`
  - After move 5: `[[1,2,3],[4,5,0]]`

### Constraints
- `board.length == 2`
- `board[i].length == 3`
- `0 <= board[i][j] <= 5`
- Each value `board[i][j]` is unique

---

## Observations

### 1. **Fixed Board Size & Fixed Target**
   - The board is always 2x3 (6 positions total)
   - The target state is always `[[1,2,3],[4,5,0]]` or `[1,2,3,4,5,0]` as a flat array
   - This means we're looking for the **minimum number of moves** from start state to one specific end state

### 2. **State Space Problem**
   - Each board configuration represents a unique state
   - Total possible states: 6! = 720 (permutations of 6 elements)
   - Not all states are reachable from all other states due to puzzle properties
   - We need to **search through the state space** to find the shortest path

### 3. **Shortest Path Problem**
   - This is a classic **shortest path in an unweighted graph** problem
   - Each state is a node
   - Each valid move (swapping 0 with adjacent tile) creates an edge to another state
   - **BFS** is the ideal algorithm to find the shortest path

### 4. **Adjacency Mapping for 2x3 Board**
   - When flattened to 1D array (6 positions: 0-5), the adjacencies are:
     - Position 0: can swap with 1, 3
     - Position 1: can swap with 0, 2, 4
     - Position 2: can swap with 1, 5
     - Position 3: can swap with 0, 4
     - Position 4: can swap with 1, 3, 5
     - Position 5: can swap with 2, 4
   - This represents which positions in a flattened 2D array are adjacent

### 5. **Visited Set to Avoid Cycles**
   - To prevent revisiting the same state and getting stuck in loops, we maintain a `visited` set
   - Each state is represented as a tuple (immutable, hashable) for storage in the set

### 6. **Impossibility Detection**
   - If BFS completes without finding the target, it's impossible to reach it
   - Return -1 in this case
   - This occurs when initial permutation is in a different cycle than the target

---

## Solution

### Algorithm: Breadth-First Search (BFS)

**Time Complexity**: O(6!) = O(720) in worst case (all possible states)  
**Space Complexity**: O(6!) = O(720) for the visited set and queue

### Key Steps

1. **Convert 2D board to 1D array**: Flatten the 2D array to simplify state representation
2. **Create adjacency map**: Pre-compute which positions are adjacent in the 2x3 board
3. **Initialize BFS**: Start with the current board state in the queue
4. **Level-by-level exploration**: Process all states at the current distance level before moving to the next
5. **Generate next states**: For each state, find the position of 0, and swap it with all adjacent tiles
6. **Check target**: If we reach the target state, return the number of moves
7. **Detect impossibility**: If BFS completes without finding the target, return -1

### Code Walkthrough

```python
class Solution:
    def slidingPuzzle(self, board: List[List[int]]) -> int:
        # Target state represented as flattened 1D array
        target = [1, 2, 3, 4, 5, 0]

        # Adjacency map for 2x3 board (position -> adjacent positions)
        adj_map = {
            0: [1, 3],        # top-left can swap with right and down
            1: [0, 2, 4],     # top-middle can swap with left, right, and down
            2: [1, 5],        # top-right can swap with left and down
            3: [0, 4],        # bottom-left can swap with up and right
            4: [1, 3, 5],     # bottom-middle can swap with up, left, and right
            5: [2, 4],        # bottom-right can swap with up and left
        }

        # Flatten the 2D board into a 1D array
        cur = [val for row in board for val in row]
        
        # Track visited states to avoid cycles
        visited = set()
        
        # Initialize BFS
        moves = 0
        q = deque([cur])
        visited.add(tuple(cur))
        
        # BFS main loop
        while q:
            size = len(q)
            # Process all states at current distance level
            for _ in range(size):
                cur = q.popleft()
                
                # Check if we reached the target
                if cur == target:
                    return moves
                
                # Find position of 0 (empty square)
                idx_0 = cur.index(0)
                
                # Try all adjacent positions
                for adj in adj_map[idx_0]:
                    # Create next state by swapping 0 with adjacent tile
                    next_state = cur[:]
                    next_state[idx_0], next_state[adj] = next_state[adj], next_state[idx_0]
                    
                    # Only add unvisited states
                    if tuple(next_state) not in visited:
                        visited.add(tuple(next_state))
                        q.append(next_state)
            
            # Increment moves after processing all states at current level
            moves += 1
        
        # If we exit the loop without finding target, it's impossible
        return -1
```

### Execution Flow Example

**Input**: `[[1,2,3],[4,0,5]]`

```
Move 0: [1, 2, 3, 4, 0, 5]  (current state)
  - Position of 0: index 4
  - Adjacent positions: 1, 3, 5
  - Generate next states:
    - Swap with 1: [1, 2, 3, 0, 4, 5]
    - Swap with 3: [1, 2, 3, 4, 5, 0] ← TARGET FOUND!
    - Swap with 5: [1, 2, 3, 4, 5, 0]

Result: 1 move
```

### Why This Works

1. **BFS guarantees shortest path**: Since all edges (moves) have equal weight (1 move), BFS explores states in order of distance
2. **Visited set prevents redundant work**: We never process the same state twice
3. **Adjacency map captures puzzle constraints**: It accurately represents which tiles can be swapped with the empty square
4. **Returns -1 for impossible states**: Sliding puzzle has permutation parity; not all configurations are reachable

---

## Tags

- **Graph Theory**: State space as graph, nodes as configurations, edges as moves
- **BFS**: Finding shortest path in unweighted graph
- **State Space Search**: Systematic exploration of all possible puzzle states
- **Permutation Theory**: Understanding which states are reachable
- **Puzzle Algorithm**: Classic computational puzzle problem

## Observations

## Solution

# Tags

