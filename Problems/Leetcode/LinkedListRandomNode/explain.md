## Problem

https://leetcode.com/problems/linked-list-random-node/description/

```
Given a singly linked list, return a random node's value from the linked list. 
Each node must have the same probability of being chosen.

Implement the Solution class:
- Solution(ListNode head): Initializes the object with the head of the singly-linked list head.
- int getRandom(): Chooses a node randomly from the list and returns its value. 
  All the nodes of the list should be equally likely to be chosen.

Example 1:
Input: ["Solution", "getRandom", "getRandom", "getRandom", "getRandom", "getRandom"]
       [[[1, 2, 3]], [], [], [], [], []]
Output: [null, 1, 3, 2, 2, 3]

Constraints:
- The number of nodes in the linked list will be in the range [1, 10^4].
- -10^4 <= Node.val <= 10^4
- At most 10^4 calls will be made to getRandom.

Follow up:
- What if the linked list is extremely large and its length is unknown to you?
- Could you solve this efficiently without using extra space?
```

## Observations

1. **Basic Approach - Array Conversion**: The simplest solution is to convert the linked list to an array during initialization, then use random indexing for `getRandom()`.

2. **Trade-offs**:
   - **Space**: O(n) - stores all node values in an array
   - **Time**: O(n) for initialization, O(1) for getRandom()
   - This approach is optimal when getRandom() is called frequently

3. **Alternative - Reservoir Sampling**: For the follow-up question (unknown/large list without extra space):
   - Use reservoir sampling algorithm
   - Space: O(1) - no array needed
   - Time: O(1) for initialization, O(n) for getRandom()
   - Each call to getRandom() traverses the list

4. **When to use each approach**:
   - **Array approach**: When getRandom() is called many times (amortized benefit)
   - **Reservoir sampling**: When memory is constrained or list is extremely large

## Solution

### Approach 1: Array Conversion (Provided Solution)

**Algorithm**:
1. **Initialization**: Traverse the linked list once and store all values in an array
2. **getRandom()**: Generate a random index and return the value at that index

**Implementation**:
```python
import random

class Solution:
    def __init__(self, head: Optional[ListNode]):
        self.arr = []
        while head:
            self.arr.append(head.val)
            head = head.next
        self.n = len(self.arr)

    def getRandom(self) -> int:
        idx = random.randint(0, self.n - 1)
        return self.arr[idx]
```

**Complexity**:
- Time: O(n) for initialization, O(1) for getRandom()
- Space: O(n) to store all values

**Pros**: Fast getRandom() calls, simple implementation
**Cons**: Uses O(n) extra space

---

### Approach 2: Reservoir Sampling (Follow-up Solution)

**Algorithm** (for getRandom()):
1. Initialize result with the first node's value
2. For each subsequent node at position i:
   - Generate random number between 0 and i (inclusive)
   - If random number is 0, replace result with current node's value
3. This ensures each node has 1/n probability of being selected

**Implementation**:
```python
import random

class Solution:
    def __init__(self, head: Optional[ListNode]):
        self.head = head

    def getRandom(self) -> int:
        result = self.head.val
        current = self.head.next
        i = 2  # Starting from second node
        
        while current:
            # Generate random number between 0 and i-1
            if random.randint(0, i - 1) == 0:
                result = current.val
            current = current.next
            i += 1
        
        return result
```

**Why this works** (Mathematical Proof):
- For node at position k (1-indexed):
  - Probability of being selected = (1/k) × (k/(k+1)) × ((k+1)/(k+2)) × ... × ((n-1)/n)
  - This simplifies to 1/n for all nodes

**Complexity**:
- Time: O(1) for initialization, O(n) for getRandom()
- Space: O(1) - only stores head reference

**Pros**: Minimal space usage, works with unknown list length
**Cons**: Each getRandom() call is O(n)

---

### Comparison

| Approach | Init Time | getRandom Time | Space | Best For |
|----------|-----------|----------------|-------|----------|
| Array | O(n) | O(1) | O(n) | Multiple getRandom() calls |
| Reservoir | O(1) | O(n) | O(1) | Memory-constrained, few calls |

For this problem with up to 10^4 calls, the **array approach is recommended** as it provides O(1) getRandom() at the cost of O(n) space, which is acceptable given the constraints.

# Tags
`Linked List` `Reservoir Sampling` `Randomization` `Math` `Probability`

