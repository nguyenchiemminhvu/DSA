class Solution:
    def isRobotBounded(self, commands: str) -> bool:
        x, y = 0, 0
        dir_x = [0, 1, 0, -1]
        dir_y = [1, 0, -1, 0]
        idir = 0
        for time in range(4):
            for command in commands:
                if command == 'L':
                    idir = ((idir - 1) + 4) % 4
                elif command == 'R':
                    idir = (idir + 1) % 4
                else:
                    x += dir_x[idir]
                    y += dir_y[idir]
        return True if x == 0 and y == 0 else False