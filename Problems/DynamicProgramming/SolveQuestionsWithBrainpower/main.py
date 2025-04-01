# https://leetcode.com/problems/solving-questions-with-brainpower/

class Solution:
    def solve_dp(self, quests: List[List[int]], i: int, mem: List[int]):
        if (i >= len(quests)):
            return 0
        
        if (mem[i] != -1):
            return mem[i]

        points = 0
        points = max(self.solve_dp(quests, i + 1, mem), quests[i][0] + self.solve_dp(quests, i + quests[i][1] + 1, mem))

        mem[i] = points
        return points

    def mostPoints(self, questions: List[List[int]]) -> int:
        mem = [-1] * (len(questions) + 1)
        return self.solve_dp(questions, 0, mem)

if __name__ == "__main__":
    # Example usage
    solution = Solution()
    questions = [[3, 2], [4, 3], [4, 4], [2, 5]]
    print(solution.mostPoints(questions))  # Output: 5
    
    questions = [[1, 1], [2, 2], [3, 3], [4, 4]]
    print(solution.mostPoints(questions))  # Output: 7
    
    questions = [[10, 0], [9, 1], [8, 1], [7, 2]]
    print(solution.mostPoints(questions))  # Output: 27