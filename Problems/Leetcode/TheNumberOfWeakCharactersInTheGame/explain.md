## Problem

https://leetcode.com/problems/the-number-of-weak-characters-in-the-game/description/

You are playing a game that contains multiple characters, and each of the characters has two main properties: **attack** and **defense**. You are given a 2D integer array `properties` where `properties[i] = [attacki, defensei]` represents the properties of the ith character in the game.

A character is said to be **weak** if any other character has both attack and defense levels **strictly greater** than this character's attack and defense levels. More formally, a character `i` is said to be weak if there exists another character `j` where `attackj > attacki` and `defensej > defensei`.

Return the number of weak characters.

### Examples

**Example 1:**
```
Input: properties = [[5,5],[6,3],[3,6]]
Output: 0
Explanation: No character has strictly greater attack and defense than the other.
```

**Example 2:**
```
Input: properties = [[2,2],[3,3]]
Output: 1
Explanation: The first character is weak because the second character has a strictly greater attack and defense.
```

**Example 3:**
```
Input: properties = [[1,5],[10,4],[4,3]]
Output: 1
Explanation: The third character is weak because the second character has a strictly greater attack and defense.
```

### Constraints

- `2 <= properties.length <= 10^5`
- `properties[i].length == 2`
- `1 <= attacki, defensei <= 10^5`

## Observations

1. **Brute Force Approach**: We could compare every character with every other character to check if it's weak. This would take O(n²) time, which is too slow for n = 10^5.

2. **Sorting Strategy**: If we sort characters by one property (attack), we can optimize the comparison process for the other property (defense).

3. **Key Insight**: If we sort by attack in ascending order, any character we're currently examining can only be dominated by characters with higher attack values that come later in the sorted array.

4. **Descending Defense within Same Attack**: When characters have the same attack value, sorting their defense in descending order ensures that characters with the same attack cannot dominate each other (since we need STRICTLY greater values for both properties).

5. **Monotonic Stack Pattern**: As we iterate through the sorted array, we can maintain a stack to track potential dominating characters. When we find a character that can dominate previous ones, we count them as weak.

## Solution

### Algorithm

The solution uses a **sorting + stack** approach:

1. **Sort the properties array**:
   - Primary key: Attack value in **ascending** order
   - Secondary key: Defense value in **descending** order (when attacks are equal)
   
   ```python
   properties.sort(key=lambda x: (x[0], -x[1]))
   ```

2. **Why this sorting strategy?**
   - Ascending attack: Ensures we process characters from weakest to strongest attack
   - Descending defense (for same attack): Prevents characters with equal attack from dominating each other, since we need strictly greater values

3. **Use a stack to track characters**:
   - Iterate through sorted properties
   - For each character `(a, d)`, check if it can dominate characters in the stack
   - If `a > last_a` AND `d > last_d` (both strictly greater), the character on stack top is weak
   - Remove all weak characters from stack and increment counter
   - Push current character onto stack

4. **Return the count** of weak characters found

### Code Implementation

```python
class Solution:
    def numberOfWeakCharacters(self, properties: List[List[int]]) -> int:
        # Sort by attack ascending, defense descending (for same attack)
        properties.sort(key=lambda x: (x[0], -x[1]))
        
        count = 0
        st = []  # Stack to maintain potential dominating characters
        
        for a, d in properties:
            # Check if current character dominates characters in stack
            while st:
                last_a, last_d = st[-1]
                
                # Current character strictly dominates the top of stack
                if a > last_a and d > last_d:
                    count += 1
                    st.pop()
                else:
                    break  # Cannot dominate, stop checking
            
            # Add current character to stack
            st.append((a, d))
        
        return count
```

### Complexity Analysis

- **Time Complexity**: O(n log n)
  - Sorting: O(n log n)
  - Stack operations: O(n) - each character is pushed and popped at most once
  
- **Space Complexity**: O(n)
  - Stack: O(n) in worst case

### Example Trace

**Input**: `properties = [[1,5],[10,4],[4,3]]`

1. **After sorting**: `[[1,5],[4,3],[10,4]]`

2. **Iteration**:
   - `(1,5)`: Stack empty, push → Stack: `[(1,5)]`, count = 0
   - `(4,3)`: 4 > 1 but 3 < 5, cannot dominate → Stack: `[(1,5),(4,3)]`, count = 0
   - `(10,4)`: 
     - Check `(4,3)`: 10 > 4 and 4 > 3 ✓ → pop, count = 1
     - Check `(1,5)`: 10 > 1 but 4 < 5 ✗ → stop
     - Push `(10,4)` → Stack: `[(1,5),(10,4)]`, count = 1

3. **Result**: 1

### Alternative Approach: Sort and Track Maximum Defense

Instead of using a stack, we can sort by attack descending and track the maximum defense seen so far:

```python
def numberOfWeakCharacters(self, properties: List[List[int]]) -> int:
    properties.sort(key=lambda x: (-x[0], x[1]))
    
    count = 0
    max_defense = 0
    
    for a, d in properties:
        if d < max_defense:
            count += 1
        max_defense = max(max_defense, d)
    
    return count
```

**Why this works**: By sorting attack in descending order and defense in ascending order (for same attack), any character we process has been checked against all characters with higher attack. If its defense is less than the max defense seen, it's weak.

# Tags

`sorting` `stack` `greedy` `array` `monotonic-stack`

