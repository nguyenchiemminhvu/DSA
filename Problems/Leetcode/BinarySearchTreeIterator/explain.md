## Problem

https://leetcode.com/problems/binary-search-tree-iterator/description/

```
Implement the BSTIterator class that represents an iterator over the in-order traversal of a binary search tree (BST):

BSTIterator(TreeNode root) Initializes an object of the BSTIterator class. The root of the BST is given as part of the constructor. The pointer should be initialized to a non-existent number smaller than any element in the BST.
boolean hasNext() Returns true if there exists a number in the traversal to the right of the pointer, otherwise returns false.
int next() Moves the pointer to the right, then returns the number at the pointer.
Notice that by initializing the pointer to a non-existent smallest number, the first call to next() will return the smallest element in the BST.

You may assume that next() calls will always be valid. That is, there will be at least a next number in the in-order traversal when next() is called.

Example 1:

Input
["BSTIterator", "next", "next", "hasNext", "next", "hasNext", "next", "hasNext", "next", "hasNext"]
[[[7, 3, 15, null, null, 9, 20]], [], [], [], [], [], [], [], [], []]
Output
[null, 3, 7, true, 9, true, 15, true, 20, false]

Explanation
BSTIterator bSTIterator = new BSTIterator([7, 3, 15, null, null, 9, 20]);
bSTIterator.next();    // return 3
bSTIterator.next();    // return 7
bSTIterator.hasNext(); // return True
bSTIterator.next();    // return 9
bSTIterator.hasNext(); // return True
bSTIterator.next();    // return 15
bSTIterator.hasNext(); // return True
bSTIterator.next();    // return 20
bSTIterator.hasNext(); // return False

Constraints:

The number of nodes in the tree is in the range [1, 105].
0 <= Node.val <= 106
At most 105 calls will be made to hasNext, and next.

Follow up:

Could you implement next() and hasNext() to run in average O(1) time and use O(h) memory, where h is the height of the tree?
```

## Observations

1. **BST In-order Traversal Property**: In a BST, in-order traversal visits nodes in ascending order. This is the key insight for implementing the iterator.

2. **Iterator Pattern**: We need to implement an iterator that can:
   - Initialize with a BST root
   - Return the next smallest element (`next()`)
   - Check if there are more elements (`hasNext()`)

3. **Approach Trade-offs**:
   - **Simple Approach**: Pre-compute all values using in-order traversal and store in array
   - **Space-Optimized Approach**: Use a stack to simulate in-order traversal on-demand

4. **Constraints Analysis**:
   - Up to 10^5 nodes and 10^5 calls to `next()`/`hasNext()`
   - Follow-up asks for O(1) average time and O(h) space complexity

## Solution

### Approach: Pre-computed In-order Traversal

**Algorithm:**
1. **Initialization**: Perform complete in-order traversal and store all values in an array
2. **Next()**: Return current element and increment index
3. **HasNext()**: Check if index is within array bounds

**Key Components:**
- **In-order Traversal**: Recursively visits left → current → right
- **Array Storage**: Stores all BST values in sorted order
- **Index Tracking**: Maintains current position in the iteration

**Time & Space Complexity:**
- **Initialization**: O(n) time, O(n) space
- **Next()**: O(1) time
- **HasNext()**: O(1) time
- **Overall Space**: O(n) for storing all values

**Pros:**
- Simple to implement and understand
- Guaranteed O(1) operations after initialization
- No risk of stack overflow for deep trees

**Cons:**
- Uses O(n) space regardless of how many elements are actually accessed
- Doesn't meet the follow-up requirement of O(h) space complexity

## Tags

binary search tree, morris traversal