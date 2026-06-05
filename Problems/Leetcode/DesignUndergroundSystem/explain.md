## 🚇 Underground System Design

### 📝 Problem

Design a system to track customer travel times between stations in an underground railway network.

Implement the `UndergroundSystem` class with:

- `checkIn(id, stationName, t)`
  - A customer checks in at a station at time `t`.

- `checkOut(id, stationName, t)`
  - The same customer checks out at another station at time `t`.

- `getAverageTime(startStation, endStation)`
  - Returns the **average travel time** between two stations.

### ⚠️ Key Constraints

- Each customer can only be checked into one station at a time.
- Events are in chronological order.
- Travel is **direct only** (check-in → check-out).
- At least one trip exists before querying average.

---

## 🔍 Observations

1. **We need two types of data:**
   - Active trips (who is currently traveling)
   - Completed trips (aggregate data for averages)

2. **Efficient average calculation**
   - Instead of storing all trip times, store:
     - Total time (`sum`)
     - Number of trips (`count`)
   - Average = `sum / count`

3. **Mapping strategy**
   - Track ongoing trips:
     ```
     id → (startStation, startTime)
     ```
   - Store completed trip stats:
     ```
     startStation → endStation → (totalTime, tripCount)
     ```

4. **Time complexity goals**
   - All operations should be **O(1)**

---

## 💡 Solution Approach

### 1. Data Structures

- `self.track`
  - Tracks active journeys
  - `{id: (station, time)}`

- `self.info`
  - Stores aggregate travel data
  - `{start: {end: (total_time, count)}}`

---

### 2. Operations

#### ✅ checkIn
- Store the user's starting station and time.

#### ✅ checkOut
- Retrieve check-in info
- Compute trip duration
- Update aggregate stats
- Remove user from active tracking

#### ✅ getAverageTime
- Retrieve `(total_time, count)`
- Return `total_time / count`

---

## 🧠 Implementation

```
class UndergroundSystem:
    def __init__(self):
        # self.info[start][end] -> (sum, count)
        self.info = defaultdict(lambda: defaultdict(lambda: (0, 0)))
        self.track = defaultdict(list) # track[id] -> [start, time]

    def checkIn(self, user: int, station: str, t: int) -> None:
        self.track[user] = [station, t]

    def checkOut(self, user: int, station: str, t: int) -> None:
        if user in self.track:
            start, time = self.track[user]
            self.track.pop(user)
            (s, count) = self.info[start][station]
            s += t - time
            count += 1
            self.info[start][station] = (s, count)

    def getAverageTime(self, start_station: str, end_station: str) -> float:
        avg = 0.0
        if start_station in self.info:
            if end_station in self.info[start_station]:
                s, count = self.info[start_station][end_station]
                avg = s / count
        return avg


# Your UndergroundSystem object will be instantiated and called as such:
# obj = UndergroundSystem()
# obj.checkIn(id,stationName,t)
# obj.checkOut(id,stationName,t)
# param_3 = obj.getAverageTime(startStation,endStation)
```