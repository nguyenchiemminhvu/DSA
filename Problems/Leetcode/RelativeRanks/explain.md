## Problem

https://leetcode.com/problems/relative-ranks/description/

```
You are given an integer array score of size n, where score[i] is the score of the ith athlete in a competition. All the scores are guaranteed to be unique.

The athletes are placed based on their scores, where the 1st place athlete has the highest score, the 2nd place athlete has the 2nd highest score, and so on. The placement of each athlete determines their rank:

The 1st place athlete's rank is "Gold Medal".
The 2nd place athlete's rank is "Silver Medal".
The 3rd place athlete's rank is "Bronze Medal".
For the 4th place to the nth place athlete, their rank is their placement number (i.e., the xth place athlete's rank is "x").
Return an array answer of size n where answer[i] is the rank of the ith athlete.

Example 1:

Input: score = [5,4,3,2,1]
Output: ["Gold Medal","Silver Medal","Bronze Medal","4","5"]
Explanation: The placements are [1st, 2nd, 3rd, 4th, 5th].

Example 2:

Input: score = [10,3,8,9,4]
Output: ["Gold Medal","5","Bronze Medal","Silver Medal","4"]
Explanation: The placements are [1st, 5th, 3rd, 2nd, 4th].

Constraints:

n == score.length
1 <= n <= 104
0 <= score[i] <= 106
All the values in score are unique.
```

## Observations

1. **Ranking System**: We need to assign ranks based on scores in descending order (highest score gets rank 1)
2. **Special Cases**: The top 3 ranks get special medal names instead of numbers
3. **Position Mapping**: We need to maintain the original positions of athletes while determining their ranks
4. **Unique Scores**: All scores are guaranteed to be unique, so no tie-breaking logic needed

## Solution

The solution uses a clever approach to solve this ranking problem:

### Algorithm Steps:

1. **Create Score-Index Pairs**: 
   - `[(val, i) for i, val in enumerate(score)]` creates pairs of (score, original_index)
   - This preserves the original position of each athlete

2. **Sort by Score Descending**:
   - `sorted(..., key=lambda x: -x[0])` sorts by score in descending order
   - The athlete with the highest score will be at index 0 (rank 1)

3. **Assign Ranks**:
   - Iterate through the sorted list where index represents rank-1
   - Use `rank_to_text(i + 1)` to convert numerical rank to appropriate string
   - Place the rank string back to the original position using `score[idx] = text`

### Key Insights:

- **Time Complexity**: O(n log n) due to sorting
- **Space Complexity**: O(n) for the pairs list
- **In-place Result**: The solution modifies the original score array to store results

### Helper Function `rank_to_text`:
```python
def rank_to_text(rank: int) -> str:
    if rank == 1: return 'Gold Medal'
    if rank == 2: return 'Silver Medal' 
    if rank == 3: return 'Bronze Medal'
    return str(rank)
```

### Example Walkthrough:
For `score = [10,3,8,9,4]`:
1. Pairs: `[(10,0), (3,1), (8,2), (9,3), (4,4)]`
2. Sorted: `[(10,0), (9,3), (8,2), (4,4), (3,1)]`
3. Ranking:
   - (10,0) → rank 1 → "Gold Medal" at index 0
   - (9,3) → rank 2 → "Silver Medal" at index 3  
   - (8,2) → rank 3 → "Bronze Medal" at index 2
   - (4,4) → rank 4 → "4" at index 4
   - (3,1) → rank 5 → "5" at index 1
4. Result: `["Gold Medal","5","Bronze Medal","Silver Medal","4"]`

## Tags

- Array
- Sorting
- Hash Table
- Ranking

