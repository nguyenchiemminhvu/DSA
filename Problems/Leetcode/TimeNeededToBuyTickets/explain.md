## Problem

https://leetcode.com/problems/time-needed-to-buy-tickets/description/

```
There are n people in a line queuing to buy tickets, where the 0th person is at the front of the line and the (n - 1)th person is at the back of the line.

You are given a 0-indexed integer array tickets of length n where the number of tickets that the ith person would like to buy is tickets[i].

Each person takes exactly 1 second to buy a ticket. A person can only buy 1 ticket at a time and has to go back to the end of the line (which happens instantaneously) in order to buy more tickets. If a person does not have any tickets left to buy, the person will leave the line.

Return the time taken for the person initially at position k (0-indexed) to finish buying tickets.

Example 1:

Input: tickets = [2,3,2], k = 2

Output: 6

Explanation:

The queue starts as [2,3,2], where the kth person is underlined.
After the person at the front has bought a ticket, the queue becomes [3,2,1] at 1 second.
Continuing this process, the queue becomes [2,1,2] at 2 seconds.
Continuing this process, the queue becomes [1,2,1] at 3 seconds.
Continuing this process, the queue becomes [2,1] at 4 seconds. Note: the person at the front left the queue.
Continuing this process, the queue becomes [1,1] at 5 seconds.
Continuing this process, the queue becomes [1] at 6 seconds. The kth person has bought all their tickets, so return 6.

Example 2:

Input: tickets = [5,1,1,1], k = 0

Output: 8

Explanation:

The queue starts as [5,1,1,1], where the kth person is underlined.
After the person at the front has bought a ticket, the queue becomes [1,1,1,4] at 1 second.
Continuing this process for 3 seconds, the queue becomes [4] at 4 seconds.
Continuing this process for 4 seconds, the queue becomes [] at 8 seconds. The kth person has bought all their tickets, so return 8.

Constraints:

n == tickets.length
1 <= n <= 100
1 <= tickets[i] <= 100
0 <= k < n
```

## Observations

1. **Queue Simulation**: This is a queue simulation problem where people buy tickets one at a time and go to the back of the line if they need more tickets.

2. **Key Insights**:
   - Each person takes exactly 1 second to buy 1 ticket
   - After buying a ticket, if the person needs more tickets, they go to the end of the line
   - If a person finishes buying all their tickets, they leave the line
   - We need to track when the person at position `k` finishes buying all their tickets

3. **Tracking the Target Person**:
   - We need to keep track of where person `k` is in the queue as the queue changes
   - The person's position changes as people leave the queue and as the person moves around

4. **Time Complexity Considerations**:
   - Simulation approach: O(sum of all tickets) time, as we simulate each ticket purchase
   - Mathematical approach: O(n) time, by calculating directly without simulation

5. **Two Approaches**:
   - **Simulation**: Actually simulate the queue process step by step
   - **Mathematical**: Calculate the result directly by considering how many times each person will be served before person `k` finishes

## Solution

### Approach 1: Queue Simulation

The current implementation uses a simulation approach with a deque:

```python
def timeRequiredToBuy(self, tickets: List[int], k: int) -> int:
    n = len(tickets)
    q = deque(tickets)
    idx = k  # Track position of person k
    steps = 0
    
    while q and q[idx] > 0:
        # Person at front buys 1 ticket
        q[0] -= 1
        steps += 1
        
        if q[0] == 0:  # Person finished buying all tickets
            if idx == 0:  # This is person k
                return steps
            else:
                q.popleft()  # Remove from queue
                n -= 1
        else:
            # Move person to back of queue
            q.append(q.popleft())
        
        # Update position of person k
        idx = (idx - 1 + n) % n
    
    return steps
```

**Time Complexity**: O(sum of all tickets) - We simulate each ticket purchase
**Space Complexity**: O(n) - For the deque

### Approach 2: Mathematical Solution (Optimized)

A more efficient approach calculates the result directly:

```python
def timeRequiredToBuy(self, tickets: List[int], k: int) -> int:
    time = 0
    target_tickets = tickets[k]
    
    for i in range(len(tickets)):
        if i <= k:
            # People at or before position k (including k)
            # They can buy min(tickets[i], target_tickets) tickets
            time += min(tickets[i], target_tickets)
        else:
            # People after position k
            # They can buy min(tickets[i], target_tickets - 1) tickets
            # (one less because person k will finish before they get their last chance)
            time += min(tickets[i], target_tickets - 1)
    
    return time
```

**Key Insight for Mathematical Solution**:
- People at positions 0 to k (including k) will have the same or more opportunities to buy tickets as person k
- People at positions k+1 to n-1 will have one fewer opportunity than person k (since person k will finish and leave before they can buy their last ticket)

**Time Complexity**: O(n)
**Space Complexity**: O(1)

### Example Walkthrough

For `tickets = [2,3,2], k = 2`:
- Person at index 0: min(2, 2) = 2 tickets
- Person at index 1: min(3, 2) = 2 tickets  
- Person at index 2 (target): min(2, 2) = 2 tickets
- Total: 2 + 2 + 2 = 6 seconds

For `tickets = [5,1,1,1], k = 0`:
- Person at index 0 (target): min(5, 5) = 5 tickets
- Person at index 1: min(1, 4) = 1 ticket (target_tickets - 1)
- Person at index 2: min(1, 4) = 1 ticket (target_tickets - 1)  
- Person at index 3: min(1, 4) = 1 ticket (target_tickets - 1)
- Total: 5 + 1 + 1 + 1 = 8 seconds

# Tags

- **Array**: Working with array indices and values
- **Queue**: Simulating queue operations (enqueue/dequeue)
- **Simulation**: Simulating the ticket buying process
- **Math**: Mathematical optimization to avoid simulation
- **Easy**: Leetcode difficulty level

