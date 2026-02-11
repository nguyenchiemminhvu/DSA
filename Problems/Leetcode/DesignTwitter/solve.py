from typing import List
from typing import Optional
import heapq

global_id = 0xFFFFFFFF

class ListNode:
    def __init__(self, key:int = 0xFFFFFFFF, val:int = 0, next_node:Optional['ListNode'] = None):
        self.key = key
        self.val = val
        self.next = next_node

class Twitter:

    def __init__(self):
        self.m_user_tweet = {} # user_id -> head of ListNode tweets
        self.m_user_follow = {} # user_id -> List of users

    def postTweet(self, user_id: int, tweet_id: int) -> None:
        global global_id
        tweet = ListNode(global_id, tweet_id)
        global_id -= 1
        if user_id not in self.m_user_tweet:
            self.m_user_tweet[user_id] = tweet
        else:
            tweet.next = self.m_user_tweet[user_id]
            self.m_user_tweet[user_id] = tweet

    def getNewsFeed(self, user_id: int) -> List[int]:
        pq = []
        if user_id in self.m_user_tweet:
            p_cur_list = self.m_user_tweet[user_id]
            heapq.heappush(pq, (p_cur_list.key, p_cur_list.val, p_cur_list.next))
        if user_id in self.m_user_follow:
            for following_user in self.m_user_follow[user_id]:
                if following_user in self.m_user_tweet:
                    p_list = self.m_user_tweet[following_user]
                    heapq.heappush(pq, (p_list.key, p_list.val, p_list.next))
        
        res = []
        k = 10
        while pq and k > 0:
            key, val, p_next = heapq.heappop(pq)
            res.append(val)
            if p_next:
                heapq.heappush(pq, (p_next.key, p_next.val, p_next.next))
            k -= 1

        return res

    def follow(self, user_id: int, target_id: int) -> None:
        if user_id not in self.m_user_follow:
            self.m_user_follow[user_id] = set()
        self.m_user_follow[user_id].add(target_id)

    def unfollow(self, user_id: int, target_id: int) -> None:
        if user_id in self.m_user_follow:
            self.m_user_follow[user_id].remove(target_id)

# Your Twitter object will be instantiated and called as such:
# obj = Twitter()
# obj.postTweet(userId,tweetId)
# param_2 = obj.getNewsFeed(userId)
# obj.follow(followerId,followeeId)
# obj.unfollow(followerId,followeeId)