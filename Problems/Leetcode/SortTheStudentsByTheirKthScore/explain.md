## Problem

https://leetcode.com/problems/sort-the-students-by-their-kth-score/description/

Given a **0-indexed m × n** integer matrix `score` where each row represents one student and `score[i][j]` is the score of the `i`-th student on the `j`-th exam, and an integer `k`, **sort the rows** of the matrix by the scores in column `k` from **highest to lowest** and return the sorted matrix.

---

## Observations

1. **Row identity matters** — we need to sort entire rows together; reordering individual elements within a row would destroy the student's record.
2. **Single column drives the order** — only column `k` determines the relative rank of two students; all other columns just follow along.
3. **Distinct integers** — the problem guarantees all scores are distinct, so there are no ties to worry about in column `k`.
4. **In-place vs. index sort** — we can either sort the rows directly (mutating the matrix) or build an ordered list of original row indices and reconstruct the result. Both are O(m log m).
5. **Stable sort is irrelevant here** because scores are distinct; however, using a stable sort makes the code predictable in general.

---

## Solution Explanation

```python
class Solution:
    def sortTheStudents(self, score: List[List[int]], k: int) -> List[List[int]]:
        m, n = len(score), len(score[0])
        student_ids = [i for i in range(m)]
        student_ids.sort(key=lambda s: (score[s][k], s), reverse=True)

        res = []
        for sid in student_ids:
            res.append(score[sid])
        return res
```

### Step-by-step walkthrough

1. **Create an index list** `student_ids = [0, 1, ..., m-1]`.  
   Instead of moving the actual rows around during comparison, we keep track of which original row index should end up where.

2. **Sort the index list** using a custom key `lambda s: (score[s][k], s)` with `reverse=True`.  
   - The primary sort key is `score[s][k]` — the score of student `s` on exam `k`.  
   - Sorting in reverse (`reverse=True`) gives us **highest → lowest** order.  
   - The secondary key `s` (the student index) is a tiebreaker; since all scores are distinct it never actually fires, but it keeps the sort deterministic.

3. **Reconstruct the result** by iterating through the sorted `student_ids` and appending the corresponding row from `score`. This produces the matrix with rows reordered by descending k-th exam score.

### Example trace — `score = [[10,6,9,1],[7,5,11,2],[4,8,3,15]], k = 2`

| Student index | Score at k=2 |
|:---:|:---:|
| 0 | 9 |
| 1 | 11 |
| 2 | 3 |

After sorting `student_ids` by `score[s][2]` descending → `[1, 0, 2]`

Result rows in that order:
- `score[1]` = `[7, 5, 11, 2]`
- `score[0]` = `[10, 6, 9, 1]`
- `score[2]` = `[4, 8, 3, 15]`

Output: `[[7,5,11,2],[10,6,9,1],[4,8,3,15]]` ✓

### Complexity

| | Value |
|---|---|
| **Time** | O(m log m) — dominated by the sort |
| **Space** | O(m) — for the `student_ids` index list and the result list |

