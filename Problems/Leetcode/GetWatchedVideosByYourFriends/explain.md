## Problem

https://leetcode.com/problems/get-watched-videos-by-your-friends/description/

There are `n` people, each person has a unique id between `0` and `n-1`. Given the arrays `watchedVideos` and `friends`, where `watchedVideos[i]` and `friends[i]` contain the list of watched videos and the list of friends respectively for the person with `id = i`.

Level `k` of videos are all watched videos by people whose **shortest path** to you is exactly `k`. Given your `id` and a target `level`, return the list of videos watched by all people at exactly that level, ordered by:
1. Frequency (ascending)
2. Alphabetically (ascending) for ties

**Example 1:**
```
Input:  watchedVideos = [["A","B"],["C"],["B","C"],["D"]]
        friends = [[1,2],[0,3],[0,3],[1,2]], id = 0, level = 1
Output: ["B","C"]
```
Friends of person 0 are persons 1 and 2.
- Person 1 watched: `["C"]`
- Person 2 watched: `["B","C"]`
- Frequencies: B→1, C→2 → sorted: `["B","C"]`

**Example 2:**
```
Input:  watchedVideos = [["A","B"],["C"],["B","C"],["D"]]
        friends = [[1,2],[0,3],[0,3],[1,2]], id = 0, level = 2
Output: ["D"]
```
Friends-of-friends of person 0 (at distance 2) is only person 3, who watched `["D"]`.

---

## Observations

- The social graph is **undirected**: if `j` is in `friends[i]`, then `i` is in `friends[j]`.
- We need to find all people at **shortest path distance exactly `level`** from the given `id`. This is a classic **BFS layer-by-layer traversal** problem.
- BFS naturally assigns the shortest distance to each node. Processing nodes level by level lets us stop exactly at the desired depth.
- Once we have the set of people at that level, we collect all their watched videos into a frequency map.
- The final sort is a two-key sort: primary key is frequency (ascending), secondary key is the video name (alphabetically ascending).

---

## Solution Explanation

```python
class Solution:
    def watchedVideosByFriends(self, videos: List[List[str]], friends: List[List[int]], id: int, level: int) -> List[str]:
        n = len(videos)

        friends_at_level = []
        steps = -1
        q = deque([id])
        visited = set()
        visited.add(id)
        while q:
            steps += 1
            row = []
            z = len(q)
            for _ in range(z):
                cur = q.popleft()
                row.append(cur)
                for f in friends[cur]:
                    if f not in visited:
                        visited.add(f)
                        q.append(f)
            
            if steps == level:
                friends_at_level = row

        f = defaultdict(int)
        for i in friends_at_level:
            for video in videos[i]:
                f[video] += 1

        return sorted(f.keys(), key=lambda x: (f[x], x))
```

### Step 1 — BFS to find people at the target level

We perform a standard **BFS** starting from `id`, tracking visited nodes to avoid revisiting. The key insight is processing the queue **snapshot by snapshot** (layer by layer):

- Before processing each layer, take `z = len(q)` — the number of nodes in the current frontier.
- Process exactly `z` nodes, collecting them in `row`, and enqueue their unvisited neighbors for the next layer.
- Increment `steps` at the start of each layer. When `steps == level`, `row` contains all people at exactly that distance.

This is exactly like a multi-source BFS where each "source" is a person in the current level frontier. The `visited` set prevents shorter-path nodes from being counted again at a deeper level.

### Step 2 — Count video frequencies

Once `friends_at_level` is populated, we iterate over every person in it and count every video they watched using a `defaultdict(int)`.

### Step 3 — Sort and return

```python
sorted(f.keys(), key=lambda x: (f[x], x))
```

Python's `sorted` with a tuple key sorts by the first element (frequency) first, then by the second element (video name string) for ties. This gives us the required ordering in a single pass.

### Complexity

| | |
|---|---|
| **Time** | $O(n + E + V \log V)$ where $E$ is total edges in the friend graph and $V$ is the total number of distinct videos across all friends at the target level |
| **Space** | $O(n + V)$ for the BFS queue, visited set, and frequency map |
