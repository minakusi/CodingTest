from collections import deque
di = [-1, 0, 1, 0]
dj = [0, 1, 0, -1]


def main():
    n, m = map(int, input().split())
    box = [list(input()) for _ in range(n)]
    blue, red = None, None
    for i in range(n):
        for j in range(m):
            if box[i][j] == 'B':
                blue = [i, j]
                box[i][j] = '.'
            elif box[i][j] == 'R':
                red = [i, j]
                box[i][j] = '.'

    cnt = 0
    que = deque()
    que.append([blue, red])
    cur_que = deque()
    while cnt < 10:
        while que:
            blue, red = que.popleft()
            for i in range(4):
                bx, by = blue[0], blue[1]
                while box[bx][by] == '.':
                    bx += di[i]
                    by += dj[i]
                if box[bx][by] == 'O':
                    continue
                bx -= di[i]
                by -= dj[i]

                rx, ry = red[0], red[1]
                while box[rx][ry] == '.':
                    rx += di[i]
                    ry += dj[i]
                if box[rx][ry] == 'O':
                    print(cnt + 1)
                    return
                rx -= di[i]
                ry -= dj[i]

                if bx == rx and by == ry:
                    if i == 0:
                        if blue[0] < red[0]:
                            rx += 1
                        else:
                            bx += 1
                    elif i == 1:
                        if blue[1] < red[1]:
                            by -= 1
                        else:
                            ry -= 1
                    elif i == 2:
                        if blue[0] < red[0]:
                            bx -= 1
                        else:
                            rx -= 1
                    else:
                        if blue[1] < red[1]:
                            ry += 1
                        else:
                            by += 1
                cur_que.append([[bx, by], [rx, ry]])
        que = cur_que
        cur_que = deque()
        cnt += 1

    print(-1)




main()