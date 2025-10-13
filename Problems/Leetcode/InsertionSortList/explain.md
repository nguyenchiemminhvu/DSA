## Problem

https://leetcode.com/problems/insertion-sort-list/description/

```
Given the head of a singly linked list, sort the list using insertion sort, and return the sorted list's head.

The steps of the insertion sort algorithm:

Insertion sort iterates, consuming one input element each repetition and growing a sorted output list.
At each iteration, insertion sort removes one element from the input data, finds the location it belongs within the sorted list and inserts it there.
It repeats until no input elements remain.
The following is a graphical example of the insertion sort algorithm. The partially sorted list (black) initially contains only the first element in the list. One element (red) is removed from the input data and inserted in-place into the sorted list with each iteration.

Example 1:

Input: head = [4,2,1,3]
Output: [1,2,3,4]

Example 2:

Input: head = [-1,5,3,4,0]
Output: [-1,0,3,4,5]

Constraints:

The number of nodes in the list is in the range [1, 5000].
-5000 <= Node.val <= 5000
```

## Observations

1. **Classic Insertion Sort on Linked List**: This problem adapts the classic insertion sort algorithm to work with a singly-linked list instead of an array. The key challenge is that we can't access elements by index and need to carefully manage pointers.

2. **In-place Sorting**: The algorithm sorts the linked list in-place by rearranging pointers rather than creating new nodes, which makes it space-efficient (O(1) extra space).

3. **Two-pointer Approach**: 
   - `cur`: points to the current node being inserted into the sorted portion
   - `prev`: points to the node before `cur`, which helps maintain connectivity when removing `cur`

4. **Sorted Portion Grows from Left**: The left portion of the list (from head) is always sorted, and we continuously insert elements from the unsorted portion into their correct position.

5. **Edge Cases**:
   - Empty list or single node: already sorted
   - Node already in correct position: no relinking needed
   - Node needs to become new head: special handling required

6. **Time Complexity**: O(n²) where n is the number of nodes
   - Outer loop: O(n) iterations
   - Inner loop: O(n) in worst case (searching for insertion position)
   
7. **Space Complexity**: O(1) - only uses a constant number of pointers

## Solution

### Algorithm Overview

This solution uses insertion sort with a **dummy head node** to simplify pointer manipulation. The dummy node eliminates the need for special case handling when inserting at the beginning of the list, making the code cleaner and more elegant.

### Key Improvements Over Basic Approach

1. **Dummy Head Node**: Using a sentinel node with value `-0x7FFFFFFF` (minimum integer) ensures all actual nodes will be inserted after it, eliminating special case logic for inserting at the head.

2. **Unified Insertion Logic**: With the dummy node, there's only one insertion case to handle - always insert after `before_p`.

### Step-by-Step Explanation

#### 1. Base Case Handling
```python
if head == None or head.next == None:
    return head
```
- If the list is empty or has only one node, it's already sorted

#### 2. Dummy Node Setup
```python
dummy = ListNode(-0x7FFFFFFF)
dummy.next = head
head = dummy
```
- Create a dummy node with minimum possible value
- Link it to the original head
- Update `head` to point to the dummy node
- This creates a "virtual head" that stays before all real nodes

#### 3. Initialization
```python
cur = head.next.next
prev = head.next
```
- `cur`: points to the second actual node (first node to be sorted)
- `prev`: points to the first actual node
- The first actual node is already "sorted" by itself

#### 4. Main Loop - Process Each Node
```python
while cur:
```
- Continue until all nodes have been processed

#### 5. Find Insertion Position
```python
key_val = cur.val
p = head
before_p = head
while p != cur and p.val < key_val:
    before_p = p
    p = p.next
```
- Store the value to insert (`key_val`)
- Start scanning from the dummy head
- `before_p` always starts at `head` (the dummy)
- Find the position where `p.val >= key_val` or reach `cur`
- `before_p` will point to the node **before** the insertion point

**Why start `before_p = head`?**
- If `key_val` is smaller than all sorted values, `before_p` stays at dummy, and we insert right after it
- This handles the "insert at beginning" case automatically

#### 6. Insert or Skip

**Case 1: Node needs insertion** (`p != cur`):
```python
prev.next = cur.next          # Remove cur from current position
cur.next = before_p.next      # Link cur to insertion point
before_p.next = cur           # Insert cur after before_p
cur = prev.next               # Move to next node to process
```

The insertion always follows the same pattern:
1. Disconnect `cur` from its current position
2. Insert `cur` between `before_p` and `before_p.next`
3. Move `cur` forward (but `prev` stays in place)

**Case 2: Already in correct position** (`p == cur`):
```python
prev = cur
cur = cur.next
```
- No relinking needed
- Advance both pointers

#### 7. Return Result
```python
return head.next
```
- Skip the dummy node and return the actual head of the sorted list

### Visual Example

Sorting `[4, 2, 1, 3]` with dummy node approach:

```
Initial setup:
dummy(-∞) -> 4 -> 2 -> 1 -> 3 -> None
             ^
           sorted portion

Step 1: Insert 2
- Sorted: [dummy, 4], Processing: 2
- Search: dummy(-∞) < 2, 4 > 2
- Insert after dummy: dummy(-∞) -> 2 -> 4 -> 1 -> 3 -> None
                                         ^
                                    sorted portion

Step 2: Insert 1
- Sorted: [dummy, 2, 4], Processing: 1
- Search: dummy(-∞) < 1, 2 > 1
- Insert after dummy: dummy(-∞) -> 1 -> 2 -> 4 -> 3 -> None
                                              ^
                                         sorted portion

Step 3: Insert 3
- Sorted: [dummy, 1, 2, 4], Processing: 3
- Search: dummy(-∞) < 3, 1 < 3, 2 < 3, 4 > 3
- Insert after 2: dummy(-∞) -> 1 -> 2 -> 3 -> 4 -> None
                                              ^
                                         sorted portion

Final: Return dummy.next
Result: 1 -> 2 -> 3 -> 4 -> None
```

### Detailed Pointer Manipulation Example

Let's trace inserting node `1` in the list `dummy -> 2 -> 4 -> 1 -> 3`:

```
Before insertion:
dummy -> 2 -> 4 -> 1 -> 3 -> None
 ^       ^    ^    ^
 head   prev   ?   cur

Finding position:
- key_val = 1
- p starts at head (dummy), before_p = head
- Check: dummy.val(-∞) < 1 → before_p = dummy, p = 2
- Check: 2.val(2) > 1 → STOP
- Result: before_p = dummy, p = 2

Insertion (p != cur):
1. prev.next = cur.next
   dummy -> 2 -> 4 -> 3 -> None
                      ^
                     cur

2. cur.next = before_p.next
   dummy -> 2 -> 4 -> 3 -> None
            ↑
   1 -------+

3. before_p.next = cur
   dummy -> 1 -> 2 -> 4 -> 3 -> None

4. cur = prev.next
   dummy -> 1 -> 2 -> 4 -> 3 -> None
                 ^         ^
                prev      cur
```

### Why This Approach is Better

1. **No Special Cases**: Eliminates the need to check if inserting at head
2. **Simpler Logic**: Only one insertion path instead of three
3. **Easier to Debug**: Unified code flow is easier to trace
4. **Less Error-Prone**: Fewer conditional branches mean fewer bugs

### Edge Cases Handled

1. **Empty list**: Returns `None` in base case
2. **Single node**: Returns unchanged in base case
3. **Already sorted**: Each node stays in place (`p == cur` case)
4. **Reverse sorted**: Each node gets inserted after dummy
5. **Duplicates**: Handled correctly by `<` comparison (stable sort)

### Complexity Analysis

- **Time Complexity**: O(n²)
  - Outer loop: O(n) iterations over all nodes
  - Inner loop: O(n) in worst case to find insertion position
  - Best case: O(n²) - already sorted still requires scanning
  - Worst case: O(n²) - reverse sorted list
  - Average case: O(n²)

- **Space Complexity**: O(1)
  - Only uses constant extra space for pointers (`dummy`, `cur`, `prev`, `p`, `before_p`, `key_val`)
  - No recursion, no additional data structures

### Common Mistakes to Avoid

1. **Forgetting to update `head` to `dummy`**: This causes the search to start from the wrong position
2. **Not returning `head.next`**: Must skip the dummy node in the result
3. **Wrong initialization of `before_p`**: Must start at `head` (dummy), not `None`
4. **Incorrect pointer order**: The three-step insertion must be done in the right order to avoid losing references

### Comparison with Array Insertion Sort

| Aspect | Array | Linked List |
|--------|-------|-------------|
| Access | O(1) random access | O(n) sequential only |
| Insertion | O(n) shift elements | O(1) pointer update |
| Search | Can use binary search | Must linear search |
| Overall | O(n²) comparisons + shifts | O(n²) comparisons only |
| In-place | Yes | Yes |

For linked lists, insertion sort is more natural than for arrays because insertion is O(1) once position is found, whereas arrays require shifting elements.

## Tags

linked list, sorting