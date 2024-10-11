#include <iostream>
#include <queue>
using namespace std;

int N, M;
int grid[10][10];
int attack_point[10][10];
pair<int, int> parent[10][10];
bool visited[10][10];
bool in_attack[10][10];


int dxy[8][2] = {
    {0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
};

void print_grid(){
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j) cout << grid[i][j] << ' ';
        cout << '\n';
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int K;
    cin >> N >> M >> K;
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j) cin >> grid[i][j];
    }

    for (int k = 1; k <= K; ++k){
        // 가장 약한 포탑, 가장 강한 포탑 선정
        pair<int, int> attacker, target;
        int biggest = 0, smallest = 5001;
        for (int i = 0; i < N; ++i){
            for (int j = 0; j < M; ++j) {
                if (grid[i][j] <= 0) continue;

                if (grid[i][j] < smallest) {
                    attacker.first = i;
                    attacker.second = j;
                    smallest = grid[i][j];
                }
                else if (grid[i][j] == smallest){
                    if (attack_point[i][j] > attack_point[attacker.first][attacker.second]) {
                        attacker.first = i;
                        attacker.second = j;
                    }
                    else if (attack_point[i][j] == attack_point[attacker.first][attacker.second]) {
                        if (i + j > attacker.first + attacker.second) {
                            attacker.first = i;
                            attacker.second = j;
                        }
                        else if (i + j == attacker.first + attacker.second){
                            if (j > attacker.second){
                                attacker.first = i;
                                attacker.second = j;
                            }
                        }
                    }
                }


                if (grid[i][j] > biggest) {
                    target.first = i;
                    target.second = j;
                    biggest = grid[i][j];
                }
                else if (grid[i][j] == biggest){
                    if (attack_point[i][j] < attack_point[target.first][target.second]) {
                        target.first = i;
                        target.second = j;
                    }
                    else if (attack_point[i][j] == attack_point[target.first][target.second]) {
                        if (i + j < target.first + target.second) {
                            target.first = i;
                            target.second = j;
                        }
                        else if (i + j == target.first + target.second){
                            if (j < target.second){
                                target.first = i;
                                target.second = j;
                            }
                        }
                    }
                }
            }
        }

        // 공격력 증가
        for (int i = 0; i < N; ++i){
            for (int  j = 0 ; j < M; ++j) {
                visited[i][j] = false;
                parent[i][j] = make_pair(-1, -1);
                in_attack[i][j] = false;
            }
        }

        grid[attacker.first][attacker.second] += N + M;
        attack_point[attacker.first][attacker.second] = k;
        in_attack[attacker.first][attacker.second] = true;
        in_attack[target.first][target.second] = true;
        
        // 레이저 공격
        queue<pair<int, int>> que;
        que.emplace(attacker);
        visited[attacker.first][attacker.second] = true;
        bool flag = false;
        while(!que.empty()){
            pair<int, int> cur = que.front(); que.pop();
            // cout << cur.first << ' ' << cur.second << '\n';
            for (int i = 0; i < 4; ++i){
                int nx = (cur.first + dxy[i][0]) % N;
                int ny = (cur.second + dxy[i][1]) % M;
                if (visited[nx][ny] || grid[nx][ny] <= 0) continue;

                parent[nx][ny] = cur;
                if (nx == target.first && ny == target.second) {
                    flag = true;
                    break;
                }
                visited[nx][ny] = true;
                que.emplace(nx, ny);
            }
            if (flag) break;
        }

        if (parent[target.first][target.second].first != -1) {
            int attack = grid[attacker.first][attacker.second];
            grid[target.first][target.second] -= attack;
            attack /= 2;
            pair<int, int> cur = parent[target.first][target.second];
            while(cur != attacker){
                grid[cur.first][cur.second] -= attack;
                in_attack[cur.first][cur.second] = true;
                cur =  parent[cur.first][cur.second];
            }
        }
        else {
            // 포탄 공격
            int attack = grid[attacker.first][attacker.second];
            grid[target.first][target.second] -= attack;
            attack /= 2;
            for (int i = 0; i < 8; ++i){
                int nx = (target.first + dxy[i][0]) % N;
                int ny = (target.second + dxy[i][1]) % M;

                if (grid[nx][ny] <= 0) continue;
                if (nx == attacker.first && ny == attacker.second) continue;

                grid[nx][ny] -= attack;
                in_attack[nx][ny] = true;
            }
        }

        // 포탑 정비
        for (int i = 0; i < N; ++i){
            for (int j = 0; j < M; ++j){
                if (grid[i][j] > 0 && !in_attack[i][j]) ++grid[i][j];
            }
        }

        // cout << "attacker: " << attacker.first << ' ' << attacker.second << '\n';
        // cout << "target: " << target.first << ' ' << target.second << '\n';
        // print_grid();
        
    }

    int ans = 0;
    for (int i = 0; i < N; ++i){
            for (int j = 0; j < M; ++j){
                if (grid[i][j] > ans) ans = grid[i][j];
            }
    }
    cout << ans;
    return 0;
}