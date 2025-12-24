## Problem

https://leetcode.com/problems/find-consecutive-integers-from-a-data-stream/description/

```
For a stream of integers, implement a data structure that checks if the last k integers 
parsed in the stream are equal to value.

Implement the DataStream class:
- DataStream(int value, int k): Initializes the object with an empty integer stream and 
  the two integers value and k.
- boolean consec(int num): Adds num to the stream of integers. Returns true if the last k 
  integers are equal to value, and false otherwise. If there are less than k integers, 
  the condition does not hold true, so returns false.

Example 1:
Input: ["DataStream", "consec", "consec", "consec", "consec"]
       [[4, 3], [4], [4], [4], [3]]
Output: [null, false, false, true, false]

Explanation:
DataStream dataStream = new DataStream(4, 3); //value = 4, k = 3 
dataStream.consec(4); // Only 1 integer is parsed, so returns False. 
dataStream.consec(4); // Only 2 integers are parsed.
                      // Since 2 is less than k, returns False. 
dataStream.consec(4); // The 3 integers parsed are all equal to value, so returns True. 
dataStream.consec(3); // The last k integers parsed in the stream are [4,4,3].
                      // Since 3 is not equal to value, it returns False.

Constraints:
- 1 <= value, num <= 10^9
- 1 <= k <= 10^5
- At most 10^5 calls will be made to consec.
```

## Observations

1. **Naive Approach**: We could maintain a queue/deque of the last k elements and check if all are equal to `value`. However, this requires O(k) space and O(k) time per check.

2. **Key Insight**: We don't need to store all k elements. We only need to know if the last k elements are all equal to `value`. This can be tracked with a counter.

3. **Wrong Element Counter**: Instead of counting correct elements, we count "wrong" elements (elements not equal to `value`) in the last k positions. If this count is 0 and we have at least k elements, return true.

4. **Counter Logic**:
   - When we see a wrong element, set `count_wrong = k` (the next k elements need to all be correct)
   - When we see a correct element, decrement `count_wrong` (one less wrong element in our window)
   - Keep `count_wrong` at 0 minimum (it can't go negative)

5. **Edge Cases**:
   - Less than k elements have been processed: always return false
   - First k elements are all correct: return true after the k-th element
   - A wrong element appears: need k more correct elements before returning true again

## Solution

### Approach: Wrong Element Counter

The clever insight is to track how many more correct elements we need to see before we can return true.

**Algorithm**:
1. Maintain `count_wrong`: represents how many more correct elements we need before the last k are all equal to `value`
2. Maintain `n`: total number of elements processed
3. For each new element:
   - If it's wrong: set `count_wrong = k` (we need k correct elements now)
   - If it's correct: decrement `count_wrong` (one step closer to having k consecutive correct elements)
   - Keep `count_wrong >= 0` always
4. Return true only if `n >= k` and `count_wrong == 0`

**Why This Works**:
- `count_wrong` acts as a "cooldown timer" after seeing a wrong element
- When we see a wrong element, we need exactly k correct elements to have k consecutive correct elements
- Each correct element decrements this counter
- When counter reaches 0 and we have processed at least k elements, we know the last k are all correct

**Example Walkthrough** (value=4, k=3):
```
consec(4): n=1, count_wrong=0->-1->0, return false (n<k)
consec(4): n=2, count_wrong=0->-1->0, return false (n<k)
consec(4): n=3, count_wrong=0->-1->0, return true (n>=k, count_wrong=0)
consec(3): n=4, count_wrong=3, return false (count_wrong>0)
consec(4): n=5, count_wrong=2, return false (count_wrong>0)
consec(4): n=6, count_wrong=1, return false (count_wrong>0)
consec(4): n=7, count_wrong=0, return true (n>=k, count_wrong=0)
```

**Implementation**:
```python
class DataStream:
    def __init__(self, value: int, k: int):
        self.value = value
        self.k = k
        self.count_wrong = 0  # How many more correct elements needed
        self.n = 0             # Total elements processed

    def consec(self, num: int) -> bool:
        self.n += 1
        
        if num != self.value:
            # Wrong element: need k consecutive correct elements now
            self.count_wrong = self.k
        else:
            # Correct element: one step closer to k consecutive
            self.count_wrong -= 1
            if self.count_wrong < 0:
                self.count_wrong = 0
        
        # Return true only if we have k+ elements and no wrong elements in last k
        if self.n < self.k or self.count_wrong > 0:
            return False
        return True
```

**Complexity Analysis**:
- Time Complexity: O(1) per `consec` call
- Space Complexity: O(1) - only storing counters, not the actual elements

**Advantages over Queue Approach**:
- O(1) space instead of O(k)
- O(1) time instead of O(k) for checking all elements
- Simpler and more elegant

# Tags
#data-stream #sliding-window #counter #design #leetcode-medium

