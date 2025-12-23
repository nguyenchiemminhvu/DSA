class Solution:
    def punishmentNumber(self, n: int) -> int:
        arr = [1,9,10,36,45,55,82,91,99,100,235,297,369,370,379,414,657,675,703,756,792,909,918,945,964,990,991,999,1000]
        tmp = []
        for val in arr:
            if val <= n:
                tmp.append(val)
        
        return sum(val * val for val in tmp)