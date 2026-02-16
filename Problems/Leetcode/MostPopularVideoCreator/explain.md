## Problem

https://leetcode.com/problems/most-popular-video-creator/description/

```
You are given two string arrays creators and ids, and an integer array views, all of length n. 
The ith video on a platform was created by creators[i], has an id of ids[i], and has views[i] views.

The popularity of a creator is the sum of the number of views on all of the creator's videos. 
Find the creator with the highest popularity and the id of their most viewed video.

- If multiple creators have the highest popularity, find all of them.
- If multiple videos have the highest view count for a creator, find the lexicographically smallest id.

Note: It is possible for different videos to have the same id, meaning that ids do not uniquely 
identify a video. For example, two videos with the same ID are considered as distinct videos with 
their own viewcount.

Return a 2D array of strings answer where answer[i] = [creatorsi, idi] means that creatorsi has 
the highest popularity and idi is the id of their most popular video. The answer can be returned 
in any order.

Example 1:
Input: creators = ["alice","bob","alice","chris"], ids = ["one","two","three","four"], views = [5,10,5,4]
Output: [["alice","one"],["bob","two"]]
Explanation:
- The popularity of alice is 5 + 5 = 10.
- The popularity of bob is 10.
- The popularity of chris is 4.
- alice and bob are the most popular creators.
- For bob, the video with the highest view count is "two".
- For alice, the videos with the highest view count are "one" and "three". 
  Since "one" is lexicographically smaller than "three", it is included in the answer.

Example 2:
Input: creators = ["alice","alice","alice"], ids = ["a","b","c"], views = [1,2,2]
Output: [["alice","b"]]
Explanation:
- The videos with id "b" and "c" have the highest view count.
- Since "b" is lexicographically smaller than "c", it is included in the answer.

Constraints:
- n == creators.length == ids.length == views.length
- 1 <= n <= 10^5
- 1 <= creators[i].length, ids[i].length <= 5
- creators[i] and ids[i] consist only of lowercase English letters.
- 0 <= views[i] <= 10^5
```

## Observations

1. **Two-level aggregation problem**: We need to aggregate at two levels:
   - Creator level: sum of all views across their videos
   - Video level: find the most viewed video per creator

2. **Multiple maximums**: Both creators and videos can have ties:
   - Multiple creators can have the same maximum popularity
   - Multiple videos can have the same maximum views for a creator

3. **Tie-breaking rule**: When multiple videos have the same view count for a creator, we need the lexicographically smallest ID

4. **Key insight**: We need to track:
   - Total popularity per creator
   - All videos per creator with their views
   - The global maximum popularity
   - All creators who achieve this maximum

## Solution

### Approach: Hash Map + Min Heap

**Strategy:**
1. Use a dictionary to map each creator to:
   - Their total popularity (sum of views)
   - A min heap of their videos (to efficiently find the most viewed video with smallest ID)

2. Use heap with `(-views, id)` tuples:
   - Negative views converts min heap to max heap behavior for views
   - When views are equal, the lexicographically smaller ID naturally comes first

3. Track the maximum popularity and maintain a set of creators with that popularity

4. Extract the top video for each maximum popularity creator from their heap

### Implementation:

```python
import heapq

class Solution:
    def mostPopularCreator(self, creators: List[str], ids: List[str], views: List[int]) -> List[List[str]]:
        n = len(ids)
        d_creator = {} # creator -> [sum_popularity, heap(videos(-views, id))]
        max_popularity = 0
        most_popular_creators = set()
        
        # Process each video
        for i in range(n):
            creator, video_id, view = creators[i], ids[i], views[i]
            
            # Initialize creator entry if first time seeing them
            if creator not in d_creator:
                d_creator[creator] = [0, []]
            
            # Update creator's total popularity
            d_creator[creator][0] += view
            
            # Add video to creator's heap (negative views for max heap, id for lexicographic order)
            heapq.heappush(d_creator[creator][1], (-view, video_id))
            
            # Update maximum popularity and tracking set
            if d_creator[creator][0] > max_popularity:
                max_popularity = d_creator[creator][0]
                most_popular_creators.clear()
                most_popular_creators.add(creator)
            elif d_creator[creator][0] == max_popularity:
                most_popular_creators.add(creator)        
        
        # Build result: for each top creator, get their most popular video
        res = []
        for creator in most_popular_creators:
            most_popular_video = d_creator[creator][1][0][1]  # heap top's id
            res.append([creator, most_popular_video])
        
        return res
```

### Complexity Analysis:

**Time Complexity:** O(n log n)
- We iterate through n videos once
- Each heap push operation is O(log n) in worst case (if one creator has all videos)
- Total: O(n log n)

**Space Complexity:** O(n)
- Dictionary stores all n videos across all creators
- Set stores at most n creators
- Total: O(n)

### Key Points:

1. **Heap trick**: Using `(-views, video_id)` elegantly solves both requirements:
   - Find maximum views (via negation)
   - Break ties lexicographically (natural string comparison)

2. **Dynamic tracking**: We update the set of most popular creators as we go, avoiding a second pass

3. **Heap top**: The heap guarantees that `heap[0]` is always the most viewed video with the smallest ID

# Tags
`Hash Map` `Heap` `String` `Greedy` `Sorting`

