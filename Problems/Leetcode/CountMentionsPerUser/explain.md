## Problem

https://leetcode.com/problems/count-mentions-per-user/description/

You are given an integer `numberOfUsers` representing the total number of users and an array `events` of size `n x 3`.

Each `events[i]` can be either of the following two types:

1. **Message Event**: `["MESSAGE", "timestampi", "mentions_stringi"]`
   - This event indicates that a set of users was mentioned in a message at `timestampi`.
   - The `mentions_stringi` string can contain one of the following tokens:
     - `id<number>`: where `<number>` is an integer in range `[0, numberOfUsers - 1]`. There can be multiple ids separated by a single whitespace and may contain duplicates. This can mention even offline users.
     - `ALL`: mentions all users (including offline users).
     - `HERE`: mentions all online users only.

2. **Offline Event**: `["OFFLINE", "timestampi", "idi"]`
   - This event indicates that the user `idi` became offline at `timestampi` for 60 time units.
   - The user will automatically be online again at time `timestampi + 60`.

Return an array `mentions` where `mentions[i]` represents the number of mentions the user with id `i` has across all MESSAGE events.

**Important Rules:**
- All users are initially online
- If a user goes offline or comes back online, their status change is processed **before** handling any message event that occurs at the same timestamp
- A user can be mentioned multiple times in a single message event, and each mention should be counted separately

**Example 1:**
```
Input: numberOfUsers = 2, events = [["MESSAGE","10","id1 id0"],["OFFLINE","11","0"],["MESSAGE","71","HERE"]]
Output: [2,2]
Explanation:
- Initially, all users are online.
- At timestamp 10, id1 and id0 are mentioned. mentions = [1,1]
- At timestamp 11, id0 goes offline.
- At timestamp 71, id0 comes back online and "HERE" is mentioned. mentions = [2,2]
```

**Example 2:**
```
Input: numberOfUsers = 2, events = [["MESSAGE","10","id1 id0"],["OFFLINE","11","0"],["MESSAGE","12","ALL"]]
Output: [2,2]
Explanation:
- Initially, all users are online.
- At timestamp 10, id1 and id0 are mentioned. mentions = [1,1]
- At timestamp 11, id0 goes offline.
- At timestamp 12, "ALL" is mentioned (includes offline users). mentions = [2,2]
```

**Example 3:**
```
Input: numberOfUsers = 2, events = [["OFFLINE","10","0"],["MESSAGE","12","HERE"]]
Output: [0,1]
Explanation:
- Initially, all users are online.
- At timestamp 10, id0 goes offline.
- At timestamp 12, "HERE" is mentioned. Because id0 is still offline, they are not mentioned. mentions = [0,1]
```

**Constraints:**
- `1 <= numberOfUsers <= 100`
- `1 <= events.length <= 100`
- `events[i].length == 3`
- `events[i][0]` will be one of `MESSAGE` or `OFFLINE`
- `1 <= int(events[i][1]) <= 10^5`
- The number of `id<number>` mentions in any "MESSAGE" event is between 1 and 100
- `0 <= <number> <= numberOfUsers - 1`
- It is guaranteed that the user id referenced in the OFFLINE event is online at the time the event occurs

## Observations

1. **Event Ordering is Critical**: OFFLINE events at the same timestamp must be processed before MESSAGE events. This is handled by sorting with a secondary key.

2. **Three Types of Mentions**:
   - `ALL`: Mentions every user regardless of online/offline status
   - `HERE`: Mentions only currently online users
   - `id<number>`: Mentions specific user IDs (can mention offline users)

3. **User Online Status Tracking**:
   - Users start online at time 0
   - When a user goes offline at time `t`, they return online at time `t + 60`
   - We can track this using `next_online[user]`: the timestamp when the user becomes online
   - A user is online at time `t` if `t >= next_online[user]`

4. **Duplicate Mentions Count**: If a user is mentioned multiple times in a single message (e.g., "id0 id0 id1"), each mention counts separately.

5. **No Need for Complex State Management**: We don't need to explicitly track whether users are online/offline at each moment. We just need to know when they'll be online next.

## Solution

### Approach: Event Processing with Time-based Online Status

**Key Insight**: Instead of maintaining a boolean online/offline flag for each user and updating it as events occur, we can track `next_online[user]` - the timestamp when a user will be online again. A user is online at time `t` if `t >= next_online[user]`.

**Algorithm:**

1. **Sort Events**: Sort by timestamp, with OFFLINE events processed before MESSAGE events at the same timestamp.
   ```python
   events.sort(key=lambda x: (int(x[1]), 0 if x[0] == "OFFLINE" else 1))
   ```

2. **Initialize State**:
   - `mentions[i]`: count of mentions for user `i` (initially 0)
   - `next_online[i]`: timestamp when user `i` is next online (initially 0, meaning online from start)

3. **Process Each Event**:
   - **OFFLINE Event**: Set `next_online[user] = t + 60`
   - **MESSAGE Event with "ALL"**: Increment mentions for all users
   - **MESSAGE Event with "HERE"**: Increment mentions only for users where `t >= next_online[user]`
   - **MESSAGE Event with IDs**: Parse the IDs and increment mentions for each (including duplicates)

**Time Complexity**: O(n log n + n × m) where n is the number of events and m is the number of users. The sorting takes O(n log n), and processing events takes O(n × m) in the worst case (when every message is "ALL" or "HERE").

**Space Complexity**: O(n + m) for storing mentions and next_online arrays, plus O(n) for sorted events.

**Why This Works:**

- By sorting with OFFLINE events first at the same timestamp, we ensure user status is updated before processing messages at that timestamp.
- The `next_online[user]` approach elegantly handles the 60-time-unit offline period without needing to track exact online/offline states.
- When checking if a user is online at time `t`, we simply check if `t >= next_online[user]`.
- The parsing logic correctly handles all three mention types: ALL, HERE, and specific IDs.

# Tags

#simulation #event-processing #sorting #array #string-parsing #time-based-logic

