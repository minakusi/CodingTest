n, m = map(int, input().split())
node = [[] for _ in range(n+1)]
visited = [False] * (n+1)

for i in range(m):
    a, b = map(int, input().split())
    node[a].append(b)
    node[b].append(a)


def search(n):
    global ans
    for nod in node[n]:
        if visited[nod] == False:
            ans += 1
            visited[nod] = True
            search(nod)

visited[1] = True
ans = 0
search(1)
print(ans)