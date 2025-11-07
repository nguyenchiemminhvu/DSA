## Problem

https://leetcode.com/problems/number-of-recent-calls/description/

```
You have a RecentCounter class which counts the number of recent requests within a certain time frame.

Implement the RecentCounter class:

RecentCounter() Initializes the counter with zero recent requests.
int ping(int t) Adds a new request at time t, where t represents some time in milliseconds, and returns the number of requests that has happened in the past 3000 milliseconds (including the new request). Specifically, return the number of requests that have happened in the inclusive range [t - 3000, t].
It is guaranteed that every call to ping uses a strictly larger value of t than the previous call.

Example 1:

Input
["RecentCounter", "ping", "ping", "ping", "ping"]
[[], [1], [100], [3001], [3002]]
Output
[null, 1, 2, 3, 3]

Explanation
RecentCounter recentCounter = new RecentCounter();
recentCounter.ping(1);     // requests = [1], range is [-2999,1], return 1
recentCounter.ping(100);   // requests = [1, 100], range is [-2900,100], return 2
recentCounter.ping(3001);  // requests = [1, 100, 3001], range is [1,3001], return 3
recentCounter.ping(3002);  // requests = [1, 100, 3001, 3002], range is [2,3002], return 3

Constraints:

1 <= t <= 109
Each test case will call ping with strictly increasing values of t.
At most 104 calls will be made to ping.
```

## Observations

1. **Time Window**: We need to count requests within a 3000ms sliding window: `[t-3000, t]`
2. **Strictly Increasing**: Timestamps are guaranteed to be strictly increasing, which means we can use a queue-based approach
3. **Sliding Window with Deque**: Since we only care about recent requests within the time window, we can remove old requests that fall outside the window
4. **FIFO Nature**: Older requests (smaller timestamps) will be at the front of the queue, newer ones at the back
5. **Time Complexity**: Each request is added once and removed at most once, giving us O(1) amortized time per ping

## Solution

The solution uses a **sliding window** approach with a **deque (double-ended queue)**:

### Algorithm:
1. **Initialize**: Create an empty deque to store timestamps
2. **For each ping(t)**:
   - Calculate the minimum valid timestamp: `min_threshold = t - 3000`
   - Remove all timestamps from the front of deque that are older than `min_threshold`
   - Add the current timestamp `t` to the back of the deque
   - Return the current size of the deque (number of valid requests)

### Why Deque?
- **Efficient removal from front**: `popleft()` is O(1)
- **Efficient addition to back**: `append()` is O(1)
- **Natural FIFO ordering**: Older timestamps at front, newer at back

### Example Walkthrough:
```
ping(1):    deque=[1], range=[-2999,1], count=1
ping(100):  deque=[1,100], range=[-2900,100], count=2
ping(3001): deque=[1,100,3001], range=[1,3001], count=3
ping(3002): 
  - min_threshold = 3002-3000 = 2
  - Remove 1 (< 2): deque=[100,3001]
  - Add 3002: deque=[100,3001,3002]
  - range=[2,3002], count=3
```

### Time & Space Complexity:
- **Time**: O(1) amortized per ping (each element added once, removed at most once)
- **Space**: O(W) where W is the maximum number of requests in any 3000ms window

# Tags
- Sliding Window
- Queue/Deque
- Data Stream

