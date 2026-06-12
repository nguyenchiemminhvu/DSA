from typing import List
from collections import deque, defaultdict

class Solution:
    def watchedVideosByFriends(self, videos: List[List[str]], friends: List[List[int]], id: int, level: int) -> List[str]:
        n = len(videos)

        friends_at_level = []
        steps = -1
        q = deque([id])
        visited = set()
        visited.add(id)
        while q:
            steps += 1
            row = []
            z = len(q)
            for _ in range(z):
                cur = q.popleft()
                row.append(cur)
                for f in friends[cur]:
                    if f not in visited:
                        visited.add(f)
                        q.append(f)
            
            if steps == level:
                friends_at_level = row

        f = defaultdict(int)
        for i in friends_at_level:
            for video in videos[i]:
                f[video] += 1

        return sorted(f.keys(), key=lambda x: (f[x], x))