## Problem

https://leetcode.com/problems/multi-source-flood-fill/description/

```
You are given two integers n and m representing the number of rows and columns of a grid, respectively.

You are also given a 2D integer array sources, where sources[i] = [ri, ci, colori] indicates that the cell
(ri, ci) is initially colored with colori. All other cells are initially uncolored and represented as 0.

At each time step, every currently colored cell spreads its color to all adjacent uncolored cells in the four
directions: up, down, left, and right. All spreads happen simultaneously.

If multiple colors reach the same uncolored cell at the same time step, the cell takes the color with the
maximum value.

The process continues until no more cells can be colored.

Return a 2D integer array representing the final state of the grid, where each cell contains its final color.

Example 1:

Input: n = 3, m = 3, sources = [[0,0,1],[2,2,2]]
Output: [[1,1,2],[1,2,2],[2,2,2]]

At time step 2, cells (0,2), (1,1), and (2,0) are reached by both colors simultaneously,
so they are assigned color 2 as it has the maximum value.

Example 2:

Input: n = 3, m = 3, sources = [[0,1,3],[1,1,5]]
Output: [[3,3,3],[5,5,5],[5,5,5]]

Example 3:

Input: n = 2, m = 2, sources = [[1,1,5]]
Output: [[5,5],[5,5]]

Constraints:

1 <= n, m <= 10^5
1 <= n * m <= 10^5
1 <= sources.length <= n * m
sources[i] = [ri, ci, colori]
0 <= ri <= n - 1
0 <= ci <= m - 1
1 <= colori <= 10^6
All (ri, ci) in sources are distinct.
```

## Observations

1. **BFS is Natural for Simultaneous Spreading**: Color spreads level-by-level (each time step = one BFS level), which maps perfectly to multi-source BFS. Initialize the queue with all source cells at once to simulate simultaneous spreading.

2. **Conflict Resolution at Equal Distance**: When two or more colors reach the same cell at the same time step (same BFS level / distance), the cell should be assigned the maximum color value. This means we cannot simply mark a cell as "visited" upon first enqueue — we need to track the *distance* at which it was first reached and allow the same cell to be updated by a higher color at the same distance.

3. **Distance Tracking is the Key**: Maintain a `dist[][]` grid (initialized to infinity). When processing a neighbor:
   - If `dist[neighbor] > dist[current] + 1`: it has not been reached yet — enqueue it and record the color.
   - If `dist[neighbor] == dist[current] + 1`: it is being reached at the same time step — update color only if the incoming color is larger (take max).
   - If `dist[neighbor] < dist[current] + 1`: it was already settled at a closer step — skip it.

4. **Why Plain "Visited" BFS Fails**: A standard BFS marks a cell visited on first visit. But if two sources are equidistant from a cell, only the first one to enqueue the cell would win, which is arbitrary and incorrect. We need to allow a second update at equal distance with a higher color.

5. **Termination**: BFS naturally terminates when the queue is empty (all reachable cells have been assigned a color at their minimum distance).

## Solution

Use **multi-source BFS with distance-aware conflict resolution**:

### Setup

```cpp
vector<vector<int>> grid(n, vector<int>(m, 0));
vector<vector<int>> dist(n, vector<int>(m, INT_MAX));

deque<tuple<int,int>> q;
for (auto& s : sources) {
    int r = s[0], c = s[1], color = s[2];
    grid[r][c] = color;
    dist[r][c] = 0;
    q.push_back({r, c});
}
```

### BFS Loop

```cpp
int dirs[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
while (!q.empty()) {
    auto [r, c] = q.front(); q.pop_front();
    for (auto& d : dirs) {
        int nr = r + d[0], nc = c + d[1];
        if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;

        int newDist = dist[r][c] + 1;

        if (newDist < dist[nr][nc]) {
            // First time this cell is reached at this distance
            dist[nr][nc] = newDist;
            grid[nr][nc] = grid[r][c];
            q.push_back({nr, nc});
        } else if (newDist == dist[nr][nc]) {
            // Tie: arrived at the same time step — take the max color
            grid[nr][nc] = max(grid[nr][nc], grid[r][c]);
            // No need to re-enqueue; the cell is already queued from the first arrival
        }
        // newDist > dist[nr][nc]: cell already settled closer — skip
    }
}
return grid;
```

### Correctness of Tie-Handling

When `newDist == dist[nr][nc]`, the neighbor is already in the queue (enqueued during the first equal-distance arrival). We only update its color value in `grid[][]`. By the time it is dequeued and processed, it will carry the maximum color among all sources that reached it at the same step — which is exactly what we want.

### Complexity

| | Value |
|---|---|
| Time | O(n × m) — each cell enqueued at most once |
| Space | O(n × m) — grid + dist + queue |

## Tags

BFS, multi-source BFS, matrix, graph
