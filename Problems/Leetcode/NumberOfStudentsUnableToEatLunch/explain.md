## Problem

https://leetcode.com/problems/number-of-students-unable-to-eat-lunch/description/

```
The school cafeteria offers circular and square sandwiches at lunch break, referred to by numbers 0 and 1 respectively. All students stand in a queue. Each student either prefers square or circular sandwiches.

The number of sandwiches in the cafeteria is equal to the number of students. The sandwiches are placed in a stack. At each step:

If the student at the front of the queue prefers the sandwich on the top of the stack, they will take it and leave the queue.
Otherwise, they will leave it and go to the queue's end.
This continues until none of the queue students want to take the top sandwich and are thus unable to eat.

You are given two integer arrays students and sandwiches where sandwiches[i] is the type of the i​​​​​​th sandwich in the stack (i = 0 is the top of the stack) and students[j] is the preference of the j​​​​​​th student in the initial queue (j = 0 is the front of the queue). Return the number of students that are unable to eat.

Example 1:

Input: students = [1,1,0,0], sandwiches = [0,1,0,1]
Output: 0 
Explanation:
- Front student leaves the top sandwich and returns to the end of the line making students = [1,0,0,1].
- Front student leaves the top sandwich and returns to the end of the line making students = [0,0,1,1].
- Front student takes the top sandwich and leaves the line making students = [0,1,1] and sandwiches = [1,0,1].
- Front student leaves the top sandwich and returns to the end of the line making students = [1,1,0].
- Front student takes the top sandwich and leaves the line making students = [1,0] and sandwiches = [0,1].
- Front student leaves the top sandwich and returns to the end of the line making students = [0,1].
- Front student takes the top sandwich and leaves the line making students = [1] and sandwiches = [1].
- Front student takes the top sandwich and leaves the line making students = [] and sandwiches = [].
Hence all students are able to eat.

Example 2:

Input: students = [1,1,1,0,0,1], sandwiches = [1,0,0,0,1,1]
Output: 3

Constraints:

1 <= students.length, sandwiches.length <= 100
students.length == sandwiches.length
sandwiches[i] is 0 or 1.
students[i] is 0 or 1.
```

## Observations

1. **Queue and Stack Simulation**: The problem simulates a queue of students and a stack of sandwiches. Students can only take the top sandwich if it matches their preference.

2. **Cyclic Behavior**: If a student doesn't want the top sandwich, they go to the back of the queue. This creates a cyclic pattern where students keep rotating.

3. **Deadlock Condition**: The process stops when no student in the queue wants the current top sandwich. This happens when all remaining students have a different preference than the top sandwich.

4. **Key Insight**: We don't need to simulate the entire process. We can count how many students prefer each type (0 or 1) and match them against the sandwiches in order.

5. **Alternative Approach**: Since sandwiches must be taken from the top of the stack in order, we can iterate through the sandwich stack and check if there are enough students who prefer each sandwich type.

6. **Termination**: The simulation terminates when either:
   - All students get their preferred sandwiches (return 0)
   - No student in the queue wants the current top sandwich (return remaining student count)

## Solution

### Approach 1: Direct Simulation (Current Implementation)

The current solution in `solve.py` uses direct simulation:

```python
def countStudents(self, students: List[int], st: List[int]) -> int:
    st.reverse()  # Make it easier to work with stack (pop from end)
    
    count_unable = 0
    students = deque(students)  # Use deque for efficient front operations
    
    # Continue until stack is empty, queue is empty, or no progress can be made
    while st and students and count_unable < len(students):
        if st[-1] == students[0]:  # Student wants the top sandwich
            count_unable = 0  # Reset counter since progress was made
            st.pop()  # Remove sandwich
            students.popleft()  # Remove student
        else:  # Student doesn't want the sandwich
            count_unable += 1  # Increment unable counter
            students.append(students.popleft())  # Move student to back
    
    return count_unable
```

**Time Complexity**: O(n²) in worst case where n is the number of students
**Space Complexity**: O(n) for the deque

### Approach 2: Counting Optimization

A more efficient approach would be to count preferences:

```python
def countStudents(self, students: List[int], sandwiches: List[int]) -> int:
    # Count student preferences
    count = [0, 0]  # count[0] = students who prefer 0, count[1] = students who prefer 1
    for student in students:
        count[student] += 1
    
    # Try to satisfy each sandwich in order
    for sandwich in sandwiches:
        if count[sandwich] > 0:
            count[sandwich] -= 1  # Student takes the sandwich
        else:
            # No student wants this sandwich, remaining students can't eat
            break
    
    return sum(count)  # Return total remaining students
```

**Time Complexity**: O(n)
**Space Complexity**: O(1)

### Why the Current Solution Works

1. **Stack Reversal**: Reversing the sandwich stack makes it easier to pop from the end (simulating stack behavior)

2. **Deque Usage**: Using `collections.deque` provides O(1) operations for both front removal and back insertion

3. **Progress Tracking**: The `count_unable` variable tracks consecutive students who couldn't get their preferred sandwich

4. **Termination Logic**: The loop continues while:
   - There are sandwiches left (`st`)
   - There are students left (`students`) 
   - Progress can still be made (`count_unable < len(students)`)

5. **Progress Reset**: When a student successfully takes a sandwich, `count_unable` resets to 0, indicating that progress was made

The solution correctly handles the cyclic nature of the queue and detects when no more progress can be made.

# Tags

- **Queue/Stack Simulation**
- **Array/Deque**
- **Counting**
- **Greedy Algorithm**
- **Easy Difficulty**

