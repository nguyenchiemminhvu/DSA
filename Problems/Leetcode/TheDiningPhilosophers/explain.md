## Problem

https://leetcode.com/problems/the-dining-philosophers/description/

```
Five silent philosophers sit at a round table with bowls of spaghetti. Forks are placed between each pair of adjacent philosophers.

Each philosopher must alternately think and eat. However, a philosopher can only eat spaghetti when they have both left and right forks. Each fork can be held by only one philosopher and so a philosopher can use the fork only if it is not being used by another philosopher. After an individual philosopher finishes eating, they need to put down both forks so that the forks become available to others. A philosopher can take the fork on their right or the one on their left as they become available, but cannot start eating before getting both forks.

Eating is not limited by the remaining amounts of spaghetti or stomach space; an infinite supply and an infinite demand are assumed.

Design a discipline of behaviour (a concurrent algorithm) such that no philosopher will starve; i.e., each can forever continue to alternate between eating and thinking, assuming that no philosopher can know when others may want to eat or think.

The problem statement and the image above are taken from wikipedia.org

The philosophers' ids are numbered from 0 to 4 in a clockwise order. Implement the function void wantsToEat(philosopher, pickLeftFork, pickRightFork, eat, putLeftFork, putRightFork) where:

philosopher is the id of the philosopher who wants to eat.
pickLeftFork and pickRightFork are functions you can call to pick the corresponding forks of that philosopher.
eat is a function you can call to let the philosopher eat once he has picked both forks.
putLeftFork and putRightFork are functions you can call to put down the corresponding forks of that philosopher.
The philosophers are assumed to be thinking as long as they are not asking to eat (the function is not being called with their number).
Five threads, each representing a philosopher, will simultaneously use one object of your class to simulate the process. The function may be called for the same philosopher more than once, even before the last call ends.

Example 1:

Input: n = 1
Output: [[3,2,1],[3,1,1],[3,0,3],[3,1,2],[3,2,2],[4,2,1],[4,1,1],[2,2,1],[2,1,1],[1,2,1],[2,0,3],[2,1,2],[2,2,2],[4,0,3],[4,1,2],[4,2,2],[1,1,1],[1,0,3],[1,1,2],[1,2,2],[0,1,1],[0,2,1],[0,0,3],[0,1,2],[0,2,2]]
Explanation:
n is the number of times each philosopher will call the function.
The output array describes the calls you made to the functions controlling the forks and the eat function, its format is:
output[i] = [a, b, c] (three integers)
- a is the id of a philosopher.
- b specifies the fork: {1 : left, 2 : right}.
- c specifies the operation: {1 : pick, 2 : put, 3 : eat}.

Constraints:

1 <= n <= 60
```

## Observations

1. **Classic Concurrency Problem**: This is the famous Dining Philosophers problem - a classic synchronization problem in computer science that demonstrates deadlock and starvation issues.

2. **Deadlock Risk**: If all philosophers pick up their left fork simultaneously, none can pick up their right fork, creating a circular wait (deadlock).

3. **Starvation Risk**: Some philosophers might never get a chance to eat if the scheduling isn't fair.

4. **Resource Sharing**: 5 forks are shared among 5 philosophers, where each philosopher needs 2 adjacent forks to eat.

5. **Threading Challenge**: The solution must handle multiple threads (philosophers) trying to access shared resources (forks) concurrently.

## Solution

The provided solution uses a **Sequential Ordering** approach with a condition variable to prevent deadlock:

### Key Components:
- **Global State**: `idx` tracks which philosopher can eat next (0-4)
- **Condition Variable**: `cond` for thread synchronization and waiting
- **Sequential Access**: Only allows philosophers to eat in a specific order (0, 2, 4, 1, 3, 0, ...)

### How It Works:

1. **Entry Control**: Each philosopher waits until it's their turn (`philosopher == idx`)
2. **Resource Acquisition**: Once allowed, philosopher picks both forks safely (no competition)
3. **Eating**: Philosopher eats without interference
4. **Resource Release**: Philosopher puts down both forks
5. **Next Turn**: Updates `idx = (idx + 2) % 5` to skip to next non-adjacent philosopher
6. **Notification**: Wakes all waiting philosophers to check if it's their turn

### Why This Works:

- **Deadlock Prevention**: Only one philosopher eats at a time, eliminating circular wait
- **Starvation Prevention**: The `(idx + 2) % 5` pattern ensures all philosophers get turns:
  - Sequence: 0 → 2 → 4 → 1 → 3 → 0 → ...
  - This alternates between non-adjacent philosophers, ensuring fair access

### Algorithm Analysis:
- **Time Complexity**: O(1) per eating operation
- **Space Complexity**: O(1) additional space
- **Synchronization**: Uses condition variable for efficient thread coordination
- **Fairness**: Guarantees all philosophers will eventually eat

### Alternative Approaches:
1. **Resource Hierarchy**: Assign order to forks (pick lower-numbered first)
2. **Waiter Solution**: Central coordinator manages fork allocation
3. **Asymmetric Solution**: Odd/even philosophers pick forks in different orders

This sequential solution is simple but conservative - it could allow more concurrency (e.g., philosophers 0 and 3 could eat simultaneously), but prioritizes correctness and simplicity over maximum throughput.

# Tags
- Concurrency
- Threading
- Synchronization
- Deadlock Prevention
- Condition Variables
- Classic CS Problem

