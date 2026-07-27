## Problem

https://leetcode.com/problems/average-waiting-time/description/

There is a restaurant with a single chef. You are given an array `customers`, where `customers[i] = [arrival_i, time_i]`:

- `arrival_i` is the arrival time of the `i`th customer. The arrival times are sorted in **non-decreasing** order.
- `time_i` is the time needed to prepare the order of the `i`th customer.

When a customer arrives, he gives the chef his order, and the chef starts preparing it once he is idle. The customer waits till the chef finishes preparing his order. The chef does not prepare food for more than one customer at a time. The chef prepares food for customers **in the order they were given in the input**.

Return the **average** waiting time of all customers. Solutions within `10^-5` from the actual answer are considered accepted.

**Constraints:**

- `1 <= customers.length <= 10^5`
- `1 <= arrival_i, time_i <= 10^4`
- `arrival_i <= arrival_i+1`

**Example 1:**

```
Input: customers = [[1,2],[2,5],[4,3]]
Output: 5.00000
Explanation:
1) Customer 1 arrives at t=1, chef starts immediately, finishes at t=3. Wait = 3-1 = 2.
2) Customer 2 arrives at t=2, chef starts at t=3 (busy), finishes at t=8. Wait = 8-2 = 6.
3) Customer 3 arrives at t=4, chef starts at t=8 (busy), finishes at t=11. Wait = 11-4 = 7.
Average = (2 + 6 + 7) / 3 = 5.00000
```

**Example 2:**

```
Input: customers = [[5,2],[5,4],[10,3],[20,1]]
Output: 3.25000
Explanation:
1) Customer 1: arrives t=5, finishes t=7.  Wait = 2.
2) Customer 2: arrives t=5, finishes t=11. Wait = 6.
3) Customer 3: arrives t=10, finishes t=14. Wait = 4.
4) Customer 4: arrives t=20, finishes t=21. Wait = 1.
Average = (2 + 6 + 4 + 1) / 4 = 3.25000
```

---

## Ideas

### Simulation (Greedy) — O(n) time, O(1) space

Track `idle_time`: the earliest moment the chef becomes free.

For each customer `[arrival, prep]`:
- If the chef is already free (`idle_time <= arrival`), he starts immediately: `idle_time = arrival + prep`.
- Otherwise the customer must wait: `idle_time = idle_time + prep`.

The waiting time for a customer is always `idle_time - arrival` (finish time minus arrival).

```
idle_time = 0
total_wait = 0

for arrival, prep in customers:
    idle_time = max(idle_time, arrival) + prep
    total_wait += idle_time - arrival

return total_wait / len(customers)
```

**Why it works:** `max(idle_time, arrival)` captures both cases — chef idle (customer waits 0 for chef) and chef busy (customer waits for chef to finish). The finish time minus arrival is always the full waiting time.
