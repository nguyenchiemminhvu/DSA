from typing import List

class Solution:
    def countMentions(self, n: int, events: List[List[str]]) -> List[int]:
        events.sort(key=lambda x: (int(x[1]), 0 if x[0] == "OFFLINE" else 1))
        mentions = [0] * n
        next_online = [0] * n
        
        for e_type, ts, data in events:
            t = int(ts)
            if e_type == "OFFLINE":
                user = int(data)
                # user goes offline at t, returns at t + 60
                next_online[user] = t + 60
            else:  # MESSAGE
                if data == "ALL":
                    # ALL mentions ALL users regardless of online/offline
                    for i in range(n):
                        mentions[i] += 1
                elif data == "HERE":
                    # HERE mentions only currently online users
                    for i in range(n):
                        if t >= next_online[i]:
                            mentions[i] += 1
                else:
                    ids = [int(s[2:]) for s in data.split()]
                    for user in ids:
                        mentions[user] += 1

        return mentions
