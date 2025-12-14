## Problem

https://leetcode.com/problems/number-of-ways-to-divide-a-long-corridor/description/

Along a long library corridor, there is a line of seats and decorative plants. You are given a 0-indexed string `corridor` of length `n` consisting of letters 'S' and 'P' where each 'S' represents a seat and each 'P' represents a plant.

One room divider has already been installed to the left of index 0, and another to the right of index n - 1. Additional room dividers can be installed. For each position between indices i - 1 and i (1 <= i <= n - 1), at most one divider can be installed.

**Task**: Divide the corridor into non-overlapping sections, where each section has **exactly two seats** with any number of plants. There may be multiple ways to perform the division. Two ways are different if there is a position with a room divider installed in the first way but not in the second way.

Return the number of ways to divide the corridor modulo 10^9 + 7. If there is no way, return 0.

**Example 1:**
- Input: `corridor = "SSPPSPS"`
- Output: `3`
- Explanation: There are 3 different ways to divide the corridor where each section has exactly two seats.

**Example 2:**
- Input: `corridor = "PPSPSP"`
- Output: `1`
- Explanation: There is only 1 way to divide the corridor, by not installing any additional dividers.

**Example 3:**
- Input: `corridor = "S"`
- Output: `0`
- Explanation: There is no way to divide the corridor because there will always be a section that does not have exactly two seats.

**Constraints:**
- `n == corridor.length`
- `1 <= n <= 10^5`
- `corridor[i]` is either 'S' or 'P'

## Observations

### Key Insights

1. **Each section must have exactly 2 seats**: This is the main constraint. We can't have sections with 0, 1, or 3+ seats.

2. **Total seats must be even**: If the total number of 'S' characters is odd, or less than 2, it's impossible to divide the corridor properly. Return 0 immediately.

3. **Decision points occur at plants between sections**: Once we have 2 seats in a section, we MUST close that section when we encounter the next seat. However, if we encounter plants ('P') after completing a 2-seat section, we have choices about where to place the divider.

4. **Plants between 2-seat sections create choices**: If there are `k` plants between the 2nd seat of one section and the 1st seat of the next section, we have `k + 1` positions to place the divider (before each plant, or after all of them).

5. **Multiplication principle**: The total number of ways is the product of choices at each decision point.

### State Representation

For the DP solution, we track:
- **index**: Current position in the corridor
- **seats**: Number of seats in the current section (0, 1, or 2)

### Critical States

- **seats == 2 and corridor[index] == 'S'**: We MUST close the current section and start a new one (forced decision).
- **seats == 2 and corridor[index] == 'P'**: We have 2 choices:
  1. Close the section here and start fresh (next state: seats = 0)
  2. Keep this plant in the current section (next state: seats = 2)
- **seats < 2**: We continue growing the section, incrementing seats if we find 'S'.

## Solution

### Approach: Dynamic Programming with Memoization (Top-Down)

The solution uses recursion with memoization to count the number of valid ways to divide the corridor.

```python
class Solution:
    def numberOfWays(self, corridor: str) -> int:
        MOD = 1_000_000_007
        
        # Cache[index][seats] = number of ways to divide from index to end
        # with 'seats' number of seats already in current section
        cache = [[-1] * 3 for _ in range(len(corridor))]
        
        def count(index, seats):
            # Base case: reached the end of corridor
            if index == len(corridor):
                # Valid only if last section has exactly 2 seats
                return 1 if seats == 2 else 0
            
            # Return cached result if available
            if cache[index][seats] != -1:
                return cache[index][seats]
            
            # Case 1: Current section already has 2 seats
            if seats == 2:
                if corridor[index] == "S":
                    # Must close section, this 'S' starts new section
                    result = count(index + 1, 1)
                else:
                    # Current is 'P', we have 2 choices:
                    # 1. Close section here, start fresh
                    # 2. Keep plant in current section
                    result = (count(index + 1, 0) + count(index + 1, 2)) % MOD
            
            # Case 2: Current section has < 2 seats
            else:
                if corridor[index] == "S":
                    # Add this seat to current section
                    result = count(index + 1, seats + 1)
                else:
                    # Keep plant in current section
                    result = count(index + 1, seats)
            
            # Memoize and return
            cache[index][seats] = result
            return result
        
        return count(0, 0)
```

### How It Works

1. **Initialization**: 
   - Start with `count(0, 0)` - from index 0 with 0 seats in current section
   - Cache stores results for each (index, seats) pair

2. **Base Case**:
   - When we reach the end (`index == len(corridor)`), return 1 if the last section has exactly 2 seats, otherwise 0

3. **Recursive Cases**:
   
   **When seats == 2** (current section is complete):
   - If `corridor[index] == 'S'`: We encounter the 3rd seat, so we MUST close the previous section. This 'S' becomes the first seat of the new section → `count(index + 1, 1)`
   - If `corridor[index] == 'P'`: We have flexibility:
     - Option 1: Close section, start new empty section → `count(index + 1, 0)`
     - Option 2: Include this plant in current section → `count(index + 1, 2)`
     - Total ways = sum of both options
   
   **When seats < 2** (still building the section):
   - If `corridor[index] == 'S'`: Add seat to section → `count(index + 1, seats + 1)`
   - If `corridor[index] == 'P'`: Add plant to section → `count(index + 1, seats)`

4. **Memoization**: Cache results to avoid recomputing the same subproblems

### Complexity Analysis

- **Time Complexity**: O(n × 3) = **O(n)**
  - We have `n` positions and 3 possible seat counts (0, 1, 2)
  - Each state is computed once due to memoization
  
- **Space Complexity**: **O(n)**
  - Cache array: O(n × 3) = O(n)
  - Recursion stack depth: O(n) in worst case

### Alternative Approach: Iterative Counting

We can also solve this by counting plants between completed 2-seat sections:

```python
def numberOfWays(self, corridor: str) -> int:
    MOD = 1_000_000_007
    seats = [i for i, c in enumerate(corridor) if c == 'S']
    
    # Need even number of seats and at least 2
    if len(seats) < 2 or len(seats) % 2 == 1:
        return 0
    
    result = 1
    # Count plants between each pair of 2-seat sections
    for i in range(2, len(seats), 2):
        # Distance between 2nd seat of previous section and 1st seat of current
        plants = seats[i] - seats[i - 1]
        # We have 'plants' positions to place divider
        result = (result * plants) % MOD
    
    return result
```

This approach:
1. Extracts all seat positions
2. Groups them into pairs (each section needs 2 seats)
3. Counts plants between consecutive sections
4. Multiplies choices together

# Tags

Dynamic Programming, Memoization, String, Combinatorics, Math

