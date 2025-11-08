## Problem

https://leetcode.com/problems/building-h2o/description/

```
There are two kinds of threads: oxygen and hydrogen. Your goal is to group these threads to form water molecules.

There is a barrier where each thread has to wait until a complete molecule can be formed. Hydrogen and oxygen threads will be given releaseHydrogen and releaseOxygen methods respectively, which will allow them to pass the barrier. These threads should pass the barrier in groups of three, and they must immediately bond with each other to form a water molecule. You must guarantee that all the threads from one molecule bond before any other threads from the next molecule do.

In other words:

If an oxygen thread arrives at the barrier when no hydrogen threads are present, it must wait for two hydrogen threads.
If a hydrogen thread arrives at the barrier when no other threads are present, it must wait for an oxygen thread and another hydrogen thread.
We do not have to worry about matching the threads up explicitly; the threads do not necessarily know which other threads they are paired up with. The key is that threads pass the barriers in complete sets; thus, if we examine the sequence of threads that bind and divide them into groups of three, each group should contain one oxygen and two hydrogen threads.

Write synchronization code for oxygen and hydrogen molecules that enforces these constraints.

Example 1:

Input: water = "HOH"
Output: "HHO"
Explanation: "HOH" and "OHH" are also valid answers.

Example 2:

Input: water = "OOHHHH"
Output: "HHOHHO"
Explanation: "HOHHHO", "OHHHHO", "HHOHOH", "HOHHOH", "OHHHOH", "HHOOHH", "HOHOHH" and "OHHOHH" are also valid answers.

Constraints:

3 * n == water.length
1 <= n <= 20
water[i] is either 'H' or 'O'.
There will be exactly 2 * n 'H' in water.
There will be exactly n 'O' in water.
```

## Observations

1. **Water Molecule Formation**: Each H2O molecule requires exactly 2 hydrogen atoms and 1 oxygen atom to be bonded together.

2. **Thread Synchronization Challenge**: This is a classic producer-consumer synchronization problem where:
   - Hydrogen threads are producers that need to wait for an oxygen thread
   - Oxygen threads are consumers that need to collect 2 hydrogen threads before proceeding

3. **Barrier Coordination**: The key challenge is ensuring threads form complete molecules (groups of 3: 2H + 1O) before any new molecule formation begins.

4. **Semaphore Usage Pattern**:
   - `h_sem`: Controls how many hydrogen threads can proceed (initialized to 2)
   - `o_sem`: Controls when oxygen threads can proceed (initialized to 0, meaning blocked)
   - The pattern creates a dependency: oxygen must wait for hydrogen pairs

5. **Counter-based Release Mechanism**: The solution uses a counter (`h_count`) to track when exactly 2 hydrogen atoms have been released, then signals the oxygen thread.

6. **Race Condition Prevention**: A lock (`lock_count`) protects the shared counter to prevent race conditions when multiple hydrogen threads access it simultaneously.

## Solution

The solution uses a clever semaphore-based approach with the following synchronization mechanism:

### Initialization:
- `h_sem = Semaphore(2)`: Allows up to 2 hydrogen threads to proceed initially
- `o_sem = Semaphore(0)`: Blocks all oxygen threads initially (they must wait)
- `lock_count`: Protects the hydrogen counter from race conditions
- `h_count`: Tracks how many hydrogen atoms have been released

### Hydrogen Thread Flow:
```python
def hydrogen(self, releaseHydrogen):
    self.h_sem.acquire()          # Acquire hydrogen permission (max 2 can proceed)
    releaseHydrogen()             # Release hydrogen atom
    self.lock_count.acquire()     # Lock to safely update counter
    self.h_count += 1             # Increment hydrogen count
    if self.h_count % 2 == 0:     # If this is the 2nd hydrogen in current molecule
        self.o_sem.release()      # Signal oxygen thread to proceed
    self.lock_count.release()     # Release counter lock
```

### Oxygen Thread Flow:
```python
def oxygen(self, releaseOxygen):
    self.o_sem.acquire()          # Wait until signaled by 2nd hydrogen
    releaseOxygen()               # Release oxygen atom
    self.h_sem.release()          # Allow 2 new hydrogen threads for next molecule
    self.h_sem.release()
```

### Synchronization Logic:

1. **Initial State**: `h_sem(2)` allows first 2 hydrogen threads to proceed, `o_sem(0)` blocks oxygen

2. **First Hydrogen**: Acquires `h_sem`, releases H, increments counter to 1

3. **Second Hydrogen**: Acquires `h_sem`, releases H, increments counter to 2, signals oxygen via `o_sem.release()`

4. **Oxygen**: Finally can acquire `o_sem`, releases O, then releases 2 permits back to `h_sem` for next molecule

5. **Cycle Repeats**: The pattern continues with `h_sem` having 2 permits for the next pair of hydrogen threads

### Key Insights:
- **Molecule Completeness**: Oxygen only proceeds after exactly 2 hydrogens have been processed
- **Resource Management**: The semaphore permits are recycled (oxygen releases 2 `h_sem` permits)
- **Order Flexibility**: While molecules are complete, the exact order within a molecule can vary (HHO, HOH, OHH all valid)
- **Deadlock Prevention**: The counter-based signaling ensures progress and prevents deadlock

This elegant solution ensures that threads form complete H2O molecules while allowing flexible ordering within each molecule group.

# Tags
Threading, Synchronization, Semaphore, Producer-Consumer, Concurrency

