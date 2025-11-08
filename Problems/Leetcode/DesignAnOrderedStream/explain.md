## Problem

https://leetcode.com/problems/design-an-ordered-stream/description/

```
There is a stream of n (idKey, value) pairs arriving in an arbitrary order, where idKey is an integer between 1 and n and value is a string. No two pairs have the same id.

Design a stream that returns the values in increasing order of their IDs by returning a chunk (list) of values after each insertion. The concatenation of all the chunks should result in a list of the sorted values.

Implement the OrderedStream class:

OrderedStream(int n) Constructs the stream to take n values.
String[] insert(int idKey, String value) Inserts the pair (idKey, value) into the stream, then returns the largest possible chunk of currently inserted values that appear next in the order.

Example:

Input
["OrderedStream", "insert", "insert", "insert", "insert", "insert"]
[[5], [3, "ccccc"], [1, "aaaaa"], [2, "bbbbb"], [5, "eeeee"], [4, "ddddd"]]
Output
[null, [], ["aaaaa"], ["bbbbb", "ccccc"], [], ["ddddd", "eeeee"]]

Explanation
// Note that the values ordered by ID is ["aaaaa", "bbbbb", "ccccc", "ddddd", "eeeee"].
OrderedStream os = new OrderedStream(5);
os.insert(3, "ccccc"); // Inserts (3, "ccccc"), returns [].
os.insert(1, "aaaaa"); // Inserts (1, "aaaaa"), returns ["aaaaa"].
os.insert(2, "bbbbb"); // Inserts (2, "bbbbb"), returns ["bbbbb", "ccccc"].
os.insert(5, "eeeee"); // Inserts (5, "eeeee"), returns [].
os.insert(4, "ddddd"); // Inserts (4, "ddddd"), returns ["ddddd", "eeeee"].
// Concatentating all the chunks returned:
// [] + ["aaaaa"] + ["bbbbb", "ccccc"] + [] + ["ddddd", "eeeee"] = ["aaaaa", "bbbbb", "ccccc", "ddddd", "eeeee"]
// The resulting order is the same as the order above.

Constraints:

1 <= n <= 1000
1 <= id <= n
value.length == 5
value consists only of lowercase letters.
Each call to insert will have a unique id.
Exactly n calls will be made to insert.
```

## Observations

1. **Stream Processing Pattern**: This problem simulates a real-world streaming scenario where data arrives out of order but needs to be processed in sequential order.

2. **Key Insight - Pointer-Based Approach**: The solution uses a pointer (`idx`) to track the next expected position in the sequence. This eliminates the need to scan from the beginning each time.

3. **Buffer Strategy**: The array `arr` acts as a buffer that stores values at their correct positions (idKey-1 since IDs are 1-indexed but arrays are 0-indexed).

4. **Chunked Output**: The algorithm returns the longest contiguous sequence starting from the current pointer position, which is exactly what the problem requires.

5. **Efficiency**: Each position in the array is visited at most twice - once when inserted and once when returned in a chunk.

## Solution

1. **Initialization**: 
   - Create an array of size `n` filled with empty strings
   - Initialize pointer `idx` to 0 (next expected position)

2. **Insert Operation**:
   - Place the value at position `idKey-1` (convert to 0-indexed)
   - Starting from current pointer position, collect all consecutive non-empty values
   - Update pointer to the first empty position found
   - Return the collected chunk

### Example Walkthrough:

```
OrderedStream(5): arr = ["", "", "", "", ""], idx = 0

insert(3, "ccccc"): 
- arr = ["", "", "ccccc", "", ""], idx = 0
- Check from idx=0: arr[0] is empty, so return []

insert(1, "aaaaa"):
- arr = ["aaaaa", "", "ccccc", "", ""], idx = 0  
- Check from idx=0: arr[0]="aaaaa", continue
- Check idx=1: arr[1] is empty, update idx=1, return ["aaaaa"]

insert(2, "bbbbb"):
- arr = ["aaaaa", "bbbbb", "ccccc", "", ""], idx = 1
- Check from idx=1: arr[1]="bbbbb", arr[2]="ccccc", continue
- Check idx=3: arr[3] is empty, update idx=3, return ["bbbbb", "ccccc"]

insert(5, "eeeee"):
- arr = ["aaaaa", "bbbbb", "ccccc", "", "eeeee"], idx = 3
- Check from idx=3: arr[3] is empty, return []

insert(4, "ddddd"):
- arr = ["aaaaa", "bbbbb", "ccccc", "ddddd", "eeeee"], idx = 3
- Check from idx=3: arr[3]="ddddd", arr[4]="eeeee", continue
- Reached end, return ["ddddd", "eeeee"]
```

### Time & Space Complexity:

- **Time Complexity**: O(1) amortized per insert operation
  - Each position is visited at most twice throughout all operations
  - Total time across all operations: O(n)
  
- **Space Complexity**: O(n) for the buffer array

### Key Design Decisions:

1. **Pointer Optimization**: Maintaining `idx` pointer avoids redundant scanning of already-processed positions
2. **In-Place Storage**: Using array indexing for direct O(1) placement of values
3. **Greedy Collection**: Collecting the maximum possible chunk in each operation as required

# Tags

Array, Design, Simulation, Stream Processing, Two Pointers

