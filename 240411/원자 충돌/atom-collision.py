from collections import deque

dx = [-1, -1, 0, 1, 1, 1, 0, -1]
dy = [0, 1, 1, 1, 0, -1, -1, -1]

atoms = dict()

n, m, k = map(int, input().split())
for _ in range(m):
    x, y, mass, speed, direction = map(int, input().split())
    atoms[(x-1, y-1)] = [[mass, speed, direction]]

while k:
    ans = 0
    # 이동
    new_atoms = dict()
    for key, value in atoms.items():
        while value:
            mass, speed, direction = value.pop()
            nx = (key[0] + dx[direction]*speed) % n
            ny = (key[1] + dy[direction]*speed) % n

            if (nx, ny) in new_atoms:
                new_atoms[(nx, ny)].append([mass, speed, direction])
            else:
                new_atoms[(nx, ny)] = [[mass, speed, direction]]

    atoms = new_atoms

    # 합성
    for key, value in atoms.items():
        cnt = len(value)
        if cnt > 1:
            final_mass, final_speed, final_dir = 0, 0, 0
            while value:
                mass, speed, direction = value.pop()
                final_mass += mass
                final_speed += speed
                final_dir += direction % 2
            final_mass = final_mass // 5
            if final_mass == 0:
                continue
            ans += final_mass * 4
            final_speed = final_speed // cnt
            final_dir = 0 if final_dir % cnt == 0 else 1

            for i in range(final_dir, 8, 2):
                atoms[key].append([final_mass, final_speed, i])
        elif cnt == 1:
            ans += value[0][0]

    k -= 1

print(ans)