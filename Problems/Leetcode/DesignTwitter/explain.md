## Problem

https://leetcode.com/problems/design-twitter/description/

Design a simplified version of Twitter where users can post tweets, follow/unfollow another user, and is able to see the 10 most recent tweets in the user's news feed.

**Implement the Twitter class:**

- `Twitter()` - Initializes your twitter object
- `void postTweet(int userId, int tweetId)` - Composes a new tweet with ID `tweetId` by the user `userId`. Each call to this function will be made with a unique `tweetId`
- `List<Integer> getNewsFeed(int userId)` - Retrieves the 10 most recent tweet IDs in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user themself. Tweets must be ordered from most recent to least recent
- `void follow(int followerId, int followeeId)` - The user with ID `followerId` started following the user with ID `followeeId`
- `void unfollow(int followerId, int followeeId)` - The user with ID `followerId` started unfollowing the user with ID `followeeId`

**Example:**
```
Input: ["Twitter", "postTweet", "getNewsFeed", "follow", "postTweet", "getNewsFeed", "unfollow", "getNewsFeed"]
       [[], [1, 5], [1], [1, 2], [2, 6], [1], [1, 2], [1]]
Output: [null, null, [5], null, null, [6, 5], null, [5]]

Explanation:
Twitter twitter = new Twitter();
twitter.postTweet(1, 5);  // User 1 posts tweet 5
twitter.getNewsFeed(1);   // Returns [5]
twitter.follow(1, 2);     // User 1 follows user 2
twitter.postTweet(2, 6);  // User 2 posts tweet 6
twitter.getNewsFeed(1);   // Returns [6, 5] - tweet 6 is more recent
twitter.unfollow(1, 2);   // User 1 unfollows user 2
twitter.getNewsFeed(1);   // Returns [5] - no longer sees user 2's tweets
```

**Constraints:**
- 1 ≤ userId, followerId, followeeId ≤ 500
- 0 ≤ tweetId ≤ 10^4
- All tweets have unique IDs
- At most 3 × 10^4 calls will be made to postTweet, getNewsFeed, follow, and unfollow
- A user cannot follow themselves

## Observations

1. **Tweet Ordering**: Tweets must be ordered by recency across all users, not just within a single user's timeline. This requires a global timestamp mechanism.

2. **K-Way Merge Problem**: Getting the news feed is essentially merging K sorted lists (where K = number of users being followed + 1 for self), and taking the 10 most recent items.

3. **Data Structure Choices**:
   - Each user's tweets form a sorted sequence (newest first)
   - We need efficient prepend operation for new tweets → **Linked List**
   - We need to merge multiple sorted sequences → **Min-Heap**
   - We need to track followers → **Set**

4. **Timestamp Strategy**: Instead of using actual timestamps, we can use a global counter that decrements. This works perfectly with Python's min-heap to get max behavior (most recent first).

5. **Space-Time Tradeoff**: We store all tweets but only retrieve 10 at a time. This is acceptable given the constraint (max 30,000 tweets total).

## Solution

### Approach: Linked List + Min-Heap (K-Way Merge)

**Core Algorithm:**

1. **postTweet**: 
   - Assign a global decreasing timestamp to each tweet
   - Prepend the tweet to the user's linked list (O(1))

2. **getNewsFeed**:
   - Initialize a min-heap with the head of each relevant tweet list (user's own + all followed users)
   - Extract min (most recent) 10 times, pushing the next tweet from that list each time
   - This is the classic k-way merge algorithm

3. **follow/unfollow**:
   - Simply add/remove from the follow set

**Data Structures:**

```python
global_id = 0xFFFFFFFF  # Start high and decrement (negatives work for recency)

class ListNode:
    key: int      # Global timestamp (decreasing)
    val: int      # Tweet ID
    next: ListNode # Next older tweet

class Twitter:
    m_user_tweet: dict    # user_id -> head of tweet linked list
    m_user_follow: dict   # user_id -> set of followed users
```

**Key Techniques:**

1. **Global Timestamp**: Starting at `0xFFFFFFFF` and decrementing ensures:
   - Each tweet has a unique timestamp
   - More recent tweets have smaller values
   - Works perfectly with min-heap to achieve max-heap behavior

2. **Linked List for Tweets**: 
   - New tweets are prepended (O(1))
   - List is naturally sorted by recency
   - Efficient for k-way merge (only need heads in heap)

3. **Min-Heap for K-Way Merge**:
   - Heap stores tuples: `(timestamp, tweet_id, next_node_pointer)`
   - Python's heapq is a min-heap, so smallest timestamp (most recent) comes first
   - After popping a tweet, push its next tweet to continue the merge

**Time Complexity:**
- `postTweet`: O(1) - simple linked list prepend
- `getNewsFeed`: O(F log F + 10 log F) = O(F log F), where F = number of followed users
  - Initial heap construction: O(F log F)
  - Extract 10 tweets: O(10 log F)
- `follow`: O(1) - set insertion
- `unfollow`: O(1) - set removal

**Space Complexity:**
- O(T + F) where T = total tweets, F = total follow relationships
- Each tweet stored once in linked list
- Follow relationships stored in sets

**Why This Works:**

The algorithm elegantly combines:
- **Linked lists** for efficient tweet storage and prepending
- **Min-heap** for merging sorted sequences
- **Global counter** for maintaining order without actual timestamps
- **Sets** for O(1) follow/unfollow operations

The k-way merge pattern is optimal for this problem because we're essentially asking "merge K sorted lists and give me the top 10 elements" where K = number of users in the news feed.

# Tags
`Design` `Hash Table` `Linked List` `Heap (Priority Queue)` `K-Way Merge` `OOD`

