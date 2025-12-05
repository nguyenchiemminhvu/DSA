class Solution:
    def countDaysTogether(self, a_arrived: str, a_leave: str, b_arrived: str, b_leave: str) -> int:
        def get_day_of_year(month, day):
            days_in_months = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
            return sum(days_in_months[:month - 1]) + day
        
        # Convert MM-DD to day-of-year
        a_start = get_day_of_year(int(a_arrived[0:2]), int(a_arrived[3:5]))
        a_end   = get_day_of_year(int(a_leave[0:2]),   int(a_leave[3:5]))
        b_start = get_day_of_year(int(b_arrived[0:2]), int(b_arrived[3:5]))
        b_end   = get_day_of_year(int(b_leave[0:2]),   int(b_leave[3:5]))
        
        overlap_start = max(a_start, b_start)
        overlap_end = min(a_end, b_end)
        
        return max(0, overlap_end - overlap_start + 1)
