## Problem

https://leetcode.com/problems/reward-top-k-students/

```
You are given two string arrays positive_feedback and negative_feedback, containing the words denoting 
positive and negative feedback, respectively. Note that no word is both positive and negative.

Initially every student has 0 points. Each positive word in a feedback report increases the points of 
a student by 3, whereas each negative word decreases the points by 1.

You are given n feedback reports, represented by a 0-indexed string array report and a 0-indexed integer 
array student_id, where student_id[i] represents the ID of the student who has received the feedback 
report report[i]. The ID of each student is unique.

Given an integer k, return the top k students after ranking them in non-increasing order by their points. 
In case more than one student has the same points, the one with the lower ID ranks higher.

Example 1:
Input: positive_feedback = ["smart","brilliant","studious"], negative_feedback = ["not"], 
       report = ["this student is studious","the student is smart"], student_id = [1,2], k = 2
Output: [1,2]
Explanation: Both the students have 1 positive feedback and 3 points but since student 1 has a lower ID 
he ranks higher.

Example 2:
Input: positive_feedback = ["smart","brilliant","studious"], negative_feedback = ["not"], 
       report = ["this student is not studious","the student is smart"], student_id = [1,2], k = 2
Output: [2,1]
Explanation: 
- The student with ID 1 has 1 positive feedback and 1 negative feedback, so he has 3-1=2 points. 
- The student with ID 2 has 1 positive feedback, so he has 3 points. 
Since student 2 has more points, [2,1] is returned.

Constraints:
- 1 <= positive_feedback.length, negative_feedback.length <= 10^4
- 1 <= positive_feedback[i].length, negative_feedback[j].length <= 100
- Both positive_feedback[i] and negative_feedback[j] consists of lowercase English letters
- No word is present in both positive_feedback and negative_feedback
- n == report.length == student_id.length
- 1 <= n <= 10^4
- report[i] consists of lowercase English letters and spaces ' '
- There is a single space between consecutive words of report[i]
- 1 <= report[i].length <= 100
- 1 <= student_id[i] <= 10^9
- All the values of student_id[i] are unique
- 1 <= k <= n
```

## Observations

1. **Scoring System**: Each positive word adds 3 points, each negative word subtracts 1 point
2. **Word Lookup**: Need fast lookup for positive and negative words → use sets for O(1) lookup
3. **Student Tracking**: Need to track scores for each student → use hashmap/dictionary
4. **Ranking Criteria**: 
   - Primary: Higher points rank higher
   - Secondary: Lower student ID ranks higher (tiebreaker)
5. **Output**: Return top k students after sorting

## Solution

### Approach: Hash Set + Score Calculation + Sorting

**Algorithm:**

1. **Convert word lists to sets** for O(1) lookup time
   - `spos = set(pos)` for positive feedback words
   - `sneg = set(neg)` for negative feedback words

2. **Calculate scores for each student:**
   - Iterate through each feedback report
   - Split report into individual words
   - For each word:
     - If in positive set: add 3 points
     - If in negative set: subtract 1 point
     - Otherwise: no change (0 points)
   - Store scores in a dictionary with student_id as key

3. **Create ranking tuples:**
   - Convert scores dictionary to list of tuples: `(score, -student_id)`
   - Use negative student_id so that lower IDs have higher priority (larger negative value)
   - This allows sorting by score descending, then by student_id ascending

4. **Sort and return top k:**
   - Sort by: `-score` (descending points), then `-student_id` (ascending actual ID)
   - Take first k elements
   - Extract student IDs (negate back to positive)

**Note on the provided code:**
The code uses a min-heap approach but then sorts the entire heap, which is inefficient. A simpler approach is to directly sort all students:

```python
from typing import List
from collections import defaultdict

class Solution:
    def topStudents(self, pos: List[str], neg: List[str], report: List[str], 
                    student_id: List[int], k: int) -> List[int]:
        # Convert to sets for O(1) lookup
        spos = set(pos)
        sneg = set(neg)
        
        # Calculate scores for each student
        scores = defaultdict(int)
        for i in range(len(student_id)):
            words = report[i].split()
            for word in words:
                if word in spos:
                    scores[student_id[i]] += 3
                elif word in sneg:
                    scores[student_id[i]] -= 1
        
        # Sort students by score (desc) then by ID (asc)
        students = sorted(scores.items(), key=lambda x: (-x[1], x[0]))
        
        # Return top k student IDs
        return [sid for sid, score in students[:k]]
```

**Complexity Analysis:**
- **Time Complexity**: O(n * m + s * log s)
  - n = number of reports, m = average words per report
  - s = number of unique students
  - Calculating scores: O(n * m)
  - Sorting: O(s * log s)
- **Space Complexity**: O(p + n + s)
  - p = total positive + negative words
  - s = number of unique students for scores dictionary

# Tags
`Hash Table`, `String`, `Sorting`, `Heap (Priority Queue)`

