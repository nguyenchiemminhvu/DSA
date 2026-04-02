## Problem

https://leetcode.com/problems/tweet-counts-per-frequency/description/

A social media company monitors activity by analyzing tweet counts over select time periods, partitioned into smaller chunks based on frequency:
- **Every minute**: 60-second chunks
- **Every hour**: 3600-second chunks  
- **Every day**: 86400-second chunks

The last chunk may be shorter than the frequency's chunk size.

**API Design Requirements:**
1. `TweetCounts()` - Initialize the object
2. `recordTweet(String tweetName, int time)` - Store a tweet with its timestamp
3. `getTweetCountsPerFrequency(String freq, String tweetName, int startTime, int endTime)` - Return list of tweet counts per chunk

**Example:**
```
Input: ["TweetCounts","recordTweet","recordTweet","recordTweet","getTweetCountsPerFrequency","getTweetCountsPerFrequency","recordTweet","getTweetCountsPerFrequency"]
       [[],["tweet3",0],["tweet3",60],["tweet3",10],["minute","tweet3",0,59],["minute","tweet3",0,60],["tweet3",120],["hour","tweet3",0,210]]
Output: [null,null,null,null,[2],[2,1],null,[4]]
```

**Constraints:**
- 0 ≤ time, startTime, endTime ≤ 10⁹
- 0 ≤ endTime - startTime ≤ 10⁴
- At most 10⁴ total calls to recordTweet and getTweetCountsPerFrequency

## Observations

1. **Data Structure Choice**: Store tweets as a list (array) per tweet name, since we need efficient range queries
   
2. **Lazy Sorting**: Sort the tweet array only when needed (during `getTweetCountsPerFrequency`), not on every insert. This is more efficient than keeping the array sorted at all times

3. **Binary Search Optimization**: Use binary search to efficiently find tweets within a specific time range rather than iterating through all tweets
   - `lower_bound(arr, target)`: Find first element ≥ target (inclusive start)
   - `upper_bound(arr, target)`: Find first element > target (for exclusive end, we use `upper_bound(arr, r)` where r is inclusive)

4. **Chunk Partitioning Logic**:
   - Total chunks = `⌊(end - start) / interval⌋ + 1`
   - For chunk i: left boundary = `start + i * interval`, right boundary = `min(start + (i+1)*interval - 1, end)`
   - This ensures the last chunk ends exactly at `end`

5. **Time Complexity**:
   - `recordTweet`: O(1) - just append
   - `getTweetCountsPerFrequency`: O(n log n) where n is total tweets for that name (due to sorting) + O(k log n) where k is the number of chunks (each binary search is O(log n))
   - Since endTime - startTime ≤ 10⁴, the number of chunks k is bounded

## Solution

```python
class TweetCounts:
    def __init__(self):
        self.mp = {}  # name -> [time]

    def recordTweet(self, name: str, time: int) -> None:
        if name not in self.mp:
            self.mp[name] = []
        self.mp[name].append(time)

    def getTweetCountsPerFrequency(self, freq: str, name: str, start: int, end: int) -> List[int]:
        def lower_bound(arr: List[int], target: int) -> int:
            """Find the index of the first element >= target"""
            na = len(arr)
            l, r, idx = 0, na - 1, na
            while l <= r:
                m = l + (r - l) // 2
                if arr[m] >= target:
                    idx = m
                    r = m - 1
                else:
                    l = m + 1
            return idx

        def upper_bound(arr: List[int], target: int) -> int:
            """Find the index of the first element > target"""
            na = len(arr)
            l, r, idx = 0, na - 1, na
            while l <= r:
                m = l + (r - l) // 2
                if arr[m] > target:
                    idx = m
                    r = m - 1
                else:
                    l = m + 1
            return idx
        
        # Map frequency to interval size
        interval = 60
        if freq == "hour":
            interval = 3600
        elif freq == "day":
            interval = 86400
        
        # Calculate number of chunks for the time range
        n = int((end - start) / interval + 1)
        chunks = [0] * n

        # Sort tweets for this name
        arr = self.mp[name]
        arr.sort()

        # For each chunk, count tweets using binary search
        for i in range(n):
            # Left boundary is inclusive, right boundary is inclusive
            l = start + i * interval
            r = min(l + interval - 1, end)
            
            # Count tweets in [l, r] using binary search
            lower = lower_bound(arr, l)      # First tweet >= l
            upper = upper_bound(arr, r)      # First tweet > r
            chunks[i] = upper - lower        # Count of tweets in [l, r]
        
        return chunks
```

**Algorithm Breakdown:**

1. **Initialization**: Create a hash map to store tweets per name

2. **Recording Tweets**: Simply append each tweet timestamp to the corresponding name's list

3. **Computing Tweet Counts**:
   - Determine the chunk size (60, 3600, or 86400 seconds)
   - Calculate the number of chunks needed to cover [start, end]
   - Sort the tweet timestamps for the given name (lazy sort)
   - For each chunk:
     - Calculate its time range [l, r]
     - Use lower_bound to find the first tweet at or after time l
     - Use upper_bound to find the first tweet after time r
     - The difference gives the count of tweets in the chunk

**Example Walkthrough:**

```
recordTweet("tweet3", 0)   → mp["tweet3"] = [0]
recordTweet("tweet3", 60)  → mp["tweet3"] = [0, 60]
recordTweet("tweet3", 10)  → mp["tweet3"] = [0, 60, 10]

getTweetCountsPerFrequency("minute", "tweet3", 0, 59):
  - Sort: [0, 10, 60]
  - n = (59 - 0) / 60 + 1 = 1 chunk
  - Chunk 0: [0, 59]
    - lower_bound([0, 10, 60], 0) = 0
    - upper_bound([0, 10, 60], 59) = 2
    - Count = 2 - 0 = 2 ✓

getTweetCountsPerFrequency("minute", "tweet3", 0, 60):
  - n = (60 - 0) / 60 + 1 = 2 chunks
  - Chunk 0: [0, 59] → Count = 2
  - Chunk 1: [60, 60]
    - lower_bound([0, 10, 60], 60) = 2
    - upper_bound([0, 10, 60], 60) = 3
    - Count = 3 - 2 = 1 ✓
  - Result: [2, 1] ✓
```

# Tags

- Binary Search
- Hash Map
- Range Query
- Lazy Sorting

