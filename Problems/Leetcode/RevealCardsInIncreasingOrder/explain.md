## Problem

https://leetcode.com/problems/reveal-cards-in-increasing-order/description/

```
You are given an integer array deck. There is a deck of cards where every card has a unique integer. 
The integer on the ith card is deck[i].

You can order the deck in any order you want. Initially, all the cards start face down (unrevealed) in one deck.

You will do the following steps repeatedly until all cards are revealed:
1. Take the top card of the deck, reveal it, and take it out of the deck.
2. If there are still cards in the deck then put the next top card of the deck at the bottom of the deck.
3. If there are still unrevealed cards, go back to step 1. Otherwise, stop.

Return an ordering of the deck that would reveal the cards in increasing order.

Example 1:
Input: deck = [17,13,11,2,3,5,7]
Output: [2,13,3,11,5,17,7]

Example 2:
Input: deck = [1,1000]
Output: [1,1000]

Constraints:
- 1 <= deck.length <= 1000
- 1 <= deck[i] <= 10^6
- All the values of deck are unique.
```

## Observations

1. **The revealing process**: We reveal the top card, then move the next card to the bottom, and repeat.
2. **Target**: We want cards to be revealed in increasing order (smallest to largest).
3. **Key insight**: If we know the final order should reveal cards as [2,3,5,7,11,13,17], we need to work **backwards** to find the deck arrangement.
4. **Reverse simulation**: Instead of simulating forward (reveal → move to bottom), we can simulate backward (insert from bottom → insert card).

## Solution

### Approach: Reverse Simulation with Deque

**Core Idea**: Work backwards from the sorted deck (largest to smallest) and reverse the revealing process.

**Algorithm**:
1. Sort the deck in **descending order** (largest to smallest): [17,13,11,7,5,3,2]
2. Start with the largest card in the result
3. For each remaining card (from second largest to smallest):
   - **Reverse the "move to bottom" operation**: Take the bottom card and move it to the top
   - **Reverse the "reveal" operation**: Place the current card on top
4. This builds the deck arrangement that will reveal cards in increasing order

**Step-by-step example with [17,13,11,2,3,5,7]**:

```
Sorted descending: [17, 13, 11, 7, 5, 3, 2]

Step 1: res = [17]

Step 2: Process 13
  - Move bottom to top: [17] (nothing to move)
  - Add 13 to top: [13, 17]

Step 3: Process 11
  - Move bottom to top: [17, 13]
  - Add 11 to top: [11, 17, 13]

Step 4: Process 7
  - Move bottom to top: [13, 11, 17]
  - Add 7 to top: [7, 13, 11, 17]

Step 5: Process 5
  - Move bottom to top: [17, 7, 13, 11]
  - Add 5 to top: [5, 17, 7, 13, 11]

Step 6: Process 3
  - Move bottom to top: [11, 5, 17, 7, 13]
  - Add 3 to top: [3, 11, 5, 17, 7, 13]

Step 7: Process 2
  - Move bottom to top: [13, 3, 11, 5, 17, 7]
  - Add 2 to top: [2, 13, 3, 11, 5, 17, 7]

Result: [2, 13, 3, 11, 5, 17, 7]
```

**Verification** (forward simulation):
- Reveal 2 → Move 13 to bottom: [3, 11, 5, 17, 7, 13]
- Reveal 3 → Move 11 to bottom: [5, 17, 7, 13, 11]
- Reveal 5 → Move 17 to bottom: [7, 13, 11, 17]
- Reveal 7 → Move 13 to bottom: [11, 17, 13]
- Reveal 11 → Move 17 to bottom: [13, 17]
- Reveal 13 → Move 17 to bottom: [17]
- Reveal 17

Cards revealed: [2, 3, 5, 7, 11, 13, 17] ✓ (increasing order)

**Python Implementation**:

```python
from collections import deque

class Solution:
    def deckRevealedIncreasing(self, deck: List[int]) -> List[int]:
        # Sort in descending order to process from largest to smallest
        deck.sort(reverse=True)
        
        # Initialize result with the largest card
        res = deque([deck[0]])
        
        # Process remaining cards
        for i in range(1, len(deck)):
            # Reverse the "move to bottom" operation
            res.appendleft(res.pop())
            # Reverse the "reveal" operation
            res.appendleft(deck[i])
        
        return list(res)
```

**Complexity Analysis**:
- **Time Complexity**: O(n log n)
  - Sorting: O(n log n)
  - Building result: O(n) with each operation being O(1) for deque
- **Space Complexity**: O(n) for the deque

**Why use deque?**
- `appendleft()` and `pop()` operations are both O(1)
- Efficient for operations at both ends of the sequence
- Perfect for simulating the deck manipulation

# Tags
`Array` `Queue` `Deque` `Simulation` `Sorting` `Reverse Thinking`

