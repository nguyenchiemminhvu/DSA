## Problem

https://leetcode.com/problems/maximum-compatibility-score-sum/description/

```
There is a survey that consists of n questions where each question's answer is either 0 (no) or 1 (yes).

The survey was given to m students numbered from 0 to m - 1 and m mentors numbered from 0 to m - 1. 
The answers of the students are represented by a 2D integer array students where students[i] is an 
integer array that contains the answers of the ith student (0-indexed). The answers of the mentors 
are represented by a 2D integer array mentors where mentors[j] is an integer array that contains 
the answers of the jth mentor (0-indexed).

Each student will be assigned to one mentor, and each mentor will have one student assigned to them. 
The compatibility score of a student-mentor pair is the number of answers that are the same for both 
the student and the mentor.

For example, if the student's answers were [1, 0, 1] and the mentor's answers were [0, 0, 1], 
then their compatibility score is 2 because only the second and the third answers are the same.

You are tasked with finding the optimal student-mentor pairings to maximize the sum of the 
compatibility scores.

Given students and mentors, return the maximum compatibility score sum that can be achieved.

Example 1:
Input: students = [[1,1,0],[1,0,1],[0,0,1]], mentors = [[1,0,0],[0,0,1],[1,1,0]]
Output: 8
Explanation: We assign students to mentors in the following way:
- student 0 to mentor 2 with a compatibility score of 3.
- student 1 to mentor 0 with a compatibility score of 2.
- student 2 to mentor 1 with a compatibility score of 3.
The compatibility score sum is 3 + 2 + 3 = 8.

Example 2:
Input: students = [[0,0],[0,0],[0,0]], mentors = [[1,1],[1,1],[1,1]]
Output: 0
Explanation: The compatibility score of any student-mentor pair is 0.

Constraints:
- m == students.length == mentors.length
- n == students[i].length == mentors[j].length
- 1 <= m, n <= 8
- students[i][k] is either 0 or 1.
- mentors[j][k] is either 0 or 1.
```

## Observations

1. **Problem Type**: This is a **maximum weighted bipartite matching** problem, where we need to find 
   the optimal 1-to-1 assignment between students and mentors.

2. **Key Constraint**: The constraint `1 <= m, n <= 8` is crucial. With at most 8 students/mentors, 
   there are at most **8! = 40,320** possible permutations, making a brute force approach feasible.

3. **Compatibility Score**: For each student-mentor pair, the compatibility score is simply the count 
   of matching answers across all questions. This can be computed in O(n) time.

4. **Search Space**: 
   - We need to explore all possible ways to assign m students to m mentors
   - This is equivalent to finding all permutations of mentor assignments
   - Total permutations: m!

5. **Optimization Opportunity**: While the brute force approach works given the constraints, this 
   problem could also be solved using:
   - **Dynamic Programming with bitmask**: Track which mentors have been assigned (O(m² × 2^m))
   - **Hungarian Algorithm**: For general assignment problems (O(m³))
   - **Backtracking with pruning**: To potentially reduce the search space

## Solution

### Approach: Brute Force with Permutations

**Strategy**:
1. Generate all possible permutations of mentor indices [0, 1, ..., m-1]
2. For each permutation, assign students[i] to mentors[permutation[i]]
3. Calculate the total compatibility score for this assignment
4. Track and return the maximum score across all permutations

**Algorithm**:
```python
from itertools import permutations

class Solution:
    def maxCompatibilitySum(self, students: List[List[int]], mentors: List[List[int]]) -> int:
        res = 0
        n = len(students)
        perms = permutations([i for i in range(n)])
        
        for m_idx in perms:
            count = 0
            i = 0
            for im in m_idx:
                # Map student[i] with mentor[im]
                # Count matching answers
                count += sum(1 if students[i][j] == mentors[im][j] else 0 
                           for j in range(len(students[i])))
                i += 1
            res = max(res, count)
        
        return res
```

**How it works**:
- `permutations([0, 1, ..., n-1])` generates all possible orderings of mentor indices
- For each permutation `m_idx`, we pair `students[i]` with `mentors[m_idx[i]]`
- For each pair, we count matching answers: `sum(1 if students[i][j] == mentors[im][j] else 0 ...)`
- We keep track of the maximum total score across all permutations

**Complexity Analysis**:
- **Time Complexity**: O(m! × m × n)
  - m! permutations to generate
  - For each permutation, iterate through m students
  - For each student, compare n answers with their assigned mentor
  - With m ≤ 8: 8! × 8 × 8 = 2,580,480 operations (very manageable)

- **Space Complexity**: O(m)
  - Storing one permutation at a time
  - Recursion stack for permutation generation

**Why this works given the constraints**:
- The small constraint (m ≤ 8) makes factorial time complexity acceptable
- Python's `itertools.permutations` is highly optimized
- The problem guarantees a solution exists (even if score is 0)

**Alternative Optimization (DP with Bitmask)**:
```python
def maxCompatibilitySum(self, students: List[List[int]], mentors: List[List[int]]) -> int:
    m, n = len(students), len(students[0])
    
    # Precompute all compatibility scores
    scores = [[0] * m for _ in range(m)]
    for i in range(m):
        for j in range(m):
            scores[i][j] = sum(students[i][k] == mentors[j][k] for k in range(n))
    
    # DP with bitmask: dp[i][mask] = max score assigning first i students 
    # to mentors indicated by mask
    dp = {}
    
    def solve(student_idx, used_mask):
        if student_idx == m:
            return 0
        if (student_idx, used_mask) in dp:
            return dp[(student_idx, used_mask)]
        
        max_score = 0
        for mentor_idx in range(m):
            if not (used_mask & (1 << mentor_idx)):  # Mentor not used
                score = scores[student_idx][mentor_idx] + \
                       solve(student_idx + 1, used_mask | (1 << mentor_idx))
                max_score = max(max_score, score)
        
        dp[(student_idx, used_mask)] = max_score
        return max_score
    
    return solve(0, 0)
```

This DP approach has better theoretical complexity O(m² × 2^m) but may not be faster in practice 
for m ≤ 8 due to constant factors.

# Tags

`#bipartite-matching` `#permutations` `#brute-force` `#dynamic-programming` `#bitmask` `#assignment-problem`

