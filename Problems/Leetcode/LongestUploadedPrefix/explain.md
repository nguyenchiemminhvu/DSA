## Problem

https://leetcode.com/problems/longest-uploaded-prefix/description/

You are given a stream of n videos, each represented by a distinct number from 1 to n that you need to "upload" to a server. You need to implement a data structure that calculates the length of the longest uploaded prefix at various points in the upload process.

We consider i to be an uploaded prefix if all videos in the range 1 to i (inclusive) have been uploaded to the server. The longest uploaded prefix is the maximum value of i that satisfies this definition.

**Implement the LUPrefix class:**
- `LUPrefix(int n)` - Initializes the object for a stream of n videos
- `void upload(int video)` - Uploads video to the server
- `int longest()` - Returns the length of the longest uploaded prefix

**Example:**
```
Input: ["LUPrefix", "upload", "longest", "upload", "longest", "upload", "longest"]
       [[4], [3], [], [1], [], [2], []]
Output: [null, null, 0, null, 1, null, 3]

Explanation:
LUPrefix server = new LUPrefix(4);
server.upload(3);  // Upload video 3
server.longest();  // Return 0 (video 1 not uploaded yet)
server.upload(1);  // Upload video 1
server.longest();  // Return 1 (prefix [1])
server.upload(2);  // Upload video 2
server.longest();  // Return 3 (prefix [1,2,3])
```

**Constraints:**
- 1 <= n <= 10^5
- 1 <= video <= n
- All values of video are distinct
- At most 2 * 10^5 calls total to upload and longest
- At least one call will be made to longest

## Observations

1. **Prefix Definition**: A valid prefix must be continuous from 1 to some value i. If video 2 is missing, we can't count videos 3, 4, 5... as part of the prefix.

2. **Sequential Nature**: The prefix can only extend when the next expected video in sequence is uploaded. For example, if we have [1, 2, 3] and upload video 5, the prefix remains [1, 2, 3] until video 4 is uploaded.

3. **Out-of-Order Uploads**: Videos can be uploaded in any order, but the prefix only grows sequentially. We need to track which videos are uploaded while waiting for gaps to be filled.

4. **Efficient Lookup**: We need to efficiently check if the next required video has been uploaded, especially when processing videos that arrive out of order.

5. **State Tracking**: We need to maintain:
   - Which videos have been uploaded
   - What the current longest prefix length is
   - Whether newly uploaded videos can extend the prefix

## Solution

### Approach: Min-Heap with Next Pointer

**Key Insight**: Use a min-heap to store out-of-order videos and a pointer to track the next expected video in the prefix sequence.

**Algorithm:**

1. **Initialize**: 
   - Create a min-heap to store uploaded videos that are ahead of the current prefix
   - Maintain a `next` pointer starting at 1, representing the next video needed to extend the prefix

2. **Upload Operation**:
   - Add the video to the min-heap
   - Check if the top of the heap (smallest video) equals `next`
   - If yes, we can extend the prefix:
     - Pop from heap and increment `next`
     - Repeat while the heap's minimum equals `next` (handle cascading extensions)
   
3. **Longest Operation**:
   - Return `next - 1` since `next` points to the next expected video, not the current prefix length

**Why This Works:**

- The min-heap keeps videos sorted by their number
- When we upload a video, we immediately check if it (or any previously uploaded videos) can extend the prefix
- The heap automatically maintains the smallest unprocessed video at the top
- By checking `pq[0] == next`, we efficiently determine if the prefix can grow

**Example Walkthrough:**

```
Initial: next = 1, heap = []

upload(3): heap = [3], next = 1 (3 ≠ 1, can't extend)
longest(): return 0

upload(1): heap = [1, 3], next = 1
           1 == 1 → pop, next = 2
           3 ≠ 2 → stop
           heap = [3], next = 2
longest(): return 1

upload(2): heap = [2, 3], next = 2
           2 == 2 → pop, next = 3
           3 == 3 → pop, next = 4
           heap = [], next = 4
longest(): return 3
```

**Complexity Analysis:**

- **Time Complexity**: 
  - `upload(video)`: O(log n) for heap insertion + O(k log n) where k is the number of consecutive videos that can be processed. Amortized O(log n) since each video is pushed and popped at most once.
  - `longest()`: O(1) - just return the stored value
  
- **Space Complexity**: O(n) - in the worst case, all n videos could be in the heap

**Implementation:**

```python
import heapq

class LUPrefix:
    def __init__(self, n: int):
        self.pq = []        # Min-heap to store out-of-order videos
        self.next = 1       # Next expected video in sequence

    def upload(self, video: int) -> None:
        heapq.heappush(self.pq, video)
        # Process all consecutive videos starting from 'next'
        while self.pq and self.pq[0] == self.next:
            self.next += 1
            heapq.heappop(self.pq)

    def longest(self) -> int:
        return self.next - 1
```

**Alternative Approaches:**

1. **Set + Next Pointer**: Use a set to store uploaded videos and increment `next` while checking set membership. Similar complexity but simpler.
   
2. **Boolean Array**: Use a boolean array to mark uploaded videos. O(1) upload and longest operations, but requires O(n) space always.

# Tags
#heap #min-heap #priority-queue #greedy #design #data-structure #streaming

