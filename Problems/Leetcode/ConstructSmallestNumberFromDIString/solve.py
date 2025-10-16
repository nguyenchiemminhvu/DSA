class Solution:
    def smallestNumber(self, pattern: str) -> str:
        candidates = []
        temp = []
        visited = set()
        def dfs(i:int) -> None:
            if i == len(pattern):
                candidates.append([val for val in temp])
                return
            
            for val in range(1, 10):
                if len(temp) == 0:
                    temp.append(val)
                    visited.add(val)
                    dfs(i + 1)
                    visited.remove(val)
                    temp.pop()
                else:
                    if pattern[i] == 'I' and val < temp[-1]:
                        continue
                    if pattern[i] == 'D' and val > temp[-1]:
                        continue
                    if val not in visited:
                        temp.append(val)
                        visited.add(val)
                        dfs(i + 1)
                        visited.remove(val)
                        temp.pop()

        dfs(-1)
        return "".join([chr(val + ord('0')) for val in min(candidates)])