## Problem

https://leetcode.com/problems/keys-and-rooms/

```
There are n rooms labeled from 0 to n - 1 and all the rooms are locked except for room 0. Your goal is to visit all the rooms. However, you cannot enter a locked room without having its key.

When you visit a room, you may find a set of distinct keys in it. Each key has a number on it, denoting which room it unlocks, and you can take all of them with you to unlock the other rooms.

Given an array rooms where rooms[i] is the set of keys that you can obtain if you visited room i, return true if you can visit all the rooms, or false otherwise.

Example 1:

Input: rooms = [[1],[2],[3],[]]
Output: true
Explanation: 
We visit room 0 and pick up key 1.
We then visit room 1 and pick up key 2.
We then visit room 2 and pick up key 3.
We then visit room 3.
Since we were able to visit every room, we return true.

Example 2:

Input: rooms = [[1,3],[3,0,1],[2],[0]]
Output: false
Explanation: We can not enter room number 2 since the only key that unlocks it is in that room.

Constraints:

n == rooms.length
2 <= n <= 1000
0 <= rooms[i].length <= 1000
1 <= sum(rooms[i].length) <= 3000
0 <= rooms[i][j] < n
All the values of rooms[i] are unique.
```

## Observations

1. **Graph Traversal Problem**: This is essentially a graph connectivity problem where:
   - Each room is a node
   - Each key represents a directed edge to another room
   - We need to check if all nodes are reachable from node `0`

2. **Starting Point**: We always start from room `0` (it's unlocked initially)

3. **Key Collection Strategy**: When we visit a room, we collect all keys from that room, which gives us access to new rooms

4. **Reachability Check**: We need to determine if we can reach all n rooms starting from room `0`

5. **BFS/DFS Approach**: This is a classic graph traversal problem that can be solved using either BFS or DFS

## Solution

The solution uses **Breadth-First Search (BFS)** to traverse the rooms:

### Algorithm:
1. **Initialize**: Start with room 0 (always accessible), mark it as visited
2. **BFS Traversal**: Use a queue to process rooms level by level
3. **Key Collection**: For each visited room, collect all keys and add unvisited rooms to the queue
4. **Visited Tracking**: Keep track of visited rooms to avoid cycles
5. **Final Check**: Return true if we visited all n rooms

### Key Insights:
- **Time Complexity**: `O(N + K)` where N is number of rooms and K is total number of keys
- **Space Complexity**: `O(N)` for the visited set and queue
- **Optimization Note**: The `key_collections` set is actually redundant - we only need to track `visited` rooms since a key is only useful if it leads to an unvisited room

## Tags

array, bfs