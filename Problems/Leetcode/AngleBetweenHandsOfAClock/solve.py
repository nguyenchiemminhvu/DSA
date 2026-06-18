class Solution:
    def angleClock(self, hour: int, minutes: int) -> float:
        h_angle_per_hour = 360.0 / 12.0
        h_angle_per_min = h_angle_per_hour / 60.0

        m_angle_per_min = 360.0 / 60

        m_angle = m_angle_per_min * minutes
        h_angle = h_angle_per_hour * hour + h_angle_per_min * minutes

        diff = abs(h_angle - m_angle)
        return min(
            diff,
            360 - diff
        )