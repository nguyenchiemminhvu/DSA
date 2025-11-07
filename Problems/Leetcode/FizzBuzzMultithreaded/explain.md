## Problem

https://leetcode.com/problems/fizz-buzz-multithreaded/description/

```
You have the four functions:

printFizz that prints the word "fizz" to the console,
printBuzz that prints the word "buzz" to the console,
printFizzBuzz that prints the word "fizzbuzz" to the console, and
printNumber that prints a given integer to the console.
You are given an instance of the class FizzBuzz that has four functions: fizz, buzz, fizzbuzz and number. The same instance of FizzBuzz will be passed to four different threads:

Thread A: calls fizz() that should output the word "fizz".
Thread B: calls buzz() that should output the word "buzz".
Thread C: calls fizzbuzz() that should output the word "fizzbuzz".
Thread D: calls number() that should only output the integers.
Modify the given class to output the series [1, 2, "fizz", 4, "buzz", ...] where the ith token (1-indexed) of the series is:

"fizzbuzz" if i is divisible by 3 and 5,
"fizz" if i is divisible by 3 and not 5,
"buzz" if i is divisible by 5 and not 3, or
i if i is not divisible by 3 or 5.
Implement the FizzBuzz class:

FizzBuzz(int n) Initializes the object with the number n that represents the length of the sequence that should be printed.
void fizz(printFizz) Calls printFizz to output "fizz".
void buzz(printBuzz) Calls printBuzz to output "buzz".
void fizzbuzz(printFizzBuzz) Calls printFizzBuzz to output "fizzbuzz".
void number(printNumber) Calls printnumber to output the numbers.

Example 1:

Input: n = 15
Output: [1,2,"fizz",4,"buzz","fizz",7,8,"fizz","buzz",11,"fizz",13,14,"fizzbuzz"]

Example 2:

Input: n = 5
Output: [1,2,"fizz",4,"buzz"]

Constraints:

1 <= n <= 50

```

## Observations

1. **Multi-threading Challenge**: This problem requires coordinating 4 different threads that must output in sequence from 1 to n
2. **Thread Coordination**: Each thread is responsible for different numbers:
   - Thread A (fizz): Numbers divisible by 3 but not 15 (3, 6, 9, 12...)
   - Thread B (buzz): Numbers divisible by 5 but not 15 (5, 10, 20...)
   - Thread C (fizzbuzz): Numbers divisible by both 3 and 5 (15, 30, 45...)
   - Thread D (number): Numbers not divisible by 3 or 5 (1, 2, 4, 7, 8, 11...)
3. **Synchronization Required**: Threads must process numbers in order (1, 2, 3, 4, 5...) despite running concurrently
4. **Shared State**: All threads need access to the current number being processed

## Solution

The solution uses a **Condition Variable** approach with a shared deque to maintain thread synchronization:

### Key Components:
1. **Shared Queue**: `self.arr = deque([val for val in range(1, n + 1)])` - Contains all numbers to process
2. **Condition Variable**: `self.cond = threading.Condition()` - Coordinates thread access and signaling
3. **Wait/Notify Pattern**: Each thread waits for its turn and notifies others when done

### Algorithm Flow:
1. Each thread enters a loop that continues while there are numbers to process
2. Thread acquires the condition lock and checks if the current number (first in deque) matches its responsibility
3. If not the right number, thread waits (`self.cond.wait()`)
4. If it's the right number, thread processes it, removes from deque, and notifies all other threads
5. Process repeats until deque is empty

### Thread-Specific Logic:
- **fizz()**: Processes numbers divisible by 3 but NOT by 15 (`num % 3 == 0 and num % 15 != 0`)
- **buzz()**: Processes numbers divisible by 5 but NOT by 15 (`num % 5 == 0 and num % 15 != 0`) 
- **fizzbuzz()**: Processes numbers divisible by 15 (`num % 15 == 0`)
- **number()**: Processes numbers NOT divisible by 3 or 5 (`num % 3 != 0 and num % 5 != 0`)

### Synchronization Pattern:
```python
while self.arr:
    with self.cond:
        while self.arr and <not_my_number_condition>:
            self.cond.wait()  # Wait for my turn
        if self.arr:
            <process_number>
            self.arr.popleft()  # Remove processed number
            self.cond.notify_all()  # Wake up all waiting threads
```

This ensures sequential processing despite concurrent execution, with each thread handling only its designated numbers.

# Tags
- Multi-threading
- Synchronization
- Condition Variables
- Thread Coordination
- Producer-Consumer Pattern

