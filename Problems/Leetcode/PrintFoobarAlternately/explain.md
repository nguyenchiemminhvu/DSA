## Problem

https://leetcode.com/problems/print-foobar-alternately/description/

```
Suppose you are given the following code:

class FooBar {
  public void foo() {
    for (int i = 0; i < n; i++) {
      print("foo");
    }
  }

  public void bar() {
    for (int i = 0; i < n; i++) {
      print("bar");
    }
  }
}
The same instance of FooBar will be passed to two different threads:

thread A will call foo(), while
thread B will call bar().
Modify the given program to output "foobar" n times.

Example 1:

Input: n = 1
Output: "foobar"
Explanation: There are two threads being fired asynchronously. One of them calls foo(), while the other calls bar().
"foobar" is being output 1 time.

Example 2:

Input: n = 2
Output: "foobarfoobar"
Explanation: "foobar" is being output 2 times.

Constraints:

1 <= n <= 1000
```

## Observations

1. **Threading Synchronization Problem**: Two threads need to coordinate to print "foobar" alternately n times
2. **Race Condition**: Without synchronization, threads could execute in any order, producing incorrect output
3. **Mutual Exclusion**: Only one thread should execute at a time, and they must alternate
4. **State Management**: Need to track which thread should execute next
5. **Blocking Mechanism**: Threads must wait for their turn and signal when they're done

## Solution

The solution uses **threading.Condition** for synchronization with the following approach:

### Key Components:
- **`threading.Condition()`**: Provides mutual exclusion and signaling between threads
- **`self.selected`**: State variable (1 = foo's turn, 2 = bar's turn)
- **Wait-Signal Pattern**: Threads wait for their turn and notify others when done

### Algorithm Flow:

1. **Initialization**: 
   - `selected = 1` ensures `foo` goes first
   - Condition object handles thread synchronization

2. **foo() method**:
   ```python
   self.cond.acquire()        # Lock the condition
   while self.selected != 1:   # Wait until it's foo's turn
       self.cond.wait()
   printFoo()                 # Execute foo
   self.selected = 2          # Give turn to bar
   self.cond.notify()         # Wake up waiting threads
   self.cond.release()        # Release the lock
   ```

3. **bar() method**:
   ```python
   self.cond.acquire()        # Lock the condition
   while self.selected != 2:   # Wait until it's bar's turn
       self.cond.wait()
   printBar()                 # Execute bar
   self.selected = 1          # Give turn back to foo
   self.cond.notify()         # Wake up waiting threads
   self.cond.release()        # Release the lock
   ```

### Why This Works:
- **Mutual Exclusion**: Only one thread can hold the condition lock at a time
- **Ordering**: `selected` variable ensures alternating execution (foo→bar→foo→bar...)
- **Blocking**: `wait()` blocks threads until their turn, preventing busy waiting
- **Signaling**: `notify()` wakes up the waiting thread after each execution

### Time Complexity: O(n)
### Space Complexity: O(1)

# Tags
- **Threading**
- **Synchronization** 
- **Condition Variables**
- **Mutual Exclusion**
- **Concurrency**

