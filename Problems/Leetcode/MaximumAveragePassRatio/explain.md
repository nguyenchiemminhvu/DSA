## Problem

https://leetcode.com/problems/maximum-average-pass-ratio/description/

```
There is a school that has classes of students and each class will be having a final exam. You are given a 2D integer array classes, where classes[i] = [passi, totali]. You know beforehand that in the ith class, there are totali total students, but only passi number of students will pass the exam.

You are also given an integer extraStudents. There are another extraStudents brilliant students that are guaranteed to pass the exam of any class they are assigned to. You want to assign each of the extraStudents students to a class in a way that maximizes the average pass ratio across all the classes.

The pass ratio of a class is equal to the number of students of the class that will pass the exam divided by the total number of students of the class. The average pass ratio is the sum of pass ratios of all the classes divided by the number of the classes.

Return the maximum possible average pass ratio after assigning the extraStudents students. Answers within 10-5 of the actual answer will be accepted.

Example 1:

Input: classes = [[1,2],[3,5],[2,2]], extraStudents = 2
Output: 0.78333
Explanation: You can assign the two extra students to the first class. The average pass ratio will be equal to (3/4 + 3/5 + 2/2) / 3 = 0.78333.

Example 2:

Input: classes = [[2,4],[3,9],[4,5],[2,10]], extraStudents = 4
Output: 0.53485

Constraints:

1 <= classes.length <= 105
classes[i].length == 2
1 <= passi <= totali <= 105
1 <= extraStudents <= 105
```

## Observations

1. **Pass Ratio**: For each class, the pass ratio is `pass[i] / total[i]`
2. **Goal**: Maximize the average pass ratio across all classes after distributing `extraStudents`
3. **Key Insight**: Adding one student to a class increases both numerator and denominator by 1
   - New ratio becomes `(pass[i] + 1) / (total[i] + 1)`
   - The gain in pass ratio is: `(pass[i] + 1)/(total[i] + 1) - pass[i]/total[i]`
4. **Diminishing Returns**: The gain from adding students to a class decreases as more students are added
   - For example: Adding to class [1,2] gives gain of 1/3 - 1/2 = -1/6 (actually 2/3 - 1/2 = 1/6)
   - Adding to class [2,3] gives gain of 3/4 - 2/3 = 1/12
5. **Greedy Strategy**: Always add the next student to the class that gives maximum gain in pass ratio
6. **Priority Queue**: Use a max heap to efficiently find the class with maximum potential gain

## Solution

### Algorithm Explanation

The solution uses a **greedy approach with a max heap (priority queue)** to optimally distribute extra students:

1. **Calculate Initial Gains**: For each class, calculate how much the pass ratio would improve if we add one student
   ```python
   gain = (pass + 1)/(total + 1) - pass/total
   ```

2. **Max Heap Setup**: Use a priority queue to always get the class with maximum potential gain
   - Python's `heapq` is a min heap, so we store negative gains to simulate max heap
   - Store tuples: `(-gain, (current_pass, current_total))`

3. **Greedy Distribution**: For each extra student:
   - Pop the class with maximum gain from heap
   - Add one student to that class (increment both pass and total)
   - Recalculate the new gain for this updated class
   - Push the updated class back to heap

4. **Final Calculation**: After distributing all extra students, calculate the average pass ratio

### Mathematical Foundation

The gain formula can be derived as:
```
gain = (p+1)/(t+1) - p/t
     = [(p+1)×t - p×(t+1)] / [t×(t+1)]
     = [pt + t - pt - p] / [t×(t+1)]
     = (t - p) / [t×(t+1)]
```

This shows that:
- Gain is always positive when `t > p` (which is always true in valid inputs)
- Gain decreases as `t` increases (diminishing returns)
- Classes with larger gaps between total and passing students benefit more initially

### Time Complexity
- **Setup**: O(n log n) - inserting n classes into heap
- **Distribution**: O(k log n) - k extra students, each operation is O(log n)
- **Final calculation**: O(n log n) - popping all elements
- **Overall**: O((n + k) log n)

### Space Complexity
- O(n) for the priority queue storing all classes

### Why This Works
The greedy approach is optimal because:
1. Each class's gain function is **concave** (diminishing returns)
2. We want to maximize the sum of individual gains
3. At each step, choosing the class with maximum current gain is locally optimal
4. Due to the concave nature, this local optimality leads to global optimality

## Tags

array, greedy, max heap, priority queue