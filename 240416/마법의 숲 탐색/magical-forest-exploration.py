import sys
input = sys.stdin.readline
from collections import deque

dr = [-1, 0, 1, 0]
dc = [0, 1, 0, -1]

def can_move_gol(cr, cc):
    for i in range(4):
        nr, nc = cr + dr[i], cc + dc[i]
        if nr < 0 or nr >= r+3 or nc < 0 or nc >= c:
            return False
        if grid[nr][nc] > 0:
            return False
    return True 

def move_gol(sc, sd, gol_num):
    sr = 1
    while True:
        if can_move_gol(sr, sc):
            if can_move_gol(sr + 1, sc):
                sr = sr + 1
            elif can_move_gol(sr, sc - 1) and can_move_gol(sr + 1, sc - 1):
                sr = sr + 1
                sc = sc - 1
                sd = (sd - 1) % 4
            elif can_move_gol(sr, sc + 1) and can_move_gol(sr + 1, sc + 1):
                sr = sr + 1
                sc = sc + 1
                sd = (sd + 1) % 4
            else:
                break
        else:
            break
    
    grid[sr][sc] = gol_num
    for i in range(4):
        nr, nc = sr + dr[i], sc + dc[i]
        if i == sd:
            grid[nr][nc] = gol_num + 10000
        else:
            grid[nr][nc] = gol_num

    return sr, sc 


def down_angel(cr, cc):
    que = deque()
    visited = [[False] * c for _ in range(r+3)]
    que.append((cr, cc))
    visited[cr][cc] = True
    answer = 0
    while len(que):
        cur_r, cur_c = que.popleft()
        cur_space = grid[cur_r][cur_c]

        for i in range(4):
            nr, nc = cur_r + dr[i], cur_c + dc[i]
            if nr < 3 or nr >= r+3 or nc < 0 or nc >= c:
                continue
            
            if visited[nr][nc]:
                continue
            
            if cur_space > 10000:
                if grid[nr][nc] > 0:
                    answer = max(answer, nr - 2)
                    que.append((nr, nc))
                    visited[nr][nc] = True
                
            else:
                if grid[nr][nc] == cur_space or grid[nr][nc] == 10000 + cur_space:
                    answer = max(answer, nr - 2)
                    que.append((nr, nc))
                    visited[nr][nc] = True
    return answer

if __name__ == "__main__":
    r, c, k = map(int, input().split())
    ans = 0
    grid = [[0] * c for _ in range(r + 3)]
    print_flag = 0
    for i in range(1, k+1):
        start_c, start_d = map(int, input().split())

        # 골렘 내려가기
        final_r, final_c = move_gol(start_c-1, start_d, i)

        # 골렘 범위 벗어나면 초기화
        flag = False
        for j in range(3):
            for p in range(c):
                if grid[j][p] > 0:
                    flag = True
                    break
            if flag:
                break
        
        if flag:
            for j in range(r+3):
                for p in range(c):
                    grid[j][p] = 0
            print_flag = i + 3
            continue

        # 정령 내려가기 + 점수
        a = down_angel(final_r, final_c)
        ans += a

    print(ans)