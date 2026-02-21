## Problem

https://leetcode.com/problems/maximum-number-of-groups-entering-a-competition/

You are given a positive integer array `grades` which represents the grades of students in a university. You would like to enter all these students into a competition in ordered non-empty groups, such that the ordering meets the following conditions:

- The sum of the grades of students in the i-th group is **less than** the sum of the grades of students in the (i + 1)-th group, for all groups (except the last).
- The total number of students in the i-th group is **less than** the total number of students in the (i + 1)-th group, for all groups (except the last).

Return the **maximum number of groups** that can be formed.

**Example 1:**
```
Input: grades = [10,6,12,7,3,5]
Output: 3
Explanation: The following is a possible way to form 3 groups of students:
- 1st group has the students with grades = [12]. Sum of grades: 12. Student count: 1
- 2nd group has the students with grades = [6,7]. Sum of grades: 13. Student count: 2
- 3rd group has the students with grades = [10,3,5]. Sum of grades: 18. Student count: 3
```

**Example 2:**
```
Input: grades = [8,8]
Output: 1
Explanation: We can only form 1 group, since forming 2 groups would lead to an equal number of students in both groups.
```

**Constraints:**
- `1 <= grades.length <= 10^5`
- `1 <= grades[i] <= 10^5`

## Observations

1. **The actual grade values don't matter** - only the count of students matters. We could have any grades and still find the maximum number of groups.

2. **Greedy grouping strategy**: If we sort grades in ascending order and assign:
   - Group 1: 1 student (smallest grade)
   - Group 2: 2 students (next 2 smallest grades)
   - Group 3: 3 students (next 3 smallest grades)
   - Group k: k students
   
   Both conditions are automatically satisfied:
   - Student count increases: 1 < 2 < 3 < ... < k ✓
   - Sum increases: Even with the smallest grades in group i and largest in group i-1, since group i has more students, we can always arrange it so the sum is larger

3. **Mathematical formulation**: The problem reduces to finding the maximum k such that:
   ```
   1 + 2 + 3 + ... + k ≤ n
   k(k+1)/2 ≤ n
   ```
   where n is the total number of students.

4. We don't need to actually sort the array or calculate sums - just find the largest k.

## Solution

```python
class Solution:
    def maximumGroups(self, grades):
        n = len(grades)
        k = 0
        need = 1
        while n >= need:
            n -= need
            k += 1
            need += 1
        return k
```

**Explanation:**

The solution uses a greedy simulation approach:

1. **Initialize**: 
   - `n` = total number of students
   - `k` = number of groups formed (starts at 0)
   - `need` = number of students needed for the next group (starts at 1)

2. **Iterative assignment**:
   - While we have at least `need` students remaining:
     - Subtract `need` from `n` (assign students to current group)
     - Increment `k` (formed one more group)
     - Increment `need` (next group needs one more student)

3. **Return** the total number of groups `k`

**Time Complexity**: O(√n)
- We form k groups where k(k+1)/2 ≤ n
- So k ≈ √(2n), meaning the loop runs approximately √n times

**Space Complexity**: O(1)
- Only using a constant amount of extra space

**Alternative approach** (direct formula):
```python
def maximumGroups(self, grades):
    n = len(grades)
    # Solve k(k+1)/2 <= n using quadratic formula
    k = int((-1 + (1 + 8*n)**0.5) / 2)
    return k
```

# Tags
`Array` `Math` `Greedy` `Sorting`

