from typing import List

class Solution:
    def earliestFinishTime(self, astart: List[int], aduration: List[int], bstart: List[int], bduration: List[int]) -> int:
        res = float('inf')

        for ia in range(len(astart)):
            a_s, a_d = astart[ia], aduration[ia]
            for ib in range(len(bstart)):
                b_s, b_d = bstart[ib], bduration[ib]

                intervals = [[a_s, a_d], [b_s, b_d]]
                intervals.sort(key=lambda x: x[0])

                first_s, first_d = intervals[0]
                second_s, second_d = intervals[1]

                first_end = first_s + first_d

                if first_end <= second_s:
                    finish_time = second_s + second_d
                else:
                    finish_time = first_end + second_d

                res = min(res, finish_time)

        return res