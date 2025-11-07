## Problem

https://leetcode.com/problems/print-zero-even-odd/

```
You have a function printNumber that can be called with an integer parameter and prints it to the console.

For example, calling printNumber(7) prints 7 to the console.
You are given an instance of the class ZeroEvenOdd that has three functions: zero, even, and odd. The same instance of ZeroEvenOdd will be passed to three different threads:

Thread A: calls zero() that should only output 0's.
Thread B: calls even() that should only output even numbers.
Thread C: calls odd() that should only output odd numbers.
Modify the given class to output the series "010203040506..." where the length of the series must be 2n.

Implement the ZeroEvenOdd class:

ZeroEvenOdd(int n) Initializes the object with the number n that represents the numbers that should be printed.
void zero(printNumber) Calls printNumber to output one zero.
void even(printNumber) Calls printNumber to output one even number.
void odd(printNumber) Calls printNumber to output one odd number.

Example 1:

Input: n = 2
Output: "0102"
Explanation: There are three threads being fired asynchronously.
One of them calls zero(), the other calls even(), and the last one calls odd().
"0102" is the correct output.

Example 2:

Input: n = 5
Output: "0102030405"

Constraints:

1 <= n <= 1000
```

## Observations

1. **Pattern Analysis**: The output follows a strict alternating pattern: `0, 1, 0, 2, 0, 3, 0, 4, ...`
   - Zeros appear at even positions (0th, 2nd, 4th, ...)
   - Numbers 1-n appear at odd positions (1st, 3rd, 5th, ...)
   - Total output length is exactly 2n

2. **Threading Challenge**: Three threads must coordinate to print numbers in the correct order
   - Thread synchronization is crucial to maintain the sequence
   - Each thread should only print when it's their turn
   - Race conditions must be avoided

3. **Concurrency Requirements**: 
   - Only one thread should be active at a time for printing
   - Threads must wait for their specific turn based on the current state
   - Need proper signaling mechanism between threads

4. **State Management**: The system needs to track what should be printed next
   - Either maintain a shared counter or pre-compute the sequence
   - Each thread needs to know when it's responsible for the next output

## Solution

### Approach: Shared Queue with Condition Variables

The solution uses a **shared deque** containing the entire sequence pre-computed, combined with **threading.Condition** for synchronization.

#### Key Components:

1. **Pre-computed Sequence**: 
   ```python
   self.arr = deque([val for p in zip([0] * n, range(1, n + 1)) for val in p])
   ```
   - Creates the pattern: [0, 1, 0, 2, 0, 3, ..., 0, n] using zip to interleave
   - For n=3: [0, 1, 0, 2, 0, 3]

2. **Condition Variable**: 
   - `threading.Condition()` provides mutual exclusion and signaling
   - Each thread waits until the front element matches their responsibility

3. **Thread Responsibilities**:
   - **Zero thread**: Prints when `arr[0] == 0`
   - **Odd thread**: Prints when `arr[0] % 2 == 1` (odd numbers only)
   - **Even thread**: Prints when `arr[0] != 0 and arr[0] % 2 == 0` (even numbers, not zero)

#### Algorithm Flow:

1. Each thread enters a loop checking the shared queue
2. Thread acquires the condition lock with `with self.cond:`
3. Thread waits (`self.cond.wait()`) while the front element isn't their responsibility
4. When it's their turn, thread prints and removes the front element (`popleft()`)
5. Thread notifies all other waiting threads (`notify_all()`)
6. Repeat until queue is empty

#### Synchronization Mechanism:

- **Wait**: `self.cond.wait()` - Thread sleeps until notified by another thread
- **Notify**: `self.cond.notify_all()` - Wake up all waiting threads to check conditions
- **Lock**: `with self.cond:` - Ensures atomic access to shared queue

#### Why This Works:

- **Mutual Exclusion**: Only one thread can access the queue at a time
- **Ordered Execution**: Threads only proceed when the next element is theirs
- **No Busy Waiting**: Threads sleep when not their turn, efficient CPU usage
- **Deadlock Prevention**: `notify_all()` ensures all threads get a chance to check

### Time & Space Complexity

- **Time Complexity**: O(n) - Each element is processed exactly once
- **Space Complexity**: O(n) - Store the entire sequence in deque
- **Thread Overhead**: Minimal - Uses efficient condition variables instead of busy waiting

### Alternative Approaches

1. **Counter-based**: Use shared counters and state variables instead of pre-computed queue
2. **Semaphore-based**: Use multiple semaphores for coordination between specific threads
3. **Lock-based**: Use separate locks for each thread type with additional state tracking

The current solution is elegant because it separates the sequence generation from the threading logic, making it easier to understand and debug.

# Tags

`Threading`, `Concurrency`, `Synchronization`, `Condition Variables`, `Queue`

