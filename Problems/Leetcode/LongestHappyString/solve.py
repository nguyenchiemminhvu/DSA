import heapq

class Solution:
    def longestDiverseString(self, a: int, b: int, c: int) -> str:
        pq = []
        if a > 0:
            heapq.heappush(pq, (-a, 'a'))
        if b > 0:
            heapq.heappush(pq, (-b, 'b'))
        if c > 0:
            heapq.heappush(pq, (-c, 'c'))

        s = "##"
        while pq:
            first_count, first_letter = heapq.heappop(pq)
            first_count *= -1
            if s[-2] == s[-1] and s[-1] == first_letter:
                if pq:
                    second_count, second_letter = heapq.heappop(pq)
                    second_count *= -1
                    s += second_letter
                    second_count -= 1
                    if second_count > 0:
                        heapq.heappush(pq, (-second_count, second_letter))
                else:
                    # If adding current letter then meet the forbidden pattern
                    # but no more substitute letters available in the heap
                    return s[2:]

            s += first_letter
            first_count -= 1 
            if first_count > 0:
                heapq.heappush(pq, (-first_count, first_letter))

        return s[2:]