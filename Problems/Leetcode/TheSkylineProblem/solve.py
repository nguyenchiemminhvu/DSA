from typing import List

class Contour:
    def __init__(self, pos:int, height:int):
        self.pos = pos
        self.height = height
    def __repr__(self):
        return f"[{self.pos}, {self.height}]"

class Solution:
    def getSkyline(self, buildings: List[List[int]]) -> List[List[int]]:
        def merge_contours(left_contours:List[Contour], right_contours:List[Contour]) -> List[Contour]:
            merged = []
            il = 0
            ir = 0
            left_height = 0
            right_height = 0
            while il < len(left_contours) and ir < len(right_contours):
                next_pos = 0
                if left_contours[il].pos < right_contours[ir].pos:
                    next_pos = left_contours[il].pos
                    left_height = left_contours[il].height
                    il += 1
                elif left_contours[il].pos > right_contours[ir].pos:
                    next_pos = right_contours[ir].pos
                    right_height = right_contours[ir].height
                    ir += 1
                else:
                    next_pos = left_contours[il].pos
                    left_height = left_contours[il].height
                    right_height = right_contours[ir].height
                    il += 1
                    ir += 1

                next_height = max(left_height, right_height)
                if not merged or next_height != merged[-1].height:
                    merged.append(Contour(next_pos, next_height))
            
            while il < len(left_contours):
                left_height = left_contours[il].height
                next_height = max(left_height, right_height)
                if not merged or next_height != merged[-1].height:
                    merged.append(Contour(left_contours[il].pos, next_height))
                il += 1
            
            while ir < len(right_contours):
                right_height = right_contours[ir].height
                next_height = max(left_height, right_height)
                if not merged or right_contours[ir].height != merged[-1].height:
                    merged.append(Contour(right_contours[ir].pos, next_height))
                ir += 1

            return merged

        def divide_and_conquer(buildings:List[List[int]], left:int, right:int) -> List[Contour]:
            if left == right:
                building = buildings[left]
                return [Contour(building[0], building[2]), Contour(building[1], 0)]
            
            mid = left + (right - left) // 2
            left_contours = divide_and_conquer(buildings, left, mid)
            right_contours = divide_and_conquer(buildings, mid + 1, right)
            return merge_contours(left_contours, right_contours)

        if not buildings:
            return []
        buildings.sort(key=lambda b: (b[0], b[1]))
        contours: List[Contour] = divide_and_conquer(buildings, 0, len(buildings) - 1)
        return [[contour.pos, contour.height] for contour in contours]