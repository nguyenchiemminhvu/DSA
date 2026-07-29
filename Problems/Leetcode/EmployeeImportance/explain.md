# Employee Importance

## Problem

https://leetcode.com/problems/employee-importance/description/

You have a data structure of employee information, including the employee's unique ID, importance value, and direct subordinates' IDs.

You are given an array of employees `employees` where:

- `employees[i].id` is the ID of the i-th employee.
- `employees[i].importance` is the importance value of the i-th employee.
- `employees[i].subordinates` is a list of the IDs of the direct subordinates of the i-th employee.

Given an integer `id` that represents an employee's ID, return the **total importance value** of this employee and all their direct and indirect subordinates.

### Examples

**Example 1:**
- Input: `employees = [[1,5,[2,3]],[2,3,[]],[3,3,[]]], id = 1`
- Output: `11`
- Explanation: Employee 1 has importance 5 and two direct subordinates (2 and 3), each with importance 3. Total = 5 + 3 + 3 = 11.

**Example 2:**
- Input: `employees = [[1,2,[5]],[5,-3,[]]], id = 5`
- Output: `-3`
- Explanation: Employee 5 has importance -3 and no subordinates.

### Constraints

- `1 <= employees.length <= 2000`
- `1 <= employees[i].id <= 2000`
- All `employees[i].id` are unique.
- `-100 <= employees[i].importance <= 100`
- One employee has at most one direct leader and may have several subordinates.
- The IDs in `employees[i].subordinates` are valid IDs.

---

## Observations

### 1. **Tree-like Hierarchy**
   - The employee structure forms a forest (collection of trees).
   - Each employee is a node; subordinate relationships are directed edges from parent to children.
   - We need to **sum importance values** across an entire subtree rooted at the given `id`.

### 2. **Graph Traversal Problem**
   - Starting from the target employee, we must visit every reachable subordinate (direct and indirect).
   - This is a classic **tree/graph traversal** — both DFS and BFS work naturally here.

### 3. **Fast Lookup by ID**
   - The input is a list of employee objects, not indexed by ID directly.
   - Build a **hash map** (`id → employee`) for O(1) lookup during traversal.
   - Without this, each lookup would cost O(n), making the overall solution O(n²).

### 4. **DFS Approach**
   - Start at the given `id`.
   - Recursively (or iteratively with a stack) visit all subordinates.
   - Accumulate importance at every visited node.
   - **Time Complexity**: O(n) — each employee is visited at most once.
   - **Space Complexity**: O(n) — recursion stack / hash map.

### 5. **BFS Approach**
   - Use a queue initialized with the target `id`.
   - Dequeue an employee, add their importance, enqueue all their subordinates.
   - Continue until the queue is empty.
   - Same time and space complexity as DFS.

---

## Solution

### Algorithm: DFS with Hash Map

**Time Complexity**: O(n)  
**Space Complexity**: O(n)

### Key Steps

1. **Build a hash map** mapping each `id` to its employee object for O(1) access.
2. **DFS from the target `id`**: accumulate importance, then recurse into each subordinate.
3. Return the accumulated total.

### Code

```python
from typing import List

class Employee:
    def __init__(self, id: int, importance: int, subordinates: List[int]):
        self.id = id
        self.importance = importance
        self.subordinates = subordinates

class Solution:
    def getImportance(self, employees: List[Employee], id: int) -> int:
        # Step 1: Build id -> employee map for O(1) lookup
        emp_map = {e.id: e for e in employees}

        # Step 2: DFS to accumulate total importance
        def dfs(eid: int) -> int:
            emp = emp_map[eid]
            total = emp.importance
            for sub_id in emp.subordinates:
                total += dfs(sub_id)
            return total

        return dfs(id)
```

### Alternative: BFS

```python
from collections import deque

class Solution:
    def getImportance(self, employees: List[Employee], id: int) -> int:
        emp_map = {e.id: e for e in employees}

        total = 0
        queue = deque([id])
        while queue:
            eid = queue.popleft()
            emp = emp_map[eid]
            total += emp.importance
            queue.extend(emp.subordinates)

        return total
```

### Execution Flow (Example 1)

```
employees = [[1,5,[2,3]], [2,3,[]], [3,3,[]]], id = 1

emp_map = {1: (5,[2,3]), 2: (3,[]), 3: (3,[])}

DFS(1):
  importance = 5
  → DFS(2): importance = 3, no subordinates → return 3
  → DFS(3): importance = 3, no subordinates → return 3
  return 5 + 3 + 3 = 11
```

---

## Tags

- **Hash Map**: O(1) employee lookup by ID
- **DFS / BFS**: Full subtree traversal
- **Tree Traversal**: Summing values across a rooted subtree
- **Graph**: Directed acyclic graph representing org hierarchy

