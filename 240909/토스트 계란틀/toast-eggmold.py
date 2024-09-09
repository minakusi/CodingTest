def dfs(init_lst):    
    y, x = init_lst
    union = []
    stack = [[y,x]]
    visited[y][x] = True
    sum_egg = 0
    
    while stack:
        cur_y, cur_x = stack.pop()
        sum_egg += field[cur_y][cur_x]
        union.append([cur_y, cur_x])
        
        for i in range(4):
            next_y, next_x = cur_y+dir[i][0], cur_x+dir[i][1]
            if 0 <= next_y < n and 0 <= next_x < n and not visited[next_y][next_x]: # 방문 가능한데
                if L <= abs(field[cur_y][cur_x]-field[next_y][next_x]) <= R: # 계란틀 여는 조건이면
                    visited[next_y][next_x] = True
                    stack.append([next_y, next_x])
    
    end_flag = True
    if len(union) > 1: # 계란틀이 열려있다면
        end_flag = False
    new_egg = sum_egg//len(union)
    for y, x in union: # 평균으로 업데이트
        tmp_field[y][x] = new_egg

    return end_flag


if __name__ == "__main__":
    n, L, R = map(int, input().split())
    field = [list(map(int, input().split())) for _ in range(n)]

    dir = [[0,1], [1,0], [0,-1], [-1,0]]

    for t in range(2000):
        end_flag = True
        visited = [[0]*n for _ in range(n)]
        tmp_field = [[0]*n for _ in range(n)] # 이번 회차에서 업데이트 된 결과
        for y in range(n):
            for x in range(n):
                if not visited[y][x]:
                    end_flag &= dfs([y,x])
        
        if end_flag: # 더 이상 열 수 있는 계란틀이 없는 경우
            print(t)
            break
        
        field = tmp_field # 계란틀 업데이트