class Solution:
    def convertTime(self, current: str, correct: str) -> int:
        cur_min = int(current[0:2]) * 60 + int(current[3:])
        cor_min = int(correct[0:2]) * 60 + int(correct[3:])
        if cur_min == cor_min:
            return 0
        
        diff = (cor_min - cur_min) if cur_min < cor_min else (1440 - cur_min + cor_min)
        count_op = 0
        while diff > 0:
            if diff >= 60:
                diff -= 60
            elif diff >= 15:
                diff -= 15
            elif diff >= 5:
                diff -= 5
            else:
                diff -= 1
            count_op += 1
        return count_op