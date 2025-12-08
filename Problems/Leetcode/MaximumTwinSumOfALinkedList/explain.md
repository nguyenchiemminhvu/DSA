## Problem

https://leetcode.com/problems/maximum-twin-sum-of-a-linked-list/description/

In a linked list of size `n` (where `n` is even), the `i`th node (0-indexed) is the **twin** of the `(n-1-i)`th node, if `0 <= i <= (n/2) - 1`.

**Twin Sum**: The sum of a node's value and its twin's value.

**Goal**: Given the head of a linked list with even length, return the maximum twin sum.

### Examples

**Example 1:**
```
Input: head = [5,4,2,1]
Output: 6
Explanation:
- Node 0 (value=5) twins with Node 3 (value=1): sum = 6
- Node 1 (value=4) twins with Node 2 (value=2): sum = 6
Maximum twin sum = 6
```

**Example 2:**
```
Input: head = [4,2,2,3]
Output: 7
Explanation:
- Node 0 (value=4) twins with Node 3 (value=3): sum = 7
- Node 1 (value=2) twins with Node 2 (value=2): sum = 4
Maximum twin sum = max(7, 4) = 7
```

**Example 3:**
```
Input: head = [1,100000]
Output: 100001
Explanation: Only pair: 1 + 100000 = 100001
```

### Constraints
- The number of nodes is an even integer in range `[2, 10^5]`
- `1 <= Node.val <= 10^5`

## Observations

1. **Twin Relationship**: For a list of length `n`:
   - Node at index `i` pairs with node at index `(n-1-i)`
   - This creates `n/2` twin pairs
   - Twin pairs are symmetric: `(0, n-1), (1, n-2), (2, n-3), ...`

2. **Key Insight**: The twin of node `i` from the start is the same as node `i` from the end (when reversed)
   - First half: indices `0, 1, 2, ..., n/2-1`
   - Second half: indices `n/2, n/2+1, ..., n-1`
   - When reversed, second half becomes: `n-1, n-2, ..., n/2`

3. **Approach Options**:
   - **Option A**: Store all values in array, then pair `arr[i] + arr[n-1-i]`
   - **Option B**: Reverse second half, then sum corresponding positions
   - **Option C**: Use fast/slow pointer to find middle, reverse second half, then traverse both halves

4. **The provided solution** uses a hybrid approach:
   - Stores original list in `arr1`
   - Reverses entire list and stores in `arr2`
   - Pairs first `n/2` elements: `arr1[i] + arr2[i]`

## Solution

### Approach: Reverse List + Array Storage

**Algorithm:**

1. **Collect original values**:
   - Traverse the linked list and store all values in `arr1`
   - This preserves the original order: `[a₀, a₁, a₂, ..., aₙ₋₁]`

2. **Reverse the list**:
   - Use the `reverse_list` helper function to reverse the linked list
   - After reversal, the list becomes: `[aₙ₋₁, aₙ₋₂, ..., a₁, a₀]`

3. **Collect reversed values**:
   - Traverse the reversed list and store values in `arr2`
   - `arr2 = [aₙ₋₁, aₙ₋₂, ..., a₁, a₀]`

4. **Calculate twin sums**:
   - For each index `i` in range `[0, n/2)`:
     - `arr1[i]` represents the node at position `i`
     - `arr2[i]` represents the node at position `n-1-i` (from original list)
     - Twin sum = `arr1[i] + arr2[i]`
   - Track the maximum sum

### Why This Works

When we reverse the list:
- Original position `i` → remains at position `i` in `arr1`
- Original position `n-1-i` → becomes position `i` in `arr2`

So `arr1[i] + arr2[i]` correctly computes the twin sum for each pair!

### Complexity Analysis

- **Time Complexity**: `O(n)`
  - First traversal to build `arr1`: `O(n)`
  - Reverse the list: `O(n)`
  - Second traversal to build `arr2`: `O(n)`
  - Find maximum over `n/2` pairs: `O(n)`
  - Total: `O(n)`

- **Space Complexity**: `O(n)`
  - `arr1` stores `n` elements
  - `arr2` stores `n` elements
  - Total extra space: `O(n)`

### Walkthrough Example: `[5,4,2,1]`

1. `arr1 = [5, 4, 2, 1]` (original order)
2. After reversal: list becomes `[1,2,4,5]`
3. `arr2 = [1, 2, 4, 5]` (reversed order)
4. Twin sums for `i = 0, 1`:
   - `i=0`: `arr1[0] + arr2[0] = 5 + 1 = 6`
   - `i=1`: `arr1[1] + arr2[1] = 4 + 2 = 6`
5. Maximum = `6` ✓

---

### Alternative Optimal Solution (O(1) Space)

A more space-efficient approach without using arrays:

```python
def pairSum(self, head: Optional[ListNode]) -> int:
    # Find middle using slow/fast pointers
    slow = fast = head
    while fast and fast.next:
        slow = slow.next
        fast = fast.next.next
    
    # Reverse second half
    prev = None
    while slow:
        nxt = slow.next
        slow.next = prev
        prev = slow
        slow = nxt
    
    # Calculate max twin sum
    max_sum = 0
    first, second = head, prev
    while second:
        max_sum = max(max_sum, first.val + second.val)
        first = first.next
        second = second.next
    
    return max_sum
```

**Advantages**:
- Time: `O(n)`
- Space: `O(1)` - no extra arrays needed
- Only modifies the list structure (can be restored if needed)

---

## Key Takeaways

1. **Twin pairs** are symmetric around the middle of the list
2. **Reversing** aligns twin nodes at corresponding positions
3. The provided solution uses arrays for clarity (`O(n)` space)
4. A more optimal solution uses two-pointer technique (`O(1)` space)
5. Both approaches leverage list reversal to align twin pairs

# Tags

`Linked List` `Two Pointers` `Stack` `Array`

