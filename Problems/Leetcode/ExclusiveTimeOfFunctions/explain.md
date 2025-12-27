## Problem

https://leetcode.com/problems/exclusive-time-of-functions/description/

On a single-threaded CPU, we execute a program containing `n` functions. Each function has a unique ID between `0` and `n-1`.

Function calls are stored in a **call stack**: when a function call starts, its ID is pushed onto the stack, and when a function call ends, its ID is popped off the stack. The function whose ID is at the top of the stack is the current function being executed.

You are given a list `logs`, where `logs[i]` represents the ith log message formatted as `"{function_id}:{"start" | "end"}:{timestamp}"`.

- `"0:start:3"` means function ID 0 started at the **beginning** of timestamp 3
- `"1:end:2"` means function ID 1 ended at the **end** of timestamp 2

A function's **exclusive time** is the sum of execution times for all function calls in the program.

Return the exclusive time of each function in an array, where the value at the ith index represents the exclusive time for the function with ID i.

**Example 1:**
```
Input: n = 2, logs = ["0:start:0","1:start:2","1:end:5","0:end:6"]
Output: [3,4]
```

**Example 2:**
```
Input: n = 1, logs = ["0:start:0","0:start:2","0:end:5","0:start:6","0:end:6","0:end:7"]
Output: [8]
```

**Constraints:**
- `1 <= n <= 100`
- `2 <= logs.length <= 500`
- `0 <= function_id < n`
- `0 <= timestamp <= 10^9`
- No two start events will happen at the same timestamp
- No two end events will happen at the same timestamp
- Each function has an "end" log for each "start" log

## Observations

1. **Stack-based execution**: Functions follow a stack-based call model (LIFO - Last In First Out). When a function starts, it's pushed onto the stack; when it ends, it's popped off.

2. **Timestamp semantics are crucial**:
   - `start` events occur at the **beginning** of the timestamp
   - `end` events occur at the **end** of the timestamp
   - If a function ends at timestamp `t`, it executes during timestamp `t`, so we need to add 1 to move to the next timestamp

3. **Time accounting**: 
   - Only the function at the top of the stack (currently executing) accumulates time
   - When a new function starts or the current function ends, we need to account for the time the previous top function executed

4. **Recursive and nested calls**: Functions can call themselves (recursion) or other functions. Each call is tracked independently on the stack.

5. **Key insight**: Before processing any event (start or end), we should credit the currently executing function (top of stack) with the time since the last event.

## Solution

```python
class Solution:
    def exclusiveTime(self, n: int, logs: List[str]) -> List[int]:
        res = [0] * n
        stack = []
        prev_time = 0

        for log in logs:
            fid, typ, time = log.split(':')
            fid, time = int(fid), int(time)

            if stack:
                res[stack[-1]] += time - prev_time

            if typ == "start":
                stack.append(fid)
                prev_time = time
            else:  # end
                stack.pop()
                res[fid] += 1
                prev_time = time + 1

        return res
```

### Explanation

**Algorithm:**

1. **Initialize**:
   - `res[0...n-1]`: stores exclusive time for each function
   - `stack`: tracks the call stack (currently executing functions)
   - `prev_time`: tracks when the last event occurred

2. **Process each log**:
   - Parse the log to extract `function_id`, `type` (start/end), and `timestamp`
   
3. **Credit the current function**:
   - Before handling any event, if there's a function on the stack (something is executing), add the time elapsed since the last event: `time - prev_time`
   - This credits the function that was at the top of the stack before this event

4. **Handle the event**:
   - **If "start"**: 
     - Push function ID onto stack (it becomes the new executing function)
     - Update `prev_time = time` (next interval starts from this timestamp)
   
   - **If "end"**:
     - Pop function ID from stack (it's done executing)
     - Add 1 to the function's time (it executes during this timestamp too)
     - Update `prev_time = time + 1` (next interval starts at the next timestamp since end happens at the **end** of the timestamp)

### Example Walkthrough (Example 1)

Input: `n = 2, logs = ["0:start:0","1:start:2","1:end:5","0:end:6"]`

| Log | Event | Stack Before | Time Credited | Stack After | prev_time | res |
|-----|-------|--------------|---------------|-------------|-----------|-----|
| Initial | - | [] | - | [] | 0 | [0,0] |
| 0:start:0 | F0 starts at 0 | [] | none (empty stack) | [0] | 0 | [0,0] |
| 1:start:2 | F1 starts at 2 | [0] | F0 += 2-0=2 | [0,1] | 2 | [2,0] |
| 1:end:5 | F1 ends at 5 | [0,1] | F1 += 5-2=3 | [0] | 6 | [2,3] |
| | | | F1 += 1 (end time) | | | [2,4] |
| 0:end:6 | F0 ends at 6 | [0] | F0 += 6-6=0 | [] | 7 | [2,4] |
| | | | F0 += 1 (end time) | | | [3,4] |

Output: `[3,4]`

### Complexity

- **Time Complexity**: O(m) where m is the number of logs. We process each log once.
- **Space Complexity**: O(n) for the result array and O(m) in the worst case for the stack (if all functions are nested).

# Tags

#stack #simulation #time-tracking

