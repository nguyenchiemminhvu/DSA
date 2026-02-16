from typing import List
import heapq

class Solution:
    def mostPopularCreator(self, creators: List[str], ids: List[str], views: List[int]) -> List[List[str]]:
        n = len(ids)
        d_creator = {} # creator -> sum_popularity, heap(videos(-views, id))
        max_popularity = 0
        most_popular_creators = set()
        for i in range(n):
            creator, video_id, view = creators[i], ids[i], views[i]
            if creator not in d_creator:
                d_creator[creator] = [0, []]
            
            d_creator[creator][0] += view
            heapq.heappush(d_creator[creator][1], (-view, video_id))
            if d_creator[creator][0] > max_popularity:
                max_popularity = d_creator[creator][0]
                most_popular_creators.clear()
                most_popular_creators.add(creator)
            elif d_creator[creator][0] == max_popularity:
                most_popular_creators.add(creator)        
        
        res = []
        for creator in most_popular_creators:
            most_popular_video = d_creator[creator][1][0][1]
            res.append([creator, most_popular_video])
        return res