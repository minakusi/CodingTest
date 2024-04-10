from collections import deque

dy = [0, 0, -1, -1, -1, 0, 1, 1, 1]
dx = [0, 1, 1, 0, -1, -1, -1, 0, 1]

n, m = map(int, input().split())
grid = [list(map(int, input().split())) for _ in range(n)]
d, p = map(int, input().split())

nut = deque()
for i in range(n-2, n):
    for j in range(0, 2):
        nut.append([i, j])

while m:
    nut_cnt = len(nut)
    # 이동
    for _ in range(nut_cnt):
        cur_y, cur_x = nut.popleft()
        cur_y = (cur_y + dy[d]*p) % n
        cur_x = (cur_x + dx[d]*p) % n
        nut.append([cur_y, cur_x])

    # 높이 증가
    for i in range(nut_cnt):
        cur_y, cur_x = nut[i]
        grid[cur_y][cur_x] += 3

    for i in range(nut_cnt):
        cur_y, cur_x = nut[i]
        for j in range(2, 9, 2):
            ny, nx = cur_y + dy[j], cur_x + dx[j]
            if ny < 0 or ny >= n or nx < 0 or nx >= n:
                continue
            if grid[ny][nx] > 0:
                grid[cur_y][cur_x] += 1

    # 영양제 재배열
    nut.clear()
    for i in range(n):
        for j in range(n):
            if grid[i][j] >= 2:
                grid[i][j] -= 2
                nut.append([i, j])
    m -= 1

ans = 0
for i in range(n):
    for j in range(n):
        ans += grid[i][j]

print(ans)