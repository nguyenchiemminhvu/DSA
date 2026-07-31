import sys

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return

    iterator = iter(input_data)
    N = int(next(iterator))
    A = [int(next(iterator)) for _ in range(N)]
    
    total_view_score = 0
    stack = [] # (index, height)
    
    for i in range(N):
        current_height = A[i]
        
        while stack and stack[-1][1] < current_height:
            stack.pop()
        
        if not stack:
            left_greater_index = -1
        else:
            left_greater_index = stack[-1][0]
        
        m = i - left_greater_index
        r_choices = N - i
        total_view_score += m * r_choices
        
        stack.append((i, current_height))
        
    print(total_view_score)

if __name__ == '__main__':
    solve()
