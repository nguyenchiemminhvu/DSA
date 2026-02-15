## Problem

https://leetcode.com/problems/toggle-light-bulbs/description/

```
You are given an array bulbs of integers between 1 and 100.

There are 100 light bulbs numbered from 1 to 100. All of them are switched off initially.

For each element bulbs[i] in the array bulbs:
- If the bulbs[i]th light bulb is currently off, switch it on.
- Otherwise, switch it off.

Return the list of integers denoting the light bulbs that are on in the end, sorted in ascending order. 
If no bulb is on, return an empty list.

Constraints:
- 1 <= bulbs.length <= 100
- 1 <= bulbs[i] <= 100
```

## Observations

1. **Initial State**: All bulbs start in the OFF state
2. **Toggle Operation**: Each occurrence of a bulb number in the array toggles that bulb's state
3. **Key Insight**: A bulb's final state depends only on how many times it appears in the array:
   - **Odd count** → bulb ends up ON (off→on, off→on→off→on, etc.)
   - **Even count** → bulb ends up OFF (off→on→off, etc.)
4. **Order doesn't matter**: We only care about frequency, not the sequence of toggles
5. **Efficient approach**: Use frequency counting instead of simulating each toggle

## Solution

```python
from collections import defaultdict

class Solution:
    def toggleLightBulbs(self, nums: list[int]) -> list[int]:
        freq = defaultdict(int)
        for val in nums:
            freq[val] += 1
        
        res = []
        for k, v in freq.items():
            if v & 1:  # Check if frequency is odd using bitwise AND
                res.append(k)
        return sorted(res)
```

### Algorithm Explanation

1. **Count Frequencies**: Use a hash map (`defaultdict`) to count how many times each bulb number appears
   - Time: O(n) where n is length of input array
   
2. **Filter Odd Frequencies**: Iterate through the frequency map and collect bulbs with odd counts
   - `v & 1` is a bitwise operation checking if the count is odd
   - Only bulbs toggled an odd number of times will be ON
   
3. **Sort Result**: Return the sorted list of bulb numbers
   - Time: O(k log k) where k is the number of unique bulbs (k ≤ 100)

### Complexity Analysis

- **Time Complexity**: O(n + k log k)
  - O(n) to count frequencies
  - O(k) to filter odd frequencies
  - O(k log k) to sort results
  - Since k ≤ 100, this is effectively O(n)
  
- **Space Complexity**: O(k) where k is the number of unique bulbs
  - HashMap stores at most 100 entries
  - Result list stores at most 100 elements

### Alternative Approaches

- **Set Toggle**: Use a set and add/remove elements as you encounter them
  - Add if not present, remove if present
  - Sort at the end
  - Same complexity but more intuitive for some

# Tags
`Array` `Hash Table` `Frequency Counter` `Bit Manipulation`

