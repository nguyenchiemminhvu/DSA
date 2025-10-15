## Problem

https://leetcode.com/problems/maximum-matching-of-players-with-trainers/

```
You are given a 0-indexed integer array players, where players[i] represents the ability of the ith player. You are also given a 0-indexed integer array trainers, where trainers[j] represents the training capacity of the jth trainer.

The ith player can match with the jth trainer if the player's ability is less than or equal to the trainer's training capacity. Additionally, the ith player can be matched with at most one trainer, and the jth trainer can be matched with at most one player.

Return the maximum number of matchings between players and trainers that satisfy these conditions.

Example 1:

Input: players = [4,7,9], trainers = [8,2,5,8]
Output: 2
Explanation:
One of the ways we can form two matchings is as follows:
- players[0] can be matched with trainers[0] since 4 <= 8.
- players[1] can be matched with trainers[3] since 7 <= 8.
It can be proven that 2 is the maximum number of matchings that can be formed.

Example 2:

Input: players = [1,1,1], trainers = [10]
Output: 1
Explanation:
The trainer can be matched with any of the 3 players.
Each player can only be matched with one trainer, so the maximum answer is 1.

Constraints:

1 <= players.length, trainers.length <= 105
1 <= players[i], trainers[j] <= 109
```

## Observations

1. **Constraint Analysis**:
   - Each player can match with at most one trainer
   - Each trainer can match with at most one player
   - A player matches with a trainer if `player_ability <= trainer_capacity`
   - This is essentially a bipartite matching problem with constraints

2. **Greedy Approach Insight**:
   - If we sort both arrays, we can use a greedy two-pointer technique
   - Key insight: Match the weakest available player with the weakest suitable trainer
   - Why? If a trainer can train a stronger player, they can also train a weaker player
   - By matching weaker players first, we save stronger trainers for stronger players

3. **Optimal Strategy**:
   - Sort both `players` and `trainers` in ascending order
   - For each player (starting from the weakest), find the first trainer who can handle them
   - If a trainer cannot handle the current player, they cannot handle any stronger player either
   - Move to the next trainer until we find a suitable match or run out of trainers

4. **Time Complexity**: O(n log n + m log m) where n = len(players), m = len(trainers)
   - Sorting both arrays dominates the complexity
   - The two-pointer traversal is O(n + m)

5. **Space Complexity**: O(1) or O(n + m) depending on the sorting algorithm used
   - In-place sorting: O(1) additional space
   - Python's Timsort may use O(n) additional space in worst case

## Solution

### Approach: Two Pointers with Greedy Matching

1. **Sorting Phase**: Both arrays are sorted in ascending order
   - `players = [4,7,9]` → stays `[4,7,9]`
   - `trainers = [8,2,5,8]` → becomes `[2,5,8,8]`

2. **Matching Phase** (using Example 1):
   - `ip=0, it=0`: `trainers[0]=2 < players[0]=4` → trainer too weak, `it++`
   - `ip=0, it=1`: `trainers[1]=5 >= players[0]=4` → **Match!** `ip++, it++`
   - `ip=1, it=2`: `trainers[2]=8 >= players[1]=7` → **Match!** `ip++, it++`
   - `ip=2, it=3`: `trainers[3]=8 < players[2]=9` → trainer too weak, `it++`
   - `it=4`: Out of trainers, stop
   - Result: `ip = 2` (two matches made)

3. **Why This Works**:
   - By sorting, we ensure we try to match the weakest player first
   - If a trainer is too weak for the current player, they're too weak for all remaining players
   - We can safely skip that trainer and never look back
   - This greedy approach guarantees the maximum number of matches

### Edge Cases:
- All trainers too weak: returns 0
- All players too strong: returns 0
- More players than trainers: returns at most `len(trainers)`
- More trainers than players: returns at most `len(players)`

## Tags

array, greedy