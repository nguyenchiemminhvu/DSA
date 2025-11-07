## Problem

https://leetcode.com/problems/print-in-order/

```
Suppose we have a class:

public class Foo {
  public void first() { print("first"); }
  public void second() { print("second"); }
  public void third() { print("third"); }
}
The same instance of Foo will be passed to three different threads. Thread A will call first(), thread B will call second(), and thread C will call third(). Design a mechanism and modify the program to ensure that second() is executed after first(), and third() is executed after second().

Note:

We do not know how the threads will be scheduled in the operating system, even though the numbers in the input seem to imply the ordering. The input format you see is mainly to ensure our tests' comprehensiveness.

Example 1:

Input: nums = [1,2,3]
Output: "firstsecondthird"
Explanation: There are three threads being fired asynchronously. The input [1,2,3] means thread A calls first(), thread B calls second(), and thread C calls third(). "firstsecondthird" is the correct output.

Example 2:

Input: nums = [1,3,2]
Output: "firstsecondthird"
Explanation: The input [1,3,2] means thread A calls first(), thread B calls third(), and thread C calls second(). "firstsecondthird" is the correct output.

Constraints:

nums is a permutation of [1, 2, 3].
```

## Observations

1. **Threading Synchronization Problem**: This is a classic threading synchronization problem where we need to ensure that three methods execute in a specific order (first → second → third) regardless of which thread calls which method first.

2. **Race Condition Challenge**: Without proper synchronization, threads could execute in any order based on OS scheduling, leading to incorrect output like "secondfirstthird" or "thirdsecondfirst".

3. **Barrier Synchronization**: The provided solution uses Python's `threading.Barrier` class, which is a synchronization primitive that blocks threads until a specified number of threads reach the barrier point.

4. **Multiple Barriers Strategy**: The solution uses three different barriers:
   - `b1`: Barrier for 1 thread (controls when first() can start)
   - `b2`: Barrier for 2 threads (synchronizes first() and second())
   - `b3`: Barrier for 3 threads (synchronizes all three methods)

5. **Execution Flow Dependencies**: Each method has specific wait points that create the necessary dependencies to ensure correct ordering.

## Solution

**Algorithm: Threading Barriers**

The solution uses a clever barrier-based approach to synchronize the three methods:

```python
import threading

b1 = threading.Barrier(1)  # Single-thread barrier
b2 = threading.Barrier(2)  # Two-thread barrier  
b3 = threading.Barrier(3)  # Three-thread barrier

class Foo:
    def first(self, printFirst):
        b1.wait()          # Passes immediately (1 thread needed)
        printFirst()       # Execute first
        b2.wait()          # Wait for second() to reach b2.wait()
        b3.wait()          # Wait for third() to reach b3.wait()

    def second(self, printSecond):
        b2.wait()          # Wait for first() to reach b2.wait()
        printSecond()      # Execute second (after first completes)
        b3.wait()          # Wait for third() to reach b3.wait()

    def third(self, printThird):
        b3.wait()          # Wait for both first() and second() to reach b3.wait()
        printThird()       # Execute third (after first and second complete)
```

**How it works:**

1. **first()** method:
   - `b1.wait()` passes immediately since it only needs 1 thread
   - Executes `printFirst()`
   - Waits at `b2.wait()` for `second()` to join
   - Waits at `b3.wait()` for `third()` to join

2. **second()** method:
   - Blocks at `b2.wait()` until `first()` reaches the same barrier
   - Once both reach `b2.wait()`, both proceed
   - `second()` executes `printSecond()` after `first()` has completed
   - Waits at `b3.wait()` for `third()` to join

3. **third()** method:
   - Blocks at `b3.wait()` until both `first()` and `second()` reach the same barrier
   - Only executes `printThird()` after both previous methods have completed

**Key Insights:**
- Barriers ensure that threads wait for each other at specific synchronization points
- The barrier counts (1, 2, 3) create a dependency chain that enforces the correct execution order
- This approach works regardless of which thread starts first or how the OS schedules the threads

**Time Complexity:** O(1) for each method call  
**Space Complexity:** O(1) - only uses three barrier objects

**Alternative Approaches:**
- Semaphores: Use counting semaphores to control execution order
- Locks/Mutexes: Use multiple locks with condition variables
- Events: Use threading events to signal completion between methods

# Tags

